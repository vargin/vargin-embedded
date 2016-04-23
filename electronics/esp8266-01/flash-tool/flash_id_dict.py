
SPI_FLASH_VENDOR_DICT = {
    0xA1 : "FM",
    0xC8 : "GD",
    0x9D : "ISSI",
    0xC2 : "KH",
    0xEF : "WB",
    }

SPI_FLASH_MODE_DICT = {
    0x40: "QUAD",
    0x30: "DUAL",
    }

SPI_FLASH_MODE_IDX = {
     "QUAD": 0,
     "DUAL": 2,
    }




SPI_FLASH_SIZE_DICT = {
    0x09 : "256Kbit",
    0x10 : "512Kbit",
    0x11 : "1Mbit",
    0x12 : "2Mbit",
    0x13 : "4Mbit",
    0x14 : "8Mbit",
    0x15 : "16Mbit",
    0x16 : "32Mbit",
    }   

SPI_FLASH_SIZE_IDX = {
    "4Mbit":0,
    "2Mbit":1,
    "8Mbit":2,
    "16Mbit":3,
    "32Mbit":4,
    }

RF_GAIN_DICT = {
    "0dB": 0xf,
    "-2.5dB":0xe,
    "-6dB":0xd,
    "-8.5dB":0x9,
    "-11.5dB":0xc,
    "-14dB":0x8,
    "-17.5dB":0x4,
    "-23dB":0x0,
    
    }
