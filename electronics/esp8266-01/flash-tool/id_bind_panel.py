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

[wxID_PANEL1, wxID_PANEL1CHECKBOX1, wxID_PANEL1STATICBOX1, 
 wxID_PANEL1STATICTEXT1, wxID_PANEL1TEXTCTRL1, 
] = [wx.NewId() for _init_ctrls in range(5)]

class Panel1(wx.Panel):
    def _init_ctrls(self, prnt,pos):
        # generated method, don't edit
        wx.Panel.__init__(self, id=wxID_PANEL1, name='', parent=prnt,
              pos=pos,#wx.Point(309, 323), 
              size=wx.Size(172, 68),
              style=wx.TAB_TRAVERSAL)
        self.SetClientSize(wx.Size(172, 68))

        self.staticBox1 = wx.StaticBox(id=wxID_PANEL1STATICBOX1,
              label=u'', name='staticBox1', parent=self, pos=wx.Point(0,
              0), size=wx.Size(145, 40), style=0)

        self.checkBox1 = wx.CheckBox(id=wxID_PANEL1CHECKBOX1,
              label=u'IDbind', name='checkBox1', parent=self,
              pos=wx.Point(4, 16), size=wx.Size(100, 13), style=0)
        self.checkBox1.SetValue(False)
        self.checkBox1.Enable(False)
        self.checkBox1.Bind(wx.EVT_CHECKBOX,
              self.IdBindCheckbox,
              id=wxID_PANEL1CHECKBOX1)        

        self.textCtrl1 = wx.TextCtrl(id=wxID_PANEL1TEXTCTRL1, name='textCtrl1',
              parent=self, pos=wx.Point(64, 13), size=wx.Size(75, 21), style=0,
              value='0x')
        self.textCtrl1.Enable()
        self.textCtrl1.SetEditable(True)
        self.textCtrl1.Bind(wx.EVT_KILL_FOCUS,
              self.AddrKillFocus)        

        #self.staticText1 = wx.StaticText(id=wxID_PANEL1STATICTEXT1,
              #label=u'ADDR', name='staticText1', parent=self, pos=wx.Point(8,
              #32), size=wx.Size(38, 13), style=0)

    def __init__(self, parent, pos):#, size, style, name):
        self._init_ctrls(parent,pos)
        self.load_path_conf()
        
    def get_bind_enable(self):
        return self.checkBox1.GetValue()
    
    def check_bind_addr(self):
        tc = self.textCtrl1
        try:
            print "tc.getvalue: ",tc.GetValue()
            offset=int( tc.GetValue().replace('\n','').replace('\n\r','') , 16)
            
            print 'test offset : ',offset ,hex(offset)
        except:
            offset=''
            
        if offset=='':
            print "id_bind:case ''"
            tc.SetBackgroundColour(( 255,50,50,255))
            #message_box("warning","Empty Address!" )
            #event.Skip()
            return False
        else:
            print "id_bind:case ok"
            tc.SetBackgroundColour(( 10,255,10,10))
            #event.Skip()
            return True       
        
        
        
    def get_bind_addr_str(self):
        return self.textCtrl1.GetValue()
    
    def get_bind_addr(self):
        try:
            return int( self.textCtrl1.GetValue().replace('\n\r','').replace(' ','').replace('\n','')  , 16)  
        except:
            print "get bind addr error"
            return ''
    
    def AddrKillFocus(self,event):
        if self.checkBox1.GetValue():
            self.check_bind_addr()
        self.textCtrl1.Refresh()
        
        print "id bind kill focus"
        event.Skip()
        
    def IdBindCheckbox(self,event):
        if self.checkBox1.GetValue():
            self.check_bind_addr()
            self.textCtrl1.Refresh()
            print "id bind checkbox"
        else:
            self.textCtrl1.SetBackgroundColour(( 255,255,255,255))
            self.textCtrl1.Refresh()
        event.Skip()
        
        
        
    def load_path_conf(self):
        try:
            f=open("tool_config.txt",'r')
            lines=f.readlines()
        
            f.close()
        except:
            lines=[]
        for line in lines:
            if "id_bind_en" in line :
                self.checkBox1.SetValue( int(line.split(":")[1]) )
            elif "id_bind_addr" in line:
                self.textCtrl1.SetValue( line.split(":")[1])

