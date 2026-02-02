import cv2
import numpy as np
import math
import config
from ip_lib import OpeningRectangle1, draw_dashed_line_fast

def DAngleInspect(ImageOVL, LocationRegion, LocationRect, \
        Parameter1, Parameter2, Parameter3, Angle,\
        MinTolerance, MaxTolerance, Color, ZOOM_RATIO, RESOLUTION, IsCorrection = False):
    # in:
    Parameter1 = int(Parameter1/RESOLUTION/ZOOM_RATIO) # distance from top finish line to bottom D measurement region
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO) # the inset distance from outer edge of the locking ring to the point where the locking ring height is to be measured
    Parameter3 = int(Parameter3/RESOLUTION/ZOOM_RATIO) # height of measurement region

    # out:
    IsDefect = False
    AngleOut = 0
    DiffAngleOut = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    bottomROI = BTOP+Parameter1
    topROI = max(bottomROI-Parameter3+1, 0)
    locationRegionCrop = LocationRegion[topROI:bottomROI, BLEFT:BRIGHT] 
    leftROI,_,_,_ = cv2.boundingRect(locationRegionCrop)
    rightROI = leftROI + Parameter2
    region = locationRegionCrop[:,leftROI:rightROI]
    openingRegion = OpeningRectangle1(region, 1, int(Parameter3*0.6))
    differenceRegion = cv2.bitwise_xor(region, openingRegion)
    # isPass, selectedRegion = SelectShapeStd(differenceRegion)
    contours, _ = cv2.findContours(differenceRegion, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    if len(contours) == 0:
        AngleOut = 90
        DiffAngleOut = AngleOut - Angle
        if DiffAngleOut < MinTolerance*(-1) or DiffAngleOut > MaxTolerance:
            IsDefect = True
        return IsDefect, ImageOVL, AngleOut, DiffAngleOut
    
    contour = max(contours, key=cv2.contourArea)
    pointX = contour[:,:,0]
    pointY = contour[:,:,1]

    # find point at bottom left
    x = np.amin(pointX)
    idx = np.where(pointX == x)
    y = np.amax(pointY[idx])
    point1 = [x, y]

    # find point 2 at bottom right
    y = np.amax(pointY)
    idx = np.where(pointY == y)
    x = np.amin(pointX[idx])
    point2 = [x, y]

    AngleOut = round(math.atan2(point2[1] - point1[1], point2[0] - point1[0])*180/math.pi, config.FLOAT_NUMBER)
    DiffAngleOut = round(AngleOut - Angle, config.FLOAT_NUMBER)
    if DiffAngleOut < MinTolerance*(-1) or DiffAngleOut > MaxTolerance:
        IsDefect = True
    
    img = cv2.cvtColor(region, cv2.COLOR_GRAY2BGR)
    cv2.line(img, point1, point2, (0, 0, 255), 1)
    


    # ovl
    x1 = int(BLEFT)*ZOOM_RATIO
    y1 = int(topROI)*ZOOM_RATIO
    x2 = int(BRIGHT)*ZOOM_RATIO
    y2 = int(bottomROI)*ZOOM_RATIO
    if IsCorrection:
        cv2.line(ImageOVL, (x1, 0), (x1, ImageOVL.shape[0]), (0, 255, 255), config.OVLSIZE)
        cv2.line(ImageOVL, (x2, 0), (x2, ImageOVL.shape[0]), (0, 255, 255), config.OVLSIZE)
        cv2.line(ImageOVL, (0, y1), (ImageOVL.shape[1], y1), Color, config.OVLSIZE)
        cv2.line(ImageOVL, (0, y2), (ImageOVL.shape[1], y2), Color, config.OVLSIZE)
    else:
        cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    x2 = int((point2[0] + leftROI + BLEFT)*ZOOM_RATIO)
    y2 = int((point2[1] + topROI)*ZOOM_RATIO)
    length = (Parameter2 + 400)*ZOOM_RATIO
    draw_dashed_line_fast(ImageOVL, (x2, y2), AngleOut + 180, length, 50, 50, Color, int(config.OVLSIZE/2))

    cx = int((BLEFT+BRIGHT)/2)
    textSize = cv2.getTextSize(f'D Angle: {round(AngleOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    cv2.putText(ImageOVL, f'D Angle: {round(AngleOut, config.FLOAT_NUMBER)}', (int(cx - textSize[0] /2), max(BTOP - 150, 100)), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)
    return IsDefect, ImageOVL, AngleOut, DiffAngleOut