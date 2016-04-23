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


import wx
import combine_bin as cb
import id_bind_panel as ibp
import os

[wxID_PANEL1, wxID_PANEL1BUTTON, wxID_PANEL1BUTTON1, wxID_PANEL1RADIOBOX1, 
 wxID_PANEL1RADIOBOX2, wxID_PANEL1STATICBOX1, wxID_PANEL1RADIOBOX3,
 wxID_PANEL2CHOICE_CRYSTAL,wxID_PANEL2STATICTEXT_CRYSTAL,wxID_PANEL1STATICBOX2,
 wxID_PANEL1TEXTCTRLDETECTEDINFO,wxID_WXFRAME1STATICBOX_SPIAUTO,
wxID_WXFRAME1CHECKBOX_SPIAUTOSET,wxID_PANEL1BUTTON_DISP,wxID_WXFRAME1CHECKBOX_SPIRAW
 
] = [wx.NewId() for _init_ctrls in range(15)]

class Panel_Combine(wx.Panel):
    def _init_ctrls(self, prnt,position):
        # generated method, don't edit
        wx.Panel.__init__(self, id=wxID_PANEL1, name='', parent=prnt,
              pos=position, size=wx.Size(420+20, 250),
              style=wx.TAB_TRAVERSAL)
        self.SetClientSize(wx.Size(420+20, 250))
        
        self.staticBoxSpiConf = wx.StaticBox(id=wxID_PANEL1STATICBOX1,
                      label=u'SPI FLASH CONFIG', name='staticBox1', parent=self,
                      pos=wx.Point(6, -27), size=wx.Size(420, 241), style=0) ###
        
        #*****************************************************************************
        self.choice_Crystal = wx.Choice(choices=["40M", "26M", "24M"],
                                        id=wxID_PANEL2CHOICE_CRYSTAL,
              name=u'choice_Crystal', parent=self.staticBoxSpiConf, pos=wx.Point(16,42 ),
              size=wx.Size(60, 30), style=0)
        self.choice_Crystal.SetSelection(1)
        self.choice_Crystal.Bind(wx.EVT_CHOICE, self.OnChoice_choice_Crystal,
              id=wxID_PANEL2CHOICE_CRYSTAL)
        self.choice_Crystal.SetToolTipString("Select the crystal frequency of your module, \
                                             \rIt is related to the system clock so make sure to set this item correctly \
                                             \rAlso the crystal freq effect the uart baud during booting.\
                                             \rFor a 40M crystal , the booting uart tx baud is 115200,(74880 for 26m accordingly\
                                             \rCrystal Freq will be set to the BYTE[48] of init_data.bin,see the RF InitConfig page")
        
        
        self.staticCrystal = wx.StaticText(id=wxID_PANEL2STATICTEXT_CRYSTAL,
              label=u'CrystalFreq :', name=u'staticCrystal', parent=self.staticBoxSpiConf,
              pos=wx.Point(16, 17), size=wx.Size(66, 17), style=0)   

        #============================================================================
        
        self.buttonCombine = wx.Button(id=wxID_PANEL1BUTTON1, label=u'CombineBin',
              name='buttonCombine', parent=self.staticBoxSpiConf, pos=wx.Point(85, 22),####
              size=wx.Size(85, 26), style=0)
        self.buttonCombine.Bind(wx.EVT_BUTTON, self.OnButtonConbine,
              id=wxID_PANEL1BUTTON1)
        self.buttonCombine.SetToolTipString("This button will combine the several binaries you have chosen to a single one\
                                             \rThis combined bin is configured according to the spi settings your choose(clk speed,spi mode,flash size)\
                                             \rThe empty field will be filled with 0xff\
                                             \rYou can use this bin for factory production.\
                                             ")

        self.buttonDefault = wx.Button(id=wxID_PANEL1BUTTON, label=u'Default',
              name=u'button', parent=self.staticBoxSpiConf, pos=wx.Point(85, 50),
              size=wx.Size(85, 26), style=0)
        self.buttonDefault.Bind(wx.EVT_BUTTON, self.OnButtonDefault,
              id=wxID_PANEL1BUTTON)   
        self.buttonDefault.SetToolTipString("Reset the spi and crtstal settings to default")
        
        #self.buttonDisp = wx.Button(id=wxID_PANEL1BUTTON_DISP, label=u'Detect',
               #name=u'button_detect', parent=self.staticBoxSpiConf, pos=wx.Point(170, 50),
               #size=wx.Size(85, 26), style=0)
         #self.buttonDisp.Bind(wx.EVT_BUTTON, self.OnButtonDetect,id=wxID_PANEL1BUTTON_DISP)
        
        self.panel_idBindPanel = ibp.Panel1(self,wx.Point(265,63)) #WHETHER IT IS NEEDED AT ALL
        #****************************************************************************

        self.radioBoxSpeed = wx.RadioBox(choices=['40MHz', '26.7MHz', '20MHz',
              '80MHz'], id=wxID_PANEL1RADIOBOX1, label=u'SPI SPEED',
              majorDimension=1, name='radioBoxSpeed', parent=self.staticBoxSpiConf, pos=wx.Point(5,38+45)
              , size=wx.Size(85, 140), style=wx.RA_SPECIFY_COLS)
        self.radioBoxSpeed.Bind(wx.EVT_RADIOBOX, self.OnRadioBoxSpiSpeed,
              id=wxID_PANEL1RADIOBOX1)
        self.radioBoxSpeed.SetToolTipString("Select the SPI clock freq for external flash:\
                                             \rDefault value is 40MHz\
                                             \rIf choose 80M ,make sure your flash support it with the mode you choose \
                                             \rand check the waveform of clk line, adjust the matching resister\
                                             \rSPI speed is SET to the lower 4 bit of the 4TH BYTE at flash address 0x0\
                                             \rflash clk freq: \
                                             \r BYTE[3]&0f :   \
                                             \r0:40MHz\
                                             \r1:26.67MHz\
                                             \r2:20MHz\
                                             \r0xf:80Mhz")

        self.radioBoxMode = wx.RadioBox(choices=['QIO', 'QOUT', 'DIO',
              'DOUT'], id=wxID_PANEL1RADIOBOX2, label=u'SPI MODE',
              majorDimension=1, name='radioBox2', parent=self.staticBoxSpiConf, pos=wx.Point(95,38+45)
              , size=wx.Size(72, 130), style=wx.RA_SPECIFY_COLS)
        self.radioBoxMode.Bind(wx.EVT_RADIOBOX, self.OnRadioBoxSpiMode,
              id=wxID_PANEL1RADIOBOX2)
        self.radioBoxMode.SetToolTipString("Select the SPI flash read mode :\
                                            \rQIO: Quad read and write mode\
                                            \rQOUT: Quad read mode \
                                            \rDIO: Dual read and write mode \
                                            \rDOUT: Dual read mode \
                                            \rCheck your flash datasheet and decided the correct mode that flash support\
                                            \rWifi performance might be better with higher flash r/w speed.    \
                                            \rFlash mode is set to the 3rd BYTE at flash address 0x0\
                                            \rBYTE[2]&0xff:\
                                            \r0:QIO\
                                            \r1:QOUT\
                                            \r2:DIO\
                                            \r3:DOUT")
        
        self.radioBoxStorage = wx.RadioBox(choices=['4Mbit', '2Mbit', '8Mbit',
              '16Mbit','32Mbit' ,     '16Mbit-C1','32Mbit-C1'], id=wxID_PANEL1RADIOBOX3, label=u'FLASH SIZE',
              majorDimension=1, name='radioBox3', parent=self.staticBoxSpiConf, pos=wx.Point(173,25)
              , size=wx.Size(80, 207), style=wx.RA_SPECIFY_COLS)
        self.radioBoxStorage.Bind(wx.EVT_RADIOBOX, self.OnRadioBoxFlashSize,
              id=wxID_PANEL1RADIOBOX3)
        #self.radioBoxStorage.Bind(wx.EVT_ENTER_WINDOW, self.OnEnterWindow_FLASHSIZE) 
        #self.radioBoxStorage.Bind(wx.EVT_LEAVE_WINDOW, self.OnLeaveWindow_FLASHSIZE) 
        #self.radioBoxStorage.Bind(wx.EVT_HELP, self.OnEnterWindow_FLASHSIZE) 
        #self.radioBoxStorage.Bind(wx.EVT_LEFT_DOWN, self.OnLeaveWindow_FLASHSIZE) 
        #self.radioBoxStorage.Bind(wx.EVT_MOTION, self.OnEnterWindow_FLASHSIZE) 
        #self.radioBoxStorage.Bind(wx.EVT_R, self.OnLeaveWindow_FLASHSIZE) 
        
        
        
        self.radioBoxStorage.SetToolTipString("Select the flash size:\
                                               \rThe flash size is related to your compile settings\
                                               \rDifferent flash map works with differnt flash cache address\
                                               \rSo please choose the size accord with your compiling settings\
                                               \rFlash size is SET to the higher 4bit of 4TH BYTE at flash address 0x0\
                                               \rADD NEW OPTIONS WITH DIFFERENT ICACHE MAPPING\
                                               \r(BYTE[3]>>4)&0xf:\
                                               \r0:512KB(256KB+256KB)\
                                               \r1:256KB\
                                               \r2:1MB(512KB+512KB)\
                                               \r3:2MB(512KB+512KB)\
                                               \r4:4MB(512KB+512KB)\
                                               \r5:2MB-C1(1024KB+1024KB)\
                                               \r6:4MB-C1(1024KB+1024KB)\
                                               ")
        
        self.staticModuleInfo = wx.StaticBox(id=wxID_PANEL1STATICBOX2,
                      label=u'DETECTED INFO', name='staticBox1', parent=self.staticBoxSpiConf,
                      pos=wx.Point(260, 93), size=wx.Size(150, 145), style=0) ###  
        
        self.textCtrlDetectedInfo = wx.TextCtrl(id=wxID_PANEL1TEXTCTRLDETECTEDINFO,
                      name=u'textCtrl_MAC', parent=self.staticModuleInfo, pos=wx.Point(5,15),
                      size=wx.Size(140, 125),style=wx.TE_MULTILINE, value=u'')   
        self.textCtrlDetectedInfo.SetToolTipString("Show the flash and crystal info detected during chip sync")
        
        #===========================================================
        
        
        self.staticBox_SpiAuto = wx.StaticBox(id=wxID_WXFRAME1STATICBOX_SPIAUTO, label=u'',
              name='staticBox3', parent=self.staticBoxSpiConf, pos=wx.Point(260, 10),
              size=wx.Size(120, 46), style=0)

        self.checkBox_SpiAutoSet = wx.CheckBox(id=wxID_WXFRAME1CHECKBOX_SPIAUTOSET,
              label=u'SpiAutoSet', name='checkBox2', parent=self.staticBox_SpiAuto,
              pos=wx.Point(8, 10), size=wx.Size(80, 17), style=0)
        self.checkBox_SpiAutoSet.SetValue(False)
        self.checkBox_SpiAutoSet.Bind(wx.EVT_CHECKBOX, self.OnCheckBoxCheckbox_SPIAUTOSET,
              id=wxID_WXFRAME1CHECKBOX_SPIAUTOSET)     
        self.checkBox_SpiAutoSet.SetToolTipString("Select to enable the flash&crystal auto detect and set.\
                                                   \rNot all the flash id is in our id list,please contact us if it mismatched.")
        
        self.checkBox_SpiRaw = wx.CheckBox(id=wxID_WXFRAME1CHECKBOX_SPIRAW,
                                               label=u'DoNotChgBin', name='checkBoxSpiRaw', parent=self.staticBox_SpiAuto,
                                               pos=wx.Point(8, 27), size=wx.Size(100, 17), style=0)        
        self.checkBox_SpiRaw.SetValue(False)
        self.checkBox_SpiRaw.Bind(wx.EVT_CHECKBOX, self.OnCheckBoxCheckbox_SPIRAW,
                                          id=wxID_WXFRAME1CHECKBOX_SPIRAW)           
        self.checkBox_SpiRaw.SetToolTipString("If selected, download tool will not change anything to the binaries.\
                                                       \rSimply download the original binaries to the flash.")        
        
        #===========================================================
        
        

        self.speed=self.radioBoxSpeed.GetSelection()
        self.mode=self.radioBoxMode.GetSelection()
        self.flashSize = self.radioBoxStorage.GetSelection()
        self.crystal = self.choice_Crystal.GetSelection()
        
        self.pp=self.frame.panel_path#    path_panel
        self.spi_auto_set = self.checkBox_SpiAutoSet.GetValue()
        self.disable_change_bin = self.checkBox_SpiRaw.GetValue()
        
        
    def OnEnterWindow_FLASHSIZE(self,event):
        print "test on me "
        
    def OnLeaveWindow_FLASHSIZE(self,event):
        print "test leave me "
    

    def __init__(self, parent, pos):
        self.frame = parent
        self._init_ctrls(parent,pos)
        self.Onload()
        

    def OnButtonConbine(self, event):
        res,dl_list = self.pp.check_all()
        if res == True:
            #try:
            cb.combineBin(dl_list,"combine/target.bin",self.mode,self.speed,self.flashSize,self.crystal,self.disable_change_bin)
            os.startfile('combine')
            #except:
                #print "open file error"
            
        else:
            pass
        event.Skip()

    def OnButtonDefault(self, event):
        self.radioBoxMode.SetSelection(0)
        self.mode=0
        self.radioBoxSpeed.SetSelection(0)
        self.speed=0
        self.radioBoxStorage.SetSelection(0)
        self.flashSize=0
        
        self.choice_Crystal.SetSelection(1)
        self.crystal = 1
        self.checkBox_SpiRaw.SetValue(False)
        self.disable_change_bin = 0
        self.checkBox_SpiAutoSet.SetValue(False)
        self.spi_auto_set=0
        event.Skip()

    def OnRadioBoxSpiSpeed(self, event):
        self.speed = int( self.radioBoxSpeed.GetSelection())
        print "speed : ",self.radioBoxSpeed.GetSelection()
        event.Skip()

    def OnRadioBoxSpiMode(self, event):
        self.mode = int( self.radioBoxMode.GetSelection())
        print "mode : ",self.radioBoxMode.GetSelection()
        event.Skip()

    def OnRadioBoxFlashSize(self,event):
        self.flashSize = int( self.radioBoxStorage.GetSelection())
        print 'flash size :',self.radioBoxStorage.GetSelection()
        #print 'type : ',type(self.radioBoxStorage.GetSelection())
        event.Skip()
        
    def OnChoice_choice_Crystal(self,event):
        self.crystal = self.choice_Crystal.GetSelection()
        print 'crystal :',self.choice_Crystal.GetSelection()
        event.Skip()
        
    def OnButton2Button(self, event):
        event.Skip()
    
    def OnCheckBoxCheckbox_SPIRAW(self,event):
        self.disable_change_bin = self.checkBox_SpiRaw.GetValue()
        print "disable set binary : %d"%self.disable_change_bin
        event.Skip()            


    def OnCheckBoxCheckbox_SPIAUTOSET(self, event):
        
        self.spi_auto_set = self.checkBox_SpiAutoSet.GetValue()
        print "spi auto set : %d"%self.spi_auto_set
        event.Skip()        
    
    def OnButtonDetect(self,event):
        print "test button detect ..."
        
    def OnSave(self):
        print "save in Panel_Combine..."
        
        spi_conf = ""
        spi_conf+="CRYSTAL:%d\n"%self.crystal
        spi_conf+="SPIAUTOSET:%d\n"%self.spi_auto_set
        spi_conf+="SPICFGDIS:%d\n"%self.disable_change_bin
        spi_conf+="SPISPEED:%d\n"%self.speed
        spi_conf+="SPIMODE:%d\n"%self.mode
        spi_conf+="FLASHSIZE:%d\n"%self.flashSize
        f=open("tool_config.txt",'a')
        f.write(spi_conf)
        f.close()
        
    def Onload(self):
        print "load config ..."
        try:
            f=open("tool_config.txt",'r')
            lines = f.readlines()
        except:
            lines = []
            
        for line in lines:
            if "CRYSTAL" in line:
                try:
                    vtmp = int( line.strip("\n").split(":")[1] )
                    self.choice_Crystal.SetSelection(vtmp)
                    self.crystal = vtmp
                except:
                    print "load setting error"
                    pass
            elif "SPIAUTOSET" in line:
                try:
                    vtmp = int( line.strip("\n").split(":")[1] )
                    self.spi_auto_set = vtmp
                    self.checkBox_SpiAutoSet.SetValue(vtmp)
                except:
                    print "load setting error"
                    pass
            elif "SPICFGDIS" in line:
                try:
                    vtmp = int( line.strip("\n").split(":")[1] )
                    self.disable_change_bin = vtmp
                    self.checkBox_SpiRaw.SetValue(vtmp)
                except:
                    print "load setting error"
                    pass
            elif "SPISPEED" in line:
                try:
                    vtmp = int( line.strip("\n").split(":")[1] )
                    self.speed = vtmp
                    self.radioBoxSpeed.SetSelection(vtmp)
                except:
                    print "load setting error"
                    pass
            elif "SPIMODE" in line:
                try:
                    vtmp = int( line.strip("\n").split(":")[1] )
                    self.mode = vtmp
                    self.radioBoxMode.SetSelection(vtmp)
                except:
                    print "load setting error"
                    pass
            elif "FLASHSIZE" in line:
                try:
                    vtmp = int( line.strip("\n").split(":")[1] )
                    self.flashSize = vtmp
                    self.radioBoxStorage.SetSelection(vtmp)
                except:
                    print "load setting error"
                    pass
                

        
        