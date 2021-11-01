# TODO this but properly, in a seperate project in C++ that this project clones and then installs, using FreeType

import argparse
import sys, os, shutil
from PIL import Image, ImageDraw
from tqdm import tqdm
import datetime
import math

class Kern0Table():
    def __init__(self, ttfReader, vertical, cross):
        self.swap = False
        self.offset = 0
        self.nPairs = 0
        self.map = {}
        self.oldIndex = -1

        self.swap = vertical and not cross or not vertical and cross
        self.file = ttfReader
        self.offset = ttfReader.position
        self.nPairs = ttfReader.getUint16()
        ttfReader.getUint16(); # searchRange
        ttfReader.getUint16(); # entrySelector
        ttfReader.getUint16(); # rangeShift

        for i in range(self.nPairs):
            left = ttfReader.getUint16()
            right = ttfReader.getUint16()
            value = ttfReader.getFword()
            self.map[(left << 16) | right] = value

        self.reset()

    def reset(self):
        self.oldIndex = -1

    def get(self, glyphIndex):
        x = 0
        if self.oldIndex >= 0:
            ch = (self.oldIndex << 16) | glyphIndex
            if ch in self.map:
                x = self.map[ch]

        self.oldIndex = glyphIndex
        if self.swap:
            return {
                'x': 0,
                'y': x
            }
        else:
            return {
                'x': x,
                'y': 0
            }

class TrueTypeCmap0():
    def __init__(self, ttfReader, length):
        self.format = 0
        self.array = []

        for i in range(256):
            glyphIndex = ttfReader.getUint8()
            self.array.append(glyphIndex)

    def map(self, charCode):
        if charCode >= 0 and charCode <= 255:
            return self.array[charCode]

        return 0

class TrueTypeCmap4():
    def __init__(self, ttfReader, length):
        self.format = 4
        self.cache = {}
        self.segments = []
        self.ttfReader = ttfReader

        i = 0

        # 2x segcount
        segCount = math.floor(ttfReader.getUint16() / 2)

        # 2 * (2**floor(log2(segCount)))
        searchRange = ttfReader.getUint16()
        # log2(searchRange)
        entrySelector = ttfReader.getUint16()
        # (2*segCount) - searchRange
        rangeShift = ttfReader.getUint16()


        # Ending character code for each segment, last is 0xffff
        for i in range(segCount):
            self.segments.append({
                'idRangeOffset': 0,
                'startCode': 0,
                'endCode': ttfReader.getUint16(),
                'idDelta': 0
            })

        # reservePad
        ttfReader.getUint16()

        # starting character code for each segment
        for i in range(segCount):
            self.segments[i]['startCode'] = ttfReader.getUint16()

        # Delta for all character codes in segment
        for i in range(segCount):
            self.segments[i]['idDelta'] = ttfReader.getUint16()

        # offset in bytes to glyph indexArray, or 0
        for i in range(segCount):
            ro = ttfReader.getUint16()
            if ro:
                self.segments[i]['idRangeOffset'] = ttfReader.position - 2 + ro
            else:
                self.segments[i]['idRangeOffset'] = 0

    def map(self, charCode):
        if not (charCode in self.cache):
            for j in range(len(self.segments)):
                segment = self.segments[j]
                if segment.startCode <= charCode and segment.endCode >= charCode:
                    index, glyphIndexAddress = None, None
                    if segment.idRangeOffset:
                        glyphIndexAddress = segment.idRangeOffset + 2 * (charCode - segment.startCode)
                        self.ttfReader.seek(glyphIndexAddress)
                        index = self.ttfReader.getUint16()
                    else:
                        index = (segment.idDelta + charCode) & 0xffff

                    self.cache[charCode] = index
                    break

            if j == len(self.segments):
                self.cache[charCode] = 0
        return self.cache[charCode]

