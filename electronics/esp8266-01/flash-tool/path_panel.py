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
import path_panel_method as func
import os,sys

[wxID_PANEL2, wxID_PANEL2BUTTON_BINPATH1, wxID_PANEL2BUTTON_BINPATH2, 
 wxID_PANEL2BUTTON_BINPATH3, wxID_PANEL2BUTTON_BINPATH4, 
 wxID_PANEL2BUTTON_BINPATH5, wxID_PANEL2BUTTON_BINPATH6, 
 wxID_PANEL2BUTTON_BINPATH7, wxID_PANEL2CHECKBOX_BINCHECK1, 
 wxID_PANEL2CHECKBOX_BINCHECK2, wxID_PANEL2CHECKBOX_BINCHECK3, 
 wxID_PANEL2CHECKBOX_BINCHECK4, wxID_PANEL2CHECKBOX_BINCHECK5, 
 wxID_PANEL2CHECKBOX_BINCHECK6, wxID_PANEL2CHECKBOX_BINCHECK7, 
 wxID_PANEL2STATICTEXT1, wxID_PANEL2STATICTEXT2, wxID_PANEL2STATICTEXT3, 
 wxID_PANEL2STATICTEXT4, wxID_PANEL2STATICTEXT5, wxID_PANEL2STATICTEXT6, 
 wxID_PANEL2STATICTEXT7, wxID_PANEL2TEXTCTRL_BINPATH1, 
 wxID_PANEL2TEXTCTRL_BINPATH2, wxID_PANEL2TEXTCTRL_BINPATH3, 
 wxID_PANEL2TEXTCTRL_BINPATH4, wxID_PANEL2TEXTCTRL_BINPATH5, 
 wxID_PANEL2TEXTCTRL_BINPATH6, wxID_PANEL2TEXTCTRL_BINPATH7, 
 wxID_PANEL2TEXTCTRL_OFFSET1, wxID_PANEL2TEXTCTRL_OFFSET2, 
 wxID_PANEL2TEXTCTRL_OFFSET3, wxID_PANEL2TEXTCTRL_OFFSET4, 
 wxID_PANEL2TEXTCTRL_OFFSET5, wxID_PANEL2TEXTCTRL_OFFSET6, 
 wxID_PANEL2TEXTCTRL_OFFSET7, wxID_PANEL1STATICBOX1
] = [wx.NewId() for _init_ctrls in range(37)]

