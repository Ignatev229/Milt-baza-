import numpy as np
from enum import Enum
import os
import json

from struct_define import TRACK_ID


class Singleton(object):
    instance = None
    def __new__(class_, *args, **kwargs):
        if not isinstance(class_.instance, class_):
            class_.instance = object.__new__(class_, *args, **kwargs)
        return class_.instance

class AppConfigParam(Singleton):
    def __init__(self) -> None:
        self.Init()
    def Init(self):
        self.resolution = {}
        self.resolution[TRACK_ID.BOTTOM] = 0.05
        # self.resolution[TRACK_ID.MID] = 0.05
        self.resolution[TRACK_ID.TOP] = 0.05

class TeachData(Singleton):
    def __init__(self) -> None:
        pass

class VARIABLE_TYPE(Enum):
    BOOL = 0
    INT = 1
    FLOAT = 2

ALARM_RANGE = 0.05

class HeightInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()

    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.height = 197.5
        self.minTolerance = 1.5
        self.maxTolerance = 1.5
        self.liftingMechanismPos = 4932
        self.CalculateAlarm()
    
    def CalculateAlarm(self):
        self.minAlarm = self.height - self.minTolerance
        self.maxAlarm = self.height + self.maxTolerance
        self.minWarning = self.minAlarm + ALARM_RANGE
        self.maxWarning = self.maxAlarm - ALARM_RANGE
        self.diffWarning = 1.5
        self.diffAlarm = 3
 
class WeightInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()

    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.weight = 355
        self.minTolerance = 10
        self.maxTolerance = 10
        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = self.weight - self.minTolerance
        self.maxAlarm = self.weight + self.maxTolerance
        self.minWarning = self.minAlarm + ALARM_RANGE
        self.maxWarning = self.maxAlarm - ALARM_RANGE
        self.diffWarning = 10
        self.diffAlarm = 20

class NonRoundShapeInspectItemParam():
    def __init__(self) -> None:
        self.Init()

    def Init(self):
        self.rectParameter = 200
        self.rectShrt = 60
        self.minRectShrtTolerance = 1.5
        self.maxRectShrtTolerance = 1.5
        self.rectLong = 60
        self.minRectLongTolerance = 1.5
        self.maxRectLongTolerance = 1.5
        self.rectDiag = 60
        self.minRectDiagTolerance = 1.5
        self.maxRectDiagTolerance = 1.5

        self.sqrParameter = 200
        self.sqrSide = 60
        self.minSqrSideTolerance = 1.5
        self.maxSqrSideTolerance = 1.5
        self.sqrDiag = 60
        self.minSqrDiagTolerance = 1.5
        self.maxSqrDiagTolerance = 1.5

        self.ovlParameter = 200
        self.ovlShrt = 60
        self.minOvlShrtTolerance = 1.5
        self.maxOvlShrtTolerance = 1.5
        self.ovlLong = 60
        self.minOvlLongTolerance = 1.5
        self.maxOvlLongTolerance = 1.5

        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minRectShrtAlarm = self.rectShrt - self.minRectShrtTolerance
        self.maxRectShrtAlarm = self.rectShrt + self.maxRectShrtTolerance
        self.minRectShrtWarning = self.minRectShrtAlarm + ALARM_RANGE
        self.maxRectShrtWarning = self.maxRectShrtAlarm - ALARM_RANGE

        self.minRectLongAlarm = self.rectLong - self.minRectLongTolerance
        self.maxRectLongAlarm = self.rectLong + self.maxRectLongTolerance
        self.minRectLongWarning = self.minRectLongAlarm + ALARM_RANGE
        self.maxRectLongWarning = self.maxRectLongAlarm - ALARM_RANGE

        self.minRectDiagAlarm = self.rectDiag - self.minRectDiagTolerance
        self.maxRectDiagAlarm = self.rectDiag + self.maxRectDiagTolerance
        self.minRectDiagWarning = self.minRectDiagAlarm + ALARM_RANGE
        self.maxRectDiagWarning = self.maxRectDiagAlarm - ALARM_RANGE

        self.minSqrSizeAlarm = self.sqrSide - self.minSqrSideTolerance
        self.maxSqrSizeAlarm = self.sqrSide + self.maxSqrSideTolerance
        self.minSqrSizeWarning = self.minSqrSizeAlarm + ALARM_RANGE
        self.maxSqrSizeWarning = self.maxSqrSizeAlarm - ALARM_RANGE

        self.minSqrDiagAlarm = self.sqrDiag - self.minSqrDiagTolerance
        self.maxSqrDiagAlarm = self.sqrDiag + self.maxSqrDiagTolerance
        self.minSqrDiagWarning = self.minSqrDiagAlarm + ALARM_RANGE
        self.maxSqrDiagWarning = self.maxSqrDiagAlarm - ALARM_RANGE

        self.minOvlShrtAlarm = self.ovlShrt - self.minOvlShrtTolerance
        self.maxOvlShrtAlarm = self.ovlShrt + self.maxOvlShrtTolerance
        self.minOvlShrtWarning = self.minOvlShrtAlarm + ALARM_RANGE
        self.maxOvlShrtWarning = self.maxOvlShrtAlarm - ALARM_RANGE

        self.minOvlLongAlarm = self.ovlLong - self.minOvlLongTolerance
        self.maxOvlLongAlarm = self.ovlLong + self.maxOvlLongTolerance
        self.minOvlLongWarning = self.minOvlLongAlarm + ALARM_RANGE
        self.maxOvlLongWarning = self.maxOvlLongAlarm - ALARM_RANGE

class NonRoundShapeInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()

    def Init(self):
        self.color = (0, 0, 255)
        self.maxNumberDimension = 8
        self.dimensionsName = [1,2,3,4,5,6,7,8]
        self.enable = True
        self.shape = 0 # 0: rectangle, 1: square, 2: oval
        self.numberDimension = 1    

        self.dimensions = [NonRoundShapeInspectItemParam(), NonRoundShapeInspectItemParam(),
                    NonRoundShapeInspectItemParam(), NonRoundShapeInspectItemParam(),
                    NonRoundShapeInspectItemParam(), NonRoundShapeInspectItemParam(),
                    NonRoundShapeInspectItemParam(), NonRoundShapeInspectItemParam()]

        self.CalculateAlarm()

    def CalculateAlarm(self):
        for d in self.dimensions:
            d.CalculateAlarm()