class TTFReader():
    def __init__(self, data):
        self.data = data
        self.position = 0
        self.tables = None
        self.cmaps = []
        self.kern = []
        self.version = None
        self.fontRevision = None
        self.checksumAdjustment = None
        self.magicNumber = None
        self.flags = None
        self.unitsPerEm = None
        self.created = None
        self.modified = None
        self.xMin = None
        self.yMin = None
        self.xMax = None
        self.yMax = None
        self.macStyle = None
        self.lowestRecPPEM = None
        self.fontDirectionHint = None
        self.indexToLocFormat = None
        self.glyphDataFormat = None
        self.fontFamily = None
        self.fontSubFamily = None
        self.fullName = None
        self.postscriptName = None
        self.ascent = None
        self.descent = None
        self.lineGap = None
        self.advanceWidthMax = None
        self.minLeftSideBearing = None
        self.minRightSideBearing = None
        self.xMaxExtent = None
        self.caretSlopeRise = None
        self.caretSlopeRun = None
        self.caretOffset = None
        self.metricDataFormat = None
        self.numOfLongHorMetrics = None
        self.numGlyphs = None
        self.maxPoints = None
        self.maxContours = None
        self.maxComponentPoints = None
        self.maxComponentContours = None
        self.maxZones = None
        self.maxTwilightPoints = None
        self.maxStorage = None
        self.maxFunctionDefs = None
        self.maxInstructionDefs = None
        self.maxStackElements = None
        self.maxSizeOfInstructions = None
        self.maxComponentElements = None
        self.maxComponentDepth = None

        self.tables = self.readOffsetTables()
        self.readHeadTable()
        self.readNameTable()
        self.readCmapTable()
        self.readHheaTable()
        self.readKernTable()
        self.readMaxpTable()
    
    def seek(self, position):
        assert position > 0 and position < len(self.data) - 1

        oldPos = self.position
        self.position = position

        return oldPos

    def getUint8(self):
        if self.position > len(self.data) - 1:
            raise Exception(f'Position exceeds data length, pos: {self.position}, len(data): {len(self.data)}')

        self.position += 1

        return self.data[self.position - 1]

    def getUint16(self):
        return (self.getUint8() << 8) | self.getUint8()

    def getUint32(self):
        return self.getInt32()

    def getInt16(self):
        result = self.getUint16()

        if (result & 0x8000):
            result -= (1 << 16)

        return result
    
    def getInt32(self):
        return ((self.getUint8() << 24) | 
                (self.getUint8() << 16) |
                (self.getUint8() <<  8) |
                (self.getUint8()         ))

    def getFword(self):
        return self.getInt16()

    def getUFword(self):
        return self.getUint16()

    def get2Dot14(self):
        return self.getInt16() / (1 << 14)

    def getFixed(self):
        return self.getInt32() / (1 << 16)

    def getUnicodeString(self, length):
        result = ""
        for i in range(0, length, 2):
            result += chr(self.getUint16())

        return result

    def getString(self, length):
        result = ''

        for i in range(length):
            result += chr(self.getUint8())
            
        return result

    def readOffsetTables(self):
        tables = {}
        self.scalarType = self.getUint32()
        numTables = self.getUint16()
        self.searchRange = self.getUint16()
        self.entrySelector = self.getUint16()
        self.rangeShift = self.getUint16()

        for i in range(numTables):
            tag = self.getString(4)
            tables[tag] = {
                'checksum': self.getUint32(),
                'offset': self.getUint32(),
                'length': self.getUint32()
            }

        return tables

    def calculateTableChecksum(self, offset, length):
        old = self.seek(offset)
        sum = 0
        nlongs = (length + 3) / 4
        while nlongs > 0:
            nlongs -= 1
            sum = sum + self.getUint32() & 0xffffffff

        self.seek(old)
        return sum

    def readHeadTable(self):
        assert('head' in self.tables)
        self.seek(self.tables['head']['offset'])

        self.version = self.getFixed()
        self.fontRevision = self.getFixed()
        self.checksumAdjustment = self.getUint32()
        self.magicNumber = self.getUint32()
        assert(self.magicNumber == 0x5f0f3cf5)
        self.flags = self.getUint16()
        self.unitsPerEm = self.getUint16()
        self.xMin = self.getFword()
        self.yMin = self.getFword()
        self.xMax = self.getFword()
        self.yMax = self.getFword()
        self.macStyle = self.getUint16()
        self.lowestRecPPEM = self.getUint16()
        self.fontDirectionHint = self.getInt16()
        self.indexToLocFormat = self.getInt16()
        self.glyphDataFormat = self.getInt16()

    def readCmapTable(self):
        assert("cmap" in self.tables)
        tableOffset = self.tables['cmap']['offset']
        self.seek(tableOffset)
        version = self.getUint16() # must be 0
        numberSubtables = self.getUint16()

        # tables must be sorted by platform id and then platform specific
        # encoding.
        for i in range(numberSubtables):
            # platforms are: 
            # 0 - Unicode -- use specific id 6 for full coverage. 0/4 common.
            # 1 - MAcintosh (Discouraged)
            # 2 - reserved
            # 3 - Microsoft
            platformID = self.getUint16()
            platformSpecificID = self.getUint16()
            offset = self.getUint32()

            if platformID == 3 and (platformSpecificID <= 1):
                self.readCmap(tableOffset + offset)

        #  use format 0 table preferably.
        # this.cmaps.sort(function(a, b) {
        #     return a.format - b.format;
        # });

    def readCmap(self, offset):
        oldPos = self.seek(offset)
        format = self.getUint16()
        length = self.getUint16()
        language = self.getUint16()
        cmap = None

        if format == 0:
            cmap = TrueTypeCmap0(self, length)
        elif format == 4:
            cmap = TrueTypeCmap4(self, length)

        if cmap:
            self.cmaps.append(cmap)

        self.seek(oldPos)

    def readKernTable(self):
        if not ('kern' in self.tables):
            return

        tableOffset = self.tables['kern']['offset']
        self.seek(tableOffset)
        version = self.getFixed() # version 0
        nTables = self.getUint16()

        for i in range(nTables):
            length = self.getUint16()
            coverage = self.getUint16()
            format = coverage >> 8
            cross = coverage & 4
            vertical = (coverage & 0x1) == 0
            kern = None
            if format == 0:
                kern = Kern0Table(self, vertical, cross != 0)
            else:
                self.seek(self.position + length)

            if kern:
                self.kern.append(kern)

    def readMaxpTable(self):
        assert 'maxp' in self.tables
        
        tableOffset = self.tables['maxp']['offset']
        self.seek(tableOffset)

        version = self.getFixed()
        self.numGlyphs = self.getUint16()
        self.maxPoints = self.getUint16()
        self.maxContours = self.getUint16()
        self.maxComponentPoints = self.getUint16()
        self.maxComponentContours = self.getUint16()
        self.maxZones = self.getUint16()
        self.maxTwilightPoints = self.getUint16()
        self.maxStorage = self.getUint16()
        self.maxFunctionDefs = self.getUint16()
        self.maxInstructionDefs = self.getUint16()
        self.maxStackElements = self.getUint16()
        self.maxSizeOfInstructions = self.getUint16()
        self.maxComponentElements = self.getUint16()
        self.maxComponentDepth = self.getUint16()


    def readNameTable(self):
        assert 'name' in self.tables
        tableOffset = self.tables['name']['offset']
        self.seek(tableOffset)
        format = self.getUint16()
        count = self.getUint16()
        stringOffset = self.getUint16()
        for i in range(count):
            platformID = self.getUint16()
            platformSpecificID = self.getUint16()
            languageID = self.getUint16()
            nameID = self.getUint16()
            length = self.getUint16()
            offset = self.getUint16()
            old = self.seek(tableOffset + stringOffset + offset)
            name = None
            if platformID == 0 or platformID == 3:
                name = self.getUnicodeString(length)
            else:
                name = self.getString(length)
                
            self.seek(old)

            if nameID == 1:
                self.fontFamily = name
            elif nameID == 2:
                self.fontSubFamily = name
            elif nameID == 4:
                self.fullName = name
            elif nameID == 6:
                self.postscriptName = name

    def readHheaTable(self):
        assert("hhea" in self.tables)
        tableOffset = self.tables['hhea']['offset']
        self.seek(tableOffset)
        version = self.getFixed() # 0x00010000
        self.ascent = self.getFword()
        self.descent = self.getFword()
        self.lineGap = self.getFword()
        self.advanceWidthMax = self.getUFword()
        self.minLeftSideBearing = self.getFword()
        self.minRightSideBearing = self.getFword()
        self.xMaxExtent = self.getFword()
        self.caretSlopeRise = self.getInt16()
        self.caretSlopeRun = self.getInt16()
        self.caretOffset = self.getFword()
        self.getInt16(); # reserved
        self.getInt16(); # reserved
        self.getInt16(); # reserved
        self.getInt16(); # reserved
        self.metricDataFormat = self.getInt16()
        self.numOfLongHorMetrics = self.getUint16()

    def getGlyphOffset(self, index):
        assert('loca' in self.tables)
        table = self.tables['loca']
        offset, old = None, None

        if (self.indexToLocFormat == 1):
            old = self.seek(table['offset'] + index * 4)
            offset = self.getUint32()
        else:
            old = self.seek(table['offset'] + index * 2)
            offset = self.getUint16() * 2

        self.seek(old)

        return offset + self.tables['glyf']['offset']

    def mapCode(self, charCode):
        index = 0
        for i in range(len(self.cmaps)):
            cmap = self.cmaps[i]
            index = cmap.map(charCode)
            if index:
                break
        
        return index

    def readGlyph(self, index):
        offset = self.getGlyphOffset(index)

        if (offset >= self.tables["glyf"]['offset'] + self.tables['glyf']['length']):
            return None

        assert(offset >= self.tables["glyf"]['offset'])
        assert(offset < self.tables["glyf"]['offset'] + self.tables['glyf']['length'])

        self.seek(offset)

        glyph = {
            'numberOfContours': self.getInt16(),
            'xMin': self.getFword(),
            'yMin': self.getFword(),
            'xMax': self.getFword(),
            'yMax': self.getFword()
        }

        assert(glyph['numberOfContours'] >= -1)

        if (glyph['numberOfContours'] == -1):
            self.readCompoundGlyph(glyph)
        else:
            self.readSimpleGlyph(glyph)

        return glyph

    def readSimpleGlyph(self, glyph):
        ON_CURVE        =  1
        X_IS_BYTE       =  2
        Y_IS_BYTE       =  4
        REPEAT          =  8
        X_DELTA         = 16
        Y_DELTA         = 32

        glyph['type'] = "simple"
        glyph['contourEnds'] = []
        glyph['points'] = []

        for i in range(glyph['numberOfContours']):
            glyph['contourEnds'].append(self.getUint16())

        # skip over intructions
        self.seek(self.getUint16() + self.position)

        if (glyph['numberOfContours'] == 0):
            return

        numPoints = max(glyph['contourEnds']) + 1

        flags = []

        for i in range(numPoints):
            flag = self.getUint8()
            flags.append(flag)
            glyph['points'].append({
                'onCurve': (flag & ON_CURVE) > 0
            })

            if (flag & REPEAT):
                repeatCount = self.getUint8()
                assert(repeatCount > 0)
                i += repeatCount
                while repeatCount > 0:
                    repeatCount -= 1
                    flags.append(flag)
                    glyph['points'].append({
                        'onCurve': (flag & ON_CURVE) > 0
                    })

        def readCoords(name, byteFlag, deltaFlag, vMin, vMax):
            value = 0

            for i in range(len(glyph['points'])):
                flag = flags[i]
                if flag & byteFlag:
                    if flag & deltaFlag:
                        value += self.getUint8()
                    else:
                        value -= self.getUint8()

                elif ~flag & deltaFlag:
                    value += self.getInt16()

                glyph['points'][i][name] = min(value, vMax) - vMin

                if 'x' not in glyph['points'][i]:
                    print(glyph['points'][i])
                    sys.exit(0)

        readCoords("x", X_IS_BYTE, X_DELTA, glyph['xMin'], glyph['xMax'])
        readCoords("y", Y_IS_BYTE, Y_DELTA, glyph['yMin'], glyph['yMax'])

    def readCompoundGlyph(self, glyph):
        ARG_1_AND_2_ARE_WORDS = 1
        ARGS_ARE_XY_VALUES = 2
        ROUND_XY_TO_GRID = 4
        WE_HAVE_A_SCALE = 8
        # RESERVED              = 16
        MORE_COMPONENTS = 32
        WE_HAVE_AN_X_AND_Y_SCALE = 64
        WE_HAVE_A_TWO_BY_TWO = 128
        WE_HAVE_INSTRUCTIONS = 256
        USE_MY_METRICS = 512
        OVERLAP_COMPONENT = 1024

        flags = MORE_COMPONENTS
        component = None
        glyph['type'] = 'compound'
        glyph['contourEnds'] = []
        glyph['points'] = []
        while flags & MORE_COMPONENTS:
            arg1, arg2 = None, None

            flags = self.getUint16()
            component = {
                'glyphIndex': self.getUint16(),
                'matrix': {
                    'a': 1, 'b': 0, 'c': 0, 'd': 1, 'e': 0, 'f': 0
                },

                'destPointIndex': 0,
                'srcPointIndex': 0
            }

            if flags & ARG_1_AND_2_ARE_WORDS:
                arg1 = self.getInt16()
                arg2 = self.getInt16()
            else:
                arg1 = self.getUint8()
                arg2 = self.getUint8()

            if flags & ARGS_ARE_XY_VALUES:
                component['matrix']['e'] = arg1
                component['matrix']['f'] = arg2
            else:
                component['destPointIndex'] = arg1
                component['srcPointIndex'] = arg2

            if flags & WE_HAVE_A_SCALE:
                component['matrix']['a'] = self.get2Dot14()
                component['matrix']['d'] = component['matrix']['a']
            elif flags & WE_HAVE_AN_X_AND_Y_SCALE:
                component['matrix']['a'] = self.get2Dot14()
                component['matrix']['d'] = self.get2Dot14()
            elif flags & WE_HAVE_A_TWO_BY_TWO:
                component['matrix']['a'] = self.get2Dot14()
                component['matrix']['b'] = self.get2Dot14()
                component['matrix']['c'] = self.get2Dot14()
                component['matrix']['d'] = self.get2Dot14()

            old = self.position
            simpleGlyph = self.readGlyph(component['glyphIndex'])
            if simpleGlyph:
                pointOffset = len(glyph['points'])
                for i in range(len(simpleGlyph['contourEnds'])):
                    glyph['contourEnds'].append(simpleGlyph['contourEnds'][i] + pointOffset)

                for i in range(len(simpleGlyph['points'])):
                    x = simpleGlyph['points'][i]['x']
                    y = simpleGlyph['points'][i]['y']
                    x = component['matrix']['a'] * x + component['matrix']['b'] * y + component['matrix']['e']
                    y = component['matrix']['c'] * x + component['matrix']['d'] * y + component['matrix']['f']
                    glyph['points'].append({
                        'x': x, 
                        'y': y, 
                        'onCurve': simpleGlyph['points'][i]['onCurve']
                    })

            self.seek(old)

        glyph['numberOfContours'] = len(glyph['contourEnds'])

        if flags & WE_HAVE_INSTRUCTIONS:
            self.seek(self.getUint16() + self.position)