class Panel2(wx.Panel):
    def _init_ctrls(self, prnt,pos):
        # generated method, don't edit
        wx.Panel.__init__(self, id=wxID_PANEL2, name='', parent=prnt,
              pos=pos, size=wx.Size(407+20, 190),
              style=wx.TAB_TRAVERSAL)
        self.SetClientSize(wx.Size(420+20, 190))
        self.Bind(wx.EVT_KILL_FOCUS, self.OnPanel2KillFocus)


        self.staticPathConf = wx.StaticBox(id=wxID_PANEL1STATICBOX1,
              label=u'Download Path Config', name='staticBox1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(430, 190), style=0) ###   
        #self.staticPathConf.SetToolTipString("tttttttttttttttttttttttt")



        self.textCtrl_BinPath1 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_BINPATH1,
              name=u'textCtrl_BinPath1', parent=self.staticPathConf, pos=wx.Point(32, 8+10),
              size=wx.Size(232, 21), style=0, value=u'set firmware path')
        self.textCtrl_BinPath1.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_BinPath1KillFocus)

        self.textCtrl_BinPath2 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_BINPATH2,
              name=u'textCtrl_BinPath2', parent=self.staticPathConf, pos=wx.Point(32, 32+10),
              size=wx.Size(232, 21), style=0, value=u'set firmware path')
        self.textCtrl_BinPath2.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_BinPath2KillFocus)

        self.textCtrl_BinPath3 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_BINPATH3,
              name=u'textCtrl_BinPath3', parent=self.staticPathConf, pos=wx.Point(32, 56+10),
              size=wx.Size(232, 21), style=0, value=u'set firmware path')
        self.textCtrl_BinPath3.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_BinPath3KillFocus)

        self.textCtrl_BinPath4 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_BINPATH4,
              name=u'textCtrl_BinPath4', parent=self.staticPathConf, pos=wx.Point(32, 80+10),
              size=wx.Size(232, 21), style=0, value=u'set firmware path')
        self.textCtrl_BinPath4.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_BinPath4KillFocus)

        self.button_BinPath1 = wx.Button(id=wxID_PANEL2BUTTON_BINPATH1,
              label=u'...', name=u'button_BinPath1', parent=self.staticPathConf,
              pos=wx.Point(264, 8+10), size=wx.Size(24, 23), style=0)
        self.button_BinPath1.Bind(wx.EVT_BUTTON, self.OnButton_BinPath1Button,
              id=wxID_PANEL2BUTTON_BINPATH1)

        self.button_BinPath2 = wx.Button(id=wxID_PANEL2BUTTON_BINPATH2,
              label=u'...', name=u'button_BinPath2', parent=self.staticPathConf,
              pos=wx.Point(264, 32+10), size=wx.Size(24, 23), style=0)
        self.button_BinPath2.Bind(wx.EVT_BUTTON, self.OnButton_BinPath2Button,
              id=wxID_PANEL2BUTTON_BINPATH2)

        self.button_BinPath3 = wx.Button(id=wxID_PANEL2BUTTON_BINPATH3,
              label=u'...', name=u'button_BinPath3', parent=self.staticPathConf,
              pos=wx.Point(264, 56+10), size=wx.Size(24, 23), style=0)
        self.button_BinPath3.Bind(wx.EVT_BUTTON, self.OnButton_BinPath3Button,
              id=wxID_PANEL2BUTTON_BINPATH3)

        self.button_BinPath4 = wx.Button(id=wxID_PANEL2BUTTON_BINPATH4,
              label=u'...', name=u'button_BinPath4', parent=self.staticPathConf,
              pos=wx.Point(264, 80+10), size=wx.Size(24, 23), style=0)
        self.button_BinPath4.Bind(wx.EVT_BUTTON, self.OnButton_BinPath4Button,
              id=wxID_PANEL2BUTTON_BINPATH4)

        self.textCtrl_Offset1 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_OFFSET1,
              name=u'textCtrl_Offset1', parent=self.staticPathConf, pos=wx.Point(346, 8+10),
              size=wx.Size(66, 21), style=0, value=u'0x7e000')
        self.textCtrl_Offset1.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_Offset1KillFocus)

        self.textCtrl_Offset2 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_OFFSET2,
              name=u'textCtrl_Offset2', parent=self.staticPathConf, pos=wx.Point(346, 32+10),
              size=wx.Size(66, 21), style=0, value=u'0x00000')
        self.textCtrl_Offset2.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_Offset2KillFocus)

        self.textCtrl_Offset4 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_OFFSET4,
              name=u'textCtrl_Offset4', parent=self.staticPathConf, pos=wx.Point(346, 80+10),
              size=wx.Size(66, 21), style=0, value=u'0x40000')
        self.textCtrl_Offset4.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_Offset4KillFocus)

        self.staticText3 = wx.StaticText(id=wxID_PANEL2STATICTEXT3,
              label=u'ADDR', name='staticText3', parent=self.staticPathConf,
              pos=wx.Point(296, 16+10), size=wx.Size(38, 13), style=0)

        self.staticText4 = wx.StaticText(id=wxID_PANEL2STATICTEXT4,
              label=u'ADDR', name='staticText4', parent=self.staticPathConf,
              pos=wx.Point(296, 40+10), size=wx.Size(38, 13), style=0)

        self.staticText5 = wx.StaticText(id=wxID_PANEL2STATICTEXT5,
              label=u'ADDR', name='staticText5', parent=self.staticPathConf,
              pos=wx.Point(296, 64+10), size=wx.Size(38, 13), style=0)

        self.staticText6 = wx.StaticText(id=wxID_PANEL2STATICTEXT6,
              label=u'ADDR', name='staticText6', parent=self.staticPathConf,
              pos=wx.Point(296, 88+10), size=wx.Size(38, 13), style=0)

        self.textCtrl_Offset3 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_OFFSET3,
              name=u'textCtrl_Offset3', parent=self.staticPathConf, pos=wx.Point(346, 56+10),
              size=wx.Size(66, 21), style=0, value=u'0x3e000')
        self.textCtrl_Offset3.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_Offset3KillFocus)

        self.textCtrl_BinPath7 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_BINPATH7,
              name=u'textCtrl_BinPath7', parent=self.staticPathConf, pos=wx.Point(32, 152+10),
              size=wx.Size(232, 21), style=0, value=u'')
        self.textCtrl_BinPath7.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_BinPath7KillFocus)

        self.button_BinPath7 = wx.Button(id=wxID_PANEL2BUTTON_BINPATH7,
              label=u'...', name=u'button_BinPath7', parent=self.staticPathConf,
              pos=wx.Point(264, 152+10), size=wx.Size(24, 23), style=0)
        self.button_BinPath7.Bind(wx.EVT_BUTTON, self.OnButton_BinPath7Button,
              id=wxID_PANEL2BUTTON_BINPATH7)

        self.checkBox_BinCheck1 = wx.CheckBox(id=wxID_PANEL2CHECKBOX_BINCHECK1,
              label=u'', name=u'checkBox_BinCheck1', parent=self.staticPathConf,
              pos=wx.Point(8, 8+10), size=wx.Size(16, 13), style=0)
        self.checkBox_BinCheck1.SetValue(False)
        self.checkBox_BinCheck1.Bind(wx.EVT_CHECKBOX,
              self.OnCheckBox_BinCheck1Checkbox,
              id=wxID_PANEL2CHECKBOX_BINCHECK1)

        self.checkBox_BinCheck2 = wx.CheckBox(id=wxID_PANEL2CHECKBOX_BINCHECK2,
              label=u'', name=u'checkBox_BinCheck2', parent=self.staticPathConf,
              pos=wx.Point(8, 32+10), size=wx.Size(16, 16), style=0)
        self.checkBox_BinCheck2.SetValue(True)
        self.checkBox_BinCheck2.Bind(wx.EVT_CHECKBOX,
              self.OnCheckBox_BinCheck2Checkbox,
              id=wxID_PANEL2CHECKBOX_BINCHECK2)

        self.checkBox_BinCheck3 = wx.CheckBox(id=wxID_PANEL2CHECKBOX_BINCHECK3,
              label=u'', name=u'checkBox_BinCheck3', parent=self.staticPathConf,
              pos=wx.Point(8, 56+10), size=wx.Size(16, 13), style=0)
        self.checkBox_BinCheck3.SetValue(True)
        self.checkBox_BinCheck3.Bind(wx.EVT_CHECKBOX,
              self.OnCheckBox_BinCheck3Checkbox,
              id=wxID_PANEL2CHECKBOX_BINCHECK3)

        self.checkBox_BinCheck4 = wx.CheckBox(id=wxID_PANEL2CHECKBOX_BINCHECK4,
              label=u'', name=u'checkBox_BinCheck4', parent=self.staticPathConf,
              pos=wx.Point(8, 80+10), size=wx.Size(16, 13), style=0)
        self.checkBox_BinCheck4.SetValue(True)
        self.checkBox_BinCheck4.Bind(wx.EVT_CHECKBOX,
              self.OnCheckBox_BinCheck4Checkbox,
              id=wxID_PANEL2CHECKBOX_BINCHECK4)
        
        self.checkBox_BinCheck5 = wx.CheckBox(id=wxID_PANEL2CHECKBOX_BINCHECK5,
              label=u'', name=u'checkBox_BinCheck5', parent=self.staticPathConf,
              pos=wx.Point(8, 104+10), size=wx.Size(16, 13), style=0)
        self.checkBox_BinCheck5.SetValue(False)
        self.checkBox_BinCheck5.Bind(wx.EVT_CHECKBOX,
              self.OnCheckBox_BinCheck5Checkbox,
              id=wxID_PANEL2CHECKBOX_BINCHECK5)  
        self.checkBox_BinCheck6 = wx.CheckBox(id=wxID_PANEL2CHECKBOX_BINCHECK6,
              label=u'', name=u'checkBox_BinCheck6', parent=self.staticPathConf,
              pos=wx.Point(8, 128+10), size=wx.Size(16, 13), style=0)
        self.checkBox_BinCheck6.SetValue(False)
        self.checkBox_BinCheck6.Bind(wx.EVT_CHECKBOX,
              self.OnCheckBox_BinCheck6Checkbox,
              id=wxID_PANEL2CHECKBOX_BINCHECK6)
        

        self.checkBox_BinCheck7 = wx.CheckBox(id=wxID_PANEL2CHECKBOX_BINCHECK7,
              label=u'', name=u'checkBox_BinCheck7', parent=self.staticPathConf,
              pos=wx.Point(8, 152+10), size=wx.Size(16, 13), style=0)
        self.checkBox_BinCheck7.SetValue(False)
        self.checkBox_BinCheck7.Bind(wx.EVT_CHECKBOX,
              self.OnCheckBox_BinCheck7Checkbox,
              id=wxID_PANEL2CHECKBOX_BINCHECK7)

        self.staticText7 = wx.StaticText(id=wxID_PANEL2STATICTEXT7,
              label=u'ADDR', name='staticText7', parent=self.staticPathConf,
              pos=wx.Point(296, 160+10), size=wx.Size(38, 16), style=0)

        self.textCtrl_Offset7 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_OFFSET7,
              name=u'textCtrl_Offset7', parent=self.staticPathConf, pos=wx.Point(346, 152+10),
              size=wx.Size(66, 21), style=0, value=u'')
        self.textCtrl_Offset7.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_Offset7KillFocus)

        self.textCtrl_BinPath5 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_BINPATH5,
              name=u'textCtrl_BinPath5', parent=self.staticPathConf, pos=wx.Point(32, 104+10),
              size=wx.Size(232, 21), style=0, value=u'')
        self.textCtrl_BinPath5.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_BinPath5KillFocus)

        self.button_BinPath5 = wx.Button(id=wxID_PANEL2BUTTON_BINPATH5,
              label=u'...', name=u'button_BinPath5', parent=self.staticPathConf,
              pos=wx.Point(264, 104+10), size=wx.Size(24, 23), style=0)
        self.button_BinPath5.Bind(wx.EVT_BUTTON, self.OnButton_BinPath5Button,
              id=wxID_PANEL2BUTTON_BINPATH5)

        self.staticText1 = wx.StaticText(id=wxID_PANEL2STATICTEXT1,
              label=u'ADDR', name='staticText1', parent=self.staticPathConf,
              pos=wx.Point(296, 112+10), size=wx.Size(38, 13), style=0)

        self.textCtrl_Offset5 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_OFFSET5,
              name=u'textCtrl_Offset5', parent=self.staticPathConf, pos=wx.Point(346, 104+10),
              size=wx.Size(66, 21), style=0, value=u'')
        self.textCtrl_Offset5.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_Offset5KillFocus)





        self.textCtrl_BinPath6 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_BINPATH6,
              name=u'textCtrl_BinPath6', parent=self.staticPathConf, pos=wx.Point(32, 128+10),
              size=wx.Size(232, 21), style=0, value=u'')
        self.textCtrl_BinPath6.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_BinPath6KillFocus)

        self.button_BinPath6 = wx.Button(id=wxID_PANEL2BUTTON_BINPATH6,
              label=u'...', name=u'button_BinPath6', parent=self.staticPathConf,
              pos=wx.Point(264, 128+10), size=wx.Size(24, 23), style=0)
        self.button_BinPath6.Bind(wx.EVT_BUTTON, self.OnButton_BinPath6Button,
              id=wxID_PANEL2BUTTON_BINPATH6)

        self.staticText2 = wx.StaticText(id=wxID_PANEL2STATICTEXT2,
              label=u'ADDR', name='staticText2', parent=self.staticPathConf,
              pos=wx.Point(296, 136+10), size=wx.Size(38, 16), style=0)

        self.textCtrl_Offset6 = wx.TextCtrl(id=wxID_PANEL2TEXTCTRL_OFFSET6,
              name=u'textCtrl_Offset6', parent=self.staticPathConf, pos=wx.Point(346, 128+10),
              size=wx.Size(66, 21), style=0, value=u'')
        self.textCtrl_Offset6.Bind(wx.EVT_KILL_FOCUS,
              self.OnTextCtrl_Offset6KillFocus)
        
        
        self.path_offset_flg=False
        self.check_order_list=[
                                self.checkBox_BinCheck1,
                                self.checkBox_BinCheck2,
                                self.checkBox_BinCheck3,
                                self.checkBox_BinCheck4,
                                self.checkBox_BinCheck5,
                                self.checkBox_BinCheck6,
                                self.checkBox_BinCheck7
                                 ]
        self.check_dict={self.checkBox_BinCheck1:[self.textCtrl_BinPath1,self.textCtrl_Offset1],
                        self.checkBox_BinCheck2:[self.textCtrl_BinPath2,self.textCtrl_Offset2],
                        self.checkBox_BinCheck3:[self.textCtrl_BinPath3,self.textCtrl_Offset3],
                        self.checkBox_BinCheck4:[self.textCtrl_BinPath4,self.textCtrl_Offset4],
                        self.checkBox_BinCheck5:[self.textCtrl_BinPath5,self.textCtrl_Offset5],
                        self.checkBox_BinCheck6:[self.textCtrl_BinPath6,self.textCtrl_Offset6],
                        self.checkBox_BinCheck7:[self.textCtrl_BinPath7,self.textCtrl_Offset7],
                              }
        
        for k,v in self.check_dict.items():
            tip_str = """=========================================
BOOT+USER.BIN:(OTA SUPPORTED)
512KB:
blank.bin -->  0x7E000 & 0x3E000
esp_init_data_default.bin --> 0x7C000
boot.bin --> 0x0
user1.bin --> 0x1000
user2.bin --> 0x41000(NOT NECESSARY)
master_device_key --> 0x3E000(IF USE ESP CLOUD SERVER)
------------------------------------------
1MB:
BOOT+USER.BIN:
blank.bin -->  0xFE000
esp_init_data_default.bin --> 0xFC000
boot.bin --> 0x0
user1.bin --> 0x1000
user2.bin --> 0x81000(NOT NECESSARY)
master_device_key --> 0x7E000(IF USE ESP CLOUD SERVER)
-------------------------------------------
=========================================
FLASH+IROM0TEXT.BIN
512KB
blank.bin -->  0x7E000
esp_init_data_default.bin --> 0x7C000
eagle.app.v6.flash.bin --> 0x0
eagle.app.v6.irom0text.bin --> 0x40000
master_device_key --> 0x3E000(IF USE ESP CLOUD SERVER)
1MB
blank.bin -->  0xFE000
esp_init_data_default.bin --> 0xFC000
eagle.app.v6.flash.bin --> 0x0
eagle.app.v6.irom0text.bin --> 0x40000
master_device_key --> 0x7E000(IF USE ESP CLOUD SERVER)                                     
"""
            v[0].SetToolTipString(tip_str)
            v[1].SetToolTipString(tip_str)
            
        self.default_path="."
        self.load_path_conf()


    def __init__(self, parent,pos):
        self.frame = parent
        self._init_ctrls(parent,pos)
        

    def OnPanel2KillFocus(self, event):
        event.Skip()