class BodyRItemParam():
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.height = 100     
        self.dimension = 79.3     
        self.minTolerance = 1.5
        self.maxTolerance = 1.5
        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = self.dimension - self.minTolerance
        self.maxAlarm = self.dimension + self.maxTolerance
        self.minWarning = self.minAlarm + ALARM_RANGE
        self.maxWarning = self.maxAlarm - ALARM_RANGE
        self.diffWarning = 0.3
        self.diffAlarm = 0.6

class BodyRInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.maxNumberDimension = 23
        self.dimensionsName = [5,6,7,8,57,58,59,60,61,62,63,64,71,72,73,74,75,76,77,78,79,80,81]
        self.enable = True
        self.numberDimension = 1    
        self.dimensions = [BodyRItemParam(), BodyRItemParam(), BodyRItemParam(), BodyRItemParam(),
                           BodyRItemParam(), BodyRItemParam(), BodyRItemParam(), BodyRItemParam(),
                           BodyRItemParam(), BodyRItemParam(), BodyRItemParam(), BodyRItemParam(),
                           BodyRItemParam(), BodyRItemParam(), BodyRItemParam(), BodyRItemParam(),
                           BodyRItemParam(), BodyRItemParam(), BodyRItemParam(), BodyRItemParam(),
                           BodyRItemParam(), BodyRItemParam(), BodyRItemParam()] 
        self.CalculateAlarm()

    def CalculateAlarm(self):
        for d in self.dimensions:
            d.CalculateAlarm()

class LeanInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.parameter1 = 35     
        self.parameter2 = 35 
        self.minDeviation = 1
        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = 0
        self.maxAlarm = self.minDeviation
        self.minWarning = 0
        self.maxWarning = self.minDeviation
        self.diffWarning = 5
        self.diffAlarm = 10

class BentNeckInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.angle = 45     
        self.minTolerance = 5
        self.maxTolerance = 5

        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = self.angle - self.minTolerance
        self.maxAlarm = self.angle + self.maxTolerance
        self.minWarning = self.minAlarm + ALARM_RANGE
        self.maxWarning = self.maxAlarm - ALARM_RANGE
        self.diffWarning = 5
        self.diffAlarm = 10

class TiltInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.parameter1 = 85 # %     
        self.parameter2 = 10     
        self.minHeight = 0.3
        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = 0
        self.maxAlarm = self.minHeight
        self.minWarning = 0
        self.maxWarning = self.maxAlarm - ALARM_RANGE
        self.diffWarning = 0.3
        self.diffAlarm = 0.6

class FinishDimensionInspectParam():
    def __init__(self, enable, parameter1, parameter2, parameter3, dimension, minTolerance, maxTolerance,
                 minAlarm, minWarning, maxWarning, maxAlarm, diffWarning, diffAlarm) -> None:
        self.color = (0, 0, 255)
        self.enable = enable
        self.parameter1 = parameter1     
        self.parameter2 = parameter2     
        self.parameter3 = parameter3     
        self.dimension = dimension     
        self.minTolerance = minTolerance
        self.maxTolerance = maxTolerance
        # self.minAlarm = minAlarm
        # self.minWarning = minWarning
        # self.maxWarning = maxWarning
        # self.maxAlarm = maxAlarm
        self.diffWarning = diffWarning
        self.diffAlarm = diffAlarm

        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = self.dimension - self.minTolerance
        self.maxAlarm = self.dimension + self.maxTolerance
        self.minWarning = self.minAlarm + ALARM_RANGE
        self.maxWarning = self.maxAlarm - ALARM_RANGE

