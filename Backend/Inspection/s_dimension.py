import cv2
import numpy as np

import config
from ip_lib import OpeningRectangle1, SelectShapeWidthHeight, OpeningCircle

def SDimensionInspect(ImageOVL, LocationRegion, LocationRect, \
                        Parameter1, Parameter2, Parameter3, Dimension, MinTolerance, MaxTolerance, CurrentDimension, Color, ZOOM_RATIO, RESOLUTION):
    # in:
    Parameter1 = int(Parameter1/RESOLUTION/ZOOM_RATIO) # thread height
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO) # thread width
    Parameter3 = int(Parameter3/RESOLUTION/ZOOM_RATIO) # distance from top finish line to bottom measurement region

    # Dimension = Dimension/RESOLUTION/ZOOM_RATIO # 
    # MinTolerance = MinTolerance/RESOLUTION/ZOOM_RATIO # tolerance for parameter 2
    # MaxTolerance = MaxTolerance/RESOLUTION/ZOOM_RATIO # tolerance for parameter 2

    # out:
    IsDefect = False
    DimensionOut = 0
    DiffDimensionOut = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    
    bottomROI = BTOP+Parameter3
    topROI = BTOP
    locationRegionCrop = LocationRegion[topROI:bottomROI, BLEFT:BRIGHT] 

    # ovl
    x1 = int(BLEFT)*ZOOM_RATIO
    y1 = int(topROI)*ZOOM_RATIO
    x2 = int(BRIGHT)*ZOOM_RATIO
    y2 = int(bottomROI)*ZOOM_RATIO
    cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    openingRegion = OpeningRectangle1(locationRegionCrop, 1, int(Parameter1*3))
    differenceRegion = cv2.bitwise_xor(locationRegionCrop, openingRegion)
    openingRegion1 = OpeningCircle(differenceRegion, 2)

    isPass, leftOut, topOut, widthOut, heightOut = SelectShapeWidthHeight(openingRegion1, \
                Parameter2*0.9, 5, Parameter2*5, 999999)
    
    if not isPass:
        return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut
    
    index = np.argmin(np.array(topOut))

    padding = 10

    x1 = int(BLEFT + leftOut[index])*ZOOM_RATIO - padding
    y1 = int(topROI + topOut[index])*ZOOM_RATIO - padding
    x2 = int(BLEFT + leftOut[index] + widthOut[index])*ZOOM_RATIO + padding
    y2 = int(topROI + topOut[index] + heightOut[index])*ZOOM_RATIO + padding
    cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    DimensionOut = abs(topOut[index])
    DimensionOut = round(DimensionOut*RESOLUTION*ZOOM_RATIO, config.FLOAT_NUMBER)
    DiffDimensionOut = round(DimensionOut - Dimension, config.FLOAT_NUMBER)
    if DiffDimensionOut < MinTolerance*(-1) or DiffDimensionOut > MaxTolerance:
        IsDefect = True

    
    x = max(int(BLEFT - 100), 300)*ZOOM_RATIO
    posY = BTOP + topOut[index]
    y1 = int(BTOP*ZOOM_RATIO)
    y2 = int(posY*ZOOM_RATIO)
    cv2.arrowedLine(ImageOVL, [x, y1],\
                    [x, y2], Color, config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [x , y2],\
                    [x, y1], Color, config.OVLSIZE, tipLength = 0.05)
    cy = ImageOVL.shape[0] - int((y1 + y2)/2)

    if CurrentDimension == 0 or \
        (CurrentDimension > DimensionOut and \
        DimensionOut != 0):
        CurrentDimension = DimensionOut

    textSize = cv2.getTextSize(f'S: {round(CurrentDimension, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_CLOCKWISE)
    cv2.putText(ImageOVL, f'S: {round(CurrentDimension, config.FLOAT_NUMBER)}', (int(cy - textSize[0]/2), x - 50), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_COUNTERCLOCKWISE)




    return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut