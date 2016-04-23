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

#import barcode
#import barcode
#from barcode.writer import ImageWriter
#from cStringIO import StringIO
import wx


EFUSE_ADDR=[0x3ff0005c,0x3ff00058,0x3ff00054,0x3ff00050]


class MacAddrMethod():
    def __init__(self,mac_panel):
        self.mp = mac_panel
        self.MAC = ""
        self.mp.MAC=""
    
    def clr_mac(self):
        self.MAC = ""
        self.mp.MAC=""
        ##self.set_mac_sashwindow("./RESOURCE/blank.bmp")
        self.mp.textCtrl_MacAddr3.SetValue("")
        
        
    def read_reg( self,addr ):
        res = xp2.readreg(addr )
        return res
    

    def gen_bar(self,MAC):
        
        ####ean = barcode.Code39(MAC, writer=ImageWriter(),add_checksum=False)
        #ean = barcode.get_barcode('code39', MAC, writer=ImageWriter(),add_checksum=False)
        ####filename = ean.save("./MAC_ADDR/"+MAC)    
        ####ean.save("current")    

        ###self.set_mac_sashwindow("./MAC_ADDR/"+MAC+".PNG")
        pass
        
    def set_mac_sashwindow(self,filepath):
        img1 = wx.Image(filepath, wx.BITMAP_TYPE_ANY)
        w = img1.GetWidth()
        h = img1.GetHeight()
        img2 = img1.Scale(w/5,h/5)
        sb1=wx.StaticBitmap(self.mp.sashWindow1, 1, wx.BitmapFromImage( img2 ))
        sb1.Refresh()           
        