### text ctrl bin path ############################################
    def OnTextCtrl_BinPath1KillFocus(self, event):
        #print self.textCtrl_BinPath1.GetBackgroundColour()
        func.check_file_exist(self.textCtrl_BinPath1,self.checkBox_BinCheck1.GetValue())
        event.Skip()
    def OnTextCtrl_BinPath2KillFocus(self, event):
        func.check_file_exist(self.textCtrl_BinPath2,self.checkBox_BinCheck2.GetValue())
        event.Skip()
    def OnTextCtrl_BinPath3KillFocus(self, event):
        func.check_file_exist(self.textCtrl_BinPath3,self.checkBox_BinCheck3.GetValue())
        event.Skip()
    def OnTextCtrl_BinPath4KillFocus(self, event):
        func.check_file_exist(self.textCtrl_BinPath4,self.checkBox_BinCheck4.GetValue())
        event.Skip()
    def OnTextCtrl_BinPath5KillFocus(self, event):
        func.check_file_exist(self.textCtrl_BinPath5,self.checkBox_BinCheck5.GetValue())
        event.Skip()
    def OnTextCtrl_BinPath7KillFocus(self, event):
        func.check_file_exist(self.textCtrl_BinPath6,self.checkBox_BinCheck6.GetValue())
        event.Skip()
    def OnTextCtrl_BinPath6KillFocus(self, event):
        func.check_file_exist(self.textCtrl_BinPath7,self.checkBox_BinCheck7.GetValue())
        event.Skip()
        
