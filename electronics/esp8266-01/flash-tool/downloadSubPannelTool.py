import sys
reload(sys)
sys.setdefaultencoding('utf-8')
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
import download_panel_info as dp
import path_panel as pp
import Panel_Combine as pc
import Panel_MacAddr as pm
              
class DownloadSubPanel(wx.Panel):
    def __init__(self,pos,prnt,id):
        wx.Panel.__init__(self, id = id, name = 'ESP FLASH DOWNLOAD TOOL V0.9.7', parent = prnt,pos = pos,
                size=(449, 143),style=wx.TAB_TRAVERSAL)
        self.parent=prnt
        self.lock_flg=False
        
        self.panel_path=self.Parent.panel_path
        self.panel_spi=self.Parent.panel_spi
        self.EFUSE_MODE = self.parent.EFUSE_MODE
        self.panel_download=dp.Panel2(self,wx.Point(0, 0),label="Download Panel %d"%id,num=id,efuse_mode=self.EFUSE_MODE)        
                
    def OnSketchMotion(self, event):
        self.statusbar.SetStatusText("Pos: %s" %
                str(event.GetPositionTuple()), 0)
        self.statusbar.SetStatusText("Current Pts: %s" %
                5, 1)
        self.statusbar.SetStatusText("Line Count: %s" %
                6, 2)
        event.Skip()
        
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
        

class StartAll(wx.Panel):
    def __init__(self,pos,prnt):
        self.parent=prnt
        wx.Panel.__init__(self, id = -1, name = '', parent = prnt,pos = pos,
                size=(449, 135),style=wx.TAB_TRAVERSAL)
        
        self.staticStartPanel = wx.StaticBox(id=-1,
              label="", name='staticBox1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(430, 130), style=0) ### 
        
        self.button_Start = wx.Button(id=-1,
              label=u'START\n\rALL', name=u'button_Start', parent=self.staticStartPanel,
              pos=wx.Point(10, 18), size=wx.Size(100, 100), style=0)
        self.button_Start.Bind(wx.EVT_BUTTON, self.OnButton_StartButton,
              id=-1)

        self.button_Stop = wx.Button(id=-1, label=u'STOP\n\rALL',
              name=u'button_Stop', parent=self.staticStartPanel, pos=wx.Point(120, 18),
              size=wx.Size(100, 100), style=0)
        self.button_Stop.Bind(wx.EVT_BUTTON, self.OnButton_StopButton,
              id=-1)     
        
    def OnButton_StartButton(self,event):
        for i in range(len(self.parent.dlp_list)):
            self.parent.dlp_list[i].panel_download.OnButton_StartButton(event)
            
    def OnButton_StopButton(self,event):
        for i in range(len(self.parent.dlp_list)):
            self.parent.dlp_list[i].panel_download.OnButton_StopButton(event)        
            
        
        
class TestPanel(wx.Panel):
    def __init__(self,parent):
        wx.Panel.__init__(self, parent=parent, id=-1, name='test frame', 
                #size=(440*3, 140*4+40))
                size=(440*2, 140*4+45))
        self.EFUSE_MODE = 1
        self.OnLoad()        
        #(self, Window parent, int id=-1, Point pos=DefaultPosition, 
                    #Size size=DefaultSize, long style=wxTAB_TRAVERSAL|wxNO_BORDER, 
                    #String name=PanelNameStr)         
        
        
        self.panel_path=pp.Panel2(self,wx.Point(0, 0))
        self.panel_spi=pc.Panel_Combine(self,wx.Point(0, 182))
        #self.fm0 = DownloadSubPanel( pos=wx.Point(0,140*3),prnt=self,id=0)
        self.panel_start=StartAll(pos=wx.Point(438,0),prnt=self)
          
        
        #self.fm1 = DownloadSubPanel( pos=wx.Point(0,140*3+8),prnt=self,id=1)
        #self.dlp_list=[self.fm1,]        

        self.fm1 = DownloadSubPanel( pos=wx.Point(0,140*3+10),prnt=self,id=1)
        self.fm2 = DownloadSubPanel( pos=wx.Point(438, 140*1),prnt=self,id=2)
        self.fm3 = DownloadSubPanel( pos=wx.Point(438, 140*2),prnt=self,id=3)
        self.fm4 = DownloadSubPanel( pos=wx.Point(438, 140*3),prnt=self,id=4)
        
        self.fm5 = DownloadSubPanel( pos=wx.Point(438+450, 140*0),prnt=self,id=5)
        self.fm6 = DownloadSubPanel( pos=wx.Point(438+450, 140*1),prnt=self,id=6)
        self.fm7 = DownloadSubPanel( pos=wx.Point(438+450, 140*2),prnt=self,id=7)
        self.fm8 = DownloadSubPanel( pos=wx.Point(438+450, 140*3),prnt=self,id=8)
        
        self.dlp_list=[self.fm1,self.fm2,self.fm3,self.fm4,
                       self.fm5,self.fm6,self.fm7,self.fm8,]
        #self.dlp_list=[self.fm1,self.fm2,self.fm3,self.fm4,]                       
        
        #self.fm2 = DownloadSubPanel( pos=(10+440,00),prnt=self)5
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)
        #self.fm1.Show()
        #self.fm2.Show()

        
        
    def OnCloseWindow(self, event):
        """
        exit
        """
        #print "close"
        #print "check all",self.panel_path.check_all(self.panel_spi.panel_idBindPanel.get_bind_enable(),self)
        if self.panel_path.check_all(self.panel_spi.panel_idBindPanel.get_bind_enable(),self):
            self.panel_path.save_path_conf()
        self.Destroy()    
    
    def OnSave(self):
        """
        exit
        """
        #print "close"
        #print "check all",self.panel_path.check_all(self.panel_spi.panel_idBindPanel.get_bind_enable(),self)
        if self.panel_path.check_all(self.panel_spi.panel_idBindPanel.get_bind_enable(),self):
            self.panel_path.save_path_conf()
        self.panel_spi.OnSave()
        
        efuse_mode = ""
        efuse_mode+="EFUSE_MODE:%d\n"%self.EFUSE_MODE
        f=open("tool_config.txt",'a')
        f.write(efuse_mode)
        f.close()        
        
    def OnLoad(self):
        print "load config ..."
        try:
            f=open("tool_config.txt",'r')
            lines = f.readlines()
        except:
            lines = []
    
        for line in lines:
            if "EFUSE_MODE" in line:
                try:
                    vtmp = int( line.strip("\n").split(":")[1] )
                    self.EFUSE_MODE = vtmp
                except:
                    print "set default EFUSE_MODE:1"
                    self.EFUSE_MODE = 1
        print "EFUSE_MODE:",self.EFUSE_MODE
                
              
        
        
        
        
if __name__ == '__main__':
    #app = wx.PySimpleApp()
    app = wx.App(False)
    
    TestPanel(None).Show()
    app.MainLoop()  
    
