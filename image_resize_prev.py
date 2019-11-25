from PIL import Image
import os, sys

path = "C:\\Users\\CAV\\Turtle_bot_pro\\Images\\"
dirs = os.listdir( path )

for item in dirs:
    if os.path.isfile(path+item):
        im = Image.open(path+item)
        f, e = os.path.splitext(path+item)
        imResize = im.resize((64,64), Image.LANCZOS)
        imResize.save(path + "folder\\" + item + ".jpg", format="JPEG")
