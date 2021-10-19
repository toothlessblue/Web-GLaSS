# TODO this but properly, in a seperate project in C++ that this project clones and then installs, so I can compile an executable and don't have to rely on ol' unreliable python

import argparse;
import sys;

parser = argparse.ArgumentParser(description='Converts an input TTF font file to a texture and UV map, outputs a directory containing both files')
parser.add_argument('inputFilePath', metavar='Input File', nargs=1, help='TTF file to process')
parser.add_argument('-o', metavar='Output Dir', dest='outputFilePath', nargs=1, help='Where to save the output directory')

args = parser.parse_args()

inputData = None

try:
    with open(args.inputFilePath[0], "r") as inputFile:
        inputData = inputFile.read()
except FileNotFoundError:
    print('Input file does not exist.')
    sys.exit(1) # Couldn't find a "file not found" exit status - 1 is general catchall apparently

