# coding=gbk
# ESP8266 ROM Bootloader Utility
# www.espressif.com
# iot.espressif.cn
# Copyright (C) 2014 Espressif Shanghai
#
# This program is a firmware download tool with a simple graphic user interface.
# Thanks to Fredrik Ahlberg's outstanding work of esptool.py
# Port form XTCOM,which is compiled via visual studio, to python so that it can also be running in linux
# 
# If any bug is figured out ,please send the bug description and console log to wangjialin@espressif.com or wangcostaud@hotmail.com


import sys
reload(sys)
sys.setdefaultencoding('gbk')
code_type = sys.getfilesystemencoding()

import wx
import fdownload_panel_method as fpm
import Panel_MacAddr as pm

import combine_bin as cb
import os
import shutil

import threading
import time
import esptool as et


from flash_id_dict import *

[wxID_PANEL2, wxID_PANEL2BUTTON_START, wxID_PANEL2BUTTON_STOP, 
 wxID_PANEL2CHOICE_BAUDRATE, wxID_PANEL2CHOICE_COMPORT, wxID_PANEL2GAUGE, 
 wxID_PANEL2STATICTEXT_BAUDRATE, wxID_PANEL2STATICTEXT_COMPORT, 
 wxID_FRAME1SASHWINDOW1,wxID_PANEL1STATICBOX1
] = [wx.NewId() for _init_ctrls in range(10)]

ESP_DL_OK = 0x0
ESP_DL_IDLE = 0x1
ESP_DL_CONNECT_ERROR = 0x2
ESP_DL_SYNC = 0x3
ESP_DL_SYNC_ERROR = 0x4
ESP_DL_ERASE = 0x5
ESP_DL_ERASE_ERROR = 0x6
ESP_DL_DOWNLOADING = 0x7
ESP_DL_DOWNLOAD_ERROR = 0x8
ESP_DL_FAIL = 0x9
ESP_DL_FINISH = 0xA
ESP_DL_STOP = 0xB





state_dict = { ESP_DL_IDLE  : "./RESOURCE/IDLE_S.bmp" , 
               ESP_DL_CONNECT_ERROR  : "./RESOURCE/CON_ERROR_S.bmp" , 
               ESP_DL_SYNC   : "./RESOURCE/SYNC_S.bmp" , 
               ESP_DL_SYNC_ERROR   : "./RESOURCE/FAIL_S.bmp" , 
               ESP_DL_ERASE   : "./RESOURCE/DOWNLOAD_S.bmp" , 
               ESP_DL_ERASE_ERROR   : "./RESOURCE/ERROR_S.bmp" ,
               ESP_DL_DOWNLOADING : "./RESOURCE/DOWNLOAD_S.bmp" ,
               ESP_DL_DOWNLOAD_ERROR : "./RESOURCE/ERROR_S.bmp" ,
               ESP_DL_FAIL : "./RESOURCE/FAIL_S.bmp" ,
               ESP_DL_FINISH : "./RESOURCE/FINISH_S.bmp" ,
               ESP_DL_STOP : "./RESOURCE/STOP_S.bmp" ,    
               }



