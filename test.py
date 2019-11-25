# -*- coding: utf-8 -*-
"""
Created on Tue Mar 19 20:46:33 2019

@author: CAV
"""


from PIL import Image
import os, sys

path = "C:/Users/CAV/Turtle_bot_pro/Images/"
path_save = "C:/Users/CAV/Turtle_bot_pro/Converted/"
dirs = os.listdir( path )

for item in dirs:
    if os.path.isfile(path+item):
        img = Image.open(path+item)
        g, h = os.path.splitext(path_save+item)
        new_img = img.resize((64,64))
        new_img.save(g+".png", "PNG", optimize=True)h