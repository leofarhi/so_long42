from PIL import Image, ImageFont, ImageDraw

import io
import itertools
import os, sys
import warnings

_XPM = "/* XPM */"
(_WANT_XPM, _WANT_NAME, _WANT_VALUES, _WANT_COLOR, _WANT_PIXELS, _DONE) = (
    "WANT_XPM", "WANT_NAME", "WANT_VALUES", "WANT_COLOR", "WANT_PIXELS", "DONE"
)
_CODES = "".join((chr(x) for x in range(32, 127) if chr(x) not in '\\"'))


def save(image, filename):
    """save an XPM file"""
    name = os.path.splitext(os.path.basename(filename))[0]
    palette, cpp = _palette_and_cpp(image)
    with open(filename, "w", encoding="ascii") as file:
        _write_header(image, file, name, cpp, len(palette))
        _write_palette(file, palette)
        _write_pixels(image, file, palette)


def _palette_and_cpp(image):
    colors = set()
    transparent = (0, 0, 0, 0)
    for color in image.getdata():
        if color == transparent:
            name = "None"  # special-case transparent
        else:  # strip off alpha
            name = "#{:02X}{:02X}{:02X}".format(color[0], color[1], color[2])
        colors.add((color, name))
    cpp = 1
    while True:
        if len(colors) <= len(_CODES) ** cpp:
            break
        cpp += 1
    colors = sorted(colors, reverse=True)
    palette = {}
    for code in itertools.product(_CODES, repeat=cpp):
        if not colors:
            break
        color, name = colors.pop()
        palette[color] = ("".join(code), name)
    return palette, cpp


def _write_header(image, file, name, cpp, colors):
    file.write("{}\nstatic char *{}[] = {{\n".format(_XPM, name))
    file.write('"{} {} {} {}'.format(image.width, image.height, colors, cpp))
    x, y = None, None
    # Add hot spot information if available
    if "x_hot" in image.info and "y_hot" in image.info:
        x = image.info["x_hot"]
        y = image.info["y_hot"]
    if x is not None and y is not None:
        file.write(" {} {}".format(x, y))
    file.write('",\n')


def _write_palette(file, palette):
    for code, name in sorted(palette.values(), key=lambda v: " " if v[1] == "None" else v[1]):
        file.write('"{}\tc {}",\n'.format(code, name))  # \t is nicer in vim


def _write_pixels(image, file, palette):
    pixels = list(image.getdata())
    for y in range(image.height):
        file.write('"')
        for x in range(image.width):
            code = palette[pixels[y * image.width + x]][0]
            file.write(code)
        file.write('",\n')
    file.seek(file.tell() - 2, io.SEEK_SET)  # Get rid of spurious ,\n
    file.write("};\n")

def remove_alpha_right_bottom(image):
    width, height = image.size
    pixels = image.load()

    # Variables pour les dimensions de la nouvelle image
    max_x = width
    max_y = height

    # Trouver la dernière colonne sans alpha
    for x in range(width - 1, -1, -1):
        alpha_column = [pixels[x, y][3] for y in range(height)]
        if any(a > 0 for a in alpha_column):
            max_x = x + 1
            break

    # Trouver la dernière ligne sans alpha
    for y in range(height - 1, -1, -1):
        alpha_row = [pixels[x, y][3] for x in range(width)]
        if any(a > 0 for a in alpha_row):
            max_y = y + 1
            break

    # Découper l'image à la nouvelle taille
    cropped_image = image.crop((0, 0, max_x, max_y))
    return cropped_image

def convert(path, font_size):
    font_color = (255, 255, 255, 255) # RGBA White

    font = ImageFont.FreeTypeFont(path, font_size, encoding="unic")

    desired_characters = ""
    for i in range(32, 127):
        desired_characters += chr(i)

    def get_size(font, text):
        try:
            return font.getsize(text)
        except:
            return abs(font.getbbox(text)[0]) + abs(font.getbbox(text)[2]), abs(font.getbbox(text)[1]) + abs(font.getbbox(text)[3])

    #make a single image with all characters
    width, height = 0, 0
    for i in desired_characters:
        w, h = get_size(font, i)
        width += w
        height = max(height, h)
    img = Image.new("RGBA", (width + 1, height + 1))
    draw = ImageDraw.Draw(img)
    #draw.text((0, 1), str(desired_characters), font=font, fill=font_color)
    x = 0
    for i in range(32, 127):
        draw.text((x, 1), chr(i), font=font, fill=font_color)
        w, h = get_size(font, chr(i))
        x += w
    #clear the first row by alpha blending with white
    for i in range(width):
        draw.point((i, 0), fill=(0, 0, 0, 0))
    x = 0
    for i in range(32, 127):
        #draw on the first row a pixel to separate the characters
        w, h = get_size(font, chr(i))
        x += w
        #print(str(x)+" ",end="")
        #black pixel
        draw.point((x, 0), fill= (255, 255, 255, 255))
    #remove extra space on the right and bottom
    img = remove_alpha_right_bottom(img)
    return img

if len(sys.argv) != 3:
	print("Usage: python ttf2xpm.py <font.ttf> <size>")
	sys.exit(1)

img = convert(sys.argv[1], int(sys.argv[2]))
save(img, sys.argv[1].replace('.ttf', '.xpm'))