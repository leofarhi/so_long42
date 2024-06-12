from PIL import Image
import io
import itertools
import os
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

if __name__ == "__main__":
	img = Image.open('example.png')  # Remplacez par le chemin de votre image
	save(img, 'example.xpm')