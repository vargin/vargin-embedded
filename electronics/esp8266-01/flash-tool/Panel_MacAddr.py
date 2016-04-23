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
import panel_MacAddr_method as pmm
import os


[wxID_PANEL1, wxID_PANEL1BUTTONGETMAC, wxID_PANEL1BUTTONPRINT, 
 wxID_PANEL1SASHWINDOW1, wxID_PANEL1STATICBOX1, wxID_PANEL1TEXTCTRL_MAC
] = [wx.NewId() for _init_ctrls in range(6)]

class Panel1(wx.Panel):
    def _init_ctrls(self, prnt,position):
        # generated method, don't edit
        wx.Panel.__init__(self, id=wxID_PANEL1, name='', parent=prnt,
              pos=position,#wx.Point(352, 288), 
              size=wx.Size(205+50+15+15, 216))
              #style=wx.TAB_TRAVERSAL)
        self.SetClientSize(wx.Size(200+50+15+15, 200))


        self.staticBox1 = wx.StaticBox(id=wxID_PANEL1STATICBOX1,
              label=u'MAC Address', name='staticBox1', parent=self,
              pos=wx.Point(2, 8), size=wx.Size(160+50+15+15, 110-40), style=0)
        
        #self.sashWindow1 = wx.SashWindow(id=wxID_PANEL1SASHWINDOW1,
              #name='sashWindow1', parent=self, pos=wx.Point(5, 32),
              #size=wx.Size(152, 72), style=wx.CLIP_CHILDREN | wx.SW_3D)
        #self.sashWindow1.Enable(False)

        self.buttonPrint = wx.Button(id=wxID_PANEL1BUTTONPRINT, label=u'PRINT',
              name='button1', parent=self.staticBox1, pos=wx.Point(75, 70),
              size=wx.Size(70, 35), style=0)
        self.buttonPrint.Bind(wx.EVT_BUTTON, self.OnButtonPrintButton,
              id=wxID_PANEL1BUTTONPRINT)

        self.buttonGetMac = wx.Button(id=wxID_PANEL1BUTTONGETMAC, label=u'ShowMac',
              name='button2', parent=self.staticBox1, pos=wx.Point(3, 70),
              size=wx.Size(70, 35), style=0)
        self.buttonGetMac.Bind(wx.EVT_BUTTON, self.OnButtonGetMacButton,
              id=wxID_PANEL1BUTTONGETMAC)

        
        self.textCtrl_MacAddr3 = wx.TextCtrl(id=wxID_PANEL1TEXTCTRL_MAC,
                      name=u'textCtrl_MAC', parent=self.staticBox1, pos=wx.Point(5,15),
                      size=wx.Size(150+50+15+10, 110-50-10), style=wx.TE_MULTILINE, value=u'')             
        #self.textCtrl_MacAddr3 = wx.TextCtrl(id=wxID_PANEL1TEXTCTRL_MAC,
                      #name=u'textCtrl_MAC', parent=self, pos=wx.Point(8, 110),
                      #size=wx.Size(150, 40), style=wx.TE_MULTILINE, value=u'')        
        
        
        #self.prnt = frame
        #self.buttonGetMac.Enable(False)
        self.MAC = ""
        self.func = pmm.MacAddrMethod(self)
        
    def clr_mac(self):
        self.MAC = ""
        
        
    def __init__(self, parent, pos,num):
        self.frame = parent
        self.num=num
        self._init_ctrls(parent,pos)
        print 'init finished '

    def OnButtonPrintButton(self, event):
        if self.MAC == "":
            pass
        else:
            self.printData = wx.PrintData() 
            self.printData.SetPaperId(wx.PAPER_LETTER) 
            self.printData.SetPrintMode(wx.PRINT_MODE_PRINTER) 
            data = wx.PrintDialogData(self.printData) 
            printout = MyPrintout(self,self.MAC) 
            printout2 = MyPrintout(self,self.MAC) 
            self.preview = wx.PrintPreview(printout, printout2, data)
            if not self.preview.Ok(): 
                wx.MessageBox("error") 
                return 
            pfrm = wx.PreviewFrame(self.preview, self.frame, "This is a print preview")
            pfrm.Initialize()
            print 'position : ',self.frame.GetPosition()
            pos_print = ( self.frame.GetPosition()[0]+self.frame.GetSize()[0], self.frame.GetPosition()[1])
            pfrm.SetPosition(pos_print)
            pfrm.SetSize(self.frame.GetSize())
            pfrm.Show(True)         
            event.Skip()
        

    def OnButtonGetMacButton(self, event):
        #pmm.get_mac()
        print 'in get mac'
        print 'mac : ',self.MAC
        if self.MAC == "":
            pass
        else:
            os.startfile("current%d.png"%self.num)
            event.Skip()
                
                
    def reset(self):
        self.clr_mac()
        self.textCtrl_MacAddr3.SetValue("")
        self.func.clr_mac()


class MyPrintout(wx.Printout): 
    def __init__(self, canvas,mac): 
        wx.Printout.__init__(self) 
        self.canvas = canvas 
        self.MAC = mac
 
    def OnBeginDocument(self, start, end): 
        return super(MyPrintout, self).OnBeginDocument(start, end) 
 
    def OnEndDocument(self): 
        super(MyPrintout, self).OnEndDocument() 
 
    def OnBeginPrinting(self): 
        super(MyPrintout, self).OnBeginPrinting() 
 
    def OnEndPrinting(self): 
        super(MyPrintout, self).OnEndPrinting() 
 
    def OnPreparePrinting(self): 
        super(MyPrintout, self).OnPreparePrinting() 
 
 
    def OnPrintPage(self, page): 
        dc = self.GetDC() 
        #------------------------------------------- 
        # One possible method of setting scaling factors... 
        img=wx.Image("./MAC_ADDR/"+self.MAC+".png",wx.BITMAP_TYPE_ANY)
        h = img.GetHeight()
        w = img.GetWidth()
        img2=img.Scale(w/2,h/2)
        
        image=img2.ConvertToBitmap() 
        dc.DrawBitmap(image,0,0,False) 
        return True 
    
    def clr_mac(self):
        self.MAC = ""    
        
