import cv2
import numpy as np

import config

from ip_lib import OpeningRectangle1, SelectShapeWidthHeight


def KnockoutInspect(ImageOVL, LocationRegion, LocationRect, \
                        Parameter3, Parameter4, OpeningRatio, MinKnockout, MaxKnockout,\
                        Color, ZOOM_RATIO, RESOLUTION):
    # in:
    MinKnockout = int(MinKnockout/RESOLUTION/ZOOM_RATIO) # 
    MaxKnockout = int(MaxKnockout/RESOLUTION/ZOOM_RATIO) # 
    Parameter3 = int(Parameter3/RESOLUTION/ZOOM_RATIO) # distance from top finish line to bottom measurement region
    Parameter4 = int(Parameter4/RESOLUTION/ZOOM_RATIO) # height of measurement region
    OpeningRatio = int(OpeningRatio/RESOLUTION/ZOOM_RATIO) # 


    # out:
    IsDefect = False
    MinKnockoutOut = 0
    MaxKnockoutOut = 0
    NumberDefect = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    bottomROI = BTOP+Parameter3
    topROI = max(bottomROI-Parameter4+1, 0)
    locationRegionCrop = LocationRegion[topROI:bottomROI, BLEFT:BRIGHT] 

    # ovl
    x1 = int(BLEFT)*ZOOM_RATIO
    y1 = int(topROI)*ZOOM_RATIO
    x2 = int(BRIGHT)*ZOOM_RATIO
    y2 = int(bottomROI)*ZOOM_RATIO
    cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), (255, 0, 0), config.OVLSIZE)

    openingRegion = OpeningRectangle1(locationRegionCrop, 1, int(OpeningRatio*3))
    # contours, _ = cv2.findContours(locationRegionCrop, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    # if len(contours) == 0:
    #     return IsDefect, ImageOVL, MinKnockoutOut, NumberDefect
    # contour = max(contours, key=cv2.contourArea)
    # approx = cv2.approxPolyDP(contour,int(Parameter4*0.5),True)
    # openingRegion = np.zeros_like(locationRegionCrop)
    # cv2.drawContours(openingRegion, [approx], -1, 255, -1)
    
    differenceRegion = cv2.bitwise_xor(locationRegionCrop, openingRegion)

    isPass, leftOut, topOut, widthOut, heightOut = SelectShapeWidthHeight(differenceRegion, \
                MinKnockout, 5, MaxKnockout, 999999)

    if not isPass:
        return IsDefect, ImageOVL, MinKnockoutOut, MaxKnockoutOut, NumberDefect
    
    padding = 10
    for i in range(len(leftOut)):
        x1 = int(BLEFT + leftOut[i])*ZOOM_RATIO - padding
        y1 = int(topROI + topOut[i])*ZOOM_RATIO - padding
        x2 = int(BLEFT + leftOut[i] + widthOut[i])*ZOOM_RATIO + padding
        y2 = int(topROI + topOut[i] + heightOut[i])*ZOOM_RATIO + padding
        cv2.rectangle(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)

    
    IsDefect = True
    MinKnockoutOut = np.amin(widthOut)*RESOLUTION*ZOOM_RATIO
    MaxKnockoutOut = np.amax(widthOut)*RESOLUTION*ZOOM_RATIO
    NumberDefect = len(leftOut)

    return IsDefect, ImageOVL, MinKnockoutOut, MaxKnockoutOut, NumberDefect