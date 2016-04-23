# coding=gbk
#!/usr/bin/env python
#
# ESP8266 ROM Bootloader Utility
# https://github.com/themadinventor/esptool
#
# Copyright (C) 2014 Fredrik Ahlberg
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful, but WITHOUT 
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
# Street, Fifth Floor, Boston, MA 02110-1301 USA.



import sys
reload(sys)
sys.setdefaultencoding('gbk')
code_type = sys.getfilesystemencoding()

import sys
import struct
import serial
import math
import time
import shutil
import os
#import argparse


from flash_id_dict import *



class ESPROM:

    # These are the currently known commands supported by the ROM
    ESP_FLASH_BEGIN = 0x02
    ESP_FLASH_DATA  = 0x03
    ESP_FLASH_END   = 0x04
    ESP_MEM_BEGIN   = 0x05
    ESP_MEM_END     = 0x06
    ESP_MEM_DATA    = 0x07
    ESP_SYNC        = 0x08
    ESP_WRITE_REG   = 0x09
    ESP_READ_REG    = 0x0a

    # Maximum block sized for RAM and Flash writes, respectively.
    ESP_RAM_BLOCK   = 0x1800
    ESP_FLASH_BLOCK = 0x400
    
    ESP_UART0_BASE_REG = 0x60000000
    ESP_UART0_CLKDIV = (ESP_UART0_BASE_REG + 0x14)
    ESP_UART0_CLKDIV_CNT = 0x000fffff
    ESP_UART0_CLKDIV_S = 0
    ESP_CMD_ADDR = 0x60000200
    ESP_CMD_RDID = (0x1<<28)
    ESP_DATA_ADDR = 0x60000240

    # Default baudrate used by the ROM. Don't know if it is possible to change.
    ESP_ROM_BAUD    = 115200

    # First byte of the application image
    ESP_IMAGE_MAGIC = 0xe9

    # Initial state for the checksum routine
    ESP_CHECKSUM_MAGIC = 0xef
    
    ESP_MAC = ""
    
    #download state
    ESP_DL_OK = 0x0
    ESP_DL_IDLE = 0x1
    ESP_DL_CONNECT_ERROR = 0x2
    ESP_DL_SYNC = 0x3
    ESP_DL_SYNC_ERROR = 0x4
    ESP_DL_ERASE = 0x5
    ESP_DL_ERASE_ERROR = 0x6
    ESP_DL_DOWNLOADING = 0x7
    ESP_DL_DOWNLOAD_ERROR = 0x8
    ESP_DL_FAIL = 0x9
    ESP_DL_FINISH = 0xA
    ESP_DL_STOP = 0xB
    

    def __init__(self, frame, port = 6, baudrate = 115200,efuse_mode=1):
        self._COM = port
        self.ESP_ROM_BAUD = baudrate
        self.isOpen =  False
        self.stopFlg = False
        self.state = self.ESP_DL_IDLE
        self.process_num = 0
        self.MAC_FLG = 0
        self.BIT_FLG = 0
        self.CHIP_FLG = 0
        self.MAC0 = 0
        self.MAC1 = 0
        self.MAC2 = 0
        self.MAC3 = 0
        self.MAC4 = 0
        self.MAC5 = 0
	self.ID0 = 0
        self.ID1 = 0
        self.ID2 = 0
        self.ID3 = 0
        self.ID4 = 0
        self.ID5 = 0
        self.ID6 = 0
        self.ID7 = 0
	self.efuse_mode=efuse_mode
        self.frame = frame
	self.flash_manufacturer_id=-1
	self.flash_device_id=-1
	self.crystal_freq = -1
        
	print "=============="
        print "_COM: ",self._COM
        print "ESP_ROM_BAUD : ",self.ESP_ROM_BAUD
	print "EFUSE_MODE:",self.efuse_mode
	print "=============="

        
    """reset some status used"""
    def reset(self):
        self.isOpen =  False
        self.stopFlg = False
        self.state = self.ESP_DL_IDLE
        self.process_num = 0        
        
    """close com port"""
    def disconnect(self):
        if self.isOpen:
            self._port.close()
            print "com closed"
            self.isOpen = False
            
        else:
            print "already closed"
            
    """open RS232 port"""
    def com_connect(self,com_port=6,baudrate=115200):
        if self.isOpen:
            print 'com open'
            self._port.close()
            print "com port closed"
        self._COM = com_port
        self.ESP_ROM_BAUD = baudrate
        try:
            self._port = serial.Serial("/dev/ttyUSB0",self.ESP_ROM_BAUD)
			# self._port = serial.Serial("/dev/ttyUSB1",self.ESP_ROM_BAUD)
            print "serial port opened"
            self.isOpen = True
            self.stopFlg=False
            self.state = self.ESP_DL_SYNC
            return True
        except:
            print "serial port open error"
            self.state = self.ESP_DL_CONNECT_ERROR
            return False
    
    """synchronize baudrate"""
    def device_sync(self):
        if self.isOpen==False:
            print "error : com not open"
        else:
            try:
                self.connect()
                print "chip sync ok!"
                self.state = self.ESP_DL_SYNC
                return True
            except:
                print "chip sync error."
                self.state = self.ESP_DL_SYNC_ERROR
                return False
                
    def flash_download(self,filename = '', address = 0,reboot=False):
        self.state = self.ESP_DL_DOWNLOADING
        image = file(filename, 'rb').read()
        print 'Erasing flash...'        
        try:
            self.flash_begin(len(image), address)
        except:
            print "erase flash error"
            self.state = self.ESP_DL_ERASE_ERROR
            return False
        seq = 0
        blocks = math.floor(len(image)/self.ESP_FLASH_BLOCK +1 )
        try:
	    print_flg=True
            while len(image) > 0 and not self.stopFlg:
		if print_flg:
		    print_flg=True
		    print '\rWriting at 0x%08x... (%d %%)' % (address + seq*self.ESP_FLASH_BLOCK, 100*self.process_num/self.total_len),#100*seq/blocks),
                self.process_num +=1
                sys.stdout.flush()
		#print "test img_len: ",len(image), " seq: ",seq
		block = image[0:self.ESP_FLASH_BLOCK]
		# Pad the last block
		block = block + '\xff' * (self.ESP_FLASH_BLOCK-len(block))	    
		self.flash_block(block, seq)
		image = image[self.ESP_FLASH_BLOCK:]
		seq += 1
	    if self.stopFlg:
		print 'stop...'
	    else:
		print '\nLeaving...'
		
	    self.state = self.ESP_DL_FINISH
	    #flash_finish(True)
	    return True
        except:
            print "error when download firmware"
            self.state = self.ESP_DL_DOWNLOAD_ERROR
            return False
        
    """a serial steps of downloading"""
    def flash_download_thread(self,com,baudrate,_dl_list):
        self.ESP_MAC = ""
        self._COM=com
        self.ESP_ROM_BAUD=baudrate
        self.stopFlg=False
        self.total_len = 0
        self.process_num = 0
        self.dl_list = []+_dl_list
        
        ret = True
        if self.isOpen==True:
            self.disconnect()
        ret = self.com_connect(self._COM,self.ESP_ROM_BAUD)
        
        if ret:
            ret = self.device_sync()
            
        if ret:
            ret = self.get_mac()
	    print "get mac res: ",ret
	    #ret = True#debug....
	    pass
	
	if ret:
	    if self.BIT_FLG == 0: #24BIT
		self.frame.panel_download.mp.textCtrl_MacAddr3.SetValue("AP MAC:  "+self.ESP_MAC_AP+'\n'+"STA MAC:  "+self.ESP_MAC_STA+"\n")
		    
	    elif self.BIT_FLG == 1: #48bit
		self.frame.panel_download.mp.textCtrl_MacAddr3.SetValue("AP MAC:  "+self.ESP_MAC_AP+'\n'+"STA MAC:  "+self.ESP_MAC_STA+"\n")
		
	if ret:
	    ret = self.get_crystal()
	if ret:
	    ret = self.get_flash_id()
    
	if ret:
	    if not self.flash_manufacturer_id == -1 and not self.flash_device_id==-1:
		vendor = "N/A"
		mode = "N/A"
		size = "N/A"
		try:
		    print "vendor:",self.flash_manufacturer_id & 0xff
		    
		    vendor = SPI_FLASH_VENDOR_DICT[self.flash_manufacturer_id & 0xff]
		    #self.Parent.panel_spi.textCtrlDetectedInfo.AppendText("flash vendor:\r\n%02Xh : %s\r\n"%(self.flash_manufacturer_id,vendor))
		except:
		    
		    vendor = "N/A"
		    #self.Parent.panel_spi.textCtrlDetectedInfo.AppendText("flash vendor:\r\n%02Xh \r\n"%self.flash_manufacturer_id)
		    pass
		try:
		    print "mode:",(self.flash_device_id>>8)&0xf0
		    mode = SPI_FLASH_MODE_DICT[(self.flash_device_id>>8)&0xf0]
		except:
		    mode = "N/A"
		try:
		    print "size:",self.flash_device_id & 0xff
		    size = SPI_FLASH_SIZE_DICT[self.flash_device_id & 0xff]
		except:
		    size = "N/A"
		
		if not mode == "N/A" and self.frame.parent.panel_spi.spi_auto_set == 1:
		    self.frame.parent.panel_spi.radioBoxMode.SetSelection(SPI_FLASH_MODE_IDX[mode])
		    self.frame.parent.panel_spi.mode = int(self.frame.parent.panel_spi.radioBoxMode.GetSelection())
		    print "mode:",self.frame.parent.panel_spi.mode 
		if not size == "N/A" and self.frame.parent.panel_spi.spi_auto_set == 1:
		    self.frame.parent.panel_spi.radioBoxStorage.SetSelection(SPI_FLASH_SIZE_IDX[size])    
		    self.frame.parent.panel_spi.size = int(self.frame.parent.panel_spi.radioBoxStorage.GetSelection())
		    print "size : ",self.frame.parent.panel_spi.size
		    
		
		    
		self.frame.parent.panel_spi.textCtrlDetectedInfo.AppendText("flash vendor:\r\n%02Xh : %s\r\n"%(self.flash_manufacturer_id,vendor))
		self.frame.parent.panel_spi.textCtrlDetectedInfo.AppendText("flash devID:\r\n%04Xh\r\n%s;%s\r\n"%(self.flash_device_id,mode,size))
	    if not self.crystal_freq == -1:
		if self.crystal_freq < 45000000 and self.crystal_freq>35000000:
		    self.crystal_freq = 40000000
		elif self.crystal_freq < 29000000 and self.crystal_freq>25000000:
		    self.crystal_freq = 26000000
		elif self.crystal_freq < 25000000 and self.crystal_freq>22000000:
		    self.crystal_freq = 24000000
					
		self.frame.parent.panel_spi.textCtrlDetectedInfo.AppendText("crystal:\r\n%d Mhz"%(self.crystal_freq/1000000))
		if self.frame.parent.panel_spi.spi_auto_set == 1:
		    print "sel.freq:",self.crystal_freq
		    if self.crystal_freq < 45000000 and self.crystal_freq>35000000:
			self.frame.parent.panel_spi.choice_Crystal.SetSelection(0)
		    elif self.crystal_freq < 29000000 and self.crystal_freq>25000000:
			self.frame.parent.panel_spi.choice_Crystal.SetSelection(1)
		    elif self.crystal_freq < 25000000 and self.crystal_freq>22000000:
			self.frame.parent.panel_spi.choice_Crystal.SetSelection(2)
		    else:
			print "warning : unknown crystal freq"
		    self.frame.parent.panel_spi.crystal = self.frame.parent.panel_spi.choice_Crystal.GetSelection()
		    print "tttttest crystal :",self.frame.parent.panel_spi.crystal
	

        if ret:
	    
            try:
                if self.frame.parent.panel_spi.panel_idBindPanel.get_bind_enable():
                    if self.MAC2==0:
                        ltmp = self.id_bind(0x18,0xfe,0x34,self.MAC3,self.MAC4,self.MAC5,self.frame.parent.panel_spi.panel_idBindPanel.get_bind_addr())
                    elif self.MAC2==1:
                        ltmp = self.id_bind(0xAC,0xD0,0x74,self.MAC3,self.MAC4,self.MAC5,self.frame.parent.panel_spi.panel_idBindPanel.get_bind_addr())
                    else:
                        print "SELF.MAC2 JUDGE ERROR ..."
                        ret = False  
                    self.dl_list.append(ltmp)
                    pass
            except:
                print "id bind generate error"
                ret = False
            pass
	
        if ret:
            image_list = []
            for idx in range(len(self.dl_list)):
                filename,offset = self.dl_list[idx]
                print 'filename: ',filename 
                print 'offset : ',offset
                image = file(filename, 'rb').read()
                blocks = math.floor(len(image)/self.ESP_FLASH_BLOCK +1 )
                self.total_len += blocks
                #print "total len !!!=============",self.total_len
                image_list.append(image)
                
            for filename,offset in self.dl_list:
                ret = self.flash_download(filename,offset,False)
                if not ret or self.stopFlg:
                    break
            if ret and not self.stopFlg:
                #self.flash_finish(True)
		pass
        
        if self.isOpen:
            self.disconnect()
            
        if self.stopFlg:
            self.state = self.ESP_DL_STOP
	
    
    """write mac addr into a given addr of flash"""
    def id_bind(self,mac0,mac1,mac2,mac3,mac4,mac5,addr):
        rep_path = os.path.join( os.path.abspath('./'),'bin_tmp')
        if not os.path.isdir(rep_path):
            os.mkdir(rep_path)        
        f = file('./bin_tmp/id_bind.bin','wb')
        print "test addr : ",addr
        offset = addr%0x1000
        
        id_data = '\xff'*offset
        id_data +="%c%c%c%c%c%c"%(mac0,mac1,mac2,mac3,mac4,mac5)
        #if (0x10-offset-6)>0:
        id_data += '\xff'*(4-(offset+6)%4)
        print('id data : ',id_data)
        f.write(id_data)
        f.close()
        del(f)
        time.sleep(0.1)
        return [rep_path+'/id_bind.bin',addr-addr%0x1000]
        
    """stop downloading"""
    def stop_download(self):
        self.stopFlg=True
        
    """get chip crystal"""
    def get_crystal(self):
	try:
	    uart_reg = self.read_reg(self.ESP_UART0_CLKDIV)
	    uart_reg = (uart_reg>>self.ESP_UART0_CLKDIV_S)&self.ESP_UART0_CLKDIV_CNT
	    print("tttest uuuuuuuuuuart : uart reg: ",uart_reg)
	    print(" baudrate: ",self._port.baudrate)
	    self.crystal_freq = self._port.baudrate * uart_reg / 2
	    print "get crystal:",self.crystal_freq
	    return True
	except:
	    print "error: read crystal"
	    return False
	
    def get_flash_id(self):
	try:
	    self.flash_begin(0,0)
	    self.write_reg(self.ESP_DATA_ADDR, 0 , 0 , 0 )
	    time.sleep(0.01)
	    self.write_reg(self.ESP_CMD_ADDR , self.ESP_CMD_RDID , self.ESP_CMD_RDID , 0 )
	    time.sleep(0.01)
	    flash_id = self.read_reg(self.ESP_DATA_ADDR)
	    print "get flash id : 0x%08x"%flash_id
	    self.flash_manufacturer_id = flash_id&0xff
	    self.flash_device_id = ((flash_id>>16)&0xff | (flash_id &( 0xff<<8)))
	    print " manufacturer_id: 0x%x\r\n"%self.flash_manufacturer_id
	    print " device_id: 0x%x\r\n"%self.flash_device_id
	    return True
	except:
	    print "get flash id error"
	    return False
	
	#self.mp.textCtrl_BinPath3.AppendText("\r\nFLASH:\r\n")
	#self.mp.textCtrl_BinPath3.AppendText("manufacturer_id: %xh\r\n"%manufacturer_id)
	#self.mp.textCtrl_BinPath3.AppendText("device_id:%xh\r\n"%device_id)
	
	
	#self.read
	#addr, value, mask, delay_us = 0
    def efuse_check(self,reg0,reg1,reg2,reg3,mode):
	print "reg0:%08x"%reg0
	print "reg1:%08x"%reg1
	print "reg2:%08x"%reg2
	print "reg3:%08x"%reg3	
	self.efuse_log = ""
	self.efuse_res = True
	efuse = reg0 | (reg1<<32) | (reg2<<64) | (reg3<<96)
	#==========================
	#error check:
	#------------ 
	check_err_0 = (efuse>>76)&0xf   #0xa , 0xb
	check_err_1 = (efuse>>124)&0x3   #0x0
	check_err_2 = (efuse>>0)&0x3     #0x0
	check_err_3 = (efuse>>56)&0xf    #0x2
	check_err_4 = (efuse>>76)&0xf    #0xb
	print "check_err_0: %02x"%check_err_0
	print "check_err_1: %02x"%check_err_1
	print "check_err_2: %02x"%check_err_2
	print "check_err_3: %02x"%check_err_3
	print "check_err_4: %02x"%check_err_4
	self.efuse_log+="""======================
	\rEFUSE LOG:
	\r---------------
	\rREG0:%08X
	\rREG1:%08X
	\rREG2:%08x
	\rREG3:%08X
	\r----------------
	\r"""%(reg0,reg1,reg2,reg3)
	
	#bit_flg = (reg2>>12)&0x1
	error_flg = 0
	warning_flg = 0
	if mode == 0:  
	    self.efuse_log+="""EFUSE FOR CUSTOMER:\r\n"""
	    if not check_err_0 in [0xa,0xb]:
		print "bit79:76 error"	
		error_flg = 1
	    if not check_err_1 == 0x0:
		print "bit[125:124] error"
		error_flg = 1
	    if not check_err_2 == 0x0:
		print "bit[1:0] error"
		error_flg = 1
	    if not check_err_3 == 0x2:
		print "bit[59:56] error"
		error_flg = 1
	    if check_err_4 == 0xb:
		b0 = (reg0>>24)&0xff
		b1 = (reg1&0xff)
		b2 = (reg1>>8)&0xff
		b3 = (reg3&0xff)
		b4 = (reg3>>8)&0xff
		b5 = (reg3>>16)&0xff
		id0 = (reg0>>4)&0xff
		id1 = (reg0>>12)&0xff
		id2 = (reg0>>20)&0xf | (reg1>>12)&0xf0
		id3 = (reg1>>20)&0xf | (reg1>>24)&0xf0
		id4 = (reg2&0xff)
		id5 = (reg2>>8)&0xf  | (reg2>>12)&0xf0
		id6 = (reg2>>20)&0xff
		id7 = (reg2>>28)&0xf |(reg3>>20)&0xf0		

		crc_efuse_4bit = ((reg0>>2)&0x03 ) | ((reg3>>28)&0x0c)
		crc_data = [b0,b1,b2,b3,b4,b5,id0,id1,id2,id3,id4,id5,id6,id7]
		crc_calc_4bit = self.calcrc(crc_data) & 0xf
		print "==============================="
		print "crc_efuse_4bit:",crc_efuse_4bit
		print "crc_calc_4bit:",crc_calc_4bit   
		print "==============================="
		if (not crc_efuse_4bit == crc_calc_4bit):
		    print "efuse crc error"	
		    error_flg |= 0x2
	    if error_flg == 0x0:
		self.efuse_log+="""EFUSE CHECK PASS...\r\n"""	
		try:
		    self.efuse_log+="""XMID:%02X %02X %02X %02X %02X %02X %02X %02X \r\n"""%(id7,id6,id5,id4,id3,id2,id1,id0)  
		except:
		    pass
		    
	    else:
		if error_flg&0x1 == 1:
		    self.efuse_log+="""EFUSE VAL ERROR..."""
		if error_flg&0x2 == 0x2:
		    self.efuse_log+="""EFUSE CRC ERROR..."""
	    
		
		
	elif mode == 1: #normal
	    print "===================="
	    print "EFUSE NORMAL MODE"
	    print "===================="
	    self.efuse_log+="""====================
	    \rEFUSE NORMAL MODE
	    \r====================\r\n"""

	    if not check_err_0 in [0xa,0xb]:
		print "bit79:76 error"
		error_flg=1
	    if not check_err_1 == 0x0:
		print "bit[125:124] error"
		error_flg=1
	    if not check_err_2 == 0x0:
		print "bit[1:0] error"
		error_flg=1
	    if not check_err_3 == 0x2:
		print "bit[59:56] error"
		error_flg=1
		
	    #debug
	    #endofdebug
	    if check_err_4 == 0xb:
		crc_cal_val = (efuse>>96)&0xffffff
		crc_data = [(crc_cal_val&0xff),(crc_cal_val>>8)&0xff,(crc_cal_val>>16)&0xff]
		crc_calc_res = self.calcrc(crc_data) &0xff
		crc_efuse_val = (efuse>>88)&0xff
		print "========================="
		print "CRC IN MODE 1:"
		print "crc_calc_res:",crc_calc_res
		print "target crc val:", crc_efuse_val
		print "========================="
		if not crc_calc_res == crc_efuse_val:
		    print "bit[119:96] crc error"
		    error_flg |= 0x2
	    if error_flg & 0x1 == 1:
		self.efuse_log+="""EFUSE VAL ERROR...\r\n"""
	    if error_flg &0x2 == 0x2:
		self.efuse_log+="""EFUSE CRC ERROR...\r\n"""
    
	    #--------------------------------------------
	    #warning items for mode 1:
	    #-----------------------
	    crc_val = (efuse>>24)&0xffffffff
	    crc_data =[(crc_val>>0)&0xff,(crc_val>>8)&0xff,(crc_val>>16)&0xff,(crc_val>>24)&0xff]
	    crc_calc_res = self.calcrc(crc_data) &0xff
	    crc_efuse_val = (efuse>>16)&0xff
	    print "========================="
	    print "CRC IN MODE 1:"
	    print "crc_calc_res:",crc_calc_res
	    print "target crc val:", crc_efuse_val
	    print "========================="
	    if not crc_calc_res == crc_efuse_val:
		print "bit[47:24] crc warning"	  
		warning_flg = 0x2
	    check_warn_0 = (efuse>>126)&0x3
	    check_warn_1 = (efuse>>120)&0xf
	    check_warn_2 = (efuse>>80)&0xff
	    check_warn_3 = (efuse>>60)&0xffff
	    check_warn_4 = (efuse>>48)&0xff
	    check_warn_5 = (efuse>>4)&0xfff
	    check_warn_6 = (efuse>>2)&0x3
	    check_warn_7 = (efuse>>88)&0xffffffff
	    #print "-----------------"
	    #print "check_warn_0:%08x"%check_warn_0
	    #print "check_warn_1:%08x"%check_warn_1
	    #print "check_warn_2:%08x"%check_warn_2
	    #print "check_warn_3:%08x"%check_warn_3
	    #print "check_warn_4:%08x"%check_warn_4
	    #print "check_warn_5:%08x"%check_warn_5
	    #print "check_warn_6:%08x"%check_warn_6
	    #print "check_warn_7:%08x"%check_warn_7
	    #print "-----------------"
	    
	    if not (check_warn_0|check_warn_1|check_warn_2|check_warn_3|check_warn_4|check_warn_5|check_warn_6)==0:
		print "efuse warning found..."
		warning_flg |= 1
	    if check_err_4 == 0xa:	
		if not check_warn_7 == 0:
		    print "efuse warning found!!!"
		    warning_flg |= 1
	    if error_flg == 0x0 and warning_flg==0x0:
		self.efuse_log+="""EFUSE CHECK PASS..."""	    
	    else:
		if warning_flg&0x1 == 0x1:
		    self.efuse_log+="""EFUSE VAL WARNING...\r\n"""
		if warning_flg&0x2 == 0x2:
		    self.efuse_log+="""EFUSE CRC WARNING...\r\n"""
	    		    
		    
	print("\r\n\n\n==================")
	print "EFUSE LOG:"
	print self.efuse_log
	
	


	
    def calcrc_onebyte(self,abyte):
	abyte=abyte&0xff
	crc_1byte = 0
	for i in range(8):
	    if ((crc_1byte^abyte)&0x01)>0:
		crc_1byte ^= 0x18
		crc_1byte >>= 1
		crc_1byte |= 0x80
	    else:
		crc_1byte >>= 1
	    abyte >>= 1
	return crc_1byte
    
    def calcrc(self,dlist):
	crc = 0
	clen = len(dlist)
	for i in range(clen):
	    crc = self.calcrc_onebyte(crc ^ dlist[i])
	    
	return crc
	
	
    """read mac addr"""
    def get_mac(self):
        retry_times = 3
	cal_crc = False
        try:
            reg0 = self.read_reg(0x3ff00050)
            reg1 = self.read_reg(0x3ff00054)
            reg2 = self.read_reg(0x3ff00058)
            reg3 = self.read_reg(0x3ff0005c) 
	    
	    print "0x3ff00050: %08x"%reg0
	    print "0x3ff00054: %08x"%reg1
	    print "0x3ff00058: %08x"%reg2
	    print "0x3ff0005c: %08x"%reg3
	    
	    
        except:
            print "read reg error"
            return False
		
	print "EFUSE MODE :",self.efuse_mode
	self.efuse_check(reg0,reg1,reg2,reg3,self.efuse_mode)#normal mode	
        print "================="
	print "reg2>>13:",(reg2>>13)&0x7
	print "================="
        chip_flg =(reg2>>13)&0x7
        bit_flg = (reg2>>12)&0x1
        self.BIT_FLG = bit_flg
        self.CHIP_FLG = chip_flg
        
        crc_cal_flg = 0
        ###EFUSE CHECK HERE!!!###
        if chip_flg == 0:
            print 'warning : FLAG ERROR,STOP'
            return False
        else:
            if bit_flg==0x0:
                print("24bit mac")
                print( 'chip_flg',chip_flg)
                m0 = ((reg1>>16)&0xff)
                m1 = ((reg1>>8)&0xff)
                m2 = ((reg1 & 0xff ))
                m3 = ((reg0>>24)&0xff)   
                self.MAC_FLG = m0
                self.MAC3 = m1
                self.MAC4 = m2
                self.MAC5 = m3
                
                id0 = (reg0>>4)&0xff
                id1 = (reg0>>12)&0xf | (reg1>>24)&0xf0
                id2 = (reg2)&0xff
                id3 = (reg2>>8)&0xf | (reg2>>12)&0xf0
                id4 = (reg2>>20)&0xff
                id5 = (reg2>>28)&0xf | (reg3<<4)&0xf0
                id6 = (reg3>>4)&0xff
                id7 = (reg3>>12)&0xff
                self.ID0,self.ID1,self.ID2,self.ID3,self.ID4,self.ID5,self.ID6,self.ID7 = [id7,id6,id5,id4,id3,id2,id1,id0]
                
            elif bit_flg==0x1:
                print("48bit mac")
                print "debug:"
                print"-----------------------"
                b0 = (reg0>>24)&0xff
                b1 = (reg1&0xff)
                b2 = (reg1>>8)&0xff
                b3 = (reg3&0xff)
                b4 = (reg3>>8)&0xff
                b5 = (reg3>>16)&0xff
                self.MAC0 = b5
                self.MAC1 = b4
                self.MAC2 = b3
                self.MAC3 = b2
                self.MAC4 = b1
                self.MAC5 = b0
                print " %02x %02x %02x %02x %02x %02x"%(b5,b4,b3,b2,b1,b0)
                
                id0 = (reg0>>4)&0xff
                id1 = (reg0>>12)&0xff
                id2 = (reg0>>20)&0xf | (reg1>>12)&0xf0
                id3 = (reg1>>20)&0xf | (reg1>>24)&0xf0
                id4 = (reg2&0xff)
                id5 = (reg2>>8)&0xf  | (reg2>>12)&0xf0
                id6 = (reg2>>20)&0xff
                id7 = (reg2>>28)&0xf |(reg3>>20)&0xf0
                self.ID0,self.ID1,self.ID2,self.ID3,self.ID4,self.ID5,self.ID6,self.ID7 = [id7,id6,id5,id4,id3,id2,id1,id0]
                
                crc_cal_flg = 1
                print "-----------------------"
	if crc_cal_flg == 1:
	    crc_efuse_4bit = ((reg0>>2)&0x03 ) | ((reg3>>28)&0x0c)
	    crc_data = [b0,b1,b2,b3,b4,b5,id0,id1,id2,id3,id4,id5,id6,id7]
	    crc_calc_4bit = self.calcrc(crc_data) &0xf
	    print "crc_efuse_4bit:",crc_efuse_4bit
	    print "crc_calc_4bit:",crc_calc_4bit
        
        return self.set_mac(self.BIT_FLG)
            
    def set_mac(self,bit_flg):
        if bit_flg == 0:
            if self.MAC_FLG ==0:
                print( "r1: %02x; r2:%02x ; r3: %02x"%(self.MAC3,self.MAC4,self.MAC5))
                mac= "1A-FE-34-%02x-%02x-%02x"%(self.MAC3,self.MAC4,self.MAC5)
                mac2 = "1AFE34%02x%02x%02x"%(self.MAC3,self.MAC4,self.MAC5)
                mac = mac.upper()
                mac2 = mac2.upper()
                mac_ap = ("1A-FE-34-%02x-%02x-%02x"%(self.MAC3,self.MAC4,self.MAC5)).upper()
                mac_sta = ("18-FE-34-%02x-%02x-%02x"%(self.MAC3,self.MAC4,self.MAC5)).upper()
		
            elif self.MAC_FLG == 1:
                print( "r1: %02x; r2:%02x ; r3: %02x"%(self.MAC3,self.MAC4,self.MAC5))
                mac= "AC-D0-74-%02x-%02x-%02x"%(self.MAC3,self.MAC4,self.MAC5)
                mac2 = "ACD074%02x%02x%02x"%(self.MAC3,self.MAC4,self.MAC5)
                mac = mac.upper()
                mac2 = mac2.upper()
                mac_ap = ("AC-D0-74-%02x-%02x-%02x"%(self.MAC3,self.MAC4,self.MAC5)).upper()
                mac_sta = ("AC-D0-74-%02x-%02x-%02x"%(self.MAC3,self.MAC4,self.MAC5)).upper()    
            else:
                print "mac read error ..."
		print "mac_flg:",self.MAC_FLG
                return False
        else:
            print "48bit mac"
            mac = "%02X-%02X-%02X-%02X-%02X-%02X-"%(self.MAC0,self.MAC1,self.MAC2,self.MAC3,self.MAC4,self.MAC5)
            mac2 = "%02X-%02X-%02X-%02X-%02X-%02X"%(self.MAC0,self.MAC1,self.MAC2,self.MAC3,self.MAC4,self.MAC5)
            mac = mac.upper()
            mac2 = mac2.upper()
            
	    #mac_ap = mac2
	    mac_sta = mac2
	    mac_0_tmp = self.MAC0 & 0x7
	    
	    if mac_0_tmp == 0:
		mac_0_tmp = 0x2
	    elif mac_0_tmp==2:
		mac_0_tmp = 0x6
	    elif mac_0_tmp == 4:
		mac_0_tmp = 0x6
	    elif mac_0_tmp==6:
		mac_0_tmp=0x2
	    
	    mac_ap ="%02X-%02X-%02X-%02X-%02X-%02X"%((self.MAC0&0xf8)|mac_0_tmp,self.MAC1,self.MAC2,self.MAC3,self.MAC4,self.MAC5)

		
	
	
	#self.mp.textCtrl_BinPath3.SetValue("AP:"+mac_ap+'\n'+"STA:"+mac_sta)
	#self.mp.textCtrl_BinPath3.SetValue(mac_sta)

	f_mac = open("./MAC_ADDR/MAC_TABLE.CSV",'a')
	f_mac.write(mac_ap+','+mac_ap.replace("-","")+","+mac_sta+","+mac_sta.replace("-","")+'\n')
	f_mac.close()
	    
	    
	    
	print 'MAC AP : %s'%mac_ap
	print 'MAC STA: %s'%mac_sta
	######self.gen_bar(mac)
	self.ESP_MAC_AP = mac_ap
	self.ESP_MAC_STA = mac_sta
	self.ESP_MAC = mac_sta
	#self.mp.MAC=mac
	return True           
        


    """ Read bytes from the serial port while performing SLIP unescaping """
    def read(self, length = 1):
        b = ''
        while len(b) < length:
            c = self._port.read(1)
            if c == '\xdb':
                c = self._port.read(1)
                if c == '\xdc':
                    b = b + '\xc0'
                elif c == '\xdd':
                    b = b + '\xdb'
                else:
                    raise Exception('Invalid SLIP escape')
            else:
                b = b + c
        return b

    """ Write bytes to the serial port while performing SLIP escaping """
    def write(self, packet):
        buf = '\xc0'
        for b in packet:
            if b == '\xc0':
                buf += '\xdb\xdc'
            elif b == '\xdb':
                buf += '\xdb\xdd'
            else:
                buf += b
        buf += '\xc0'
        self._port.write(buf)

    """ Calculate checksum of a blob, as it is defined by the ROM """
    @staticmethod
    def checksum(data, state = ESP_CHECKSUM_MAGIC):
        for b in data:
            state ^= ord(b)
        return state

    """ Send a request and read the response """
    def command(self, op = None, data = None, chk = 0):
        if op:
            # Construct and send request
            pkt = struct.pack('<BBHI', 0x00, op, len(data), chk) + data
            self.write(pkt)

        # Read header of response and parse
        if self._port.read(1) != '\xc0':
            raise Exception('Invalid head of packet')
        hdr = self.read(8)
        (resp, op_ret, len_ret, val) = struct.unpack('<BBHI', hdr)
        if resp != 0x01 or (op and op_ret != op):
            raise Exception('Invalid response')

        # The variable-length body
        body = self.read(len_ret)

        # Terminating byte
        if self._port.read(1) != chr(0xc0):
            raise Exception('Invalid end of packet')

        return val, body

    """ Perform a connection test """
    def sync(self):
        self.command(ESPROM.ESP_SYNC, '\x07\x07\x12\x20'+32*'\x55')
        for i in xrange(7):
            self.command()

    """ Try connecting repeatedly until successful, or giving up """
    def connect(self):
        print 'Connecting...'
        self._port.timeout = 0.2
        for i in xrange(50):
            if self.stopFlg:
                print 'stop...'
                break
            else:
                    
                try:
                    self._port.flushInput()
                    self._port.flushOutput()
                    self.sync()
                    self._port.timeout = 1
                    
                    return 0
                except:
                    time.sleep(0.05)
        raise Exception('Failed to connect')

    """ Read memory address in target """
    def read_reg(self, addr):
        res = self.command(ESPROM.ESP_READ_REG, struct.pack('<I', addr))
        if res[1] != "\0\0":
            raise Exception('Failed to read target memory')
        return res[0]

    """ Write to memory address in target """
    def write_reg(self, addr, value, mask, delay_us = 0):
        if self.command(ESPROM.ESP_WRITE_REG,
                struct.pack('<IIII', addr, value, mask, delay_us))[1] != "\0\0":
            raise Exception('Failed to write target memory')

    """ Start downloading an application image to RAM """
    def mem_begin(self, size, blocks, blocksize, offset):
        if self.command(ESPROM.ESP_MEM_BEGIN,
                struct.pack('<IIII', size, blocks, blocksize, offset))[1] != "\0\0":
            raise Exception('Failed to enter RAM download mode')

    """ Send a block of an image to RAM """
    def mem_block(self, data, seq):
        if self.command(ESPROM.ESP_MEM_DATA,
                struct.pack('<IIII', len(data), seq, 0, 0)+data, ESPROM.checksum(data))[1] != "\0\0":
            raise Exception('Failed to write to target RAM')

    """ Leave download mode and run the application """
    def mem_finish(self, entrypoint = 0):
        if self.command(ESPROM.ESP_MEM_END,
                struct.pack('<II', int(entrypoint == 0), entrypoint))[1] != "\0\0":
            raise Exception('Failed to leave RAM download mode')

    """ Start downloading to Flash (performs an erase) """
    def flash_begin(self, _size, offset):
        old_tmo = self._port.timeout
        self._port.timeout = 90
        
	area_len = _size
	sector_no = offset/4096;
	sector_num_per_block = 16;	 
	#total_sector_num = (0== (area_len%4096))? area_len/4096 :  1+(area_len/4096);
	if 0== (area_len%4096):
	    total_sector_num = area_len/4096
	else:
	    total_sector_num = 1+(area_len/4096)
	#check if erase area reach over block boundary
	head_sector_num = sector_num_per_block - (sector_no%sector_num_per_block);
	#head_sector_num = (head_sector_num>=total_sector_num)? total_sector_num : head_sector_num;   
	if head_sector_num>=total_sector_num :
	    head_sector_num = total_sector_num
	else:
	    head_sector_num = head_sector_num   
	    
	if (total_sector_num - 2 * head_sector_num)> 0:
	    size = (total_sector_num-head_sector_num)*4096
	    print "head: ",head_sector_num,";total:",total_sector_num
	    print "erase size : ",size
	else:
	    size = int( math.ceil( total_sector_num/2.0) * 4096 )
	    print "head:",head_sector_num,";total:",total_sector_num
	    print "erase size :",size


        if self.command(ESPROM.ESP_FLASH_BEGIN,
                struct.pack('<IIII', size, 0x200, 0x400, offset))[1] != "\0\0":
            raise Exception('Failed to enter Flash download mode')
        self._port.timeout = old_tmo

    """ Write block to flash """
    def flash_block(self, data, seq):
        if self.command(ESPROM.ESP_FLASH_DATA,
                struct.pack('<IIII', len(data), seq, 0, 0)+data, ESPROM.checksum(data))[1] != "\0\0":
            raise Exception('Failed to write to target Flash')

    """ Leave flash mode and run/reboot """
    def flash_finish(self, reboot = False):
        res = self.command(ESPROM.ESP_FLASH_END,
                struct.pack('<I', int(not reboot)))[1]
        #if self.command(ESPROM.ESP_FLASH_END,
                #struct.pack('<I', int(not reboot)))[1] != "\0\0":
        print res
        if res[1] != "\0\0":
            pass
            #raise Exception('Failed to leave Flash mode')


