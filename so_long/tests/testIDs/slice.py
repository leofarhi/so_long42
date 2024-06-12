from PIL import Image
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

def slice(name):
    # Open the image
    image_path = name+".png"  # Replace with the actual image path
    image = Image.open(image_path)

    # Create the "slice" folder if it doesn't exist
    folder_path = "tiles/"+name  # Replace with the desired folder path
    os.makedirs(folder_path, exist_ok=True)

    # Slice the image into tiles
    tile_size = 24
    width, height = image.size
    for y in range(0, height, tile_size):
        for x in range(0, width, tile_size):
            tile = image.crop((x, y, x + tile_size, y + tile_size))
            tile.save(os.path.join(folder_path, f"tile_{x}_{y}.png"))

lst = os.listdir()
for i in lst:
    if i.endswith(".png"):
        slice(i[:-4])

print("Image sliced and tiles saved successfully!")