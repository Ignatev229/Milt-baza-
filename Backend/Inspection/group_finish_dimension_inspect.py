import cv2
import numpy as np
import math
import config

from ip_lib import OpeningRectangle1

def FinishDimensionInspect(ImageOVL, LocationRegion, LocationRect, \
                        Parameter1, Parameter2, Dimension, MinTolerance, MaxTolerance,\
                        DimensionName, Color, Index, ZOOM_RATIO, RESOLUTION, IsCorrection = False):
    # in:
    Parameter1 = int(Parameter1/RESOLUTION/ZOOM_RATIO) # distance from top finish line to bottom of area
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO) # height of measurement area
    # Dimension = Dimension/RESOLUTION/ZOOM_RATIO # 
    # MinTolerance = MinTolerance/RESOLUTION/ZOOM_RATIO # 
    # MaxTolerance = MaxTolerance/RESOLUTION/ZOOM_RATIO # 


    # out:
    IsDefect = False
    DimensionOut = 0
    DiffDimensionOut = 0


    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    bottomROI = BTOP+Parameter1+1
    topROI = max(bottomROI-Parameter2, 0)
    locationRegionCrop = LocationRegion[topROI:bottomROI, BLEFT:BRIGHT] 
    # mask = np.zeros(LocationRegion.shape, dtype=np.uint8)
    # cv2.rectangle(mask, (BLEFT, topROI), (BRIGHT, bottomROI), 255, -1)
    # locationRegionCrop = cv2.bitwise_and(LocationRegion, mask)

    if DimensionName == "E":
        # special for E
        locationRegionCrop = OpeningRectangle1(locationRegionCrop, 1, int(Parameter2*0.8))

    x,y,w,h = cv2.boundingRect(locationRegionCrop)

    # # rect 2
    # contours, _ = cv2.findContours(locationRegionCrop, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    # if len(contours) == 0:
    #     return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut
    # rect = cv2.minAreaRect(contours[0])
    # box = cv2.boxPoints(rect)
    # box = np.int0(box)
    # dx1 = box[0][0] - box[1][0]
    # dy1 = box[0][1] - box[1][1]
    # dx2 = box[0][0] - box[2][0]
    # dy2 = box[0][1] - box[2][1]
    # img = cv2.cvtColor(locationRegionCrop, cv2.COLOR_GRAY2BGR)
    # cv2.drawContours(img,[box],0,(0,0,255),2)
    # if dx1 < dx2:
    #     d = math.sqrt(dx2*dx2 + dy2*dy2)
    # else:
    #     d = math.sqrt(dx1*dx1 + dy1*dy1)

    DimensionOut = w
    DimensionOut = round(DimensionOut*RESOLUTION*ZOOM_RATIO, config.FLOAT_NUMBER)
    DiffDimensionOut = round(DimensionOut - Dimension, config.FLOAT_NUMBER)

    if DiffDimensionOut < MinTolerance*(-1) or DiffDimensionOut > MaxTolerance:
        IsDefect = True

    # ovl
    x1 = int(BLEFT + x)*ZOOM_RATIO
    y1 = int(topROI)*ZOOM_RATIO
    x2 = int(BLEFT + x + w)*ZOOM_RATIO
    y2 = int(bottomROI)*ZOOM_RATIO
    if IsCorrection:
        cv2.line(ImageOVL, (x1, 0), (x1, ImageOVL.shape[0]), (0, 255, 255), config.OVLSIZE)
        cv2.line(ImageOVL, (x2, 0), (x2, ImageOVL.shape[0]), (0, 255, 255), config.OVLSIZE)
        cv2.line(ImageOVL, (0, y1), (ImageOVL.shape[1], y1), Color, config.OVLSIZE)
        cv2.line(ImageOVL, (0, y2), (ImageOVL.shape[1], y2), Color, config.OVLSIZE)
    else:
        cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    y = (BBOTTOM - Index*120)*ZOOM_RATIO
    x = int((x1 + x2)/2)
    cv2.arrowedLine(ImageOVL, [x1, y],\
                    [x2, y], Color, config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [x2 , y],\
                    [x1, y], Color, config.OVLSIZE, tipLength = 0.05)
        

    # ovl
    textSize = cv2.getTextSize(f'{DimensionName}: {round(DimensionOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    cv2.putText(ImageOVL, f'{DimensionName}: {round(DimensionOut, config.FLOAT_NUMBER)}', (int(x - textSize[0] /2), y - 50), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)

    return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut
