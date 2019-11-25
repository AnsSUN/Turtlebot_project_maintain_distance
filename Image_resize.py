#!/usr/bin/python
from PIL import Image
import os, sys

path = "C:/Users/CAV/Turtle_bot_pro/Images/"
path_save = "C:/Users/CAV/Turtle_bot_pro/Converted/"
dirs = os.listdir( path )

def resize():
    for item in dirs:
        if os.path.isfile(path+item):
            im = Image.open(path+item)
            #f, e = os.path.splitext(path+item)
            g, h = os.path.splitext(path_save+item)
            #imResize = im.resize((64,64), Image.ANTIALIAS).
            #print(im)
            imResize = im.resize((64,64), Image.ANTIALIAS)
            imResize.save(g + '.jpg', 'JPEG', optimize=True)

resize()
