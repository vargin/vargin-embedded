#Boa:Frame:wxFrame1

import wx
import wx.grid
import read_xls_to_h as rx
import os
import struct
from flash_id_dict import RF_GAIN_DICT

def create(parent):
    return wxFrameGrid(parent)

[wxID_WXFRAME1, wxID_WXFRAME1GRID1, wxID_WXPANEL1,wxID_WXPANEL1GRID1,
 wxID_WXFRAME1SPINCTRL1,
 wxID_WXFRAME1STATICBOX1,wxID_WXFRAME1STATICTEXT1,wxID_WXFRAME1STATICTEXT2,wxID_WXFRAME1STATICTEXT3,
 wxID_WXFRAME1STATICTEXT4,wxID_WXFRAME1STATICTEXT5,wxID_WXFRAME1STATICTEXT6,wxID_WXFRAME1SPINCTRL2,
 wxID_WXFRAME1SPINCTRL3,wxID_WXFRAME1SPINCTRL4,wxID_WXFRAME1SPINCTRL5,wxID_WXFRAME1SPINCTRL6,
 wxID_WXFRAME1SPINCTRL7,wxID_WXFRAME1STATICTEXT7,wxID_WXFRAME1STATICTEXT8,wxID_WXFRAME1STATICTEXT9,
 wxID_WXFRAME1STATICTEXT10,wxID_WXFRAME1STATICTEXT11,wxID_WXFRAME1STATICTEXT12,wxID_WXFRAME1STATICBOX2,
 wxID_WXFRAME1CHECKBOX1,wxID_WXFRAME1STATICTEXT13,wxID_WXFRAME1TEXTCTRL1,wxID_WXFRAME1STATICTEXT14,
 wxID_WXFRAME1RADIOBOX1,wxID_WXFRAME1STATICBOX3,xID_WXFRAME1STATICTEXT15 ,wxID_WXFRAME1STATICTEXT16 ,
wxID_WXFRAME1choice_RFGAIN ,wxID_WXFRAME1spinCtrl_DIGITALGAIN ,wxID_WXFRAME1STATICTEXT17,wxID_WXFRAME1STATICTEXT15,
wxID_WXFRAME1STATICBOX_FREQOFFSET,
wxID_WXFRAME1CHECKBOX_SETFREQEN,
wxID_WXFRAME1SPINCTRL_FREQ,
wxID_WXFRAME1STATICTEXT_PPM,
wxID_WXFRAME1STATICTEXT_KHZ,
wxID_WXFRAME1TEXTCTRL_VPPM,
wxID_WXFRAME1STATICTEXT_VPPM,
wxID_WXFRAME1STATICBOX_BUTTONS,
wxID_WXFRAME1BUTTON_BUTTON_DEFAULT,
wxID_WXFRAME1BUTTON_APPLY,
wxID_WXFRAME1CHECKBOX_LOWPOSWEREN,
wxID_WXFRAME1CHECKBOX_SETAUTOCAL,
wxID_WXFRAME1TEXTCTRL_VDD,
wxID_WXFRAME1STATICBOX_TOUT,
wxID_WXFRAME1STATICTEXT_VDD,
wxID_WXFRAME1STATICTEXT_VVDD,
wxID_WXFRAME1BUTTON_GEN,
wxID_WXFRAME1BUTTON_LOAD,wxID_WXFRAME1CHECKBOX_BACKOFFEN,
wxID_WXFRAME1TEXTCTRL_BACKOFF,wxID_WXFRAME1STATICTEXT1_BKOFFUNIT,
wxID_WXFRAME1SPINCTRL_BACKOFF,wxID_WXFRAME1CHECKBOX_LIMITEN,
wxID_WXFRAME1SPINCTRL_POWERLIMIT,wxID_WXFRAME1STATICTEXT1_PLIMIT,
wxID_WXFRAME1SPINCTRL_LOWPOWER,wxID_WXFRAME1RADIOBOX_CRYSTAL,
wxID_WXFRAME1STATICBOX_TOUTBOX,
wxID_WXFRAME1RADIOBUTTON_TOUTADC,
wxID_WXFRAME1RADIOBUTTON_TOUTVDD,
wxID_WXFRAME1TEXTCTRL_ADCVDD,
wxID_WXFRAME1STATICTEXT_TOUTV,
wxID_WXFRAME1STATICTEXT_TOUTVDD,
wxID_WXFRAME1RADIOBOX_RFINITMODE,

 
] = [wx.NewId() for _init_ctrls in range(71)]

class wxFrameGrid(wx.Frame):
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_WXFRAME1, name='', parent=prnt,
              pos=wx.Point(318, 214), size=wx.Size(432, 242),
              style=wx.DEFAULT_FRAME_STYLE, title='wxFrame1')
        self.SetClientSize(wx.Size(424, 215))

        self.grid1 = wx.grid.Grid(id=wxID_WXFRAME1GRID1, name='grid1',
              parent=self, pos=wx.Point(0, 0), size=wx.Size(424, 215), style=0)
        self.grid1.EnableGridLines(True)
        

    def __init__(self, parent):
        self._init_ctrls(parent)

        # Either CreateGrid or SetTable must be manually added in your code
        # before you populate the grid
        self.grid1.CreateGrid(3, 3)
        
