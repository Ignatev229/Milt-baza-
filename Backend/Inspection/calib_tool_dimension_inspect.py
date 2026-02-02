import cv2
import numpy as np
import math
import config

from ip_lib import OpeningRectangle1


def CalibToolDimensionTopInspect(ImageOVL, LocationRegion, LocationRect, \
                        Parameter1, Parameter2, Dimension, Color, ZOOM_RATIO):
    # all param is pixel 
    # Dimension is mm

    # in:
    Parameter1 = int(Parameter1/ZOOM_RATIO) # distance from top finish line to bottom of area
    Parameter2 = int(Parameter2/ZOOM_RATIO) # height of measurement area

    # out:
    IsPass = False
    DimensionOut = 0 # pixel
    ResolutionOut = 0 # mm/pixel

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    bottomROI = BTOP+Parameter1+1
    topROI = max(bottomROI-Parameter2, 0)
    locationRegionCrop = LocationRegion[topROI:bottomROI, BLEFT:BRIGHT] 
    x,y,w,h = cv2.boundingRect(locationRegionCrop)

    DimensionOut = w*ZOOM_RATIO
    if DimensionOut == 0:
        IsPass = False
        return IsPass, ImageOVL, ResolutionOut
    
    ResolutionOut = round(Dimension/DimensionOut, config.CALIBRATION_FLOAT_NUMBER)
    IsPass = True

    # ovl
    x1 = int(BLEFT + x)*ZOOM_RATIO
    y1 = int(topROI)*ZOOM_RATIO
    x2 = int(BLEFT + x + w)*ZOOM_RATIO
    y2 = int(bottomROI)*ZOOM_RATIO
    cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    y = int((y1+y2)/2)
    x = int((x1 + x2)/2)
    cv2.arrowedLine(ImageOVL, [x1, y],\
                    [x2, y], Color, config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [x2 , y],\
                    [x1, y], Color, config.OVLSIZE, tipLength = 0.05)
    
    # ovl
    textSize = cv2.getTextSize(f'Diameter: {round(Dimension, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    cv2.putText(ImageOVL, f'Diameter: {round(Dimension, config.FLOAT_NUMBER)}', (int(x - textSize[0] /2), y - 50), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)

    return IsPass, ImageOVL, ResolutionOut

def CalibToolDimensionBotInspect(ImageOVL, LocationRegion, LocationRect, \
                        Parameter1, Parameter2, Dimension, Color, ZOOM_RATIO):
    # all param is pixel 
    # Dimension is mm

    # in:
    Parameter1 = int(Parameter1/ZOOM_RATIO) # distance from top finish line to bottom of area
    Parameter2 = int(Parameter2/ZOOM_RATIO) # height of measurement area

    # out:
    IsPass = False
    DimensionOut = 0 # pixel
    ResolutionOut = 0 # mm/pixel

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    leftROI = BRIGHT-Parameter1
    rightROI = leftROI+Parameter2
    locationRegionCrop = LocationRegion[BTOP:BBOTTOM, leftROI:rightROI] 
    x,y,w,h = cv2.boundingRect(locationRegionCrop)

    DimensionOut = h*ZOOM_RATIO
    if DimensionOut == 0:
        IsPass = False
        return IsPass, ImageOVL, ResolutionOut
    
    ResolutionOut = round(Dimension/DimensionOut, config.CALIBRATION_FLOAT_NUMBER)
    IsPass = True

    # ovl
    x1 = int(leftROI)*ZOOM_RATIO
    y1 = int(BTOP)*ZOOM_RATIO
    x2 = int(rightROI)*ZOOM_RATIO
    y2 = int(BBOTTOM)*ZOOM_RATIO
    cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    y = int((y1+y2)/2)
    x = int((x1 + x2)/2)
    cv2.arrowedLine(ImageOVL, [x, y1],\
                    [x, y2], Color, config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [x , y2],\
                    [x, y1], Color, config.OVLSIZE, tipLength = 0.05)
    
    # ovl
    textSize = cv2.getTextSize(f'Diameter: {round(Dimension, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_COUNTERCLOCKWISE)
    cv2.putText(ImageOVL, f'Diameter: {round(Dimension, config.FLOAT_NUMBER)}', (int(y - textSize[0] /2), ImageOVL.shape[0] - (x + 50)), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_CLOCKWISE)
    return IsPass, ImageOVL, ResolutionOut



