from PIL import Image
import imageio
import os, sys
import xpm


os.chdir(os.path.dirname(os.path.abspath(__file__)))
    
def slice(path):
    dico = {}
    # Open the image
    image_path = path  # Replace with the actual image path
    image = Image.open(image_path)

    # Create the "slice" folder if it doesn't exist
    folder_path = "out"  # Replace with the desired folder path
    os.makedirs(folder_path, exist_ok=True)

    # Slice the image into tiles
    tile_size = 24
    width, height = image.size
    for y in range(0, height, tile_size):
        for x in range(0, width, tile_size):
            tile = image.crop((x, y, x + tile_size, y + tile_size))
            dico[(x//tile_size, y//tile_size)] = tile
    i = 0
    del dico[(0, 0)]
    del dico[(0, 1)]
    del dico[(1, 0)]
    del dico[(1, 1)]
    for key, tile in dico.items():
        x, y = key
        #tile.save(f"{folder_path}/{x}_{y}.png")
        nb = "00"
        if i < 10:
            nb = "0" + str(i)
        else:
            nb = str(i)
        xpm.save(tile, f"{folder_path}/{nb}.xpm")
        i += 1
            

slice("MV wall.png")