########################################################


####button bin path######################################

    def OnButton_BinPath1Button(self, event):
        func.set_file_path(self,self.textCtrl_BinPath1)
        event.Skip()
    def OnButton_BinPath2Button(self, event):
        func.set_file_path(self,self.textCtrl_BinPath2)
        event.Skip()
    def OnButton_BinPath3Button(self, event):
        func.set_file_path(self,self.textCtrl_BinPath3)
        event.Skip()
    def OnButton_BinPath4Button(self, event):
        func.set_file_path(self,self.textCtrl_BinPath4)
        event.Skip()
    def OnButton_BinPath5Button(self, event):
        func.set_file_path(self,self.textCtrl_BinPath5)
        event.Skip()
    def OnButton_BinPath6Button(self, event):
        func.set_file_path(self,self.textCtrl_BinPath6)
        event.Skip()
    def OnButton_BinPath7Button(self, event):
        func.set_file_path(self,self.textCtrl_BinPath7)
        
        event.Skip()

#####text ctrl offset ########################################

    def OnTextCtrl_Offset1KillFocus(self, event):
        print "1 kill"
        func.check_offset(self.textCtrl_Offset1,self.checkBox_BinCheck1.GetValue())
        event.Skip()
    def OnTextCtrl_Offset2KillFocus(self, event):
        print "2 kill"
        func.check_offset(self.textCtrl_Offset2,self.checkBox_BinCheck2.GetValue())
        event.Skip()
    def OnTextCtrl_Offset3KillFocus(self, event):
        print "3 kill"
        func.check_offset(self.textCtrl_Offset3,self.checkBox_BinCheck3.GetValue())
        event.Skip()
    def OnTextCtrl_Offset4KillFocus(self, event):
        print "4 kill"
        func.check_offset(self.textCtrl_Offset4,self.checkBox_BinCheck4.GetValue())
        event.Skip()

    def OnTextCtrl_Offset5KillFocus(self, event):
        print "5 kill"
        func.check_offset(self.textCtrl_Offset5,self.checkBox_BinCheck5.GetValue())
        event.Skip()      
    def OnTextCtrl_Offset6KillFocus(self, event):
        print '6 kill'
        func.check_offset(self.textCtrl_Offset6,self.checkBox_BinCheck6.GetValue())
        event.Skip()
    def OnTextCtrl_Offset7KillFocus(self, event):
        print '7 kill'
        func.check_offset(self.textCtrl_Offset7,self.checkBox_BinCheck7.GetValue())
        event.Skip()
