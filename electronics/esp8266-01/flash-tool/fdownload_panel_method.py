# coding=gbk
# ESP8266 ROM Bootloader Utility
# www.espressif.com
# bbs.espressif.com
# iot.espressif.cn
# Copyright (C) 2014 Espressif Shanghai
#
# This program is a firmware download tool with a simple graphic user interface.
# Thanks to Fredrik Ahlberg's outstanding work of esptool.py
# Port form XTCOM,which is compiled via visual studio, to python so that it can also be running in linux
# 
# If any bug is figured out ,please send the bug description and console log to wangjialin@espressif.com or wangcostaud@hotmail.com



"""not used any more, for the older version of xtcom"""






#class FlashDownloadState():
    
    #def __init__(self,download_panel,path_panel,case,combine_panel,mac_panel):
        ##print "test prnt ;",prnt
        #self.dlp=download_panel
        #self.path_panel=path_panel        
        #self.dl_list=[]
        #self.tot_len=[]
        #self.tot_len_num=0
        #self.gauge_base=[]
        #self.check_res=[]
        #self.running=False
        
        #self.comport=self.set_com_port()
        #self.baudrate=self.set_baudrate()
        #self.re_sync_num=0

        ##global fdl
        #self.dl_list=[]
        #self.gauge_base=[]      
        ##if case==2:
            ##self.xp=xp2
            ###print "flggggggggggg  xp2"
        ##elif case==3:
            ##self.xp=xp3
            ###print "flggggggggggg xp3"
        
        #self.cp=combine_panel
        #self.mp=mac_panel
        #self.mac_m = pmm.MacAddrMethod(self.mp)
        ##global fdl
        ##global dl_list
        ##global tot_len        
    
    #def set_com_port(self):
        #comport=self.dlp.choice_ComPort.Selection + 1
        #self.dlp.comport=comport
        #self.comport=comport
        #return comport
    
    #def set_baudrate(self):
        #baudrate=int(self.dlp.choice_Baudrate.GetStringSelection())
        #self.baudrate=baudrate
        #self.dlp.baudrate=baudrate
        #return baudrate
    
    #def start_fdl(self):
        ##global dl_list
        ##global tot_len
        ##global tot_len_num
        ##global gauge_base
        ##global check_res
        ##tot_len=[]
        #rep_path = os.path.join( os.path.abspath('./'),'bin_tmp')
        #if not os.path.isdir(rep_path):
            #os.mkdir(rep_path)
            
        #if self.running:
            #pass
        #else:
            #self.mac_m.set_mac_sashwindow("./RESOURCE/blank.bmp")
            #self.mac_m.clr_mac()
            
            #self.xp.stopsync(0)
            #self.check_res=self.path_panel.check_all()
            #if self.check_res[0]:
                ##try:
                    ##path_panel.save_path_conf()
                ##except:
                    ##print "save conf file error"
                ##do flash download
                ###dl_list=check_res[1]
                
                #self.connect_and_sync()#wjl test
                #pass
                
            #pass
        
    
    
    #def connect_and_sync(self):
        ##xp.download('eagle.app.flash.bin')

          
        ##fdl=_fdl
        #print "connect"
        #print "comport :" ,self.comport ,"  baudrate: ",self.baudrate
        #res=self.xp.connect(self.comport,self.baudrate)
        
        #if res:
            #print "open error\n"
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/CON_ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()
            #self.running=False
            #return
        #else:
            #self.dlp.gauge.SetValue(0)
            #self.xp.stopFlashDownload(0)
            #self.tot_len=[]  
            #self.dl_list=self.check_res[1]
            #print "test dl list :",self.dl_list
            #for fn in [infoList[0] for infoList in self.dl_list ]:
                #self.tot_len.append( self.xp.GetPacketNum(fn) )
            #self.tot_len_num=sum(self.tot_len)
            #self.gauge_base=0
            #print "test tot len: ",self.tot_len      
            
            #print "port open\n"
            #print "start sync\n"
            #self.running=True
            #self.xp.sync()
            
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/SYNC_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()
            
            #self.dlp.Bind(wx.EVT_TIMER, self.check_sync)#wjl test
            #self.dlp.timer.Start(100)#wjl test
    
    
    #def check_sync(self,event):

        
        
        #sync_res=self.xp.get_connect_ok()
        #if sync_res==0:
            ##print "waiting for sync\n"
            #pass
        #elif sync_res==2:
            #print "sync stopped \n"
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/STOP_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()      
            
            #self.dlp.timer.Stop()
            #self.re_sync_num=0
            #self.running=False
            #self.xp.disconnect()
            
        #elif sync_res==-1:
            #print "sync error\n"
            ##sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
            ##sb1.Refresh()            
            #if self.re_sync_num==2:
                #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
                #sb1.Refresh()                   
                #self.running=False
                #self.dlp.timer.Stop()
                #self.xp.disconnect() 
                #self.re_sync_num=0
                
            #else:
                #self.xp.sync()
                #self.re_sync_num+=1
                #print "re sync num: ",self.re_sync_num
                
            

            
            
        #elif sync_res==1:
            #print "sync ok\n"
            #rep_path = os.path.join( os.path.abspath('./'),'bin_tmp')
            
            
            ##///////////////////////////////
            #self.dlp.timer.Stop()
            #self.re_sync_num=0
            #self.mac_m.get_mac()#////////////////////////
            #dl_info=self.dl_list.pop(0)
            ###print "dl_info : ",dl_info
            #print dl_info
            #if dl_info[1]==0x0 or 'esp_init_data' in dl_info[0]:
                #fr=file(dl_info[0],'rb')
                #data=fr.read()
                #dlen=len(data)
                #fr.close()
                #del(fr)
                #if cb.VERSION == 'V0.8' and dl_info[1]==0x0:
                    #data=( data[0:2]+ cb.mode_list[self.cp.mode] + cb.speed_list[self.cp.speed] +data[4:] )
                #elif cb.VERSION == 'V0.9+' and dl_info[1]==0x0:
                    #size_speed = (cb.size_list_d[self.cp.flashSize]<<4)|cb.speed_list_d[self.cp.speed]
                    #print "size_speed : %x"%size_speed
                    #data=( data[0:2]+cb.mode_list[self.cp.mode]+'%c'%(size_speed)+data[4:] )
                #elif 'esp_init_data' in dl_info[0]:
                    #data = ( data[0:48]+cb.crystal_list[self.cp.crystal]+data[49:] )
                #file_rep=dl_info[0]+"_rep"
                #filePath,fileName = os.path.split(dl_info[0])
                #filePath = os.path.join(filePath,'_temp_by_dltool')
                #fileName=os.path.join(filePath,(fileName+'_rep'))
                #if not os.path.isdir( filePath ):
                    #os.makedirs( filePath)
                #fw=open(fileName,'wb')
                #print "mode :",cb.mode_list[self.cp.mode],'  speed:',cb.speed_list[self.cp.speed]
                #print "write bin : ",fileName
                #fw.write(data)
                #fw.close()
                #dest_rep = os.path.join( rep_path , os.path.split(fileName)[1] )####
                #shutil.copy( fileName , dest_rep )####
                #print "write bin : ",dest_rep
                ##self.xp.flashdownload(fileName,dl_info[1])#wjl test  
                #time.sleep(0.5)
                #self.xp.flashdownload(dest_rep,dl_info[1])#wjl test
            #else:
                #dest_rep = os.path.join( rep_path , os.path.split(dl_info[0])[1] )####
                #shutil.copy( dl_info[0] , dest_rep )####
                #print "write bin : ",dest_rep
                #time.sleep(0.5)
                #self.xp.flashdownload(dest_rep,dl_info[1])#wjl test
                ##self.xp.flashdownload(dl_info[0],dl_info[1])#wjl test
                #pass
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/DOWNLOAD_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()    
            
            #self.dlp.Bind(wx.EVT_TIMER, self.check_flashdl)#wjl test
            #self.dlp.timer.Start(100)#wjl test
    
    
    #def check_flashdl(self,event):
        #rep_path = os.path.join( os.path.abspath('./'),'bin_tmp')
 
            
        #block_num = self.xp.get_block()
        #block_num_total = self.xp.get_block_total()
        #flash_dl_res=self.xp.get_flash_download_res()
        #if flash_dl_res == 1:#block_num==block_num_total: //add flash download error here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            #self.dlp.timer.Stop()
            #print "download finished"
            #if self.dl_list==[]:
                #self.xp.flashdownloadFinish()
                #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/FINISH_S.bmp", wx.BITMAP_TYPE_ANY)))  
                #sb1.Refresh()                   
                #self.running=False
                #self.xp.disconnect()
            #else:
                #dl_info=self.dl_list.pop(0)
                #print dl_info
                #self.gauge_base+=self.tot_len.pop(0)
                #if dl_info[1]==0x0 or 'esp_init_data' in dl_info[0]:
                    #fr=file(dl_info[0],'rb')
                    #data=fr.read()
                    #dlen=len(data)
                    #fr.close()
                    #del(fr)
                    #if cb.VERSION == 'V0.8' and dl_info[1]==0x0:
                        #data=( data[0:2]+ cb.mode_list[self.cp.mode] + cb.speed_list[self.cp.speed] +data[4:] )
                    #elif cb.VERSION == 'V0.9+' and dl_info[1]==0x0:
                        #size_speed = (cb.size_list_d[self.cp.flashSize]<<4)|cb.speed_list_d[self.cp.speed]
                        #print "size_speed : %x"%size_speed
                        #data=( data[0:2]+cb.mode_list[self.cp.mode]+'%c'%(size_speed)+data[4:] )
                    #elif 'esp_init_data' in dl_info[0]:
                        #data = ( data[0:48]+cb.crystal_list[self.cp.crystal]+data[49:] )
                    #file_rep=dl_info[0]+"_rep"
                    #filePath,fileName = os.path.split(dl_info[0])
                    #filePath = os.path.join(filePath,'_temp_by_dltool')
                    #fileName=os.path.join(filePath,(fileName+'_rep'))
                    #if not os.path.isdir( filePath ):
                        #os.makedirs( filePath)
                    #fw=open(fileName,'wb')
                    #print "mode :",cb.mode_list[self.cp.mode],'  speed:',cb.speed_list[self.cp.speed]
                    #print "write bin : ",fileName
                    #fw.write(data)
                    #fw.close()
                    #dest_rep = os.path.join( rep_path , os.path.split(fileName)[1] )####
                    #shutil.copy( fileName , dest_rep )####      
                    #print "write bin : ",dest_rep
                    #time.sleep(0.5)
                    #self.xp.flashdownload(dest_rep,dl_info[1])
                    ##self.xp.flashdownload(fileName,dl_info[1])
                #else:
                    #dest_rep = os.path.join( rep_path , os.path.split(dl_info[0])[1] )####
                    #shutil.copy( dl_info[0] , dest_rep )####   
                    #print "write bin : ",dest_rep
                    #time.sleep(0.5)
                    #self.xp.flashdownload(dest_rep,dl_info[1])
                    ##self.xp.flashdownload(dl_info[0],dl_info[1])
                #self.dlp.Bind(wx.EVT_TIMER, self.check_flashdl)
                ##self.timer=wx.Timer(self)
                #self.dlp.timer.Start(100)            
        #elif flash_dl_res==2:
            #print "open file error\n"
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()             
            #self.dlp.timer.Stop()
            #self.running=False
            #self.xp.disconnect()    
        #elif flash_dl_res==3:
            #print "fail to alloc buffer\n"
            #self.dlp.timer.Stop()
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()               
            #self.running=False
            #self.xp.disconnect()    
        #elif flash_dl_res==4:
            #print "address offset not aligned to 4KB\n"
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()               
            #self.dlp.timer.Stop()
            #self.running=False
            #self.xp.disconnect()   
        #elif flash_dl_res==5:
            #print "address over reach \n"
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()               
            #self.dlp.timer.Stop()
            #self.running=False
            #self.xp.disconnect()  
        #elif flash_dl_res==6:
            #print "flash download start error \n"
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()               
            #self.dlp.timer.Stop()
            #self.running=False
            #self.xp.disconnect()   
        #elif flash_dl_res==7:
            #print "flash download error \n"
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/ERROR_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()               
            #self.dlp.timer.Stop()
            #self.running=False
            #self.xp.disconnect()  
        #elif flash_dl_res==8:
            #print "flash download stop!! \n"
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/STOP_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()               
            #self.dlp.timer.Stop()
            #self.running=False
            #self.xp.disconnect()          
            
            
        #else:
            #self.dlp.gauge.SetRange(self.tot_len_num)
            #self.dlp.gauge.SetValue(block_num+self.gauge_base+1)
            
            ##print 'test tot len num : ',self.tot_len_num
            ##print 'test block num:',block_num
            ##print 'test gauge_base :',self.gauge_base
            
            #pass
        
            

    #def stop_sync_dl(self):
        #if self.running==False:
            #sb1=wx.StaticBitmap(self.dlp.sashWindow1, 1, wx.BitmapFromImage(wx.Image("./RESOURCE/IDLE_S.bmp", wx.BITMAP_TYPE_ANY)))  
            #sb1.Refresh()
            #self.mac_m.set_mac_sashwindow("./RESOURCE/blank.bmp")
            ##self.mac_m.set_mac_sashwindow("./RESOURCE/blank.bmp")
            #self.mac_m.clr_mac()            
        #else:                
            #self.xp.stopsync(1)
            #self.xp.stopFlashDownload(1)
            #self.running=False
        