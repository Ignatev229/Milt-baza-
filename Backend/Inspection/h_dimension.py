import cv2
import numpy as np

import config
from ip_lib import FindMaxDiamterOfOneLine

def HDimensionInspect(ImageOVL, LocationRegion, LocationRect, \
            Parameter1, Parameter2, Dimension, MinTolerance, MaxTolerance,\
            Color, ZOOM_RATIO, RESOLUTION, IsCorrection = False):
    # in:
    Parameter1 = int(Parameter1/RESOLUTION/ZOOM_RATIO) # search region height
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO) # the diameter for search for
    Dimension = Dimension/RESOLUTION/ZOOM_RATIO # 
    MinTolerance = MinTolerance/RESOLUTION/ZOOM_RATIO # tolerance for parameter 2
    MaxTolerance = MaxTolerance/RESOLUTION/ZOOM_RATIO # tolerance for parameter 2


    minDiameter = Parameter2 - MinTolerance
    maxDiameter = Parameter2 + MaxTolerance

    # out:
    IsDefect = False
    DimensionOut = 0
    DiffDimensionOut = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    if minDiameter > (BRIGHT - BLEFT):
        # can not find
        IsDefect = True
        return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut
    firstY = -1
    lastY = -1
    # method 1
    # for y in range(BTOP, BBOTTOM, 1):
    #     regionCrop = LocationRegion[y:y+1, BLEFT:BRIGHT]
    #     isPass, firstX, lastX, diameter = FindMaxDiamterOfOneLine(regionCrop, False)
    #     if not isPass or diameter > maxDiameter or diameter < minDiameter:
    #         if firstY != -1:
    #             lastY = y
    #             break
    #         continue
    #     if firstY == -1:
    #         firstY = y



    # method 2
    topROI = int(Dimension - Parameter1/2)
    bottomROI = int(Dimension + Parameter1/2)
    mask = np.zeros(LocationRegion.shape, dtype=np.uint8)
    cv2.rectangle(mask, (BLEFT, topROI), (BRIGHT, bottomROI), 255, -1)
    LocationRegion = cv2.bitwise_and(LocationRegion, mask)
    contours, _ = cv2.findContours(LocationRegion, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    if len(contours) == 0:
        return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut
    listX = contours[0][:,:,0]
    listY = np.array(contours[0][:,:,1])
    for y in range(BTOP, BBOTTOM, 1):
        idx = np.where(listY == y)[0]
        if(len(idx) == 0):
            continue
        xmin = np.amin(listX[idx])
        xmax = np.amax(listX[idx])
        diameter = xmax - xmin
        if diameter > maxDiameter or diameter < minDiameter:
            if firstY != -1:
                lastY = y
                break
            continue
        if firstY == -1:
            firstY = y



    if lastY == -1:
        lastY = BBOTTOM
    if firstY == -1:
        # can not find
        IsDefect = True
        posY = -1
        # return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut
    else:
        posY = (firstY + lastY)/2
        DimensionOut = abs(BTOP - posY)
        DimensionOut = round(DimensionOut*RESOLUTION*ZOOM_RATIO, config.FLOAT_NUMBER)
        DiffDimensionOut = round(DimensionOut - Dimension, config.FLOAT_NUMBER)


    # if DiffDimensionOut < MinTolerance*(-1) or DiffDimensionOut > MaxTolerance:
    #     IsDefect = True
    # # Defect info
    # DimensionOut = DimensionOut*RESOLUTION*ZOOM_RATIO
    # DiffDimensionOut = DiffDimensionOut*RESOLUTION*ZOOM_RATIO

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

    x = max(int(BLEFT - 50), 400)*ZOOM_RATIO
    if posY != -1:
        y1 = int(BTOP*ZOOM_RATIO)
        y2 = int(posY*ZOOM_RATIO)
        cv2.arrowedLine(ImageOVL, [x, y1],\
                        [x, y2], Color, config.OVLSIZE, tipLength = 0.05)
        cv2.arrowedLine(ImageOVL, [x , y2],\
                        [x, y1], Color, config.OVLSIZE, tipLength = 0.05)
        cy = ImageOVL.shape[0] - int((y1 + y2)/2)
    else:
        y1 = int(BTOP*ZOOM_RATIO)
        y2 = int((topROI + bottomROI)/2*ZOOM_RATIO)
        cy = ImageOVL.shape[0] - int((y1 + y2)/2)


    textSize = cv2.getTextSize(f'H: {round(DimensionOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_CLOCKWISE)
    cv2.putText(ImageOVL, f'H: {round(DimensionOut, config.FLOAT_NUMBER)}', (int(cy - textSize[0]/2), x - 50), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_COUNTERCLOCKWISE)



    return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut