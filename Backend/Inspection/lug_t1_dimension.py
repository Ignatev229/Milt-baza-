import cv2
import numpy as np

import config
from ip_lib import draw_dashed_line_fast

def LugT1DimensionInspect(ImageOVL, LocationRegion, LocationRect, \
            Parameter1, Parameter2, Dimension, MinTolerance, MaxTolerance,\
            Index, Color, ZOOM_RATIO, RESOLUTION, IsCorrection = False):
    # Find max horizontal diameter in area
    # in:
    Parameter1 = int(Parameter1/RESOLUTION/ZOOM_RATIO) # search region height
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO) # the diameter for search for
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

    # Find max horizontal diameter in area
    region = locationRegionCrop
    contours, _ = cv2.findContours(region, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    if len(contours) == 0:
        IsDefect = True
        return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut
    
    listX = contours[0][:,:,0]
    listY = np.array(contours[0][:,:,1])
    diameters = []
    diameterPosX = []
    for i in range(0, Parameter2):
        idx = np.where(listY == i)[0]
        if(len(idx) == 0):
            # diameters.append(0)
            continue
        xmin = np.amin(listX[idx])
        xmax = np.amax(listX[idx])
        diameters.append(xmax - xmin)
        diameterPosX.append((xmin, xmax))
        
    maxDiameter = np.amax(np.array(diameters))
    maxDiameterIdx = np.argmax(np.array(diameters))


    DimensionOut = maxDiameter
    DimensionOut = round(DimensionOut*RESOLUTION*ZOOM_RATIO, config.FLOAT_NUMBER)
    DiffDimensionOut = round(DimensionOut - Dimension, config.FLOAT_NUMBER)
    if DiffDimensionOut < MinTolerance*(-1) or DiffDimensionOut > MaxTolerance:
        IsDefect = True

    # # Defect info
    # DimensionOut = DimensionOut*RESOLUTION*ZOOM_RATIO
    # DiffDimensionOut = DiffDimensionOut*RESOLUTION*ZOOM_RATIO

    # ovl
    x1 = int(BLEFT)*ZOOM_RATIO
    y1 = int(topROI)*ZOOM_RATIO
    x2 = int(BRIGHT)*ZOOM_RATIO
    y2 = int(bottomROI)*ZOOM_RATIO
    if IsCorrection:
        x1 = diameterPosX[maxDiameterIdx][0] + BLEFT
        x2 = diameterPosX[maxDiameterIdx][1] + BLEFT
        cv2.line(ImageOVL, (x1, 0), (x1, ImageOVL.shape[0]), (0, 255, 255), config.OVLSIZE)
        cv2.line(ImageOVL, (x2, 0), (x2, ImageOVL.shape[0]), (0, 255, 255), config.OVLSIZE)
        cv2.line(ImageOVL, (0, y1), (ImageOVL.shape[1], y1), Color, config.OVLSIZE) #(0, 102, 255)
        cv2.line(ImageOVL, (0, y2), (ImageOVL.shape[1], y2), Color, config.OVLSIZE) #(0, 0, 255)
    else:
        cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    y = (maxDiameterIdx + topROI)*ZOOM_RATIO
    # length = (BRIGHT - BLEFT + 100)*ZOOM_RATIO
    length = x2-x1+100
    draw_dashed_line_fast(ImageOVL, (x1, y), 0, length, 50, 50, (86, 22, 217), config.OVLSIZE)
    
    x1 = int(diameterPosX[maxDiameterIdx][0] + BLEFT)*ZOOM_RATIO
    x2 = int(diameterPosX[maxDiameterIdx][1] + BLEFT)*ZOOM_RATIO
    y = (BBOTTOM - Index*120)*ZOOM_RATIO
    x = int((x1 + x2)/2)
    cv2.arrowedLine(ImageOVL, [x1, y],\
                    [x2, y], Color, config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [x2, y],\
                    [x1, y], Color, config.OVLSIZE, tipLength = 0.05)
    

    # ovl
    textSize = cv2.getTextSize(f'LugT1: {round(DimensionOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    cv2.putText(ImageOVL, f'LugT1: {round(DimensionOut, config.FLOAT_NUMBER)}', (int(x - textSize[0] /2), y - 50), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)


    return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut