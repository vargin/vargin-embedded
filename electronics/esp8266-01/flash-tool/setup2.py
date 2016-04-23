# -*- coding:cp936-*-
from distutils.core import setup
import py2exe
import glob

includes = ["encodings","encodings.*"]

options = {"py2exe":
           {#"compressed":1,
            "optimize":2,
            "ascii":1,
            "includes":includes,
            "bundle_files":1,
            #'dll_excludes': ['libgdk-win32-2.0-0.dll','libgobject-2.0-0.dll','_imagingft.pyd']   ,  
            }}

#data_files = [(r'PIL', glob.glob(r'C:\Python26\Lib\site-packages\PIL\*.*')),
                   ## Because matplotlibrc does not have an extension, glob does not find it (at least I think that's why)
                    ## So add it manually here:
                  #(r'mpl-data', [r'C:\Python26\Lib\site-packages\matplotlib\mpl-data\matplotlibrc']),
                 #(r'mpl-data\images',glob.glob(r'C:\Python26\Lib\site-packages\matplotlib\mpl-data\images\*.*')),
                   #(r'mpl-data\fonts',glob.glob(r'C:\Python26\Lib\site-packages\matplotlib\mpl-data\fonts\*.*'))
                   #]
                   

setup(
    options = options,
    zipfile = None,
    console = [{"script":"wxFrame_test.py","icon_resources":[(1,"logo.ico")]}],
    #windows = [{"script":"frame_test.py","icon_resources":[(1,"logo.ico")]}],
    #windows = ["frame_test.py"],
    #includes = ["PIL"],
    #data_files=data_files,
    #version = "2015-02-02-v094",
    description = "ESP_IOT_FLASH_DOWNLOAD",
    name = "ESP_FLASH_DOWNLOAD_TOOL",
    )