###############################################

    
####check box bin check ##############################################
    def OnCheckBox_BinCheck1Checkbox(self, event):
        func.check_file_and_offset(self.textCtrl_BinPath1,self.textCtrl_Offset1,self.checkBox_BinCheck1.GetValue() )
        event.Skip()
    def OnCheckBox_BinCheck2Checkbox(self, event):
        func.check_file_and_offset(self.textCtrl_BinPath2,self.textCtrl_Offset2,self.checkBox_BinCheck2.GetValue() )
        event.Skip()
    def OnCheckBox_BinCheck3Checkbox(self, event):
        func.check_file_and_offset(self.textCtrl_BinPath3,self.textCtrl_Offset3,self.checkBox_BinCheck3.GetValue() )
        event.Skip()
    def OnCheckBox_BinCheck4Checkbox(self, event):
        func.check_file_and_offset(self.textCtrl_BinPath4,self.textCtrl_Offset4,self.checkBox_BinCheck4.GetValue() )
        event.Skip()
    def OnCheckBox_BinCheck5Checkbox(self, event):
        func.check_file_and_offset(self.textCtrl_BinPath5,self.textCtrl_Offset5,self.checkBox_BinCheck5.GetValue() )
        event.Skip()
    def OnCheckBox_BinCheck6Checkbox(self, event):
        func.check_file_and_offset(self.textCtrl_BinPath6,self.textCtrl_Offset6,self.checkBox_BinCheck6.GetValue() )
        event.Skip()
    def OnCheckBox_BinCheck7Checkbox(self, event):
        func.check_file_and_offset(self.textCtrl_BinPath7,self.textCtrl_Offset7,self.checkBox_BinCheck7.GetValue() )
        event.Skip()