class wxPanelGrid(wx.Panel):
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Panel.__init__(self, id=wxID_WXPANEL1, name='', parent=prnt,
              pos=wx.Point(650, 650), size=wx.Size(650, 650),
              style=wx.TAB_TRAVERSAL)
       
        self.SetClientSize(wx.Size(650, 650))
        
        self.staticInitSettings = wx.StaticBox(id=-1,
              label="RF Settings", name='staticBox1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(600, 340), style=0) ### 
        
        
        #------------------------------------------------------
        
        self.staticBox_TxPowerConfig = wx.StaticBox(id=wxID_WXFRAME1STATICBOX1,
              label=u'TxTargetPowerConfig', name='staticBox1', parent=self.staticInitSettings,
              pos=wx.Point(5, 15), size=wx.Size(193, 184), style=0)

        

        self.staticText1 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT1,
              label=u'MCS0-1', name='staticText1', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(32-23, 56-10-12-3), size=wx.Size(46, 18), style=0)

        self.staticText2 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT2,
              label=u'MCS2-3', name='staticText2', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(32-23, 80-23-3), size=wx.Size(46, 18), style=0)

        self.staticText3 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT3,
              label=u'MCS4', name='staticText3', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(40-23, 104-10-12-3), size=wx.Size(34, 18), style=0)

        self.staticText4 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT4,
              label=u'MCS5', name='staticText4', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(40-23, 128-10-12-3), size=wx.Size(34, 18), style=0)

        self.staticText5 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT5,
              label=u'MCS6', name='staticText5', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(40-23, 152-10-12-3), size=wx.Size(34, 18), style=0)

        self.staticText6 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT6,
              label=u'MCS7', name='staticText6', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(40-23, 176-10-12-3), size=wx.Size(34, 18), style=0)
        
        self.spinCtrl1 = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL1, initial=0,
                      max=100, min=0, name='spinCtrl1', parent=self.staticBox_TxPowerConfig,
                      pos=wx.Point(96-25, 48-10-10), size=wx.Size(60, 22),inc=0.25,
                      style=wx.SP_ARROW_KEYS)
        self.spinCtrl1.SetRange(-10, 22)
        self.spinCtrl1.SetValue(20.5)
        
        self.spinCtrl1.SetToolTipString(u'Target power for 11n MCS0 & MCS1 \
                                        \rPower is set at tx_param5\
                                        \rEffected rate is defined by tx_param11&12')
        self.spinCtrl1.Enable(False)

        self.spinCtrl2 = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL2, initial=19.5,
              max=100, min=0, name='spinCtrl2', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(96-25, 72-10-10), size=wx.Size(60, 22),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl2.SetValue(19.5)
        self.spinCtrl2.SetRange(-10, 22)
        self.spinCtrl2.Enable(False)
        self.spinCtrl2.SetToolTipString(u'Target power for 11n MCS2&MCS3 \
                                          \rPower is set at tx_param6\
                                          \rEffected rate is defined by tx_param13&14')

        #self.spinCtrl3 = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL3, initial=18.5,
              #max=100, min=0, name='spinCtrl3', parent=self.staticBox_TxPowerConfig,
              #pos=wx.Point(96-15, 96-10-10), size=wx.Size(0, 0), inc=0.25,
              #style=wx.SP_ARROW_KEYS)
        #self.spinCtrl3.SetValue(18.5)
        #self.spinCtrl3.SetRange(10, 22)  
        self.spinCtrl3 = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL3, initial=0,
              max=100, min=0, name='spinCtrl7', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(96-25, 96-10-10), size=wx.Size(60, 22),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl3.SetValue(18.5)
        self.spinCtrl3.SetRange(-10, 22)    
        self.spinCtrl3.Enable(False)
        self.spinCtrl3.SetToolTipString(u'Target power for 11n MCS4 \
                                         \rPower is set at tx_param7\
                                         \rEffected rate is defined by tx_param15')

        self.spinCtrl4 = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL4, initial=17,
              max=100, min=0, name='spinCtrl4', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(96-25, 120-10-10), size=wx.Size(60, 22),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl4.SetValue(17)
        self.spinCtrl4.SetRange(-10, 22)
        self.spinCtrl4.Enable(False)
        self.spinCtrl4.SetToolTipString(u'Target power for 11n MCS5 \
                                         \rPower is set at tx_param8\
                                         \rEffected rate is defined by tx_param16')
        

        self.spinCtrl5 = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL5, initial=0,
              max=100, min=0, name='spinCtrl5', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(96-25, 144-10-10), size=wx.Size(60, 22),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl5.SetValue(16.0)
        self.spinCtrl5.SetRange(-10, 22)
        self.spinCtrl5.Enable(False)
        self.spinCtrl5.SetToolTipString(u'Target power for 11n MCS6 \
                                          \rPower is set at tx_param9\
                                          \rEffected rate is defined by tx_param17')

        self.spinCtrl6 = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL6, initial=0,
              max=100, min=0, name='spinCtrl6', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(96-25, 168-10-10), size=wx.Size(60, 22),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl6.SetValue(14)
        self.spinCtrl6.SetRange(-10, 22)
        self.spinCtrl6.Enable(False)
        self.spinCtrl6.SetToolTipString(u'Target power for 11n MCS7 \
                                          \rPower is set at tx_param10\
                                          \rEffected rate is defined by tx_param18')


        

        self.staticText7 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT7,
              label=u'dBm', name='staticText7', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(232-95, 56-10-12), size=wx.Size(27, 18), style=0)

        self.staticText8 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT8,
              label=u'dBm', name='staticText8', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(232-95, 80-10-12), size=wx.Size(27, 18), style=0)

        self.staticText9 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT9,
              label=u'dBm', name='staticText9', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(232-95, 104-10-12), size=wx.Size(32, 18), style=0)

        self.staticText10 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT10,
              label=u'dBm', name='staticText10', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(232-95, 128-10-12), size=wx.Size(27, 18), style=0)

        self.staticText11 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT11,
              label=u'dBm', name='staticText11', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(232-95, 152-10-12), size=wx.Size(27, 18), style=0)

        self.staticText12 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT12,
              label=u'dBm', name='staticText12', parent=self.staticBox_TxPowerConfig,
              pos=wx.Point(232-95, 176-10-12), size=wx.Size(27, 18), style=0)
        

        #---------------------------------------------------------------------------------        
        
        ##self.staticBox2 = wx.StaticBox(id=wxID_WXFRAME1STATICBOX2,
              ##label=u'RFInit Mode', name='staticBox2', parent=self.staticInitSettings,
              ##pos=wx.Point(405, 200), size=wx.Size(183, 125), style=0)
        ##self.staticBox2.Enable(False)
        ##self.staticBox2.SetToolTipString("Choose to set RFInit Mode")
        
        self.radioBox_RFInit = wx.RadioBox(choices=['LoadRFCalParam', 'TxPwrCtrl in init',
                                               'FullRFCal in RFInit' ],
                                     id=wxID_WXFRAME1RADIOBOX_RFINITMODE, label='RFInit mode', majorDimension=1,
                                     name='radioBox1', parent=self, pos=wx.Point(405, 200),
                                     size=wx.Size(183, 130), style=wx.RA_SPECIFY_COLS)
        self.radioBox_RFInit.Bind(wx.EVT_RADIOBOX, self.OnRadioBox_RFInit,
                                   id=wxID_WXFRAME1RADIOBOX_RFINITMODE)       
        self.radioBox_RFInit.SetToolTipString("""0: RF init no RF CAL, using all RF CAL data in flash, it takes about 2ms for RF init 
1: RF init only do TX power control CAL, others using RF CAL data in flash , it takes about 20ms for RF init 
2: RF init no RF CAL, using all RF CAL data in flash, it takes about 2ms for RF init  
3: RF init do all RF CAL, it takes about 200ms for RF init  """)        



        #self.checkBox1 = wx.CheckBox(id=wxID_WXFRAME1CHECKBOX1,
              #label=u'EN_SetTestChannel', name='checkBox1', parent=self.staticBox2,
              #pos=wx.Point(13, 24), size=wx.Size(136, 17), style=0)
        #self.checkBox1.SetValue(False)
        #self.checkBox1.Enable(False)

        #self.staticText13 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT13,
              #label=u'TestCHN:', name='staticText13', parent=self.staticBox2,
              #pos=wx.Point(5, 48), size=wx.Size(64, 18), style=0)

        #self.textCtrl1 = wx.TextCtrl(id=wxID_WXFRAME1TEXTCTRL1,
              #name='2512', parent=self.staticBox2, pos=wx.Point(56, 48),
              #size=wx.Size(61, 24), style=0, value='2412')
        #self.textCtrl1.Enable(False)

        #self.staticText14 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT14,
              #label=u'MHz', name='staticText14', parent=self.staticBox2,
              #pos=wx.Point(125, 48), size=wx.Size(27, 18), style=0)   
        
        
        #====================================================================   
        #self.staticBox_tout = wx.StaticBox(id=wxID_WXFRAME1STATICBOX_TOUT,
              #label=u'', name='staticBox2', parent=self.staticInitSettings,
              #pos=wx.Point(380, 200), size=wx.Size(170, 85), style=0)
        
        #self.radioBox1 = wx.RadioBox(choices=['EN_ADC', 'EN_VDD33'],
              #id=wxID_WXFRAME1RADIOBOX1, label=u'TOUT_CONFIG', majorDimension=1,
              #name='radioBox1', parent=self.staticInitSettings, pos=wx.Point(483, 200),
              #size=wx.Size(95, 82), style=wx.RA_SPECIFY_COLS)
        #self.radioBox1.SetStringSelection(u'EN_VDD33')
        #self.radioBox1.SetToolTipString(u'radioBox1')
        #self.radioBox1.Bind(wx.EVT_RADIOBOX, self.OnRadioBox1Radiobox,
              #id=wxID_WXFRAME1RADIOBOX1)        
        
        #self.textCtrl_vdd = wx.TextCtrl(id=wxID_WXFRAME1TEXTCTRL_VDD,
                      #name=u'textCtrl1', parent=self.staticInitSettings, pos=wx.Point(480, 230),
                      #size=wx.Size(30, 24), style=0, value=u'0')   
        #self.textCtrl_vdd.SetValue("3.3")
        #self.textCtrl_vdd.Enable(False)
        
        
        #self.staticText_vdd = wx.StaticText(id=wxID_WXFRAME1STATICTEXT_VDD,
                      #label=u'VDD', name='staticText2', parent=self.staticInitSettings,
                      #pos=wx.Point(480, 215), size=wx.Size(30, 18), style=0) 
        
        
        #self.staticText_vvdd = wx.StaticText(id=wxID_WXFRAME1STATICTEXT_VVDD,
                              #label=u'V', name='staticText2', parent=self.staticInitSettings,
                              #pos=wx.Point(510, 230), size=wx.Size(10, 18), style=0)         
        
        #=======================================================================


        self.staticBox_LowPower = wx.StaticBox(id=wxID_WXFRAME1STATICBOX3,
              label=u'LowPowerMode', name='staticBox3', parent=self.staticInitSettings,
              pos=wx.Point(202, 15), size=wx.Size(200, 184), style=0)

        self.checkBox_LowPowerEn = wx.CheckBox(id=wxID_WXFRAME1CHECKBOX_LOWPOSWEREN,
              label=u'LowPowerEn', name='checkBox1', parent=self.staticBox_LowPower,
              pos=wx.Point(5, 30), size=wx.Size(90, 17), style=0)
        self.checkBox_LowPowerEn.SetValue(False)
        #self.checkBox_LowPowerEn.Enable(False)
        self.checkBox_LowPowerEn.Bind(wx.EVT_CHECKBOX, self.OnCheckBox_LowPowerEn,
              id=wxID_WXFRAME1CHECKBOX_LOWPOSWEREN)  
        self.checkBox_LowPowerEn.SetToolTipString("If lowpower mode enabled, you need to set a target power value below. \
                                                   \rTool will modify the tx_param24-26")
        
        #self.staticText15 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT15,
              #label=u'RF Gain', name='staticText15', parent=self.staticBox_LowPower,
              #pos=wx.Point(123, 40), size=wx.Size(44, 15), style=0)

        self.choice_RFGAIN = wx.Choice(choices=['0dB', '-2.5dB', '-6dB', '-8.5dB',
              '-11.5dB', '-14dB', '-17.5dB', '-23dB'], id=wxID_WXFRAME1choice_RFGAIN,
              name='choice_RFGAIN', parent=self.staticBox_LowPower, pos=wx.Point(123, 60),
              size=wx.Size(70, 20), style=0)
        self.choice_RFGAIN.SetSelection(0)
        self.choice_RFGAIN.Enable(False)
        self.choice_RFGAIN.SetToolTipString("RF gain value set for lowpower mode")
        
        self.spinCtrl_lowpower = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL_LOWPOWER, initial=12,
              max=12, min=-10, name='spinCtrl_DIGITALGAIN', parent=self.staticBox_LowPower,
              pos=wx.Point(30, 55), size=wx.Size(60, 20),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl_lowpower.SetValue(12)
        self.spinCtrl_lowpower.Enable(False)
        self.spinCtrl_lowpower.Bind(wx.EVT_TEXT, self.OnCheckBox_LowPowerEn,
              id=wxID_WXFRAME1SPINCTRL_LOWPOWER)        
              
        #self.staticText16 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT16,
              #label=u'Digital Gain', name='staticText16', parent=self.staticBox_LowPower,
              #pos=wx.Point(8+30, 40), size=wx.Size(67, 15), style=0)
        
        #self.spinCtrl_DIGITALGAIN = wx.SpinCtrlDouble(id=wxID_WXFRAME1spinCtrl_DIGITALGAIN, initial=0,
              #max=0, min=-6, name='spinCtrl_DIGITALGAIN', parent=self.staticBox_LowPower,
              #pos=wx.Point(8+30, 60), size=wx.Size(60, 20),inc=0.25,
              #style=wx.SP_ARROW_KEYS)
        self.spinCtrl_DIGITALGAIN = wx.SpinCtrlDouble(id=wxID_WXFRAME1spinCtrl_DIGITALGAIN, initial=0,
              max=0, min=-6, name='spinCtrl_DIGITALGAIN', parent=self.staticBox_LowPower,
              pos=wx.Point(123, 35), size=wx.Size(60, 20),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl_DIGITALGAIN.SetRange(-6, 0)
        self.spinCtrl_DIGITALGAIN.SetValue(0)
        #self.spinCtrl_DIGITALGAIN.SetInitialSize(wx.Size(60, 25))
        self.spinCtrl_DIGITALGAIN.Enable(False)
        self.spinCtrl_DIGITALGAIN.SetToolTipString("Digital gain value set for lowpower mode")

        self.staticText17 = wx.StaticText(id=wxID_WXFRAME1STATICTEXT17,
              label=u'dBm', name='staticText17', parent=self.staticBox_LowPower,
              pos=wx.Point(95, 55), size=wx.Size(15, 18), style=0)
        
        self.checkBox_BackOffEn = wx.CheckBox(id=wxID_WXFRAME1CHECKBOX_BACKOFFEN,
              label=u'BackOffEn:', name='checkBox1', parent=self.staticBox_LowPower,
              pos=wx.Point(5, 85), size=wx.Size(90, 17), style=0)
        self.checkBox_BackOffEn.SetValue(False)
        #self.checkBox_LowPowerEn.Enable(False)
        self.checkBox_BackOffEn.Bind(wx.EVT_CHECKBOX, self.OnCheckBox_BackOffEn,
              id=wxID_WXFRAME1CHECKBOX_BACKOFFEN)    
        self.checkBox_BackOffEn.SetToolTipString("To set the backoff value to reduce tx power on each rate.")
        
        
        self.spinCtrl_backoff = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL_BACKOFF, initial=0,
              max=0, min=-6, name='spinCtrl4', parent=self.staticBox_LowPower,
              pos=wx.Point(30, 105), size=wx.Size(60, 20),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl_backoff.SetValue(0)
        self.spinCtrl_backoff.SetRange(-6, 0)
        self.spinCtrl_backoff.Enable(False)
         
        self.spinCtrl_backoff.Bind(wx.EVT_TEXT, self.update_tx_power,
              id=wxID_WXFRAME1SPINCTRL_BACKOFF)        
        
        
        #self.textCtrl_backoff= wx.TextCtrl(id=wxID_WXFRAME1TEXTCTRL_BACKOFF,
                      #name=u'textCtrl1', parent=self.staticBox_LowPower, pos=wx.Point(65, 105),
                      #size=wx.Size(30, 20), style=0, value=u'0')    
        self.staticText1_bkoffuint = wx.StaticText(id=wxID_WXFRAME1STATICTEXT1_BKOFFUNIT,
                      label=u'dB', name='staticText16', parent=self.staticBox_LowPower,
                      pos=wx.Point(95, 105), size=wx.Size(67, 15), style=0)  
        
        
        self.checkBox_LimitEn = wx.CheckBox(id=wxID_WXFRAME1CHECKBOX_LIMITEN,
              label=u'PowerLimitEn:', name='checkBox1', parent=self.staticBox_LowPower,
              pos=wx.Point(5, 135), size=wx.Size(100, 17), style=0)
        self.checkBox_LimitEn.SetValue(False)
        #self.checkBox_LowPowerEn.Enable(False)
        self.checkBox_LimitEn.Bind(wx.EVT_CHECKBOX, self.OnCheckBox_LimitEn,
              id=wxID_WXFRAME1CHECKBOX_LIMITEN)  
        self.checkBox_LimitEn.SetToolTipString("To set the power limit value to cut the exceeded tx power against the set one on each rate.")
        
        self.spinCtrl_powerlimit = wx.SpinCtrlDouble(id=wxID_WXFRAME1SPINCTRL_POWERLIMIT, initial=0,
              max=20.5, min=12, name='spinCtrl4', parent=self.staticBox_LowPower,
              pos=wx.Point(30, 155), size=wx.Size(60, 20),inc=0.25,
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl_powerlimit.SetValue(20.5)
        self.spinCtrl_powerlimit.SetRange(14, 20.5)
        self.spinCtrl_powerlimit.Enable(False)
        self.spinCtrl_powerlimit.Bind(wx.EVT_TEXT, self.update_tx_power,
                      id=wxID_WXFRAME1SPINCTRL_POWERLIMIT)           



        self.staticText1_plimituint = wx.StaticText(id=wxID_WXFRAME1STATICTEXT1_PLIMIT,
                      label=u'dBm', name='staticText16', parent=self.staticBox_LowPower,
                      pos=wx.Point(95, 155), size=wx.Size(67, 15), style=0)          
        
        
#============================================================================


        self.staticBox_FreqOffset = wx.StaticBox(id=wxID_WXFRAME1STATICBOX_FREQOFFSET,
              label=u'FreqOffset', name='staticBox1', parent=self.staticInitSettings,
              pos=wx.Point(262, 200), size=wx.Size(140, 130), style=0)

        self.checkBox_SetFreqEn = wx.CheckBox(id=wxID_WXFRAME1CHECKBOX_SETFREQEN,
              label=u'SetFreqEnable', name='checkBox1', parent=self.staticBox_FreqOffset,
              pos=wx.Point(16, 24), size=wx.Size(120, 17), style=0)
        self.checkBox_SetFreqEn.SetValue(False)
        self.checkBox_SetFreqEn.Bind(wx.EVT_CHECKBOX, self.OnCheckBox1Checkbox,
              id=wxID_WXFRAME1CHECKBOX_SETFREQEN)
        self.checkBox_SetFreqEn.SetToolTipString("enable the function to modify a positive frequency offset \
                                                      \rmode3: auto calibrate,only positive offset ;\
                                                      \rmode7:set the offset by force,only positive offset") 
        
        
        
        self.checkBox_SetAutoCal = wx.CheckBox(id=wxID_WXFRAME1CHECKBOX_SETAUTOCAL,
              label=u'AutoCalEn', name='checkBox1', parent=self.staticBox_FreqOffset,
              pos=wx.Point(16, 44), size=wx.Size(100, 17), style=0)
        self.checkBox_SetAutoCal.SetValue(False)
        self.checkBox_SetAutoCal.Enable(True)
        self.checkBox_SetAutoCal.Bind(wx.EVT_CHECKBOX, self.OnCheckBox_FreqAuto,
              id=wxID_WXFRAME1CHECKBOX_SETAUTOCAL)    
        self.checkBox_SetAutoCal.SetToolTipString("enable the function to modify a positive frequency offset \
                                                      \rmode3: auto calibrate,only positive offset ;\
                                                      \rmode7:set the offset by force,only positive offset")        
        
     

        self.spinCtrl_Freq = wx.SpinCtrl(id=wxID_WXFRAME1SPINCTRL_FREQ, initial=50,
              max=400, min=50, name='spinCtrl1', parent=self.staticBox_FreqOffset,
              pos=wx.Point(22, 92), size=wx.Size(60, 25),
              style=wx.SP_ARROW_KEYS)
        self.spinCtrl_Freq.SetInitialSize(wx.Size(60, 25))
        self.spinCtrl_Freq.Bind(wx.EVT_TEXT, self.OnSpinCtrl1Spin,
              id=wxID_WXFRAME1SPINCTRL_FREQ)
        self.spinCtrl_Freq.Enable(False)
        self.spinCtrl_Freq.SetValue(50)
        self.spinCtrl_Freq.SetToolTipString("fill the practical freq offset ,\
                                             \ronly positive offset is supported")
        
        
        self.staticText_ppm = wx.StaticText(id=wxID_WXFRAME1STATICTEXT_PPM,
              label=u'ppm', name='staticText1', parent=self.staticBox_FreqOffset,
              pos=wx.Point(100, 126), size=wx.Size(27, 18), style=0)
        
        self.staticText_khz = wx.StaticText(id=wxID_WXFRAME1STATICTEXT_KHZ,
              label=u'KHz', name='staticText2', parent=self.staticBox_FreqOffset,
              pos=wx.Point(100, 98), size=wx.Size(23, 18), style=0)
        
        #self.textCtrl_vppm = wx.TextCtrl(id=wxID_WXFRAME1TEXTCTRL_VPPM,
              #name=u'textCtrl1', parent=self.staticBox_FreqOffset, pos=wx.Point(24, 124),
              #size=wx.Size(72, 24), style=0, value=u'0')
        #self.textCtrl_vppm.Bind(wx.EVT_KILL_FOCUS, self.OnTextCtrl1KillFocus)
        #self.textCtrl_vppm.Bind(wx.EVT_TEXT, self.OnTextCtrl1Text,
              #id=wxID_WXFRAME1TEXTCTRL_VPPM)
        #self.textCtrl_vppm.Enable(False)
        
        self.staticText_freqoffset = wx.StaticText(id=wxID_WXFRAME1STATICTEXT_VPPM,
              label=u'PracticalFreqOffset', name='staticText3',
              parent=self.staticBox_FreqOffset, pos=wx.Point(16, 68), size=wx.Size(120, 24),
              style=0)
        
        #============================================================================

        self.staticBox_button = wx.StaticBox(id=wxID_WXFRAME1STATICBOX_BUTTONS,
              label=u'Buttons', name='staticBox2', parent=self.staticInitSettings,
              pos=wx.Point(405, 15), size=wx.Size(183, 184), style=0)
        
        self.button_default = wx.Button(id=wxID_WXFRAME1BUTTON_BUTTON_DEFAULT, label=u'Default',
              name='Default', parent=self.staticBox_button, pos=wx.Point(16, 25),
              size=wx.Size(75, 30), style=0)
        self.button_default.Bind(wx.EVT_BUTTON, self.OnButton_Default,
              id=wxID_WXFRAME1BUTTON_BUTTON_DEFAULT)
        self.button_default.SetToolTipString("Reset all the settings and values to the default")

        #self.button_apply = wx.Button(id=wxID_WXFRAME1BUTTON_APPLY, label=u'Apply',
              #name='Apply', parent=self.staticBox_button, pos=wx.Point(16, 60),
              #size=wx.Size(75, 30), style=0)
        #self.button_apply.Bind(wx.EVT_BUTTON, self.OnButton_Apply,
              #id=wxID_WXFRAME1BUTTON_APPLY)
        #self.button_apply.SetToolTipString("Apply all the settings to the current param table")
        
        self.button_gen = wx.Button(id=wxID_WXFRAME1BUTTON_GEN, label=u'GenInitBin',
              name='Apply', parent=self.staticBox_button, pos=wx.Point(16, 60),
              size=wx.Size(75, 30), style=0)
        self.button_gen.Bind(wx.EVT_BUTTON, self.OnButton_gen,
              id=wxID_WXFRAME1BUTTON_GEN)  
        self.button_gen.SetToolTipString("Generate init_data.bin according to the current param table")
        
        self.button_load = wx.Button(id=wxID_WXFRAME1BUTTON_LOAD, label=u'LoadInitBin',
                        name='Load', parent=self.staticBox_button, pos=wx.Point(16, 95),
                        size=wx.Size(75, 30), style=0)
        self.button_load.Bind(wx.EVT_BUTTON, self.OnButton_load,
              id=wxID_WXFRAME1BUTTON_LOAD)    
        self.button_load.SetToolTipString("Load a init_data.bin file values to the param table below.  \
                                           \rYou can modify the settings based on the params we given for your module")
#============================================================================
        self.radioBox_Crystal = wx.RadioBox(choices=['40Mhz', '26Mhz', '24Mhz'],
            id=wxID_WXFRAME1RADIOBOX_CRYSTAL, label=u'CrystalFreq', majorDimension=1,
            name='radioBox1', parent=self.staticInitSettings, pos=wx.Point(8, 200),
            size=wx.Size(112, 130), style=wx.RA_SPECIFY_COLS)
        self.radioBox_Crystal.Bind(wx.EVT_RADIOBOX, self.OnRadioBox_FREQ,
              id=wxID_WXFRAME1RADIOBOX_CRYSTAL)
        self.radioBox_Crystal.SetToolTipString("To select the crystal freq you are using.This will decide the system clock during the module is booting up. \
                                                \rIf you are using a 40M crystal, the booting uart output is at 115200bps,and 74880 for 26M    \
                                                \rThis param must be set correctly, or wifi channel will be mismatched")

 #============================================================================

        self.staticBox_TOUTBOX = wx.StaticBox(id=wxID_WXFRAME1STATICBOX_TOUTBOX,
              label=u'TOUT PinConf', name='staticBox4', parent=self.staticInitSettings,
              pos=wx.Point(123, 200), size=wx.Size(136, 130), style=0)

        self.radioButton_TOUTADC = wx.RadioButton(id=wxID_WXFRAME1RADIOBUTTON_TOUTADC,
              label=u'TOUT_ADC_EN', name='radioButton1', parent=self.staticBox_TOUTBOX,
              pos=wx.Point(16, 24), size=wx.Size(104, 17), style=0)
        self.radioButton_TOUTADC.SetValue(True)
        self.radioButton_TOUTADC.Bind(wx.EVT_RADIOBUTTON,
              self.OnRadioButton1Radiobutton, id=wxID_WXFRAME1RADIOBUTTON_TOUTADC)
        self.radioButton_TOUTADC.SetToolTipString("Config the TOUT(pin6) pin as an external ADC  \
                                                   \rThe measure range is 0v - 1.0v  \
                                                   \ryou need to enter the practical power supply on pin3 and pin4(1.8v-3.6v) \
                                                   \rerror range: +-0.2v")
        

        self.radioButton_TOUTVDD = wx.RadioButton(id=wxID_WXFRAME1RADIOBUTTON_TOUTVDD,
              label=u'TOUT_VDD_EN', name='radioButton2', parent=self.staticBox_TOUTBOX,
              pos=wx.Point(16, 80), size=wx.Size(104, 17), style=0)
        self.radioButton_TOUTVDD.SetValue(True)
        self.radioButton_TOUTVDD.Bind(wx.EVT_RADIOBUTTON,
              self.OnRadioButton2Radiobutton, id=wxID_WXFRAME1RADIOBUTTON_TOUTVDD)
        self.radioButton_TOUTVDD.SetToolTipString("Config the TOUT(pin6) pin as internal voltage measurement  \
                                                   \rSo that you can measure the power supply voltage on pin3 and pin4 \
                                                   \rCAUSION: IN THIS MODE , TOUT(PIN6) MUST BE FLOATING!!")

        self.textCtrl_ADCVDD = wx.TextCtrl(id=wxID_WXFRAME1TEXTCTRL_ADCVDD, name=u'VDD',
              parent=self.staticBox_TOUTBOX, pos=wx.Point(64, 48), size=wx.Size(40, 24),
              style=0, value=u'3.3')
        self.textCtrl_ADCVDD.Bind(wx.EVT_KILL_FOCUS, self.OnVDDKillFocus)

        self.staticText_TOUTV = wx.StaticText(id=wxID_WXFRAME1STATICTEXT_TOUTV,
              label=u'V', name='staticText4', parent=self.staticBox_TOUTBOX,
              pos=wx.Point(112, 52), size=wx.Size(10, 18), style=0)

        self.staticText_TOUTVDD = wx.StaticText(id=wxID_WXFRAME1STATICTEXT_TOUTVDD,
              label=u'VDD:', name='staticText5', parent=self.staticBox_TOUTBOX,
              pos=wx.Point(32, 52), size=wx.Size(29, 18), style=0)
 


#============================================================================
        self.grid1 = wx.grid.Grid(id=wxID_WXPANEL1GRID1, name='grid1',
              parent=self, pos=wx.Point(0, 350), size=wx.Size(600, 430), style=0)
        self.grid1.EnableGridLines(True)
        self.grid1.SetDefaultCellOverflow(False)
        #self.grid1.Enable(False)
        #self.grid1.row
        
        #self.grid1.SetColSizes(wx.Size(1,2))

    def __init__(self, parent):
        self._init_ctrls(parent)

        # Either CreateGrid or SetTable must be manually added in your code
        # before you populate the grid
        self.grid1.CreateGrid(128, 3)
        #self.grid1.SetColSize(2,200)
        #self.grid1.SetAutoLayout(True)
        self.table = TestTable()
        self.grid1.SetTable(self.table, True)  
        
        self.grid1.SetColSize(0,50)
        self.grid1.SetColSize(2,210)
        self.grid1.ForceRefresh()
        
        #self.checkBox1.Enable(False)
        #self.textCtrl1.Enable(False)
        
        self.OnLoad()
        #self.grid1.SelectColumns()
        #self.Parent.
        self.tx_spin_list = [self.spinCtrl1,self.spinCtrl2,self.spinCtrl3,
                             self.spinCtrl4,self.spinCtrl5,self.spinCtrl6,]
        self.default_tx_power = [20.5,19.5,18.5,17,16,14]
        self.v_rf_gain = [0,-2.5,-6,-8.5,-11.5,-14,-17.5,-23]
        #self.v_digital_gain = [0,-0
        self.apply_all()
        
    def OnRadioButton1Radiobutton(self,event):
        print "test on radio 1"
        self.textCtrl_ADCVDD.Enable(True)
        self.apply_all()
        pass
    
    def OnRadioButton2Radiobutton(self,event):
        print "test on radio 2"
        self.textCtrl_ADCVDD.Enable(False)
        self.apply_all()
        pass
    
    def OnVDDKillFocus(self,event):
        print "VDD kill focus "
        self.apply_all()
        pass
        
        
    def update_tx_power(self,event):
        #print "test spin cb"
        #if self.checkBox_BackOffEn.GetValue()==True:
        for i in range(len(self.tx_spin_list)):
            if self.checkBox_BackOffEn.GetValue()==True:
                v_backoff = self.spinCtrl_backoff.GetValue()
            else:
                v_backoff = 0
                
            if self.checkBox_LimitEn.GetValue()==True:
                v_limit_up = self.spinCtrl_powerlimit.GetValue()
            else:
                v_limit_up = 100000
                
            
            v_set = v_backoff+self.default_tx_power[i]
            if v_set > v_limit_up:
                v_set = v_limit_up
                
            if self.checkBox_BackOffEn.GetValue()==True:
                if v_set<12:
                    v_set =12
                    
            #print "test vset :",v_set
            spin_item = self.tx_spin_list[i]
            spin_item.SetValue( v_set )
            
        
        self.apply_all()
        pass
    
    
    def OnCheckBox_BackOffEn(self,event):
        print "tx backoff : ",self.checkBox_BackOffEn.GetValue()
        if self.checkBox_BackOffEn.GetValue()==True:
            self.spinCtrl_backoff.Enable(True)
            self.checkBox_LowPowerEn.SetValue(False)
            self.checkBox_LowPowerEn.Enable(False)
            self.spinCtrl_lowpower.Enable(False)
        else:
            self.spinCtrl_backoff.Enable(False)
            if self.checkBox_LimitEn.GetValue()==False:
                self.checkBox_LowPowerEn.Enable(True)
            
        self.update_tx_power(None)
        self.apply_all()
        pass

    def OnCheckBox_LimitEn(self,event):
        print "tx limit:",self.checkBox_LimitEn.GetValue()
        if self.checkBox_LimitEn.GetValue()==True:
            self.spinCtrl_powerlimit.Enable(True)
            self.checkBox_LowPowerEn.SetValue(False)
            self.checkBox_LowPowerEn.Enable(False)
            self.spinCtrl_lowpower.Enable(False)
        else:
            self.spinCtrl_powerlimit.Enable(False)
            if self.checkBox_LimitEn.GetValue()==False:
                self.checkBox_LowPowerEn.Enable(True)            
            
        self.update_tx_power(None)
        self.apply_all()
        pass
    def OnRadioBox_FREQ(self,event):
        print "crystal freq,",self.radioBox_Crystal.GetSelection()
        #self.table.SetValue(48,4,int( self.radioBox_Crystal.GetSelection()) )
        self.apply_all()
        pass
    
    def OnRadioBox_RFInit(self,event):
        #print "rf init ratio box"
        rfinit_opt = self.radioBox_RFInit.GetSelection()
        if rfinit_opt<2:
            pass
        elif rfinit_opt==2:
            rfinit_opt = 3
            
        self.table.SetValue(114, 4, rfinit_opt)
        #print "crystal freq,",self.radioBox_Crystal.GetSelection()
        #self.table.SetValue(48,4,int( self.radioBox_Crystal.GetSelection()) )
        self.apply_all()
        pass
    
    
    def OnCheckBox1Checkbox(self, event):
        #print "test :",self.checkBox_SetFreqEn.GetValue()
        if self.checkBox_SetFreqEn.GetValue()==True:
            self.spinCtrl_Freq.Enable(True)
            self.checkBox_SetAutoCal.SetValue(False)
            #self.textCtrl_vppm.Enable(False)
        else:
            self.spinCtrl_Freq.Enable(False)
            self.checkBox_SetAutoCal.SetValue(False)
            #self.textCtrl_vppm.Enable(False)  
        self.apply_all()
        #event.Skip()
        
        
    def OnCheckBox_FreqAuto(self, event):
        #print "test :",self.checkBox_SetFreqEn.GetValue()
        if self.checkBox_SetAutoCal.GetValue()==True:
            self.checkBox_SetFreqEn.SetValue(False)
            self.spinCtrl_Freq.Enable(False)
            #self.textCtrl_vppm.Enable(False)
        else:
            self.checkBox_SetFreqEn.SetValue(False)
            self.spinCtrl_Freq.Enable(False)
            #self.textCtrl_vppm.Enable(False)  
        self.apply_all()
        #event.Skip()    

    def OnSpinCtrl1Spin(self, event):
        self.update_tx_power(None)
        self.apply_all()
        event.Skip()

    def OnTextCtrl1KillFocus(self, event):
        self.apply_all()
        event.Skip()

    def OnTextCtrl1Text(self, event):
        self.apply_all()
        event.Skip()

    def OnButton_Default(self, event):
        self.reinit()
        self.table.data =  rx.get_table(sheetName='Sheet1',tname='./init_data/ESP8266_RF_init.xls')
        self.grid1.ForceRefresh()
        #self.apply_all()
        event.Skip()

    def OnButton_Apply(self, event):
        self.apply_all()
        event.Skip()
        
    def OnCheckBox_LowPowerEn(self,event):
        
        #print "test : ",self.checkBox_LowPowerEn.GetValue()
        if self.checkBox_LowPowerEn.GetValue() == True:
            self.spinCtrl_lowpower.Enable(True)
            self.checkBox_BackOffEn.SetValue(False)
            self.checkBox_LimitEn.SetValue(False)
            self.checkBox_BackOffEn.Enable(False)
            self.checkBox_LimitEn.Enable(False)
            self.spinCtrl_backoff.Enable(False)
            self.spinCtrl_powerlimit.Enable(False)
            #self.choice_RFGAIN.Enable(True)
            #self.spinCtrl_DIGITALGAIN.Enable(True)
            for i in range(len(self.tx_spin_list)):
                
                self.tx_spin_list[i].SetValue( self.spinCtrl_lowpower.GetValue() ) 
            v_target = self.spinCtrl_lowpower.GetValue()
            #print "target:",v_target
            vtmp = self.v_rf_gain[0]
            #print "vtmp:",vtmp
            for v in self.v_rf_gain:
                
                if (self.default_tx_power[-1]+v)<v_target:
                    
                    #print "flag 1, target:",v_target
                    #print "default:",self.default_tx_power[-1]
                    break
                else:
                    #print "flag 2:",vtmp
                    vtmp = v
            #print "test vtmp: ",vtmp
            self.choice_RFGAIN.SetSelection( self.v_rf_gain.index(vtmp) )
            #print "test rf gain selection:",self.v_rf_gain.index(vtmp)
            self.spinCtrl_DIGITALGAIN.SetValue( (-1)*(self.default_tx_power[-1]+vtmp-v_target) )

                
                
        else:
            self.spinCtrl_lowpower.Enable(False)
            self.checkBox_BackOffEn.Enable(True)
            self.checkBox_LimitEn.Enable(True)            
            #self.choice_RFGAIN.Enable(False)
            #self.spinCtrl_DIGITALGAIN.Enable(False)    
            for i in range(len(self.tx_spin_list)):
                self.tx_spin_list[i].SetValue( self.default_tx_power[i] )            
            
        self.apply_all()
        pass
        
    def reinit(self):
        self.spinCtrl1.SetValue(20.5)
        self.spinCtrl2.SetValue(19.5)
        self.spinCtrl3.SetValue(18.5)
        self.spinCtrl4.SetValue(17)
        self.spinCtrl5.SetValue(16)
        self.spinCtrl6.SetValue(14)
        #self.spinCtrl1.SetValue(20.5)
        self.choice_RFGAIN.SetSelection(0)
        self.spinCtrl_DIGITALGAIN.SetValue(0)
        
        #self.radioBox1.SetStringSelection("EN_VDD33")
        self.radioButton_TOUTADC.SetValue(True)
        self.radioButton_TOUTVDD.SetValue(False)
        self.textCtrl_ADCVDD.SetValue("3.3")
        
        
        self.checkBox_SetFreqEn.SetValue(False)
        #self.textCtrl_vppm.SetValue("0")
        self.spinCtrl_Freq.SetValue(0)
        self.spinCtrl_Freq.Enable(False)
        
        self.checkBox_LowPowerEn.SetValue(False)
        self.checkBox_LowPowerEn.Enable(True)
        self.checkBox_LimitEn.SetValue(False)
        self.checkBox_LimitEn.Enable(True)
        self.checkBox_BackOffEn.SetValue(False)
        self.checkBox_BackOffEn.Enable(True)
        
        self.spinCtrl_backoff.Enable(False)
        self.spinCtrl_backoff.SetValue(12)
        self.spinCtrl_lowpower.Enable(False)
        self.spinCtrl_lowpower.SetValue(0)
        self.spinCtrl_powerlimit.Enable(False)
        self.spinCtrl_powerlimit.SetValue(20.5)
        
        
        
        self.radioBox_Crystal.SetSelection(0)
        #self.checkBox_SetFreqEn.SetValue(False)
        #self.OnCheckBox_LowPowerEn(None)
        #self.OnCheckBox1Checkbox(None)
        
        self.radioBox_RFInit.SetSelection(0)
        self.checkBox_SetAutoCal.SetValue(True)

        
    def get_target_power_list(self):
        return [self.spinCtrl1.GetValue()*4,
                self.spinCtrl2.GetValue()*4,
                self.spinCtrl3.GetValue()*4,
                self.spinCtrl4.GetValue()*4,
                self.spinCtrl5.GetValue()*4,
                self.spinCtrl6.GetValue()*4,
                ]
                
    def OnRadioBox1Radiobox(self,event):
        if self.radioBox1.GetStringSelection() == "EN_ADC":
            self.textCtrl_vdd.Enable(True)
        else:
            self.textCtrl_vdd.Enable(False)
        self.apply_all()
            
    def OnButton_gen(self,event):
        init_data_list = [x[4] for x in self.table.data]
        #for i in range(len(self.table.data));
        print "test init data list:"
        print init_data_list
        rx.make_bin(init_data_list,"./init_data/esp_init_data_setting.bin",128)
        #os.system("init_data/")
        os.startfile('init_data')
        self.apply_all()
        
    def OnButton_load(self,event):
        signed_list = range(2,26)+range(30,34)
        print "test load..."
        try:
            path = self.Parent.Parent.panelTest.panel_path.default_path
        except:
            print "get path error"
            path = './'
        bin_path = self.set_file_path(path)

        print "test bin path:",bin_path
        if not bin_path == "":
            f = open(bin_path,'rb')
            data = f.read(128)
            print "test data len:",len(data)
            f.close()
            print "test data:"
            print data ,' ; ', type(data[1])
            data = struct.unpack("128B",data)
            #print "dlist: ",dlist
            dlist=[]
            for i in range(len(data)):
                if data[i]>127 and i in signed_list:
                    dtmp = data[i]-256
                else:
                    dtmp = data[i]
                
                dlist.append(dtmp)
            
            for i in range(len(dlist)):
                self.table.SetValue(i,4,int(dlist[i]))
            self.grid1.ForceRefresh()
            print "test dlist : ",
            print dlist
            
            
            
        pass
        
    def set_file_path(self,default_path):
        wildcard = "Binary file (*.bin)|*.bin|" \
                "Image file (*.img)|*.img|" \
                "All files (*.*)|*.*"
        dialog = wx.FileDialog(None, "Choose a file", default_path,#os.getcwd(), 
                "", wildcard, wx.OPEN)
        binpath = ""
        if dialog.ShowModal() == wx.ID_OK:
            binpath=dialog.GetPath()
            #tc.SetValue(binpath )
            #tc.SetBackgroundColour((10,255,10,10))
            #if ".bin" in binpath or ".img" in binpath:
                #pp.default_path=  os.path.split(binpath)[0]
            #print binpath
        dialog.Destroy() 
        return binpath
    
    def OnLoad(self):
        f=open("tool_config.txt",'r')
        lines = f.readlines()
        f.close()
        for line in lines:
            if "TARGETPOWER1" in line:
                vtmp= int( float( line.strip("\n").split(":")[1] )*10)/10.0
                self.spinCtrl1.SetValue(vtmp)
            elif "TARGETPOWER2" in line:
                vtmp= int( float( line.strip("\n").split(":")[1] )*10)/10.0
                self.spinCtrl2.SetValue(vtmp)  
            elif "TARGETPOWER2" in line:
                vtmp= int( float( line.strip("\n").split(":")[1] )*10)/10.0
                self.spinCtrl2.SetValue(vtmp)                  
            elif "TARGETPOWER3" in line:
                vtmp= int( float( line.strip("\n").split(":")[1] )*10)/10.0
                self.spinCtrl3.SetValue(vtmp)          
            elif "TARGETPOWER4" in line:
                vtmp= int( float( line.strip("\n").split(":")[1] )*10)/10.0
                self.spinCtrl4.SetValue(vtmp)      
            elif "TARGETPOWER5" in line:
                vtmp= int( float( line.strip("\n").split(":")[1] )*10)/10.0
                self.spinCtrl5.SetValue(vtmp)  
            elif "TARGETPOWER6" in line:
                vtmp= int( float( line.strip("\n").split(":")[1] )*10)/10.0
                self.spinCtrl6.SetValue(vtmp)  
                
            elif "LOWPOWEREN" in line:
                vtmp = int( line.strip("\n").split(":")[1] )
                self.checkBox_LowPowerEn.SetValue(vtmp)
            elif "RFGAIN" in line:
                vtmp = int( float(line.strip("\n").split(":")[1])*10 )/10.0
                self.choice_RFGAIN.SetSelection(vtmp)
            elif "DIGITALGAIN" in line:
                vtmp = int(line.strip("\n").split(":")[1])
                self.spinCtrl_DIGITALGAIN.SetValue(vtmp)
            elif "TARGETLOWPOWER" in line:
                vtmp = float(line.strip("\n").split(":")[1])
                self.spinCtrl_lowpower.SetValue(vtmp)
                
            elif "BACKOFFEN" in line:
                vtmp = int( line.strip("\n").split(":")[1] )
                self.checkBox_BackOffEn.SetValue(vtmp)            
            elif "BACKOFFVAL" in line:
                vtmp = float(line.strip("\n").split(":")[1])
                self.spinCtrl_backoff.SetValue(vtmp)
                
            elif "LIMITEN" in line:
                vtmp = int( line.strip("\n").split(":")[1] )
                self.checkBox_LimitEn.SetValue(vtmp)            
            elif "LIMITVAL" in line:
                vtmp = float(line.strip("\n").split(":")[1])
                self.spinCtrl_powerlimit.SetValue(vtmp)
                
                
            elif "SETFREQEN" in line:
                vtmp = int(line.strip("\n").split(":")[1])
                self.checkBox_SetFreqEn.SetValue(vtmp)
            elif "AUTOCALEN" in line:
                vtmp = int(line.strip("\n").split(":")[1])
                self.checkBox_SetAutoCal.SetValue(vtmp)
            elif "FREQOFFSET" in line:
                vtmp = int(line.strip("\n").split(":")[1])
                self.spinCtrl_Freq.SetValue(vtmp)   
                
            elif "TOUTADC" in line:
                vtmp = int(line.strip("\n").split(":")[1])
                self.radioButton_TOUTADC.SetValue(vtmp)
            elif "TOUTVDD" in line:
                vtmp = int(line.strip("\n").split(":")[1])
                self.radioButton_TOUTVDD.SetValue(vtmp)   
                #self.radioBox1.SetSelection(vtmp)  
            elif "VDD" in line:
                vtmp = line.strip("\n").split(":")[1]
                self.textCtrl_ADCVDD.SetValue(vtmp)
                
            elif "CRYFREQ" in line:
                vtmp = int(line.strip("\n").split(":")[1])
                self.radioBox_Crystal.SetSelection(vtmp)
            elif "RFINITMODE" in line:
                vtmp = int(line.strip("\n").split(":")[1])
                self.radioBox_RFInit.SetSelection(vtmp)            
            
                
                
                
    def OnSave(self):
        print "save RF INIT settings..."
        rf_init_conf =""
        rf_init_conf+="TARGETPOWER1:%f\n"%self.spinCtrl1.GetValue()
        rf_init_conf+="TARGETPOWER2:%f\n"%self.spinCtrl2.GetValue()
        rf_init_conf+="TARGETPOWER3:%f\n"%self.spinCtrl3.GetValue()
        rf_init_conf+="TARGETPOWER4:%f\n"%self.spinCtrl4.GetValue()
        rf_init_conf+="TARGETPOWER5:%f\n"%self.spinCtrl5.GetValue()
        rf_init_conf+="TARGETPOWER6:%f\n"%self.spinCtrl6.GetValue()
        
        rf_init_conf+="LOWPOWEREN:%d\n"%self.checkBox_LowPowerEn.GetValue()
        rf_init_conf+="RFGAIN:%d\n"%self.choice_RFGAIN.GetSelection()
        rf_init_conf+="DIGITALGAIN:%d\n"%self.spinCtrl_DIGITALGAIN.GetValue()
        rf_init_conf+="TARGETLOWPOWER:%02f\n"%self.spinCtrl_lowpower.GetValue()
        
        rf_init_conf+="BACKOFFEN:%d\n"%self.checkBox_BackOffEn.GetValue()
        rf_init_conf+="BACKOFFVAL:%02f\n"%self.spinCtrl_backoff.GetValue()
        #rf_init_conf+=
        
        rf_init_conf+="LIMITEN:%d\n"%self.checkBox_LimitEn.GetValue()
        rf_init_conf+="LIMITVAL:%02f\n"%self.spinCtrl_powerlimit.GetValue()
        

        rf_init_conf+="SETFREQEN:%d\n"%self.checkBox_SetFreqEn.GetValue()
        rf_init_conf+="AUTOCALEN:%d\n"%self.checkBox_SetAutoCal.GetValue()
        rf_init_conf+="FREQOFFSET:%d\n"%self.spinCtrl_Freq.GetValue()
        
        rf_init_conf+="TOUTADC:%d\n"%self.radioButton_TOUTADC.GetValue()
        rf_init_conf+="TOUTVDD:%d\n"%self.radioButton_TOUTVDD.GetValue()
        rf_init_conf+="VDD:%s\n"%self.textCtrl_ADCVDD.GetValue()
        
        rf_init_conf+="CRYFREQ:%d\n"%self.radioBox_Crystal.GetSelection()
        rf_init_conf+="RFINITMODE:%d\n"%self.radioBox_RFInit.GetSelection()
        
        
        
        
        f=open("tool_config.txt",'a')
        f.write(rf_init_conf)
        f.close()
        
        
        
        
    def apply_all(self):
        #===========SET TARGET POWER===================
        #setting done at the click action
        #wait........
        if self.checkBox_LowPowerEn.GetValue()==True:
            for i in range(len(self.default_tx_power)):
                self.table.SetValue(34+i,4, int(self.default_tx_power[i]*4))            
        else:
            target_power = self.get_target_power_list()
            #print "test type:",type(target_power[0])
            for i in range(len(target_power)):
                self.table.SetValue(34+i,4,int(target_power[i]))
        #===================================================
        
        #===========SET TX POWER GAIN===================
        if self.checkBox_LowPowerEn.GetValue() == True:
            #print "test 1:",self.choice_RFGAIN.GetStringSelection(),type(self.choice_RFGAIN.GetStringSelection())
            #print "test 2:",self.spinCtrl_DIGITALGAIN.GetValue(),type(self.spinCtrl_DIGITALGAIN.GetValue())
            digital_gain = int(self.spinCtrl_DIGITALGAIN.GetValue() * (-4))
            rf_gain = RF_GAIN_DICT[self.choice_RFGAIN.GetStringSelection()]
            print "Digital gain:",digital_gain
            print "RF gain:",rf_gain
            self.table.SetValue(93,4,1)
            self.table.SetValue(94,4,rf_gain)
            self.table.SetValue(95,4,digital_gain)
            
            
        else:
            self.table.SetValue(93,4,0)
            self.table.SetValue(94,4,0xf)
            self.table.SetValue(95,4,0)
        #===============================================
        #===========SET FREQ FORCE OFFSET===============
        if self.checkBox_SetFreqEn.GetValue()==True:
            if self.checkBox_SetAutoCal.GetValue()==True:
                self.table.SetValue(112,4,6)
                self.table.SetValue(113,4,0)
            else:
                self.table.SetValue(112,4,7)
                freq_ofst = self.spinCtrl_Freq.GetValue()
                #print "test freq ofst: ",freq_ofst,type(freq_ofst)
                freq_val = (256-freq_ofst/8)
                
                self.table.SetValue(113,4,freq_val)
        elif self.checkBox_SetAutoCal.GetValue()==True:
            self.table.SetValue(112,4,3)
            self.table.SetValue(113,4,0)
        else:
            
            self.table.SetValue(112,4,0)
            self.table.SetValue(113,4,0)            
        #===============================================
        #===========SET CRYSTAL=====================
        
        crystal = self.radioBox_Crystal.GetSelection()
        self.table.SetValue(48,4,crystal)
        
        
        
        
        #===========SET TOUT CONFIG=====================
        
        #if self.radioBox1.GetStringSelection() == "EN_VDD33":
        if self.radioButton_TOUTVDD.GetValue()==True:
            #print "tout as vdd33"
            self.table.SetValue(107,4,0xff)
        else:
            print "tout as adc"
            #vdd = self.textCtrl_vdd.GetValue()
            vdd = self.textCtrl_ADCVDD.GetValue()
            try:
                vdd = float(vdd)
            except:
                self.textCtrl_ADCVDD.SetValue("3.0")
                vdd = 3.0
            
            if vdd>3.6:
                vdd = 3.6
            elif vdd<1.8:
                vdd = 1.8
                
            self.table.SetValue(107,4,int(vdd*10))
                
        
        #===============================================
        #RF INIT
        #------------
        rfinit_opt = self.radioBox_RFInit.GetSelection()
        
        if rfinit_opt<2:
            pass
        elif rfinit_opt==2:
            rfinit_opt = 3
            
            
        self.table.SetValue(114, 4, rfinit_opt)        
        
        #===============================================
        
        #data_tmp = []
        #data_tmp+=self.table.data
        #data_tmp[

        self.grid1.ForceRefresh()   
        print "RF option applied..."
        pass
        
        
        
        
        
class TestTable(wx.grid.PyGridTableBase):
    def __init__(self):
        wx.grid.PyGridTableBase.__init__(self)
        #self.data = [ [1, 1,"111111111111"],
                      #[2, 2,"f222222222222222222222"] ,
                      #[3, 3,"tttttt33333333333333"] ,
                      #[4, 4,"55555555555553444444444444"] ,
                      #]
        self.data = rx.get_table(sheetName='Sheet1',tname='./init_data/ESP8266_RF_init.xls')
        #self.base_SetColLabelValue(1,'11')
        #self.base_SetColLabelValue(2,'33')
        self.SetColLabelValue(1,"11")
        self.SetColLabelValue(2,"33")
        

# these five are the required methods
    def GetNumberRows(self):
        return len(self.data)

    def GetNumberCols(self):        
        return len(self.data[0])
    
    def IsEmptyCell(self, row, col):        
        return True
    
    def GetValue(self, row, col):        
        return self.data[row][col]
    
    def SetValue(self, row, col, value):  
        #print "test row : ",row
        #print "test col : ",col
        #print "self.data: ",self.data
        #print "test row :",self.data[row]
        #print "test cell: ",self.data[row][col]

        
        self.data[row][col] = value
        #self.data[row,col] = value
        pass
 

if __name__ == '__main__':
    app = wx.PySimpleApp()
    wx.InitAllImageHandlers()
    frame = create(None)
    frame.Show()
    app.MainLoop()