class GlyphDrawer():
    def __init__(self, glyphs, targetResolution = None):
        self.glyphs = glyphs
        self.scale = 1/37
        self.maxI = 3200

        self.resolution = self.calculateResolution(self.scale, targetResolution)
        self.positions = self.calculatePositions(self.scale)
        
    def calculateResolution(self, scale, targetResolution = None):
        print('calculating resolution: ', end='', flush=True)

        complete = False
        targetResolution = 1
        rowWidth = 0
        rowHeight = 0
        currentY = 0
        counter = 0

        while not complete:
            complete = True
            for glyph in self.glyphs:
                if counter >= self.maxI:
                    break

                counter += 1

                width = (glyph['xMax'] - glyph['xMin']) * scale
                height = ((glyph['yMax'] - glyph['yMin']) * scale) + 1

                if height > rowHeight:
                    rowHeight = height

                    if rowHeight + currentY > targetResolution:
                        targetResolution *= 2
                        rowWidth = 0
                        rowHeight = 0
                        complete = False
                        break

                if width + rowWidth > targetResolution:
                    rowWidth = 0
                    currentY += rowHeight
                    rowHeight = 0

                rowWidth += width

        print(targetResolution)

        return targetResolution

    def calculatePositions(self, scale):
        print('calculating positions... ', end='', flush=True)
        rowWidth = 0
        rowHeight = 0
        currentY = 0
        counter = 0

        glyphPositions = []

        for glyph in self.glyphs:
            if counter >= self.maxI:
                break
                
            counter += 1

            width = (glyph['xMax'] - glyph['xMin']) * scale
            height = (glyph['yMax'] - glyph['yMin']) * scale

            if height > rowHeight:
                rowHeight = height

            if width + rowWidth > self.resolution:
                rowWidth = 0
                currentY += rowHeight
                rowHeight = 0

            glyphPositions.append((rowWidth, currentY))
            rowWidth += width

        print('done')
        return glyphPositions

    def drawLine(self, glyphTex, fromPos, toPos, topLeft, glyphWidth, glyphHeight):
        try:
            dx = fromPos['x'] - toPos['x']
            dy = fromPos['y'] - toPos['y']
        except KeyError as e:
            print('last: ', end='')
            print(fromPos)
            print('current: ', end='')
            print(toPos)

        distance = math.sqrt((dx * dx) + (dy * dy))

        if distance == 0:
            return

        increment = 1 / distance

        v = 0
        while v < 1:
            x = v * fromPos['x'] + (1 - v) * toPos['x']
            y = v * fromPos['y'] + (1 - v) * toPos['y']

            v += increment

            pixelX = math.floor(x * self.scale + topLeft[0])
            pixelY = math.floor((glyphHeight - y) * self.scale + topLeft[1])

            if pixelX >= self.resolution or pixelY >= self.resolution or pixelX < 0 or pixelY < 0:
                continue

            try:
                glyphTex.putpixel((pixelX, pixelY), (255, 255, 255, 255))

            except IndexError as e:
                print('Pixel coords: ', end='')
                print((pixelX, pixelY))
                raise e

    def drawGlyph(self, i, glyphTex):
        glyph = self.glyphs[i]
        position = self.positions[i]

        width = glyph['xMax'] - glyph['xMin']
        height = glyph['yMax'] - glyph['yMin']

        contourStartIndex = 0
        lastPointContourEnd = False

        for pointI in range(1, len(glyph['points'])):
            lastPoint = glyph['points'][pointI - 1]
            currentPoint = glyph['points'][pointI]

            if not lastPointContourEnd:
                self.drawLine(glyphTex, lastPoint, currentPoint, position, width, height)
            
            if pointI in glyph['contourEnds']: # if current point is a contour end
                contourStartPoint = glyph['points'][contourStartIndex]
                self.drawLine(glyphTex, currentPoint, contourStartPoint, position, width, height)
                contourStartIndex = pointI + 1
                lastPointContourEnd = True

            else:
                lastPointContourEnd = False

    def drawGlyphs(self, glyphTex):
        print('Drawing glyphs')
        for i in tqdm(range(min(len(self.glyphs), self.maxI))):
            self.drawGlyph(i, glyphTex)

    def drawTexture(self, filepath):
        glyphTex = Image.new('RGBA', (self.resolution, self.resolution), color = 'black')
        self.drawGlyphs(glyphTex)
        glyphTex.save(filepath)

