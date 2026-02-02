import cv2
import numpy as np
import config

def DDimensionInspect(ImageOVL, LocationRegion, LocationRect, \
                Parameter1, Parameter2, Parameter3, Dimension, MinTolerance,\
                MaxTolerance, Color, ZOOM_RATIO, RESOLUTION, IsCorrection = True):
    # in:
    Parameter1 = int(Parameter1/RESOLUTION/ZOOM_RATIO) # distance from top finish line to bottom D measurement region
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO) # the inset distance from outer edge of the locking ring to the point where the locking ring height is to be measured
    Parameter3 = int(Parameter3/RESOLUTION/ZOOM_RATIO) # height of measurement region
    # Dimension = Dimension/RESOLUTION/ZOOM_RATIO # 
    # MinTolerance = MinTolerance/RESOLUTION/ZOOM_RATIO # 
    # MaxTolerance = MaxTolerance/RESOLUTION/ZOOM_RATIO # 


    # out:
    IsDefect = False
    DimensionOut = 0
    DiffDimensionOut = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    bottomROI = BTOP+Parameter1
    topROI = max(bottomROI-Parameter3+1, 0)
    locationRegionCrop = LocationRegion[topROI:bottomROI, BLEFT:BRIGHT] 
    x,_,_,_ = cv2.boundingRect(locationRegionCrop)
    posX = x + Parameter2
    region = locationRegionCrop[:,x:posX]
    _,y,_,h = cv2.boundingRect(region)

    d = y + h + topROI - BTOP
    DimensionOut = y + h + topROI - BTOP
    DimensionOut = round(DimensionOut*RESOLUTION*ZOOM_RATIO, config.FLOAT_NUMBER)
    DiffDimensionOut = round(DimensionOut - Dimension, config.FLOAT_NUMBER)
    if DiffDimensionOut < MinTolerance*(-1) or DiffDimensionOut > MaxTolerance:
        IsDefect = True


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

    x1 = int(BLEFT + x)*ZOOM_RATIO
    y1 = int(topROI + y)*ZOOM_RATIO
    x2 = int(BLEFT + posX)*ZOOM_RATIO
    y2 = int(topROI + y + h)*ZOOM_RATIO
    cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    x = max(int(BLEFT + x - 300), 200)*ZOOM_RATIO
    y1 = int(BTOP)*ZOOM_RATIO
    y2 = int(BTOP + d)*ZOOM_RATIO
    cv2.arrowedLine(ImageOVL, [x, y1],\
                    [x, y2], Color, config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [x , y2],\
                    [x, y1], Color, config.OVLSIZE, tipLength = 0.05)

    # # Defect info
    # DimensionOut = DimensionOut*RESOLUTION*ZOOM_RATIO
    # DiffDimensionOut = DiffDimensionOut*RESOLUTION*ZOOM_RATIO

    cy = ImageOVL.shape[0] - int((y1 + y2)/2)
    textSize = cv2.getTextSize(f'D: {round(DimensionOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]

    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_CLOCKWISE)
    cv2.putText(ImageOVL, f'D: {round(DimensionOut, config.FLOAT_NUMBER)}', (int(cy - textSize[0]/2), x - 50), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)
    ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_COUNTERCLOCKWISE)


    return IsDefect, ImageOVL, DimensionOut, DiffDimensionOut