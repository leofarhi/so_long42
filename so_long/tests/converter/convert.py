from PIL import Image
import os, sys
import xpm

os.chdir(os.path.dirname(os.path.abspath(__file__)))

lst = os.listdir("from")
for i in lst:
	os.makedirs(f"to", exist_ok=True)
	image = Image.open(f"from/{i}")
	xpm.save(image, f"to/{i}.xpm")