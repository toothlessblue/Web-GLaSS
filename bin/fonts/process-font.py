# TODO this but properly, in a seperate project in C++ that this project clones and then installs, so I can compile an executable and don't have to rely on ol' unreliable python

import argparse
import sys, os, shutil
from fontTools.ttLib import TTFont
from PIL import Image, ImageFont, ImageDraw

parser = argparse.ArgumentParser(description='Converts an input TTF font file to a texture and UV map, outputs a directory containing both files')
parser.add_argument('inputFilePath', metavar='Input File', nargs=1, help='TTF file to process')
parser.add_argument('-o', dest='outputFilePath', nargs=1, help='Where to save the output directory')
parser.add_argument('-r', '--resolution', default=1024, dest='resolution', nargs=1, help='Resolution of the output texture')
parser.add_argument('-O', '--overwrite', dest='overwrite', nargs='?', const=True, help='Delete the output directory if it already exists')

args = parser.parse_args()

# Prepare output directory
outputPath = args.outputFilePath or 'bin/fonts/out/'
dirPath = outputPath + args.inputFilePath[0].split('/')[-1] + '/'; 

if os.path.isdir(dirPath):
    if args.overwrite:
        print('Output directory already exists, overwriting')
        shutil.rmtree(dirPath)
    else:
        print('Output directory already exists, run with -O to override')
        sys.exit(os.EX_OSFILE)

os.mkdir(dirPath)

# Render font to texture
font = None

try:
    #font = ImageFont.truetype(args.inputFilePath[0], 15)
    font = TTFont(args.inputFilePath[0])
except FileNotFoundError:
    print('Input file does not exist.')
    sys.exit(os.EX_NOINPUT)

print(font.getGlyphID(font.getGlyphNames()[1]))
exit()


texture = Image.new('RGBA', (args.resolution, args.resolution))
draw = ImageDraw.Draw(texture)
# Save files
texture.save(dirPath + '/atlas.png')