class GroupFinishDimensionInspect(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.dimensionF = FinishDimensionInspectParam(True, 10, 0, 0, 24.9, 0.3, 0.3, 23.5, 24, 25, 26, 0.3, 0.6)
        self.dimensionA = FinishDimensionInspectParam(True, 17.4, 0, 0, 27.7, 0.3, 0.3, 25.5, 26.5, 28, 29.5, 0.3, 0.6)
        self.dimensionT = FinishDimensionInspectParam(True, 15.4, 10, 0, 27.1, 0.3, 0.3, 25.5, 26.5, 28, 29.5, 0.3, 0.6)
        self.dimensionE = FinishDimensionInspectParam(True, 17.4, 10, 0, 25.5, 0.3, 0.3, 23.5, 24, 26, 26.5, 0.3, 0.6)
        self.dimensionD = FinishDimensionInspectParam(True, 18, 1, 5, 15.4, 0.25, 0.25, 14, 14.5, 16, 16.5, 0.25, 0.5)
        self.dimensionB = FinishDimensionInspectParam(True, 18, 5, 0, 27, 0.3, 0.3, 25.5, 26.5, 28, 29.5, 0.3, 0.6)
        self.dimensionS1 = FinishDimensionInspectParam(True, 2.2, 0.8, 0, 5, 0.3, 0.3, 13.5, 14, 15.5, 16, 0.3, 0.6)
        self.dimensionH = FinishDimensionInspectParam(True, 10, 28, 0, 28.3, 0.3, 0.3, 27, 27.5, 28.5, 29.5, 0.3, 0.6)
        self.dimensionLugT = FinishDimensionInspectParam(True, 17, 8, 1, 27, 0.3, 0.3, 26, 26.5, 27.5, 28.5, 0.3, 0.6)
        self.dimensionLugT1 = FinishDimensionInspectParam(True, 18, 8, 1, 26, 0.3, 0.3, 26, 26.5, 27.5, 28.5, 0.3, 0.6)
        self.dimensionDAngle = FinishDimensionInspectParam(True, 17.5, 2, 5, 0, 10, 10, 0, 0, 5, 10, 5, 10)

        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.dimensionF.CalculateAlarm()
        self.dimensionA.CalculateAlarm()
        self.dimensionT.CalculateAlarm()
        self.dimensionE.CalculateAlarm()
        self.dimensionD.CalculateAlarm()
        self.dimensionB.CalculateAlarm()
        self.dimensionS1.CalculateAlarm()
        self.dimensionH.CalculateAlarm()
        self.dimensionLugT.CalculateAlarm()
        self.dimensionLugT1.CalculateAlarm()
        self.dimensionDAngle.CalculateAlarm()

class FlangeInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.parameter1 = 0.3     
        self.parameter2 = 2
        self.parameter3 = 12
        self.parameter4 = 9

        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = self.parameter1
        self.maxAlarm = 999999
        self.minWarning = self.parameter1
        self.maxWarning = 999999
        self.diffWarning = 0.3
        self.diffAlarm = 0.6

class KnockoutInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.parameter1 = 0.3
        self.parameter2 = 2
        self.parameter3 = 12
        self.parameter4 = 9
        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = self.parameter1
        self.maxAlarm = 999999
        self.minWarning = self.parameter1
        self.maxWarning = 999999
        self.diffWarning = 0.3
        self.diffAlarm = 0.6

class PushupBodyInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.pushup = 3     
        self.minTolerance = 0.3
        self.maxTolerance = 0.3

        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = self.pushup - self.minTolerance
        self.maxAlarm = self.pushup + self.maxTolerance
        self.minWarning = self.minAlarm + ALARM_RANGE
        self.maxWarning = self.maxAlarm - ALARM_RANGE
        self.diffWarning = 0.3
        self.diffAlarm = 0.6

class InsideNeckInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.diameter = 24     
        self.minTolerance = 0.3 
        self.maxTolerance = 0.3 

        self.CalculateAlarm()

    def CalculateAlarm(self):
        self.minAlarm = self.diameter - self.minTolerance
        self.maxAlarm = self.diameter + self.maxTolerance
        self.minWarning = self.minAlarm + ALARM_RANGE
        self.maxWarning = self.maxAlarm - ALARM_RANGE
        self.diffWarning = 0.3
        self.diffAlarm = 0.6

class WallThicknessInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.thickness = 1     
        self.minTolerance = 0.3 
        self.maxTolerance = 0.3 
        
class SeamInspectParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.bodyHeight = 90     
        self.minBodyHeightTolerance = 1 
        self.maxBodyHeightTolerance = 1 
        self.bottomHeight = 50     
        self.minBottomHeightTolerance = 1 
        self.maxBottomHeightTolerance = 1 

class CalibCameraPositionParam(Singleton):
    def __init__(self) -> None:
        self.Init()
        
    def Init(self):
        self.color = (0, 0, 255)
        self.enable = True
        self.toolHeight = 300     
        self.toolWidth = 30
        self.hideBottleHeight = {}
        self.hideBottleHeight[TRACK_ID.BOTTOM] = 110.0778
        self.hideBottleHeight[TRACK_ID.TOP] = 258.4
        self.maxBottleHeightInBottom = 220

class NumberCodeDecodeParam(Singleton):
    def __init__(self) -> None:
        self.Init()

    def Init(self):
        self.color = (255, 0, 0)
        self.enable = True
        self.codeNumber = 1
        self.bottomROI = 5 # from bottom of bottle to bottom of ROI
        self.heightROI = 20 # 

appConfigParam = AppConfigParam()
calibCameraPositionParam = CalibCameraPositionParam()

heightInspectParam = HeightInspectParam()
weightInspectParam = WeightInspectParam()
nonRoundShapeInspectParam = NonRoundShapeInspectParam()
bodyRInspectParam = BodyRInspectParam()
leanInspectParam = LeanInspectParam()
bentNeckInspectParam = BentNeckInspectParam()
tiltInspectParam = TiltInspectParam()
groupFinishDimensionInspect = GroupFinishDimensionInspect()
flangeInspectParam = FlangeInspectParam()
knockoutInspectParam = KnockoutInspectParam()
pushupBodyInspectParam = PushupBodyInspectParam()
insideNeckInspectParam = InsideNeckInspectParam()
wallThicknessInspectParam = WallThicknessInspectParam()
seamInspectParam = SeamInspectParam()
numberCodeDecodeParam = NumberCodeDecodeParam()

def ExtractFile(path: str):
    f = open(path, "r")
    data = np.array(f.readlines())
    data = [i.replace("\n", "") for i in data]
    startIndex = [i for i in range(len(data)) if ']' in data[i]]
    endIndex = [i for i in range(len(data)) if data[i] == '']
    value = {}
    for i in range(len(startIndex)):
        value[data[startIndex[i]].replace('[','').replace(']','')] = data[startIndex[i]+1:endIndex[i]]
    return value

def GetValue(data, key: str, value, type: VARIABLE_TYPE):
    index = [i for i in range(len(data)) if key in data[i] and '=' in data[i]]
    if len(index) > 0:
        if type == VARIABLE_TYPE.BOOL:
            value = int(data[index[0]].split("=")[1]) == 1
        elif type == VARIABLE_TYPE.INT:
            value = int(data[index[0]].split("=")[1])
        elif type == VARIABLE_TYPE.FLOAT:
            value = float(data[index[0]].split("=")[1])

    return value

def ReadVisionParam(path: str):
    if not os.path.exists(path):
        return False
    try:
        data = ExtractFile(path)


        appConfigParam.Init()
        calibCameraPositionParam.Init()
        heightInspectParam.Init()
        weightInspectParam.Init()
        nonRoundShapeInspectParam.Init()
        bodyRInspectParam.Init()
        leanInspectParam.Init()
        bentNeckInspectParam.Init()
        tiltInspectParam.Init()
        groupFinishDimensionInspect.Init()
        flangeInspectParam.Init()
        knockoutInspectParam.Init()
        pushupBodyInspectParam.Init()
        insideNeckInspectParam.Init()
        wallThicknessInspectParam.Init()
        seamInspectParam.Init()
        numberCodeDecodeParam.Init()

        key = "class HeightInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            heightInspectParam.enable = GetValue(param, key, heightInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"height"
            heightInspectParam.height = GetValue(param, key, heightInspectParam.height, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            heightInspectParam.minTolerance = GetValue(param, key, heightInspectParam.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            heightInspectParam.maxTolerance = GetValue(param, key, heightInspectParam.maxTolerance, VARIABLE_TYPE.FLOAT)
            heightInspectParam.liftingMechanismPos = CalculateLiftingMechanismPos(TRACK_ID.TOP, heightInspectParam.height)            

        key = "class WeightInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            weightInspectParam.enable = GetValue(param, key, weightInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"weight"
            weightInspectParam.weight = GetValue(param, key, weightInspectParam.weight, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            weightInspectParam.minTolerance = GetValue(param, key, weightInspectParam.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            weightInspectParam.maxTolerance = GetValue(param, key, weightInspectParam.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class NonRoundShapeInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            nonRoundShapeInspectParam.enable = GetValue(param, key, nonRoundShapeInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"shape"
            nonRoundShapeInspectParam.shape = GetValue(param, key, nonRoundShapeInspectParam.shape, VARIABLE_TYPE.INT)
            key = f"numberDimension"
            nonRoundShapeInspectParam.numberDimension = GetValue(param, key, nonRoundShapeInspectParam.numberDimension, VARIABLE_TYPE.INT)

        for i in range(nonRoundShapeInspectParam.maxNumberDimension):
            key = f"class NonRoundShapeInspect :: dimension{nonRoundShapeInspectParam.dimensionsName[i]}"
            
            if key in data.keys():
                param = data[key]
                
                key = f"rectParameter"
                nonRoundShapeInspectParam.dimensions[i].rectParameter = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].rectParameter, VARIABLE_TYPE.FLOAT)
                key = f"rectShrt"
                nonRoundShapeInspectParam.dimensions[i].rectShrt = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].rectShrt, VARIABLE_TYPE.FLOAT)
                key = f"minRectShrtTolerance"
                nonRoundShapeInspectParam.dimensions[i].minRectShrtTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].minRectShrtTolerance, VARIABLE_TYPE.FLOAT)
                key = f"maxRectShrtTolerance"
                nonRoundShapeInspectParam.dimensions[i].maxRectShrtTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].maxRectShrtTolerance, VARIABLE_TYPE.FLOAT)

                key = f"rectLong"
                nonRoundShapeInspectParam.dimensions[i].rectLong = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].rectLong, VARIABLE_TYPE.FLOAT)
                key = f"minRectLongTolerance"
                nonRoundShapeInspectParam.dimensions[i].minRectLongTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].minRectLongTolerance, VARIABLE_TYPE.FLOAT)
                key = f"maxRectLongTolerance"
                nonRoundShapeInspectParam.dimensions[i].maxRectLongTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].maxRectLongTolerance, VARIABLE_TYPE.FLOAT)

                key = f"rectDiag"
                nonRoundShapeInspectParam.dimensions[i].rectDiag = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].rectDiag, VARIABLE_TYPE.FLOAT)
                key = f"minRectDiagTolerance"
                nonRoundShapeInspectParam.dimensions[i].minRectDiagTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].minRectDiagTolerance, VARIABLE_TYPE.FLOAT)
                key = f"maxRectDiagTolerance"
                nonRoundShapeInspectParam.dimensions[i].maxRectDiagTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].maxRectDiagTolerance, VARIABLE_TYPE.FLOAT)


                key = f"sqrParameter"
                nonRoundShapeInspectParam.dimensions[i].sqrParameter = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].sqrParameter, VARIABLE_TYPE.FLOAT)
                key = f"sqrSide"
                nonRoundShapeInspectParam.dimensions[i].sqrSide = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].sqrSide, VARIABLE_TYPE.FLOAT)
                key = f"minSqrSideTolerance"
                nonRoundShapeInspectParam.dimensions[i].minSqrSideTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].minSqrSideTolerance, VARIABLE_TYPE.FLOAT)
                key = f"maxSqrSideTolerance"
                nonRoundShapeInspectParam.dimensions[i].maxSqrSideTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].maxSqrSideTolerance, VARIABLE_TYPE.FLOAT)

                key = f"sqrDiag"
                nonRoundShapeInspectParam.dimensions[i].sqrDiag = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].sqrDiag, VARIABLE_TYPE.FLOAT)
                key = f"minSqrDiagTolerance"
                nonRoundShapeInspectParam.dimensions[i].minSqrDiagTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].minSqrDiagTolerance, VARIABLE_TYPE.FLOAT)
                key = f"maxSqrDiagTolerance"
                nonRoundShapeInspectParam.dimensions[i].maxSqrDiagTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].maxSqrDiagTolerance, VARIABLE_TYPE.FLOAT)


                key = f"ovlParameter"
                nonRoundShapeInspectParam.dimensions[i].ovlParameter = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].ovlParameter, VARIABLE_TYPE.FLOAT)
                key = f"ovlShrt"
                nonRoundShapeInspectParam.dimensions[i].ovlShrt = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].ovlShrt, VARIABLE_TYPE.FLOAT)
                key = f"minOvlShrtTolerance"
                nonRoundShapeInspectParam.dimensions[i].minOvlShrtTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].minOvlShrtTolerance, VARIABLE_TYPE.FLOAT)
                key = f"maxOvlShrtTolerance"
                nonRoundShapeInspectParam.dimensions[i].maxOvlShrtTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].maxOvlShrtTolerance, VARIABLE_TYPE.FLOAT)

                key = f"ovlLong"
                nonRoundShapeInspectParam.dimensions[i].ovlLong = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].ovlLong, VARIABLE_TYPE.FLOAT)
                key = f"minOvlLongTolerance"
                nonRoundShapeInspectParam.dimensions[i].minOvlLongTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].minOvlLongTolerance, VARIABLE_TYPE.FLOAT)
                key = f"maxOvlLongTolerance"
                nonRoundShapeInspectParam.dimensions[i].maxOvlLongTolerance = GetValue(param, key, nonRoundShapeInspectParam.dimensions[i].maxOvlLongTolerance, VARIABLE_TYPE.FLOAT)

        key = "class BodyRInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            bodyRInspectParam.enable = GetValue(param, key, bodyRInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"numberDimension"
            bodyRInspectParam.numberDimension = GetValue(param, key, bodyRInspectParam.numberDimension, VARIABLE_TYPE.INT)

        for i in range(bodyRInspectParam.maxNumberDimension):
            key = f"class BodyRInspect :: dimension{bodyRInspectParam.dimensionsName[i]}"
            if key in data.keys():
                param = data[key]
                key = f"enable"
                bodyRInspectParam.dimensions[i].enable = GetValue(param, key, bodyRInspectParam.dimensions[i].enable, VARIABLE_TYPE.BOOL)
                key = f"height"
                bodyRInspectParam.dimensions[i].height = GetValue(param, key, bodyRInspectParam.dimensions[i].height, VARIABLE_TYPE.FLOAT)
                key = f"dimension"
                bodyRInspectParam.dimensions[i].dimension = GetValue(param, key, bodyRInspectParam.dimensions[i].dimension, VARIABLE_TYPE.FLOAT)
                key = f"minTolerance"
                bodyRInspectParam.dimensions[i].minTolerance = GetValue(param, key, bodyRInspectParam.dimensions[i].minTolerance, VARIABLE_TYPE.FLOAT)
                key = f"maxTolerance"
                bodyRInspectParam.dimensions[i].maxTolerance = GetValue(param, key, bodyRInspectParam.dimensions[i].maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class LeanInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            leanInspectParam.enable = GetValue(param, key, leanInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            leanInspectParam.parameter1 = GetValue(param, key, leanInspectParam.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            leanInspectParam.parameter2 = GetValue(param, key, leanInspectParam.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"minDeviation"
            leanInspectParam.minDeviation = GetValue(param, key, leanInspectParam.minDeviation, VARIABLE_TYPE.FLOAT)

        key = "class BentNeckInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            bentNeckInspectParam.enable = GetValue(param, key, bentNeckInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"angle"
            bentNeckInspectParam.angle = GetValue(param, key, bentNeckInspectParam.angle, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            bentNeckInspectParam.minTolerance = GetValue(param, key, bentNeckInspectParam.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            bentNeckInspectParam.maxTolerance = GetValue(param, key, bentNeckInspectParam.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class TiltInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            tiltInspectParam.enable = GetValue(param, key, tiltInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            tiltInspectParam.parameter1 = GetValue(param, key, tiltInspectParam.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            tiltInspectParam.parameter2 = GetValue(param, key, tiltInspectParam.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"minHeight"
            tiltInspectParam.minHeight = GetValue(param, key, tiltInspectParam.minHeight, VARIABLE_TYPE.FLOAT)
       
        key = "class GroupFinishDimensionInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.enable = GetValue(param, key, groupFinishDimensionInspect.enable, VARIABLE_TYPE.BOOL)

        key = "class GroupFinishDimensionInspect :: dimensionF"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionF.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionF.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionF.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionF.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionF.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionF.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionF.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionF.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionF.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionF.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionF.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionF.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionF.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionF.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionA"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionA.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionA.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionA.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionA.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionA.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionA.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionA.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionA.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionA.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionA.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionA.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionA.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionA.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionA.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionT"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionT.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionT.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionT.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionT.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionT.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionT.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionT.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionT.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionT.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionT.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionT.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionT.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionT.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionT.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionE"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionE.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionE.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionE.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionE.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionE.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionE.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionE.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionE.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionE.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionE.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionE.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionE.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionE.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionE.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionD"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionD.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionD.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionD.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionD.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionD.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionD.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionD.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionD.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionD.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionD.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionD.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionD.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionD.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionD.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionB"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionB.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionB.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionB.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionB.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionB.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionB.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionB.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionB.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionB.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionB.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionB.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionB.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionB.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionB.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionS1"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionS1.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionS1.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionS1.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionS1.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionS1.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionS1.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionS1.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionS1.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionS1.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionS1.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionS1.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionS1.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionS1.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionS1.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionH"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionH.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionH.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionH.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionH.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionH.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionH.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionH.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionH.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionH.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionH.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionH.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionH.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionH.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionH.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionLugT"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionLugT.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionLugT.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionLugT.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionLugT.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionLugT.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionLugT.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionLugT.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionLugT1"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionLugT1.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT1.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionLugT1.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT1.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionLugT1.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT1.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionLugT1.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT1.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionLugT1.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT1.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionLugT1.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT1.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionLugT1.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionLugT1.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class GroupFinishDimensionInspect :: dimensionDAngle"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            groupFinishDimensionInspect.dimensionDAngle.enable = GetValue(param, key, groupFinishDimensionInspect.dimensionDAngle.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            groupFinishDimensionInspect.dimensionDAngle.parameter1 = GetValue(param, key, groupFinishDimensionInspect.dimensionDAngle.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            groupFinishDimensionInspect.dimensionDAngle.parameter2 = GetValue(param, key, groupFinishDimensionInspect.dimensionDAngle.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            groupFinishDimensionInspect.dimensionDAngle.parameter3 = GetValue(param, key, groupFinishDimensionInspect.dimensionDAngle.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"dimension"
            groupFinishDimensionInspect.dimensionDAngle.dimension = GetValue(param, key, groupFinishDimensionInspect.dimensionDAngle.dimension, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            groupFinishDimensionInspect.dimensionDAngle.minTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionDAngle.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            groupFinishDimensionInspect.dimensionDAngle.maxTolerance = GetValue(param, key, groupFinishDimensionInspect.dimensionDAngle.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class FlangeInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            flangeInspectParam.enable = GetValue(param, key, flangeInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            flangeInspectParam.parameter1 = GetValue(param, key, flangeInspectParam.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            flangeInspectParam.parameter2 = GetValue(param, key, flangeInspectParam.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            flangeInspectParam.parameter3 = GetValue(param, key, flangeInspectParam.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"parameter4"
            flangeInspectParam.parameter4 = GetValue(param, key, flangeInspectParam.parameter4, VARIABLE_TYPE.FLOAT)

        key = "class KnockoutInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            knockoutInspectParam.enable = GetValue(param, key, knockoutInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"parameter1"
            knockoutInspectParam.parameter1 = GetValue(param, key, knockoutInspectParam.parameter1, VARIABLE_TYPE.FLOAT)
            key = f"parameter2"
            knockoutInspectParam.parameter2 = GetValue(param, key, knockoutInspectParam.parameter2, VARIABLE_TYPE.FLOAT)
            key = f"parameter3"
            knockoutInspectParam.parameter3 = GetValue(param, key, knockoutInspectParam.parameter3, VARIABLE_TYPE.FLOAT)
            key = f"parameter4"
            knockoutInspectParam.parameter4 = GetValue(param, key, knockoutInspectParam.parameter4, VARIABLE_TYPE.FLOAT)

        key = "class PushupBodyInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            pushupBodyInspectParam.enable = GetValue(param, key, pushupBodyInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"pushup"
            pushupBodyInspectParam.pushup = GetValue(param, key, pushupBodyInspectParam.pushup, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            pushupBodyInspectParam.minTolerance = GetValue(param, key, pushupBodyInspectParam.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            pushupBodyInspectParam.maxTolerance = GetValue(param, key, pushupBodyInspectParam.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class InsideNeckInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            insideNeckInspectParam.enable = GetValue(param, key, insideNeckInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"diameter"
            insideNeckInspectParam.diameter = GetValue(param, key, insideNeckInspectParam.diameter, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            insideNeckInspectParam.minTolerance = GetValue(param, key, insideNeckInspectParam.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            insideNeckInspectParam.maxTolerance = GetValue(param, key, insideNeckInspectParam.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class WallThicknessInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            wallThicknessInspectParam.enable = GetValue(param, key, wallThicknessInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"thickness"
            wallThicknessInspectParam.thickness = GetValue(param, key, wallThicknessInspectParam.thickness, VARIABLE_TYPE.FLOAT)
            key = f"minTolerance"
            wallThicknessInspectParam.minTolerance = GetValue(param, key, wallThicknessInspectParam.minTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxTolerance"
            wallThicknessInspectParam.maxTolerance = GetValue(param, key, wallThicknessInspectParam.maxTolerance, VARIABLE_TYPE.FLOAT)

        key = "class SeamInspect"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            seamInspectParam.enable = GetValue(param, key, seamInspectParam.enable, VARIABLE_TYPE.BOOL)
            key = f"bodyHeight"
            seamInspectParam.bodyHeight = GetValue(param, key, seamInspectParam.bodyHeight, VARIABLE_TYPE.FLOAT)
            key = f"minBodyHeightTolerance"
            seamInspectParam.minBodyHeightTolerance = GetValue(param, key, seamInspectParam.minBodyHeightTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxBodyHeightTolerance"
            seamInspectParam.maxBodyHeightTolerance = GetValue(param, key, seamInspectParam.maxBodyHeightTolerance, VARIABLE_TYPE.FLOAT)
            key = f"bottomHeight"
            seamInspectParam.bottomHeight = GetValue(param, key, seamInspectParam.bottomHeight, VARIABLE_TYPE.FLOAT)
            key = f"minBottomHeightTolerance"
            seamInspectParam.minBottomHeightTolerance = GetValue(param, key, seamInspectParam.minBottomHeightTolerance, VARIABLE_TYPE.FLOAT)
            key = f"maxBottomHeightTolerance"
            seamInspectParam.maxBottomHeightTolerance = GetValue(param, key, seamInspectParam.maxBottomHeightTolerance, VARIABLE_TYPE.FLOAT)

        key = "class NumberCodeDecode"
        if key in data.keys():
            param = data[key]
            key = f"enable"
            numberCodeDecodeParam.enable = GetValue(param, key, numberCodeDecodeParam.enable, VARIABLE_TYPE.BOOL)
            key = f"codeNumber"
            numberCodeDecodeParam.codeNumber = GetValue(param, key, numberCodeDecodeParam.codeNumber, VARIABLE_TYPE.INT)
            key = f"bottomROI"
            numberCodeDecodeParam.bottomROI = GetValue(param, key, numberCodeDecodeParam.bottomROI, VARIABLE_TYPE.FLOAT)
            key = f"heightROI"
            numberCodeDecodeParam.heightROI = GetValue(param, key, numberCodeDecodeParam.heightROI, VARIABLE_TYPE.FLOAT)

    except:
        return False

    return True

def ReadTeachData(path: str):
    if not os.path.exists(path):
        return False
    try:
        data = ExtractFile(path)
       
    except:
        return False
    return True

def ReadConfigData(path: str):
    if not os.path.exists(path):
        return False
    try:
        with open(path, 'r', encoding='utf-8') as file:
            data = json.load(file)
            cameraData = data["Camera"]
            appConfigParam.resolution[TRACK_ID.BOTTOM] = cameraData["Camera 1 Resolution"]
            # appConfigParam.resolution[TRACK_ID.MID] = cameraData["Camera 2 Resolution"]
            appConfigParam.resolution[TRACK_ID.TOP] = cameraData["Camera 2 Resolution"]

        pass
    except:
        return False

    return True

def WriteConfigData(path: str):
    if not os.path.exists(path):
        return False
    try:
        with open(path, 'r', encoding='utf-8') as file:
            data = json.load(file)
        cameraData = data["Camera"]
        cameraData["Camera 1 Resolution"] = appConfigParam.resolution[TRACK_ID.BOTTOM]
        cameraData["Camera 2 Resolution"] = appConfigParam.resolution[TRACK_ID.TOP]

        data["Camera"] = cameraData
        # Save the changes back to the file
        with open(path, 'w', encoding='utf-8') as file:
            json.dump(data, file, indent=4)

        pass
    except:
        return False

    return True

def ReadCalibCameraPositionData(path: str):
    if not os.path.exists(path):
        return False
    try:
        with open(path, 'r', encoding='utf-8') as file:
            data = json.load(file)
            hideBottleHeight = data["Hide Bottle Height"]
            calibCameraPositionParam.hideBottleHeight[TRACK_ID.BOTTOM] = hideBottleHeight["Bottom"]
            calibCameraPositionParam.hideBottleHeight[TRACK_ID.TOP] = hideBottleHeight["Top"]

            toolInfo = data["Tool Info"]
            calibCameraPositionParam.toolHeight = toolInfo["Height"]
            calibCameraPositionParam.toolWidth = toolInfo["Width"]
            calibCameraPositionParam.maxBottleHeightInBottom = toolInfo["Max Bottle Height In Bottom"]


        pass
    except:
        return False

    return True

def WriteCalibCameraPositionData(path: str):
    if not os.path.exists(path):
        return False
    try:
        with open(path, 'r', encoding='utf-8') as file:
            data = json.load(file)

        hideBottleHeight = {}
        hideBottleHeight["Bottom"] = calibCameraPositionParam.hideBottleHeight[TRACK_ID.BOTTOM]
        hideBottleHeight["Top"] = calibCameraPositionParam.hideBottleHeight[TRACK_ID.TOP]
        data["Hide Bottle Height"] = hideBottleHeight


        toolInfo = {}
        toolInfo["Height"] = calibCameraPositionParam.toolHeight
        toolInfo["Width"] = calibCameraPositionParam.toolWidth
        toolInfo["Max Bottle Height In Bottom"] = calibCameraPositionParam.maxBottleHeightInBottom
        data["Tool Info"] = toolInfo

        # Save the changes back to the file
        with open(path, 'w', encoding='utf-8') as file:
            json.dump(data, file, indent=4)


        pass
    except:
        return False

    return True

def ReadLimitParam(path: str):
    return True
    if not os.path.exists(path):
        return False
    try:
        with open(path, 'r') as file:
            datas = json.load(file)
            
        for data in datas:
            if data["name"] == "Height":
                HeightInspectParam.instance.minAlarm = data["minimumAlarm"]
                HeightInspectParam.instance.minWarning = data["minimumWarning"]
                HeightInspectParam.instance.maxWarning = data["maximumWarning"]
                HeightInspectParam.instance.maxAlarm = data["maximumAlarm"]
                HeightInspectParam.instance.diffWarning = data["differenceWarning"]
                HeightInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "Weight":
                WeightInspectParam.instance.minAlarm = data["minimumAlarm"]
                WeightInspectParam.instance.minWarning = data["minimumWarning"]
                WeightInspectParam.instance.maxWarning = data["maximumWarning"]
                WeightInspectParam.instance.maxAlarm = data["maximumAlarm"]
                WeightInspectParam.instance.diffWarning = data["differenceWarning"]
                WeightInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "Tilt":
                TiltInspectParam.instance.minAlarm = data["minimumAlarm"]
                TiltInspectParam.instance.minWarning = data["minimumWarning"]
                TiltInspectParam.instance.maxWarning = data["maximumWarning"]
                TiltInspectParam.instance.maxAlarm = data["maximumAlarm"]
                TiltInspectParam.instance.diffWarning = data["differenceWarning"]
                TiltInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "Lean":
                LeanInspectParam.instance.minAlarm = data["minimumAlarm"]
                LeanInspectParam.instance.minWarning = data["minimumWarning"]
                LeanInspectParam.instance.maxWarning = data["maximumWarning"]
                LeanInspectParam.instance.maxAlarm = data["maximumAlarm"]
                LeanInspectParam.instance.diffWarning = data["differenceWarning"]
                LeanInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "BentNeck":
                BentNeckInspectParam.instance.minAlarm = data["minimumAlarm"]
                BentNeckInspectParam.instance.minWarning = data["minimumWarning"]
                BentNeckInspectParam.instance.maxWarning = data["maximumWarning"]
                BentNeckInspectParam.instance.maxAlarm = data["maximumAlarm"]
                BentNeckInspectParam.instance.diffWarning = data["differenceWarning"]
                BentNeckInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "A":
                GroupFinishDimensionInspect.instance.dimensionA.minAlarm = data["minimumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionA.minWarning = data["minimumWarning"]
                GroupFinishDimensionInspect.instance.dimensionA.maxWarning = data["maximumWarning"]
                GroupFinishDimensionInspect.instance.dimensionA.maxAlarm = data["maximumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionA.diffWarning = data["differenceWarning"]
                GroupFinishDimensionInspect.instance.dimensionA.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "B":
                GroupFinishDimensionInspect.instance.dimensionB.minAlarm = data["minimumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionB.minWarning = data["minimumWarning"]
                GroupFinishDimensionInspect.instance.dimensionB.maxWarning = data["maximumWarning"]
                GroupFinishDimensionInspect.instance.dimensionB.maxAlarm = data["maximumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionB.diffWarning = data["differenceWarning"]
                GroupFinishDimensionInspect.instance.dimensionB.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "D":
                GroupFinishDimensionInspect.instance.dimensionD.minAlarm = data["minimumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionD.minWarning = data["minimumWarning"]
                GroupFinishDimensionInspect.instance.dimensionD.maxWarning = data["maximumWarning"]
                GroupFinishDimensionInspect.instance.dimensionD.maxAlarm = data["maximumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionD.diffWarning = data["differenceWarning"]
                GroupFinishDimensionInspect.instance.dimensionD.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "E":
                GroupFinishDimensionInspect.instance.dimensionE.minAlarm = data["minimumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionE.minWarning = data["minimumWarning"]
                GroupFinishDimensionInspect.instance.dimensionE.maxWarning = data["maximumWarning"]
                GroupFinishDimensionInspect.instance.dimensionE.maxAlarm = data["maximumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionE.diffWarning = data["differenceWarning"]
                GroupFinishDimensionInspect.instance.dimensionE.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "F":
                GroupFinishDimensionInspect.instance.dimensionF.minAlarm = data["minimumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionF.minWarning = data["minimumWarning"]
                GroupFinishDimensionInspect.instance.dimensionF.maxWarning = data["maximumWarning"]
                GroupFinishDimensionInspect.instance.dimensionF.maxAlarm = data["maximumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionF.diffWarning = data["differenceWarning"]
                GroupFinishDimensionInspect.instance.dimensionF.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "S":
                GroupFinishDimensionInspect.instance.dimensionS1.minAlarm = data["minimumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionS1.minWarning = data["minimumWarning"]
                GroupFinishDimensionInspect.instance.dimensionS1.maxWarning = data["maximumWarning"]
                GroupFinishDimensionInspect.instance.dimensionS1.maxAlarm = data["maximumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionS1.diffWarning = data["differenceWarning"]
                GroupFinishDimensionInspect.instance.dimensionS1.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "T":
                GroupFinishDimensionInspect.instance.dimensionT.minAlarm = data["minimumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionT.minWarning = data["minimumWarning"]
                GroupFinishDimensionInspect.instance.dimensionT.maxWarning = data["maximumWarning"]
                GroupFinishDimensionInspect.instance.dimensionT.maxAlarm = data["maximumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionT.diffWarning = data["differenceWarning"]
                GroupFinishDimensionInspect.instance.dimensionT.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "H":
                GroupFinishDimensionInspect.instance.dimensionH.minAlarm = data["minimumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionH.minWarning = data["minimumWarning"]
                GroupFinishDimensionInspect.instance.dimensionH.maxWarning = data["maximumWarning"]
                GroupFinishDimensionInspect.instance.dimensionH.maxAlarm = data["maximumAlarm"]
                GroupFinishDimensionInspect.instance.dimensionH.diffWarning = data["differenceWarning"]
                GroupFinishDimensionInspect.instance.dimensionH.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "Pushup":
                PushupBodyInspectParam.instance.minAlarm = data["minimumAlarm"]
                PushupBodyInspectParam.instance.minWarning = data["minimumWarning"]
                PushupBodyInspectParam.instance.maxWarning = data["maximumWarning"]
                PushupBodyInspectParam.instance.maxAlarm = data["maximumAlarm"]
                PushupBodyInspectParam.instance.diffWarning = data["differenceWarning"]
                PushupBodyInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "Flange":
                FlangeInspectParam.instance.minAlarm = data["minimumAlarm"]
                FlangeInspectParam.instance.minWarning = data["minimumWarning"]
                FlangeInspectParam.instance.maxWarning = data["maximumWarning"]
                FlangeInspectParam.instance.maxAlarm = data["maximumAlarm"]
                FlangeInspectParam.instance.diffWarning = data["differenceWarning"]
                FlangeInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "Knockout":
                KnockoutInspectParam.instance.minAlarm = data["minimumAlarm"]
                KnockoutInspectParam.instance.minWarning = data["minimumWarning"]
                KnockoutInspectParam.instance.maxWarning = data["maximumWarning"]
                KnockoutInspectParam.instance.maxAlarm = data["maximumAlarm"]
                KnockoutInspectParam.instance.diffWarning = data["differenceWarning"]
                KnockoutInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            if data["name"] == "InsideNeck":
                InsideNeckInspectParam.instance.minAlarm = data["minimumAlarm"]
                InsideNeckInspectParam.instance.minWarning = data["minimumWarning"]
                InsideNeckInspectParam.instance.maxWarning = data["maximumWarning"]
                InsideNeckInspectParam.instance.maxAlarm = data["maximumAlarm"]
                InsideNeckInspectParam.instance.diffWarning = data["differenceWarning"]
                InsideNeckInspectParam.instance.diffAlarm = data["differenceAlarm"]
                continue

            for i in range(bodyRInspectParam.maxNumberDimension):
                if data["name"] == f"dimension{bodyRInspectParam.dimensionsName[i]}":
                    BodyRInspectParam.instance.dimensions[i].minAlarm = data["minimumAlarm"]
                    BodyRInspectParam.instance.dimensions[i].minWarning = data["minimumWarning"]
                    BodyRInspectParam.instance.dimensions[i].maxWarning = data["maximumWarning"]
                    BodyRInspectParam.instance.dimensions[i].maxAlarm = data["maximumAlarm"]
                    BodyRInspectParam.instance.dimensions[i].diffWarning = data["differenceWarning"]
                    BodyRInspectParam.instance.dimensions[i].diffAlarm = data["differenceAlarm"]


        pass
    except:
        return False

    return True
    
def CalculateAlarm():
    heightInspectParam.CalculateAlarm()
    weightInspectParam.CalculateAlarm()
    nonRoundShapeInspectParam.CalculateAlarm()
    bodyRInspectParam.CalculateAlarm()
    leanInspectParam.CalculateAlarm()
    bentNeckInspectParam.CalculateAlarm()
    tiltInspectParam.CalculateAlarm()
    groupFinishDimensionInspect.CalculateAlarm()
    flangeInspectParam.CalculateAlarm()
    knockoutInspectParam.CalculateAlarm()
    pushupBodyInspectParam.CalculateAlarm()
    insideNeckInspectParam.CalculateAlarm()



def CalculateLiftingMechanismPos(camIndex: TRACK_ID, height: float):
    # mm
    value = calibCameraPositionParam.hideBottleHeight[camIndex] + (height - calibCameraPositionParam.toolHeight)

    # value = 0
    # if(camIndex == TRACK_ID.TOP):
    #     lifting = 1054 - height # table
    #     value = 1012.4 - lifting # bottom of top camera
    # elif(camIndex == TRACK_ID.BOTTOM):
    #     lifting = 804 - height # table
    #     value = 614.0778 - lifting # bottom of top camera
    #     if value < 0:
    #         value = 0
    return value




