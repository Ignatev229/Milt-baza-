import cv2
import numpy as np
import math
import config
from ip_lib import draw_dashed_line_fast, FindFistWhitePixel

def FindMainHorizontalExist(region):
    contours, _ = cv2.findContours(region, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if len(contours) != 1:
        return False, 0, (0, 0), (0, 0)
    rect = cv2.minAreaRect(contours[0])
    box = cv2.boxPoints(rect)
    box = np.int0(box)
    diffX1 = box[0][0] - box[1][0]
    diffY1 = box[0][1] - box[1][1]
    diffX2 = box[2][0] - box[1][0]
    diffY2 = box[2][1] - box[1][1]

    if abs(diffX1) > abs(diffX2):
        cx1 = int((box[0][0] + box[3][0])/2)
        cy1 = int((box[0][1] + box[3][1])/2)
        cx2 = int((box[1][0] + box[2][0])/2)
        cy2 = int((box[1][1] + box[2][1])/2)
        diffX = cx1 - cx2
        diffY = cy1 - cy2
        baseAngle = math.atan2(diffY, diffX)*180/math.pi
    else:
        cx1 = int((box[0][0] + box[1][0])/2)
        cy1 = int((box[0][1] + box[1][1])/2)
        cx2 = int((box[3][0] + box[2][0])/2)
        cy2 = int((box[3][1] + box[2][1])/2)
        diffX = cx1 - cx2
        diffY = cy1 - cy2
        baseAngle = math.atan2(diffY, diffX)*180/math.pi

    if baseAngle >= 180:
        baseAngle -= 180
    elif baseAngle < 0:
        baseAngle += 180

    return True, baseAngle, (cx1, cy1), (cx2, cy2)

def FindMainVerticalExist(region):
    contours, _ = cv2.findContours(region, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if len(contours) != 1:
        return False, 0, (0, 0), (0, 0)
    rect = cv2.minAreaRect(contours[0])
    box = cv2.boxPoints(rect)
    box = np.int0(box)
    diffX1 = box[0][0] - box[1][0]
    diffY1 = box[0][1] - box[1][1]
    diffX2 = box[2][0] - box[1][0]
    diffY2 = box[2][1] - box[1][1]

    if abs(diffY1) > abs(diffY2):
        cx1 = int((box[0][0] + box[3][0])/2)
        cy1 = int((box[0][1] + box[3][1])/2)
        cx2 = int((box[1][0] + box[2][0])/2)
        cy2 = int((box[1][1] + box[2][1])/2)
        diffX = cx1 - cx2
        diffY = cy1 - cy2
        baseAngle = math.atan2(diffY, diffX)*180/math.pi
    else:
        cx1 = int((box[0][0] + box[1][0])/2)
        cy1 = int((box[0][1] + box[1][1])/2)
        cx2 = int((box[3][0] + box[2][0])/2)
        cy2 = int((box[3][1] + box[2][1])/2)
        diffX = cx1 - cx2
        diffY = cy1 - cy2
        baseAngle = math.atan2(diffY, diffX)*180/math.pi

    if baseAngle >= 180:
        baseAngle -= 180
    elif baseAngle < 0:
        baseAngle += 180

    return True, baseAngle, (cx1, cy1), (cx2, cy2)

def LeanInspectBK(ImageOVL, LocationRegion, LocationRect, Parameter1, Parameter2, MinAngle, Color, ZOOM_RATIO, RESOLUTION):
    Parameter1 = int(Parameter1/RESOLUTION/ZOOM_RATIO) # PIXEL/ZOOM_RATIO
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO)
    # out:
    IsDefect = False
    MinAngleOut = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    bottomROI = BTOP+Parameter2
    # bottomRegion = LocationRegion[BTOP:BBOTTOM, BLEFT:BRIGHT-Parameter1]
    topRegion = LocationRegion[BTOP:bottomROI, BLEFT:BRIGHT]

    # # process bottom
    # isPass, bottomAngle, bP1, bP2 = FindMainHorizontalExist(bottomRegion)
    # if not isPass:
    #     return IsDefect, ImageOVL, MinAngleOut
    bottomAngle = 90

    # process top
    isPass, topAngle, tP1, tP2 = FindMainVerticalExist(topRegion)
    if not isPass:
        IsDefect = True
        return IsDefect, ImageOVL, MinAngleOut

    MinAngleOut = round(abs(bottomAngle - topAngle), config.FLOAT_NUMBER)
    if MinAngleOut > MinAngle:
        IsDefect = True

    # # ovl
    # if bP1[0] < bP2[0]:
    #     x1 = int(bP1[0] + BLEFT)*config.ZOOM_RATIO
    #     y1 = int(bP1[1] + BTOP)*config.ZOOM_RATIO
    # else:
    #     x1 = int(bP2[0] + BLEFT)*config.ZOOM_RATIO
    #     y1 = int(bP2[1] + BTOP)*config.ZOOM_RATIO
    # length = (BRIGHT - BLEFT + 100)*config.ZOOM_RATIO
    # draw_dashed_line_fast(ImageOVL, (x1, y1), bottomAngle, length, 50, 50, (0, 255, 0), config.OVLSIZE)

    # if IsDefect:
    # ovl
    if tP1[1] > tP2[1]:
        x1 = int(tP1[0] + BLEFT)*ZOOM_RATIO
        y1 = int(tP1[1] + BTOP)*ZOOM_RATIO
    else:
        x1 = int(tP2[0] + BLEFT)*ZOOM_RATIO
        y1 = int(tP2[1] + BTOP)*ZOOM_RATIO
    length = (Parameter2 + 400)*ZOOM_RATIO
    draw_dashed_line_fast(ImageOVL, (x1, y1 + 200), topAngle + 180, length, 50, 50, Color, config.OVLSIZE)
    cx = int((BLEFT+BRIGHT)/2)
    textSize = cv2.getTextSize(f'Lean Diff Angle: {round(MinAngleOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    cv2.putText(ImageOVL, f'Lean Diff Angle: {round(MinAngleOut, config.FLOAT_NUMBER)}', (int(cx - textSize[0] /2), max(BTOP - 250, 200)), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)


    return IsDefect, ImageOVL, MinAngleOut

def LeanInspect(ImageOVL, LocationRegion, LocationRect, Parameter1, Parameter2, MinDeviation, Color, ZOOM_RATIO, RESOLUTION):
    Parameter1 = int(Parameter1/RESOLUTION/ZOOM_RATIO) # PIXEL/ZOOM_RATIO
    Parameter2 = int(Parameter2/RESOLUTION/ZOOM_RATIO)
    # out:
    IsDefect = False
    MinDeviationOut = 0

    BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
    bottomROI = BTOP+Parameter2
    # bottomRegion = LocationRegion[BTOP:BBOTTOM, BLEFT:BRIGHT-Parameter1]
    locationRegionCrop = LocationRegion[BTOP:bottomROI, BLEFT:BRIGHT]

    x,y,w,h = cv2.boundingRect(locationRegionCrop)
    padding = int(w*(1-85/100.0)/2)
    x1 = x + padding
    x2 = x + w - padding
    region1 = locationRegionCrop[y:y+h, x1:x1+1]
    y1 = FindFistWhitePixel(region1)
    if y1 == -1:
        IsDefect = True
        return IsDefect, ImageOVL, MinDeviationOut
    region2 = locationRegionCrop[y:y+h, x2:x2+1]
    y2 = FindFistWhitePixel(region2)
    if y2 == -1:
        IsDefect = True
        return IsDefect, ImageOVL, MinDeviationOut

    dx = x2-x1
    dy = y2-y1
    length = 1000
    pt1 = (int(x1 - dx * length), int(y1 - dy * length))
    pt2 = (int(x1 + dx * length), int(y1 + dy * length))
    
    mask = np.zeros_like(locationRegionCrop)
    cv2.line(mask, pt1, pt2, 255, 1)

    regionIntersection = cv2.bitwise_and(mask, locationRegionCrop)
    # Find (y, x) coordinates of pixels with value 255
    regionIntersectionPoints = np.argwhere(regionIntersection == 255)
    listX = regionIntersectionPoints[:,1]
    listY = regionIntersectionPoints[:,0]
    idx1 = np.argmin(listX)
    idx2 = np.argmax(listX)
    x1 = listX[idx1]
    y1 = listY[idx1]
    x2 = listX[idx2]
    y2 = listY[idx2]

    MinDeviationOut = abs(y1 - y2)
    
    # defect info
    MinDeviationOut = round(MinDeviationOut*RESOLUTION*ZOOM_RATIO, config.FLOAT_NUMBER)

    if MinDeviationOut > MinDeviation:
        IsDefect = True

    # ovl
    x1 = int(x1 + BLEFT)*ZOOM_RATIO
    y1 = int(y1 + BTOP)*ZOOM_RATIO
    x2 = int(x2 + BLEFT)*ZOOM_RATIO
    y2 = int(y2 + BTOP)*ZOOM_RATIO
    cv2.line(ImageOVL, (x1, y1), (x2, y2), Color, config.OVLSIZE)
    # cv2.drawMarker(ImageOVL, (x1, y1), (255, 0, 0), markerType=cv2.MARKER_CROSS, markerSize=50, thickness=config.OVLSIZE)
    # cv2.drawMarker(ImageOVL, (x2, y2), (255, 0, 0), markerType=cv2.MARKER_CROSS, markerSize=50, thickness=config.OVLSIZE)
    cx = int((BLEFT+BRIGHT)/2)
    textSize = cv2.getTextSize(f'Lean Deviation: {round(MinDeviationOut, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    cv2.putText(ImageOVL, f'Lean Deviation: {round(MinDeviationOut, config.FLOAT_NUMBER)}', (int(cx - textSize[0] /2), max(BTOP - 250, 200)), config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)

    return IsDefect, ImageOVL, MinDeviationOut