class Panel2(wx.Panel):
    def _init_ctrls(self, prnt,position,label):#,p_pos):
        # generated method, don't edit
        wx.Panel.__init__(self, id=wxID_PANEL2, name='', parent=prnt,
              pos=position,#wx.Point(20, 200), 
              size=wx.Size(449, 140),
              style=wx.TAB_TRAVERSAL)
        self.SetClientSize(wx.Size(449,140))
        
        
        self.staticDownloadPanel = wx.StaticBox(id=wxID_PANEL1STATICBOX1,
              label=label, name='staticBox1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(430, 140), style=0) ###         

        self.choice_ComPort = wx.Choice(choices=["COM1", "COM2", "COM3", "COM4",
              "COM5", "COM6", "COM7", "COM8", "COM9","COM10","COM11","COM12","COM13",
              "COM14","COM15","COM16","COM17","COM18","COM19","COM20","COM21"], 
                                        id=wxID_PANEL2CHOICE_COMPORT,
              name=u'choice_ComPort', parent=self.staticDownloadPanel, 
              pos=wx.Point(85, 85),size=wx.Size(80, 21), style=0)
        self.choice_ComPort.SetSelection(0)
        self.choice_ComPort.Bind(wx.EVT_CHOICE, self.OnChoice_ComPortChoice,
              id=wxID_PANEL2CHOICE_COMPORT)

        self.staticText_ComPort = wx.StaticText(id=wxID_PANEL2STATICTEXT_COMPORT,
              label=u'COM PORT:', name=u'staticText_ComPort', parent=self.staticDownloadPanel,
              pos=wx.Point(8, 85), size=wx.Size(75, 13), style=0)

        self.staticText_Baudrate = wx.StaticText(id=wxID_PANEL2STATICTEXT_BAUDRATE,
              label=u'BAUDRATE:', name=u'staticText_Baudrate', parent=self.staticDownloadPanel,
              pos=wx.Point(173 , 85), size=wx.Size(66, 18), style=0)

        self.choice_Baudrate = wx.Choice(choices=['9600','23040','46080','57600','115200', '230400', '345600',
              '460800', '576000'], id=wxID_PANEL2CHOICE_BAUDRATE,
              name=u'choice_Baudrate', parent=self.staticDownloadPanel, 
              pos=wx.Point(253, 85),size=wx.Size(80, 21), style=0)
        self.choice_Baudrate.SetSelection(0)
        self.choice_Baudrate.Bind(wx.EVT_CHOICE, self.OnChoice_BaudrateChoice,
              id=wxID_PANEL2CHOICE_BAUDRATE)

        self.button_Start = wx.Button(id=wxID_PANEL2BUTTON_START,
              label=u'START', name=u'button_Start', parent=self.staticDownloadPanel,
              pos=wx.Point(85, 16), size=wx.Size(74, 30), style=0)
        self.button_Start.Bind(wx.EVT_BUTTON, self.OnButton_StartButton,
              id=wxID_PANEL2BUTTON_START)

        self.button_Stop = wx.Button(id=wxID_PANEL2BUTTON_STOP, label=u'STOP',
              name=u'button_Stop', parent=self.staticDownloadPanel, pos=wx.Point(85, 49),
              size=wx.Size(74, 26), style=0)
        self.button_Stop.Bind(wx.EVT_BUTTON, self.OnButton_StopButton,
              id=wxID_PANEL2BUTTON_STOP)

        #download state window
        self.sashWindow1 = wx.SashWindow(id=wxID_FRAME1SASHWINDOW1,
              name='sashWindow1', parent=self.staticDownloadPanel, pos=wx.Point(8, 16),
              size=wx.Size(74, 64), style=wx.CLIP_CHILDREN | wx.SW_3D)
        self.sashWindow1.SetBackgroundColour(wx.Colour(255, 255, 255))
        sb1 = wx.StaticBitmap(self.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/IDLE_S.bmp", wx.BITMAP_TYPE_ANY)))  

        self.gauge = wx.Gauge(id=-1, name="test", parent=self.staticDownloadPanel, pos=wx.Point(8,110), 
                              range=100, size=wx.Size(380, 25), style=wx.GA_HORIZONTAL)
        
        self.baudrate=int(self.choice_Baudrate.GetStringSelection())
        self.comport=self.choice_ComPort.Selection + 1
        
        self.timer = wx.Timer(self)
        self.timer2 = wx.Timer(self)
        
        self.cp=self.frame.panel_spi#    combine_panel
        #self.mp=self.frame.panel_mac#          mac_panel
        self.panel_mac=pm.Panel1(self,wx.Point(170,3),self.num )
        self.mp=self.panel_mac
        self.path_panel=self.frame.panel_path         #path_panel
        
        
        #self.dls=fpm.FlashDownloadState(self,self.path_panel,case,self.cp,self.mp)
        
        

        self.check_res = []
        self.dl_list = []


    def __init__(self, parent,position,label,num,efuse_mode):#, pos):#id, pos, size, style, name):
        self.frame = parent
        self.num = num
        print 'test label:',label
        print 'self.num:',self.num
        self._init_ctrls(parent,position,label)#,pos)
        self.running =  False
        self.ESP_FDL = et.ESPROM(parent,6,115200,efuse_mode)
        self.ESP_FDL_STATE = -1
        #self.frame = parent
        
        self.Bind(wx.EVT_TIMER, self.update_pic,self.timer)
        self.Bind(wx.EVT_TIMER, self.set_gauge,self.timer2)
        self.load_path_conf()

    def OnChoice_ComPortChoice(self, event):
        self.set_com_port()
        #fpm.set_com_port(self)
        print "test cp intop : ",self.comport
        event.Skip()
        
    def set_com_port(self):
        comport=self.choice_ComPort.Selection + 1
        self.comport=comport
        return comport
    
    def set_baudrate(self):
        baudrate=int(self.choice_Baudrate.GetStringSelection())
        print "test baudrate: ",baudrate
        print "test baudrate selection:  ",self.choice_Baudrate.GetSelection()
        self.baudrate=baudrate
        return baudrate    
    
    def get_com_port(self):
        return self.choice_ComPort.Selection 
    
    def get_baudrate(self):
        return int(self.choice_Baudrate.GetSelection())

    def OnChoice_BaudrateChoice(self, event):
        #fpm.set_baudrate(self)
        self.set_baudrate()
        print "test baudrate intop: ",self.baudrate
        event.Skip()

    def OnButton_StartButton(self, event):
        #self.set_baudrate()
        #self.set_com_port()
        
        
        self.check_res = self.path_panel.check_all(self.frame.parent.panel_spi.panel_idBindPanel.get_bind_enable(),frame=self.frame) #wjl
        print self.check_res
        if self.check_res[0]:
            #self.dl_list = self.check_res[1]
            if not self.running:
                self.dl_list=[]
                path_tmp = os.path.join( os.path.abspath('./'),'bin_tmp')
                if os.path.isdir(os.path.join(path_tmp,'downloadPanel%d'%self.num)):
                    try:
                        shutil.rmtree( os.path.join( os.path.abspath('./'),'bin_tmp') )
                        #shutil.rmtree( "./bin_tmp",True)
                    except:
                        print "del temp img error"
                for i in range(len(self.check_res[1])):
                    filename,offset = self.check_res[1][i]
                    self.dl_list.append(  self.flash_config(filename,offset)  )                

                self.running = True
                self.tth = TestThread(self,self.comport,self.baudrate,self.dl_list)
                self.tth.start()
    
                #self.Bind(wx.EVT_TIMER, self.update_pic,self.timer)#wjl test
                self.timer.Start(100)#wjl test   
                self.timer2.Start(100)#wjl test  
        else:
            print 'path and address set error'
            self.OnButton_StopButton(event)
        event.Skip()

    def OnButton_StopButton(self, event):
        if self.ESP_FDL.stopFlg:
            self.reset(event)
        else:
            self.ESP_FDL.stop_download()
        
        event.Skip()
        
    #reset some status
    def reset(self,event):
        self.timer.Stop()
        self.timer2.Stop()
        self.ESP_FDL.state=self.ESP_FDL.ESP_DL_IDLE
        self.update_pic(event)
        self.ESP_FDL.process_num=0
        self.gauge.SetValue(0)     
        self.mp.reset()
        
        
    #update current state of downloading via timer event
    def update_pic(self,event):   
        if not self.ESP_FDL_STATE==self.ESP_FDL.state:
        
            pic_path=state_dict[self.ESP_FDL.state]
            sb1=wx.StaticBitmap(self.sashWindow1, 1, wx.BitmapFromImage(wx.Image(pic_path, wx.BITMAP_TYPE_ANY)))  
            sb1.Refresh()      
            #if self.ESP_FDL.state in [ESP_DL_CONNECT_ERROR,ESP_DL_SYNC_ERROR ,ESP_DL_ERASE_ERROR ,ESP_DL_DOWNLOAD_ERROR ,ESP_DL_FAIL ,ESP_DL_FINISH ,ESP_DL_STOP ]:
                #self.timer.Stop()
            self.ESP_FDL_STATE = self.ESP_FDL.state
            if self.ESP_FDL.state ==  ESP_DL_DOWNLOADING:
                self.mp.func.gen_bar(self.ESP_FDL.ESP_MAC_AP)
                self.mac_ap = self.ESP_FDL.ESP_MAC_AP
                self.mac_sta = self.ESP_FDL.ESP_MAC_STA
                self.flash_manufacturer_id  = self.ESP_FDL.flash_manufacturer_id
                self.flash_device_id  = self.ESP_FDL.flash_device_id
                self.crystal_freq  = self.ESP_FDL.crystal_freq
                self.mp.MAC=self.mac_sta
		try:
		    if self.ESP_FDL.BIT_FLG==0:
			self.mp.textCtrl_MacAddr3.SetValue("AP  MAC:  "+self.mac_ap+'\n'+"STA MAC:  "+self.mac_sta+"\n")
		    elif self.ESP_FDL.BIT_FLG==1:
			self.mp.textCtrl_MacAddr3.SetValue("AP  MAC:  "+self.mac_ap+'\n'+"STA MAC:  "+self.mac_sta+"\n")
		except:
		    print "exception in download_panel_info:update_pic"
		    self.mp.textCtrl_MacAddr3.SetValue("AP  MAC:  "+self.mac_ap+'\n'+"STA MAC:  "+self.mac_sta)
		    
                self.Parent.panel_spi.textCtrlDetectedInfo.SetValue("")
                if not self.flash_manufacturer_id == -1 and not self.flash_device_id==-1:
                    vendor = "N/A"
                    mode = "N/A"
                    size = "N/A"
                    try:
                        vendor = SPI_FLASH_VENDOR_DICT[self.flash_manufacturer_id & 0xff]
                        #self.Parent.panel_spi.textCtrlDetectedInfo.AppendText("flash vendor:\r\n%02Xh : %s\r\n"%(self.flash_manufacturer_id,vendor))
                    except:
                        vendor = "N/A"
                        #self.Parent.panel_spi.textCtrlDetectedInfo.AppendText("flash vendor:\r\n%02Xh \r\n"%self.flash_manufacturer_id)
                        pass
                    try:
                        mode = SPI_FLASH_MODE_DICT[(self.flash_device_id>>8)&0xf0]
                    except:
                        mode = "N/A"
                    try:
                        size = SPI_FLASH_SIZE_DICT[self.flash_device_id & 0xff]
                    except:
                        size = "N/A"
                    
                    if not mode == "N/A" and self.Parent.panel_spi.spi_auto_set == 1:
                        self.Parent.panel_spi.radioBoxMode.SetSelection(SPI_FLASH_MODE_IDX[mode])
                        self.Parent.panel_spi.mode = int(self.Parent.panel_spi.radioBoxMode.GetSelection())
                        print "mode:",self.Parent.panel_spi.mode 
                    if not size == "N/A" and self.Parent.panel_spi.spi_auto_set == 1:
                        self.Parent.panel_spi.radioBoxStorage.SetSelection(SPI_FLASH_SIZE_IDX[size])    
                        self.Parent.panel_spi.size = int(self.Parent.panel_spi.radioBoxStorage.GetSelection())
                        print "size : ",self.Parent.panel_spi.size
                        
                    
                        
                    self.Parent.panel_spi.textCtrlDetectedInfo.AppendText("flash vendor:\r\n%02Xh : %s\r\n"%(self.flash_manufacturer_id,vendor))
                    self.Parent.panel_spi.textCtrlDetectedInfo.AppendText("flash devID:\r\n%04Xh\r\n%s;%s\r\n"%(self.flash_device_id,mode,size))
                if not self.crystal_freq == -1:
    
		    if self.crystal_freq < 45000000 and self.crystal_freq>35000000:
			self.crystal_freq = 40000000
		    elif self.crystal_freq < 29000000 and self.crystal_freq>25000000:
			self.crystal_freq = 26000000
		    elif self.crystal_freq < 25000000 and self.crystal_freq>22000000:
			self.crystal_freq = 24000000
					    
		    self.frame.parent.panel_spi.textCtrlDetectedInfo.AppendText("crystal:\r\n%d Mhz"%(self.crystal_freq/1000000))                    
                    if self.Parent.panel_spi.spi_auto_set == 1:
                        print "sel.freq:",self.crystal_freq
                        if self.crystal_freq < 44000000 and self.crystal_freq>35000000:
                            self.Parent.panel_spi.choice_Crystal.SetSelection(0)                            
                        elif self.crystal_freq < 29000000 and self.crystal_freq>25000000:
                            self.Parent.panel_spi.choice_Crystal.SetSelection(1)                            
                        elif self.crystal_freq < 25000000 and self.crystal_freq>22000000:
                            self.Parent.panel_spi.choice_Crystal.SetSelection(2)                            
                        else:
                            print "warning : unknown crystal freq"
                        self.Parent.panel_spi.crystal = self.Parent.panel_spi.choice_Crystal.GetSelection()
                        print "tttttest crystal :",self.Parent.panel_spi.crystal
                else:
                    self.Parent.panel_spi.textCtrlDetectedInfo.AppendText("crystal:\r\n%s Mhz"%"N/A")
                    
                    

                            

    #update download procedure via timer2 event
    def set_gauge(self,event):
        if self.ESP_FDL.state == ESP_DL_DOWNLOADING:
            self.gauge.SetRange(self.ESP_FDL.total_len)
            self.gauge.SetValue(self.ESP_FDL.process_num)
        elif self.ESP_FDL.state == ESP_DL_FINISH:
            self.gauge.SetRange(self.ESP_FDL.total_len)
            self.gauge.SetValue(self.ESP_FDL.total_len)
            #self.timer.Stop()
            #self.timer2.Stop()            
            
    def load_path_conf(self):
        try:
            f=open("tool_config.txt",'r')
            lines=f.readlines()
            f.close()
        except:
            lines=[]
        for line in lines:
            #if "id_bind_en" in line :
                #self.checkBox1.SetValue( int(line.split(":")[1]) )
            #elif "id_bind_addr" in line:
                #self.textCtrl1.SetValue( line.split(":")[1])
            if "com_port%d"%self.num in line:
                self.choice_ComPort.SetSelection( int(line.split(":")[1]))
                self.set_com_port()
            elif "baudrate%d"%self.num in line:
                self.choice_Baudrate.SetSelection( int( line.split(":")[1])) 
                #self.choice_Baudrate.Select(
                self.set_baudrate()
                
                
            
    #setup spi config
    def flash_config(self,filename,offset):
        rep_path = os.path.join( os.path.abspath('./'),'bin_tmp')
        rep_path = os.path.join( rep_path,'downloadPanel%d'%self.num)
        #/downloadPanel%d'%self.num
        if not os.path.isdir(rep_path):
            print "rep_path :",rep_path
            os.makedirs(rep_path)
        fr=file(filename,'rb')
        data=fr.read()
        dlen=len(data)
        fr.close()
        del(fr)        
            
        if offset==0x0 or 'esp_init_data' in filename or (data[0] == '\xe9' and data[1] == '\x03') :
            #fr=file(filename,'rb')
            #data=fr.read()
            #dlen=len(data)
            #fr.close()
            #del(fr)
            #print "tttttttttttttttttttttttt"
            #print "t data 0 : ",data[0] == '\xe9'
            #print "t data 11 : ",data[1] == '\x03'
	    if self.cp.disable_change_bin == 0:
		if offset==0x0:
		    size_speed = (cb.size_list_d[self.cp.flashSize]<<4)|cb.speed_list_d[self.cp.speed]
		    print "size_speed : %x"%size_speed
		    data=( data[0:2]+cb.mode_list[self.cp.mode]+'%c'%(size_speed)+data[4:] )
		elif 'esp_init_data' in filename:
		    data = ( data[0:48]+cb.crystal_list[self.cp.crystal]+data[49:] )
		#elif (data[0] == '\xe9' and data[1] == '\x03'):
		    #size_speed = (cb.size_list_d[self.cp.flashSize]<<4)|cb.speed_list_d[self.cp.speed]
		    #print "user.bin size_speed : %x"%size_speed
		    #data=( data[0:2]+cb.mode_list[self.cp.mode]+'%c'%(size_speed)+data[4:] )
	    else:
		print "========================"
		print "NOTE: BINARY CONFIG DISABLED, "
		print "JUST DOWNLOAD THE ORIGINAL BINARIES"
		print "========================"  		


            file_rep=filename+"_rep"
            
            fpath,fname = os.path.split(filename)
            #--------------------------------------
            fpath = os.path.join(fpath,'_temp_by_dltool/downloadPanel%d'%self.num)
            fname=os.path.join(fpath,(fname+'_rep'))
            print "test fpath:",fpath
            print "test fname:",fname
            if not os.path.isdir( fpath ):
                os.makedirs( fpath)
            fw=open(fname,'wb')
            print "mode :",cb.mode_list[self.cp.mode],'  speed:',cb.speed_list[self.cp.speed]
            print "write bin : ",fname
            fw.write(data)
            fw.close()
        else:
            fname = filename
            

        dest_rep = os.path.join( rep_path , os.path.split(fname)[1] )####
        shutil.copy( fname , dest_rep )####     
        return [dest_rep,offset]
        
        

        
class TestThread(threading.Thread):
    def __init__(self, dl_panel,com_port,baudrate,dl_list):
        threading.Thread.__init__(self)
        self.timeToQuit = threading.Event()
        self.running = False
        self.com = com_port
        self.baudrate = baudrate
        self.dl_panel = dl_panel
        self.dl_thread = self.dl_panel.ESP_FDL
        self.dl_list = dl_list
        

    def stop(self):
        self.timeToQuit.set()

    def run(self):
        print "test running :",self.running
        self.dl_thread.flash_download_thread(self.com,self.baudrate,self.dl_list)
        self.dl_panel.running = False
        self.dl_thread.stopFlg = True
        

            
           
