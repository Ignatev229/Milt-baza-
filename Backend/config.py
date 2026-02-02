import numpy as np
import cv2

PORT = 27015
NUMBER_PROCESS = 2
# ZOOM_RATIO = 2
OVLSIZE = 5
PADDING = 21
FONT_FAMILY = cv2.FONT_ITALIC
FONT_SIZE = 2
FLOAT_NUMBER = 2
CALIBRATION_FLOAT_NUMBER = 4

TOP_THREAD_DETECTION_MODEL_PATH = 'Inspection/vp.pt'
BOTTOM_NUMBER_READER_MODEL_PATH = 'Inspection/number_reader.pt'



def DebugLog(tab, info):
    print(f"[{tab}]:", info)

def RGB2Hex(rgb):
    return '%02x%02x%02x' % rgb

def Hex2RGB(value):
    value = value.lstrip('#')
    lv = len(value)
    return tuple(int(value[i:i+lv//3], 16) for i in range(0, lv, lv//3))

def AddRectangleOverlayInfos(L, T, R, B, F, OverlayInfos):
    if len(L) == 0:
        return
    padding = 10
    if len(L) > 20:
        x = np.concatenate((np.array(L), np.array(R)))
        y = np.concatenate((np.array(T), np.array(B)))
        left = [np.amin(x) - padding]
        right = [np.amax(x) + padding]
        top = [np.amin(y) - padding]
        bottom = [np.amax(y) + padding]
        x = np.array([left,top,right,top,right,bottom,left,bottom]).transpose().astype(str)
        r = [F + ','.join(i) for i in x]
        OverlayInfos += r
        return OverlayInfos
    # process T > B and L > R
    index = np.where(T > B)
    temp = B[index]
    B[index] = T[index]
    T[index] = temp

    index = np.where(L > R)
    temp = R[index]
    R[index] = L[index]
    L[index] = temp

    L = L - padding
    T = T - padding
    R = R + padding
    B = B + padding
    x = np.array([L,T,R,T,R,B,L,B]).transpose().astype(str)
    r = [F + ','.join(i) for i in x]
    OverlayInfos += r
    return OverlayInfos

def AddContourOverlayInfos(Contour, F, OverlayInfos, Shift = [0, 0]):
    if Contour is None:
        return
    repeat = 1
    if len(Contour) > 2000:
        repeat = 3
    x = np.array([Contour[0:len(Contour):repeat, 0, 0] + Shift[0], Contour[0:len(Contour):repeat, 0, 1] + Shift[1]]).transpose().astype(str).reshape(1,-1)
    r = [F + ','.join(i) for i in x]
    OverlayInfos += r
    return OverlayInfos