#####################################################################


    """check the file path and addr setting"""
    def check_all(self,id_bind_en=False,frame=None):
        res=func.check_all(self.check_dict,self.check_order_list,id_bind_en,frame)
        #print "test check all res:  ",res   
        return res
    
    def change_devkey(self):
        res = self.check_dict
        for check_box in self.check_order_list:
            
            if check_box.GetValue():#self.check_dict[check_box].getValue():
                path = self.check_dict[check_box][0].GetValue()
                offset = self.check_dict[check_box][1].GetValue()
                
                try:
                    offset = int(offset,16)
                    
                except:
                    offset = -1
                    
                print "test offset : ",offset , 
                if offset== 0x3e000:
                    path_new = path.strip(".bin")+"_done.bin"
                    os.rename(path,path_new)
                    #self.check_all(id_bind_en=False,frame=self.frame)
                    print "test path : ",path,os.path.split(path)
                    folder = os.path.split(path)[0]
                    dir_list = os.listdir(folder)
                    next_key = ""
                    for fpath in dir_list:
                        if not "_done" in fpath:
                            next_key = fpath
                            break
                    if not next_key == "":
                        self.check_dict[check_box][0].SetValue( os.path.join(folder,next_key) )
                    else:
                        print "not any devkey remained..."
                    
                    break
                        
                    
                    #print "save to : ",path_new,os.path.split(path_new)
                    
                
        #print "test res: ",res
    
    """save config params"""
    def save_path_conf(self):
        #try:
        fm_list = [self.frame.fm1,self.frame.fm2,self.frame.fm3,self.frame.fm4,
                   self.frame.fm5,self.frame.fm6,self.frame.fm7,self.frame.fm8]
        if True:
            f=open("tool_config.txt",'w')
            conf="path_data:\n"
            for cb in self.check_order_list:#self.check_dict.keys():
                if cb.GetValue():
                    conf+=( "choosed:"+self.check_dict[cb][0].GetValue()+";"+self.check_dict[cb][1].GetValue()+";\n" )
                else:
                    conf+=("empty:"+self.check_dict[cb][0].GetValue()+";"+self.check_dict[cb][1].GetValue()+";\n" )
            conf+="default_path:"+self.default_path+";\n"
            for i in range(len(fm_list)):
                conf+="COM%d:\n\r"%(i+1)
                conf+="com_port%d:"%(i+1)+str(fm_list[i].panel_download.get_com_port())+"\n"
                conf+="baudrate%d:"%(i+1)+str(fm_list[i].panel_download.get_baudrate())+"\n"                
                
            #conf+="COM1:\n\r"
            #conf+="com_port:"+str(self.frame.fm1.panel_download.get_com_port())+"\n"
            #conf+="baudrate:"+str(self.frame.fm1.panel_download.get_baudrate())+"\n"
            conf+="ID_BIND:\n\r"
            conf+="id_bind_en:"+str( int(self.frame.panel_spi.panel_idBindPanel.get_bind_enable()))+"\n"
            conf+="id_bind_addr:"+str( self.frame.panel_spi.panel_idBindPanel.get_bind_addr_str())+"\n"
            f.write(conf)
            f.close()
        #except:
            #print "exception in save_path_conf"
            #pass
        

    """load config params"""
    def load_path_conf(self):
        try:
            f=open("tool_config.txt",'r')
            lines=f.readlines()
        
            f.close()
        except:
            lines=[]
        clist=self.check_order_list
        idx=0
        for line in lines:
            if "choosed:" in line:
                str_path=line.split('choosed:')[1].split(';')[0]
                #print "test line : ",line
                str_offset=line.split('choosed:')[1].split(';')[1]
                clist[idx].SetValue(True)
                self.check_dict[ clist[idx] ][0].SetValue(str_path)
                self.check_dict[ clist[idx] ][1].SetValue(str_offset)
                idx+=1
            elif "empty" in line:
                str_path=line.split('empty:')[1].split(';')[0]
                str_offset=line.split('empty:')[1].split(';')[1]                
                clist[idx].SetValue(False)
                self.check_dict[ clist[idx] ][0].SetValue(str_path)
                self.check_dict[ clist[idx] ][1].SetValue(str_offset)
                idx+=1    
            elif "default_path:" in line:
                self.default_path=line.split("default_path:")[1].split(';')[0]
 





    