class ESPFirmwareImage:
    
    def __init__(self, filename = None):
        self.segments = []
        self.entrypoint = 0

        if filename is not None:
            f = file(filename, 'rb')
            (magic, segments, _, _, self.entrypoint) = struct.unpack('<BBBBI', f.read(8))
            
            # some sanity check
            if magic != ESPROM.ESP_IMAGE_MAGIC or segments > 16:
                raise Exception('Invalid firmware image')
        
            for i in xrange(segments):
                (offset, size) = struct.unpack('<II', f.read(8))
                if offset > 0x40200000 or offset < 0x3ffe0000 or size > 65536:
                    raise Exception('Suspicious segment %x,%d' % (offset, size))
                self.segments.append((offset, size, f.read(size)))

            # Skip the padding. The checksum is stored in the last byte so that the
            # file is a multiple of 16 bytes.
            align = 15-(f.tell() % 16)
            f.seek(align, 1)

            self.checksum = ord(f.read(1))

    def add_segment(self, addr, data):
        self.segments.append((addr, len(data), data))

    def save(self, filename):
        f = file(filename, 'wb')
        f.write(struct.pack('<BBBBI', ESPROM.ESP_IMAGE_MAGIC, len(self.segments), 0, 0, self.entrypoint))

        checksum = ESPROM.ESP_CHECKSUM_MAGIC
        for (offset, size, data) in self.segments:
            f.write(struct.pack('<II', offset, size))
            f.write(data)
            checksum = ESPROM.checksum(data, checksum)

        align = 15-(f.tell() % 16)
        f.seek(align, 1)
        f.write(struct.pack('B', checksum))

