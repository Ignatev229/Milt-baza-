import cv2
import numpy as np
import config
from ip_lib import FindFistWhitePixel

def TiltInspect(ImageOVL, LocationRegion, LocationRect, Parameter1, Parameter2, MinHeight, Color, ZOOM_RATIO, RESOLUTION):
    # MinHeight = MinHeight/RESOLUTION/ZOOM_RATIO
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO) # top of finish go down to find center of finish

    # out:
    IsDefect = False
    MinHeightOut = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    locationRegionCrop = LocationRegion[BTOP:BTOP+Parameter2, BLEFT:BRIGHT] 
    # openingRegion = OpeningRectangle1(locationRegionCrop, int(31/ZOOM_RATIO), int(Parameter2/2))
    x,y,w,h = cv2.boundingRect(locationRegionCrop)
    padding = int(w*(1-Parameter1/100.0)/2)
    x1 = x + padding
    x2 = x + w - padding
    region1 = locationRegionCrop[y:y+h, x1:x1+1]
    y1 = FindFistWhitePixel(region1)
    if y1 == -1:
        IsDefect = True
        return IsDefect, ImageOVL, MinHeightOut
    region2 = locationRegionCrop[y:y+h, x2:x2+1]
    y2 = FindFistWhitePixel(region2)
    if y2 == -1:
        IsDefect = True
        return IsDefect, ImageOVL, MinHeightOut
    MinHeightOut = abs(y1 - y2)
    
    # defect info
    MinHeightOut = round(MinHeightOut*RESOLUTION*ZOOM_RATIO, config.FLOAT_NUMBER)

    if MinHeightOut > MinHeight:
        IsDefect = True

    # ovl
    # if IsDefect:
    
    x1 = int(x1 + BLEFT)*ZOOM_RATIO
    y1 = int(y1 + BTOP)*ZOOM_RATIO
    x2 = int(x2 + BLEFT)*ZOOM_RATIO
    y2 = int(y2 + BTOP)*ZOOM_RATIO
    cv2.line(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)
    cv2.drawMarker(ImageOVL, (x1, y1), (255, 0, 0), markerType=cv2.MARKER_CROSS, markerSize=50, thickness=config.OVLSIZE)
    cv2.drawMarker(ImageOVL, (x2, y2), (255, 0, 0), markerType=cv2.MARKER_CROSS, markerSize=50, thickness=config.OVLSIZE)
    cx = int((BLEFT+BRIGHT)/2)
    textSize = cv2.getTextSize(f'Tilt Height: {round(MinHeightOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    cv2.putText(ImageOVL, f'Tilt Height: {round(MinHeightOut, config.FLOAT_NUMBER)}', (int(cx - textSize[0] /2), max(BTOP - 350, 100)), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)


    
    return IsDefect, ImageOVL, MinHeightOut
    