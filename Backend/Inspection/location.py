import cv2
import numpy as np
import time
import config
from ip_lib import ClosingRectangle1, FillUp, OpeningCircle, SelectShapeStd, OpeningRectangle1



def TopLocation(Image, ImageTopMask, ImageOVL, MaxThreshold, ZOOM_RATIO):
    _, region = cv2.threshold(Image, MaxThreshold, 255, cv2.THRESH_BINARY_INV)
    intersectionRegion = cv2.bitwise_and(region, ImageTopMask)
    closingRegion = ClosingRectangle1(intersectionRegion, int(101/ZOOM_RATIO), 1)
    fillupRegion = FillUp(closingRegion)
    openingRegion = OpeningCircle(fillupRegion, int(11/ZOOM_RATIO))
    isPass, selectedRegion, left, top, width, height = SelectShapeStd(openingRegion)

    locationRegion = selectedRegion
    locationRect1 = [left, top, left + width, top + height]

    rect = np.array(locationRect1)*ZOOM_RATIO

    # OVL
    cv2.rectangle(ImageOVL, [rect[0], rect[1]], [rect[2], rect[3]], (0, 255, 0), config.OVLSIZE)

    x = 150#max(int(rect[0] - 400), 150)
    y1 = int(rect[1])
    y2 = int(rect[3])
    cy = int((rect[1] + rect[3])/2)
    w = rect[2] - rect[0]
    h = rect[3] - rect[1]
    cv2.arrowedLine(ImageOVL, [x, y1],\
                [x, y2], (255, 0, 0), config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [x, y2],\
                [x, y1], (255, 0, 0), config.OVLSIZE, tipLength = 0.05)
    
    # h += 4932 # plc move 1100mm # 155,86 mm
    # textSize = cv2.getTextSize(f'Height: {h}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]

    # ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_CLOCKWISE)
    # cv2.putText(ImageOVL, f'Height: {h}', (int(cy - textSize[0]) , x - 50), config.FONT_FAMILY, config.FONT_SIZE, (255, 0, 0), config.OVLSIZE)
    # ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_COUNTERCLOCKWISE)

    return isPass, ImageOVL, locationRegion, locationRect1 

def BotomLocation(Image, ImageOVL, MaxThreshold, ZOOM_RATIO, RESOLUTION):
    _, region = cv2.threshold(Image, MaxThreshold, 255, cv2.THRESH_BINARY_INV)
    closingRegion = ClosingRectangle1(region, 1, int(201/ZOOM_RATIO))
    fillupRegion = FillUp(closingRegion)
    openingRegion = OpeningRectangle1(fillupRegion, 11, int(Image.shape[0]*0.8))
    differenceRegion = cv2.bitwise_xor(openingRegion, fillupRegion)
    openingRegion1 = OpeningCircle(differenceRegion, int(11/ZOOM_RATIO))
    intersectionRegion = cv2.bitwise_and(openingRegion1, closingRegion)
    fillupRegion1 = FillUp(intersectionRegion)
    openingRegion1 = OpeningRectangle1(fillupRegion1, 35, int(Image.shape[0]*0.1))

    isPass, selectedRegion, left, top, width, height = SelectShapeStd(openingRegion1)

    locationRegion = selectedRegion
    locationRect1 = [left, top, left + width, top + height]

    # OVL
    rect = np.array(locationRect1)*ZOOM_RATIO
    cv2.rectangle(ImageOVL, [rect[0], rect[1]], [rect[2], rect[3]], (0, 255, 0), config.OVLSIZE)


    y = max(int(rect[1] - 100), 100)    
    x = int((rect[0] + rect[2])/2)
    w = rect[2] - rect[0]
    h = rect[3] - rect[1]
    cv2.arrowedLine(ImageOVL, [rect[0], y],\
                    [rect[2], y], (255, 0, 0), config.OVLSIZE, tipLength = 0.05)
    cv2.arrowedLine(ImageOVL, [rect[2], y],\
                    [rect[0], y], (255, 0, 0), config.OVLSIZE, tipLength = 0.05)
    textSize = cv2.getTextSize(f'Height: {round(w*RESOLUTION, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
    cv2.putText(ImageOVL, f'Height: {round(w*RESOLUTION, config.FLOAT_NUMBER)}', (int(x - textSize[0]/2), y - 50), config.FONT_FAMILY, config.FONT_SIZE, (255, 0, 0), config.OVLSIZE)

    return isPass, ImageOVL, locationRegion, locationRect1