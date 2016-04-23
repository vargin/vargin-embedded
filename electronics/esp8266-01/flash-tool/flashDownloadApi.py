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


"""not used any more , this is for xtom version"""

#import xtcom_python2 as xp


#def openPort(comport=6,baudrate=115200):
    #ret = xp.connect(comport,baudrate)


#def connectDev():
    #ret= xp.sync()

#def flashDownLoad(file_path,addr_offset):
    #ret=xp.flashdownload(file_path,addr_offset)
    
#def closePort():
    #ret = xp.disconnect()
    
#def main():
    #ret=openPort(6,115200)
    #if not ret==0:
        #print "open port error\n"
    
    #ret=connectDev()
    #if not ret==0:
        #print "connect dev error\n"
    
    #ret=flashDownLoad("eagle.app.flash.bin",0x0)
    #if not ret==0:
        #print "flash download error\n"
    
    #ret=flashDownLoad('eagle.app.flash.bin',0x10000)
    #if not ret==0:
        #print "flash download 2nd error\n"
    
    #closePort()    
    
#def start_ins():
    #xp.ins_num_thread()
    
#def get_num():
    #num=xp.get_num()
    #print "num : ",num
    
    
#if __name__=="__main__":
    #main()