def arg_auto_int(x):
    return int(x, 0)

if __name__ == '__main__':
    pass
    #parser = argparse.ArgumentParser(description = 'ESP8266 ROM Bootloader Utility', prog = 'esptool')

    #parser.add_argument(
            #'--port', '-p',
            #help = 'Serial port device',
            #default = '/dev/ttyUSB0')

    #subparsers = parser.add_subparsers(
            #dest = 'operation',
            #help = 'Run esptool {command} -h for additional help')

    #parser_load_ram = subparsers.add_parser(
            #'load_ram',
            #help = 'Download an image to RAM and execute')
    #parser_load_ram.add_argument('filename', help = 'Firmware image')

    #parser_dump_mem = subparsers.add_parser(
            #'dump_mem',
            #help = 'Dump arbitrary memory to disk')
    #parser_dump_mem.add_argument('address', help = 'Base address', type = arg_auto_int)
    #parser_dump_mem.add_argument('size', help = 'Size of region to dump', type = arg_auto_int)
    #parser_dump_mem.add_argument('filename', help = 'Name of binary dump')

    #parser_read_mem = subparsers.add_parser(
            #'read_mem',
            #help = 'Read arbitrary memory location')
    #parser_read_mem.add_argument('address', help = 'Address to read', type = arg_auto_int)

    #parser_write_mem = subparsers.add_parser(
            #'write_mem',
            #help = 'Read-modify-write to arbitrary memory location')
    #parser_write_mem.add_argument('address', help = 'Address to write', type = arg_auto_int)
    #parser_write_mem.add_argument('value', help = 'Value', type = arg_auto_int)
    #parser_write_mem.add_argument('mask', help = 'Mask of bits to write', type = arg_auto_int)

    #parser_write_flash = subparsers.add_parser(
            #'write_flash',
            #help = 'Write a binary blob to flash')
    #parser_write_flash.add_argument('address', help = 'Base address, 4KiB-aligned', type = arg_auto_int)
    #parser_write_flash.add_argument('filename', help = 'Binary file to write')

    #parser_image_info = subparsers.add_parser(
            #'image_info',
            #help = 'Dump headers from an application image')
    #parser_image_info.add_argument('filename', help = 'Image file to parse')

    #parser_make_image = subparsers.add_parser(
            #'make_image',
            #help = 'Create an application image from binary files')
    #parser_make_image.add_argument('output', help = 'Output image file')
    #parser_make_image.add_argument('--segfile', '-f', action = 'append', help = 'Segment input file') 
    #parser_make_image.add_argument('--segaddr', '-a', action = 'append', help = 'Segment base address', type = arg_auto_int) 
    #parser_make_image.add_argument('--entrypoint', '-e', help = 'Address of entry point', type = arg_auto_int, default = 0)

    #args = parser.parse_args()

    ## Create the ESPROM connection object, if needed
    #esp = None
    #if args.operation not in ('image_info','make_image'):
        #esp = ESPROM(args.port)
        #esp.connect()

    ## Do the actual work. Should probably be split into separate functions.
    #if args.operation == 'load_ram':
        #image = ESPFirmwareImage(args.filename)

        #print 'RAM boot...'
        #for (offset, size, data) in image.segments:
            #print 'Downloading %d bytes at %08x...' % (size, offset),
            #sys.stdout.flush()
            #esp.mem_begin(size, math.ceil(size / float(esp.ESP_RAM_BLOCK)), esp.ESP_RAM_BLOCK, offset)

            #seq = 0
            #while len(data) > 0:
                #esp.mem_block(data[0:esp.ESP_RAM_BLOCK], seq)
                #data = data[esp.ESP_RAM_BLOCK:]
                #seq += 1
            #print 'done!'

        #print 'All segments done, executing at %08x' % image.entrypoint
        #esp.mem_finish(image.entrypoint)

    #elif args.operation == 'read_mem':
        #print '0x%08x = 0x%08x' % (args.address, esp.read_reg(args.address))

    #elif args.operation == 'write_mem':
        #esp.write_reg(args.address, args.value, args.mask, 0)
        #print 'Wrote %08x, mask %08x to %08x' % (args.value, args.mask, args.address)

    #elif args.operation == 'dump_mem':
        #f = file(args.filename, 'wb')
        #for i in xrange(args.size/4):
            #d = esp.read_reg(args.address+(i*4))
            #f.write(struct.pack('<I', d))
            #if f.tell() % 1024 == 0:
                #print '\r%d bytes read... (%d %%)' % (f.tell(), f.tell()*100/args.size),
                #sys.stdout.flush()
        #print 'Done!'

    #elif args.operation == 'write_flash':
        #image = file(args.filename, 'rb').read()
        #print 'Erasing flash...'
        #esp.flash_begin(len(image), args.address)
        #seq = 0
        #blocks = math.ceil(len(image)/esp.ESP_FLASH_BLOCK)
        #while len(image) > 0:
            #print '\rWriting at 0x%08x... (%d %%)' % (args.address + seq*esp.ESP_FLASH_BLOCK, 100*seq/blocks),
            #sys.stdout.flush()
            #esp.flash_block(image[0:esp.ESP_FLASH_BLOCK], seq)
            #image = image[esp.ESP_FLASH_BLOCK:]
            #seq += 1
        #print '\nLeaving...'
        #esp.flash_finish(False)

    #elif args.operation == 'image_info':
        #image = ESPFirmwareImage(args.filename)
        #print ('Entry point: %08x' % image.entrypoint) if image.entrypoint != 0 else 'Entry point not set'
        #print '%d segments' % len(image.segments)
        #print
        #checksum = ESPROM.ESP_CHECKSUM_MAGIC
        #for (idx, (offset, size, data)) in enumerate(image.segments):
            #print 'Segment %d: %5d bytes at %08x' % (idx+1, size, offset)
            #checksum = ESPROM.checksum(data, checksum)
        #print
        #print 'Checksum: %02x (%s)' % (image.checksum, 'valid' if image.checksum == checksum else 'invalid!')

    #elif args.operation == 'make_image':
        #image = ESPFirmwareImage()
        #if len(args.segfile) == 0:
            #raise Exception('No segments specified')
        #if len(args.segfile) != len(args.segaddr):
            #raise Exception('Number of specified files does not match number of specified addresses')
        #for (seg, addr) in zip(args.segfile, args.segaddr):
            #data = file(seg, 'rb').read()
            #image.add_segment(addr, data)
        #image.entrypoint = args.entrypoint
        #image.save(args.output)
