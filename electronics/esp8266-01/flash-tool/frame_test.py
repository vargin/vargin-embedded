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



import wx
import download_panel as dp
import path_panel as pp
import Panel_Combine as pc
import Panel_MacAddr as pm
import id_bind_panel as ibp
#from PIL import Image, ImageDraw, ImageFont

#wx.Panel.__init__(self, id=wxID_PANEL2, name='', parent=prnt,
              #position=wx.Point(10, 10), size=wx.Size(407, 212),
              #style=wx.TAB_TRAVERSAL)



class TestFrame_uint(wx.Panel):
    def __init__(self,pos,prnt):
        wx.Panel.__init__(self, id = -1, name = 'ESP FLASH DOWNLOAD TOOL V0.9.3.2', parent = prnt,pos = pos,
                size=(440, 630))
        #self.sketch = wx.Window(self, id = -1 , pos = wx.Point(0,500) )
        self.SetBackgroundColour("White")
        #self.initStatusBar()
        
        #self.createMenuBar()
        #self.sketch.Bind(wx.EVT_MOTION, self.OnSketchMotion)
        self.lock_flg=False
        
        self.panel_path=pp.Panel2(self)
        self.panel_spi=pc.Panel_Combine(self,wx.Point(0, 190))
        self.panel_mac=pm.Panel1(self,wx.Point(256,190) )
        self.panel_download=dp.Panel2(self,wx.Point(20, 440))
        #self.panel_path=pp.Panel2(self)
        self.panel_idBindPanel = ibp.Panel1(self,wx.Point(256,375))
        
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)
        
    def OnSketchMotion(self, event):
        self.statusbar.SetStatusText("Pos: %s" %
                str(event.GetPositionTuple()), 0)
        self.statusbar.SetStatusText("Current Pts: %s" %
                5, 1)
        self.statusbar.SetStatusText("Line Count: %s" %
                6, 2)
        event.Skip()
        
    #def initStatusBar(self):
        #self.statusbar = self.CreateStatusBar()
        #self.statusbar.SetFieldsCount(3)
        #self.statusbar.SetStatusWidths([-1, -2, -3])
        
    def OnNew(self, event): pass
    def OnOpen(self, event): pass
    def OnSave(self, event): pass
    def OnColor(self, event): pass
    def OnLock(self,event):
        if self.lock_flg:
            self.lock_flg=False
            print "lock flg: ",self.lock_flg
        else :
            self.lock_flg=True
            print "lock flg: ",self.lock_flg
            
    def menuData(self):
        return [("&File", (
                    ("&New", "New Sketch file", self.OnNew),
                    ("&Open", "Open sketch file", self.OnOpen),
                    ("&Save", "Save sketch file", self.OnSave),
                    ("&Lock", "Lock the config settings", self.OnLock, wx.ITEM_CHECK),
                    ("", "", ""),
                    ("", "", ""),
                    ("&Quit", "Quit", self.OnCloseWindow)))]
    
    def OnCloseWindow(self, event):
        """
        exit
        """
        #print "close"
        #print "check all",self.panel_path.check_all(self.panel_idBindPanel.get_bind_enable(),self)
        if self.panel_path.check_all(self.panel_idBindPanel.get_bind_enable(),self):
            self.panel_path.save_path_conf()
        self.Destroy()
        
    def createMenuBar(self):
        menuBar = wx.MenuBar()
        for eachMenuData in self.menuData():
            menuLabel = eachMenuData[0]
            menuItems = eachMenuData[1]
            menuBar.Append(self.createMenu(menuItems), menuLabel)
        self.SetMenuBar(menuBar)

    def createMenu(self, menuData):
        menu = wx.Menu()
        for eachItem in menuData:
            if len(eachItem) == 2:
                label = eachItem[0]
                subMenu = self.createMenu(eachItem[1])
                menu.AppendMenu(wx.NewId(), label, subMenu)
            else:
                self.createMenuItem(menu, *eachItem)
        return menu


    def createMenuItem(self, menu, label, status, handler, kind=wx.ITEM_NORMAL):
        if not label:
            menu.AppendSeparator()
            return
        menuItem = menu.Append(-1, label, status, kind)
        self.Bind(wx.EVT_MENU, handler, menuItem)

        #__init__(self,pos,prnt):
class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, 'test frame', 
                size=(440*3, 630*2))
        self.fm1 = TestFrame_uint( pos=(20,20),prnt=self)
        self.fm2 = TestFrame_uint( pos=(30+440,30+630),prnt=self)
        #self.fm1.Show()
        #self.fm2.Show()
        
        
        
        
        
        
if __name__ == '__main__':
    app = wx.PySimpleApp()
    TestFrame().Show()
    app.MainLoop()  
    