parser = argparse.ArgumentParser(description='Converts an input TTF font file to a texture and UV map, outputs a directory containing both files')
parser.add_argument('inputFilePath', metavar='Input file', nargs=1, help='TTF file to process')
parser.add_argument('-o', dest='outputFilePath', nargs=1, help='Where to save the output directory')
parser.add_argument('-r', '--resolution', default=1024, dest='resolution', nargs=1, help='Resolution of the output texture')
parser.add_argument('-O', '--overwrite', dest='overwrite', nargs='?', const=True, help='Delete the output directory if it already exists')
parser.add_argument('-t', '--targetResolution', nargs='?', help='Target a resolution instead of a font scale')

args = parser.parse_args()

# Prepare output directory
outputPath = args.outputFilePath or 'bin/fonts/out/'
dirPath = outputPath + args.inputFilePath[0].split('/')[-1] + '/'; 

if os.path.isdir(dirPath):
    if args.overwrite:
        print('Output directory already exists, overwriting')
    else:
        print('Output directory already exists, run with -O to override')
        sys.exit(os.EX_OSFILE)


# Render font to texture
fontData = None

try:
    with open(args.inputFilePath[0], 'rb') as fontFile:
        fontData = fontFile.read()

except FileNotFoundError:
    print('Input file does not exist.')
    sys.exit(os.EX_NOINPUT)

ttf = TTFReader(fontData)

print('Num glyphs: ' + str(ttf.numGlyphs))

glyphDrawer = GlyphDrawer([ttf.readGlyph(i) for i in range(ttf.numGlyphs)])

if os.path.isdir(dirPath):
    shutil.rmtree(dirPath)

os.makedirs(dirPath)
glyphDrawer.drawTexture(dirPath + 'texture.png')