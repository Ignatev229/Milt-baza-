import cv2
import numpy as np

import config

def NonRoundShapeInspect(ImageOVL, LocationRegion, LocationRect, Height,\
                                DimensionName, Color, ZOOM_RATIO, RESOLUTION):
    Height = int(Height/RESOLUTION/ZOOM_RATIO) # distance from top finish line to bodyR

    # out:
    IsDefect = False
    DimensionOut = 0
    DiffDimensionOut = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    leftROI = BRIGHT-Height
    rightROI = leftROI+1
    locationRegionCrop = LocationRegion[BTOP:BBOTTOM, leftROI:rightROI] 

    x,y,w,h = cv2.boundingRect(locationRegionCrop)
    DimensionOut = h

    y1 = (BTOP + y)*ZOOM_RATIO
    y2 = (BTOP + y + h)*ZOOM_RATIO
    x = (leftROI)*ZOOM_RATIO
    cv2.arrowedLine(ImageOVL, [x, y1],\
                    [x, y2], Color, config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [x , y2],\
                    [x, y1], Color, config.OVLSIZE, tipLength = 0.05)
    
    # defect info
    DimensionOut = np.array(DimensionOut)*RESOLUTION*ZOOM_RATIO

    y = int((y1+y2)/2)
    textSize = cv2.getTextSize(f'Shape Dimension {DimensionName}: {round(DimensionOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_COUNTERCLOCKWISE)
    cv2.putText(ImageOVL, f'Shape Dimension {DimensionName}: {round(DimensionOut, config.FLOAT_NUMBER)}', (int(y - textSize[0]/2), ImageOVL.shape[0] - (x + 50)), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_CLOCKWISE)

    return IsDefect, ImageOVL, DimensionOut
    