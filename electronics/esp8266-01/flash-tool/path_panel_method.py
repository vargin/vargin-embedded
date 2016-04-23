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

import os.path 
import wx

def check_file_exist(tc,check):
    if check:
        filepath = tc.GetValue()
        if os.path.exists(filepath) and os.path.isfile(filepath):
            tc.SetBackgroundColour((10,255,10,10))
            return True
        else:
            tc.SetBackgroundColour((255,50,50,255))
            return False
    else:
        return True
    
def set_file_path(pp,tc):
    wildcard = "Binary file (*.bin)|*.bin|" \
            "Image file (*.img)|*.img|" \
            "All files (*.*)|*.*"
    dialog = wx.FileDialog(None, "Choose a file", pp.default_path,#os.getcwd(), 
            "", wildcard, wx.OPEN)
    if dialog.ShowModal() == wx.ID_OK:
        binpath=dialog.GetPath()
        tc.SetValue(binpath )
        tc.SetBackgroundColour((10,255,10,10))
        if ".bin" in binpath or ".img" in binpath:
            pp.default_path=  os.path.split(binpath)[0]
        print binpath
    dialog.Destroy()    

def message_box(title_str,warning_str):
    dlg = wx.MessageBox(parent=None, message=warning_str,
                          caption=title_str,
                          style=wx.OK)# | wx.ICON_QUESTION)
    print "test dlg : ",dlg

def check_offset(tc,check):
    if check:
        try:
            offset=int( tc.GetValue() , 16)
            print 'test offset : ',offset ,hex(offset)
        except:
            offset=''
        
        if offset=='':
            print "case ''"
            tc.SetBackgroundColour(( 255,50,50,255))
            return False
        elif (not (offset & 0xfff)==0):
            print "case not &fff--0"
            tc.SetBackgroundColour(( 255,50,50,255))
            return False
        else:
            print "case ok"
            tc.SetBackgroundColour(( 10,255,10,10))
            return True
    else:
        return True
            
def check_file_and_offset(tc_path,tc_offset,check):
    pass_flg=True
    if check:
        res=check_file_exist(tc_path,check)
        if res==False:
            pass_flg=False
        res=check_offset(tc_offset,check)
        if res==False:
            pass_flg=False
        tc_path.Refresh()
        tc_offset.Refresh()
    else:
        tc_path.SetBackgroundColour(( 255,255,255,255))
        tc_offset.SetBackgroundColour(( 255,255,255,255))
        tc_path.Refresh()
        tc_offset.Refresh()
    return pass_flg

def check_all(_dict,order_list,id_bind_en=False,frame=None):
    global dl_list
    pass_flg= True
    dl_list=[]
    for cb in order_list:#_dict.keys():
        res=check_file_and_offset(_dict[cb][0],_dict[cb][1],cb.GetValue())
        if res==False:
            pass_flg=False
        else:
            if cb.GetValue():
                dl_list.append( [ _dict[cb][0].GetValue(),int(_dict[cb][1].GetValue(),16) ])
    
    if pass_flg and not id_bind_en == False:
        if frame.panel_spi.panel_idBindPanel.get_bind_enable():
            if frame.panel_spi.panel_idBindPanel.check_bind_addr():
                print "id bind check ok"
                frame.panel_spi.panel_idBindPanel.textCtrl1.Refresh()
                pass_flg = True
            else:
                print "id bind check error"
                frame.panel_spi.panel_idBindPanel.textCtrl1.Refresh()
                pass_flg = False
        pass
    
    
    #return pass_flg,dl_list
    _dtmp = {}
    dl_list_2 = []
    sort_tmp = []
    if pass_flg:
        for i in range(len(dl_list)):
            _dtmp[ dl_list[i][1] ] = dl_list[i]
        sort_tmp+= _dtmp.keys()
        sort_tmp.sort()
        
        for item in sort_tmp:
            dl_list_2.append( _dtmp[ item ])
        return pass_flg,dl_list_2
    else:
        return pass_flg,dl_list