from Inspection.lib import*
from struct_define import TRACK_ID, DEFECT_NAME, MOLD_RESULT, InspectNonRoundShapeData, TopInspectData, CorrectinInspectData, NumberReaderData
from config import RGB2Hex, AddRectangleOverlayInfos, AddContourOverlayInfos
import config

import cv2
import time
import numpy as np
import copy
import os
import math
from typing import List
try:
    from ultralytics import YOLO
    import torch
except:
    pass


from Inspection.location import TopLocation, BotomLocation
from Inspection.tilt_inspect import TiltInspect
from Inspection.lean_inspect import LeanInspect
from Inspection.bodyR_inspect import BodyRInspect
from Inspection.group_finish_dimension_inspect import FinishDimensionInspect
from Inspection.h_dimension import HDimensionInspect
from Inspection.d_dimension import DDimensionInspect
from Inspection.lug_t1_dimension import LugT1DimensionInspect
from Inspection.d_angle import DAngleInspect
from Inspection.knockout_inspect import KnockoutInspect
from Inspection.glass_container_shape_inspect import NonRoundShapeInspect
from Inspection.s_dimension import SDimensionInspect
from Inspection.calib_tool_dimension_inspect import CalibToolDimensionTopInspect, CalibToolDimensionBotInspect
from Inspection.number_reader_decode import NumberReaderDecode
from ip_lib import DrawOvlStr

class MLCore():
    def __init__(self, id:int) -> None:
        super(MLCore, self).__init__() 
        self.id = id # cam index
        self.isLoadModelSuccess = self.initialize()

    def initialize(self):
        try:
            self.topThreadDetectionModel = None
            self.bottomNumberReaderDetectionModel = None
            if not os.path.exists(config.TOP_THREAD_DETECTION_MODEL_PATH) or \
                not os.path.exists(config.BOTTOM_NUMBER_READER_MODEL_PATH):
                return False
            #LOAD MODEL
            # self.topThreadDetectionModel = YOLO(config.TOP_THREAD_DETECTION_MODEL_PATH) # load a custom model
            self.bottomNumberReaderDetectionModel = NumberReaderDecode(config.BOTTOM_NUMBER_READER_MODEL_PATH) # load a custom model

            try:
                # inspect first time for warming up
                # image = np.zeros((1000, 1000, 3), np.uint8)
                # if self.topThreadDetectionModel is not None:
                #     self.topThreadDetectionModel.predict(source=image,
                #             conf = 0.1, iou = 0.25, device = self.device, save=False,
                #             save_txt = False, boxes = False, show_labels = True)

                image = np.zeros((300, 1000, 3), np.uint8)
                if self.bottomNumberReaderDetectionModel is not None:
                    self.bottomNumberReaderDetectionModel.inference(image)
                    
            except:
                self.topThreadDetectionModel = None
                self.bottomNumberReaderDetectionModel = None
                return True
        except:
            self.topThreadDetectionModel = None
            self.bottomNumberReaderDetectionModel = None
            return False
        return True




    
IS_DEBUG = True
def InspectTop(ImageTOP, ImageMID, ImageBOT, ImageTopMask, TopInspectionShareData: TopInspectData, ImageTopOVL):
    if ImageTopOVL is None:
        ImageOVL = cv2.cvtColor(ImageTOP, cv2.COLOR_GRAY2BGR)
    else:
        ImageOVL = ImageTopOVL.copy()

    DefectCodes = set()
    DefectInfos = []
    OverlayInfos = []
    t = time.time()
    OvlStringSpace = 70
    OvlStringPos = [OvlStringSpace, OvlStringSpace]
    MoldResult = MOLD_RESULT.PASS.value
    try:
        ZOOM_RATIO = 1
        zoomSize = (int(ImageTOP.shape[1]/ZOOM_RATIO), int(ImageTOP.shape[0]/ZOOM_RATIO))
        ImageTopZoom = cv2.resize(ImageTOP, zoomSize, interpolation=cv2.INTER_LINEAR)

        ##### Location #####
        t1 = time.time()
        MaxThreshold = 100
        isPass, ImageOVL, LocationRegion, LocationRect = TopLocation(ImageTopZoom, \
                    ImageTopMask, ImageOVL, MaxThreshold, ZOOM_RATIO)
        if not isPass:
            pass
        print("Location time: ", time.time() - t1)
        ##### End Location #####

        BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect # pixel/ZOOM_RATIO


        ##### Height Inspect #####
        if HeightInspectParam.instance.enable:
            t1 = time.time()
            minHeight = HeightInspectParam.instance.height - HeightInspectParam.instance.minTolerance # mm
            maxHeight = HeightInspectParam.instance.height + HeightInspectParam.instance.maxTolerance # mm
            bottleHeight = round((BBOTTOM - BTOP)*ZOOM_RATIO*AppConfigParam.instance.resolution[TRACK_ID.TOP] +\
                HeightInspectParam.instance.liftingMechanismPos, config.FLOAT_NUMBER)
            color = (255, 0, 0)

            # OVL
            x = 150
            cy = ImageOVL.shape[0] - int((BTOP + BBOTTOM)/2*ZOOM_RATIO)
            textSize = cv2.getTextSize(f'Height: {round(bottleHeight, config.FLOAT_NUMBER)}', config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
            ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_CLOCKWISE)
            cv2.putText(ImageOVL, f'Height: {round(bottleHeight, config.FLOAT_NUMBER)}', (int(cy - textSize[0]/2) , x - 50), config.FONT_FAMILY, config.FONT_SIZE, color, config.OVLSIZE)
            ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_COUNTERCLOCKWISE)
            # Defect Info
            IsDefect = False
            if bottleHeight > maxHeight or bottleHeight < minHeight:
                IsDefect = True
                DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.HEIGHT.value}")
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Height", color)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.HEIGHT.name};Height;{round(bottleHeight, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.HEIGHT.name};Diff Height;{round(bottleHeight - HeightInspectParam.instance.height, config.FLOAT_NUMBER)};{not IsDefect}")

            # Mold result
            if bottleHeight >= HeightInspectParam.instance.maxAlarm or bottleHeight <= HeightInspectParam.instance.minAlarm:
                MoldResult = MOLD_RESULT.ALARM.value
            elif (bottleHeight >= HeightInspectParam.instance.maxWarning or bottleHeight <= HeightInspectParam.instance.minWarning) \
                and MoldResult == MOLD_RESULT.PASS.value:
                MoldResult = MOLD_RESULT.WARNING.value
            
            print("Height Inspect time: ", time.time() - t1)
        ##### End Height #####

        ##### Lean Inspect #####
        if LeanInspectParam.instance.enable:
            t1 = time.time()
            # mm
            minDeviation = LeanInspectParam.instance.minDeviation 
            parameter1 = LeanInspectParam.instance.parameter1 # Bottom of lean
            parameter2 = LeanInspectParam.instance.parameter2 # Top of lean
            color = (52, 35, 160)

            IsDefect, ImageOVL, MinAngleOut = LeanInspect(ImageOVL, LocationRegion, LocationRect,\
                                    parameter1, parameter2, minDeviation, color, ZOOM_RATIO, 
                                    AppConfigParam.instance.resolution[TRACK_ID.TOP])
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LEAN.name};Deviation;{round(MinAngleOut, config.FLOAT_NUMBER)};{not IsDefect}")
            if IsDefect:
                DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LEAN.value}")
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Lean", color)
            print("Lean Inspect time: ", time.time() - t1)
            
            # Mold result
            if MinAngleOut >= LeanInspectParam.instance.maxAlarm:
                MoldResult = MOLD_RESULT.ALARM.value
            elif (MinAngleOut >= LeanInspectParam.instance.maxWarning) \
                and MoldResult == MOLD_RESULT.PASS.value:
                MoldResult = MOLD_RESULT.WARNING.value
        ##### End Lean #####

        ##### Tilt Inspect #####
        if TiltInspectParam.instance.enable:
            t1 = time.time()
            minHeight = TiltInspectParam.instance.minHeight
            parameter1 = TiltInspectParam.instance.parameter1 # %
            parameter2 = TiltInspectParam.instance.parameter2 # top of finish go down to find center of finish

            color = (31, 0, 184)

            IsDefect, ImageOVL, MinHeightOut = TiltInspect(ImageOVL, LocationRegion, LocationRect,\
                                parameter1, parameter2, minHeight, color, ZOOM_RATIO,
                                AppConfigParam.instance.resolution[TRACK_ID.TOP])
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.TILT.name};Height;{round(MinHeightOut, config.FLOAT_NUMBER)};{not IsDefect}")
            if IsDefect:
                DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.TILT.value}")
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Tilt", color)
            
            # Mold result
            if MinHeightOut >= TiltInspectParam.instance.maxAlarm:
                MoldResult = MOLD_RESULT.ALARM.value
            elif (MinHeightOut >= TiltInspectParam.instance.maxWarning) \
                and MoldResult == MOLD_RESULT.PASS.value:
                MoldResult = MOLD_RESULT.WARNING.value
            print("Tilt Inspect time: ", time.time() - t1)
        ##### End Tilt #####

        #### Group Finish Dimension Inspect #####
        if GroupFinishDimensionInspect.instance.enable:
            t1 = time.time()
            
            if GroupFinishDimensionInspect.instance.dimensionF.enable:
                # F Dimension
                dimension = GroupFinishDimensionInspect.instance.dimensionF.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionF.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionF.maxTolerance
                parameter1 = GroupFinishDimensionInspect.instance.dimensionF.parameter1 # distance from top finish line to bottom of F area
                parameter2 = GroupFinishDimensionInspect.instance.dimensionF.parameter1 # height of measurement area
                color = (0, 255, 255)
                index = 1
                dimensionName = "F"
                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = FinishDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                                    parameter1, parameter2, dimension, minTolerance, maxTolerance, dimensionName,\
                                                    color, index, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.F_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.F_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.F_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension F", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionF.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionF.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionF.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionF.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value
                 
            if GroupFinishDimensionInspect.instance.dimensionA.enable:
                # A Dimension
                dimension = GroupFinishDimensionInspect.instance.dimensionA.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionA.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionA.maxTolerance
                parameter1 = GroupFinishDimensionInspect.instance.dimensionA.parameter1 # distance from top finish line to bottom of F
                parameter2 = GroupFinishDimensionInspect.instance.dimensionA.parameter1 # height of measurement area
                color = (0, 102, 255)
                index = 2
                dimensionName = "A"

                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = FinishDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                                    parameter1, parameter2, dimension, minTolerance, maxTolerance, dimensionName,\
                                                    color, index, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.A_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.A_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.A_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension A", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionA.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionA.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionA.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionA.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value

            if GroupFinishDimensionInspect.instance.dimensionT.enable:
                # T Dimension
                dimension = GroupFinishDimensionInspect.instance.dimensionT.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionT.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionT.maxTolerance
                parameter1 = GroupFinishDimensionInspect.instance.dimensionT.parameter1 # distance from top finish line to bottom of F
                parameter2 = GroupFinishDimensionInspect.instance.dimensionT.parameter2 # height of measurement area
                color = (242, 121, 67)
                index = 3
                dimensionName = "T"

                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = FinishDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                                    parameter1, parameter2, dimension, minTolerance, maxTolerance, dimensionName,\
                                                    color, index, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.T_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.T_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.T_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension T", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionT.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionT.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionT.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionT.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value

            if GroupFinishDimensionInspect.instance.dimensionE.enable:
                # E Dimension
                dimension = GroupFinishDimensionInspect.instance.dimensionE.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionE.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionE.maxTolerance
                parameter1 = GroupFinishDimensionInspect.instance.dimensionE.parameter1 # distance from top finish line to bottom of F
                parameter2 = GroupFinishDimensionInspect.instance.dimensionE.parameter2 # height of measurement area
                color = (84, 117, 17)
                index = 4
                dimensionName = "E"

                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = FinishDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                                    parameter1, parameter2, dimension, minTolerance, maxTolerance, dimensionName,\
                                                    color, index, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.E_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.E_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.E_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension E", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionE.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionE.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionE.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionE.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value

            if GroupFinishDimensionInspect.instance.dimensionD.enable:
                # D Dimension
                # Find vertical distance from top to a point on the unnder surface at the band that inset a special distance
                dimension = GroupFinishDimensionInspect.instance.dimensionD.dimension # locking ring depth
                minTolerance = GroupFinishDimensionInspect.instance.dimensionD.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionD.maxTolerance
                parameter1 = GroupFinishDimensionInspect.instance.dimensionD.parameter1 # distance from top finish line to bottom D measurement region
                parameter2 = GroupFinishDimensionInspect.instance.dimensionD.parameter2 # the inset distance from outer edge of the locking ring to the point where the locking ring height is to be measured
                parameter3 = GroupFinishDimensionInspect.instance.dimensionD.parameter3 # height of measurement region
                color = (49,78,108)

                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = DDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                    parameter1, parameter2, parameter3, dimension, minTolerance, maxTolerance,\
                                    color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension D", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionD.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionD.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionD.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionD.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value

            if GroupFinishDimensionInspect.instance.dimensionB.enable:
                # B Dimension
                dimension = GroupFinishDimensionInspect.instance.dimensionB.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionB.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionB.maxTolerance
                parameter1 = GroupFinishDimensionInspect.instance.dimensionB.parameter1 # distance from top finish line to bottom of F
                parameter2 = GroupFinishDimensionInspect.instance.dimensionB.parameter2 # height of measurement area
                color = (126, 90, 240)
                index = 5
                dimensionName = "B"

                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = FinishDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                                    parameter1, parameter2, dimension, minTolerance, maxTolerance, dimensionName,\
                                                    color, index, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.B_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.B_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.B_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension B", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionB.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionB.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionB.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionB.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value


            #### Dimension S Inspect ####
            if GroupFinishDimensionInspect.instance.dimensionS1.enable:
                dimension = GroupFinishDimensionInspect.instance.dimensionS1.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionS1.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionS1.maxTolerance                
                parameter1 = GroupFinishDimensionInspect.instance.dimensionS1.parameter1 # thread height
                parameter2 = GroupFinishDimensionInspect.instance.dimensionS1.parameter2 # (T-E)/2 thread width
                parameter3 = 20 # distance from top finish line to bottom measurement region
                color = (95, 143, 222)
                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = SDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                        parameter1, parameter2, parameter3, dimension, minTolerance,\
                        maxTolerance, TopInspectionShareData.sDimensionData.dimension, color, ZOOM_RATIO, 
                        AppConfigParam.instance.resolution[TRACK_ID.TOP])

                # store data
                if TopInspectionShareData.sDimensionData.dimension == 0 or \
                    (TopInspectionShareData.sDimensionData.dimension > DimensionOut and \
                    DimensionOut != 0):
                    TopInspectionShareData.sDimensionData.dimension = DimensionOut

                IsDefect = False
                diff = round(TopInspectionShareData.sDimensionData.dimension - dimension, config.FLOAT_NUMBER)
                if diff < minTolerance*(-1) or diff > maxTolerance:
                    IsDefect = True
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.S_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension S", color)


                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.S_DIMENSION.name};Dimension;{round(TopInspectionShareData.sDimensionData.dimension, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.S_DIMENSION.name};Diff Dimension;{round(diff, config.FLOAT_NUMBER)};{not IsDefect}")

                # Mold result
                # DimensionOut = TopInspectionShareData.sDimensionData.dimension
                # if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionS1.maxAlarm or \
                #     DimensionOut <= GroupFinishDimensionInspect.instance.dimensionS1.minAlarm:
                #     MoldResult = MOLD_RESULT.ALARM.value
                # elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionS1.maxWarning or \
                #     DimensionOut <= GroupFinishDimensionInspect.instance.dimensionS1.minWarning) \
                #     and MoldResult == MOLD_RESULT.PASS.value:
                #     MoldResult = MOLD_RESULT.WARNING.value

            #### End Dimension S Inspect ####

            if GroupFinishDimensionInspect.instance.dimensionH.enable:
                # H Dimension
                # Find distance from top to where correct diameter
                dimension = GroupFinishDimensionInspect.instance.dimensionH.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionH.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionH.maxTolerance                
                parameter1 = GroupFinishDimensionInspect.instance.dimensionH.parameter1 # search region height
                parameter2 = GroupFinishDimensionInspect.instance.dimensionH.parameter2 # the diameter for search for

                color = (210,71,175)

                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = HDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                    parameter1, parameter2, dimension, minTolerance, maxTolerance,\
                                    color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.H_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.H_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.H_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension H", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionH.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionH.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionH.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionH.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value

            ##### LugT Inspect #####
            if GroupFinishDimensionInspect.instance.dimensionLugT.enable:
                # LUG Dimension
                dimension = GroupFinishDimensionInspect.instance.dimensionLugT.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionLugT.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionLugT.maxTolerance
                parameter1 = GroupFinishDimensionInspect.instance.dimensionLugT.parameter1 # distance from top finish line to bottom of F
                parameter2 = GroupFinishDimensionInspect.instance.dimensionLugT.parameter2 # height of measurement area
                color = (152, 190, 255)
                index = 6
                dimensionName = "LugT"

                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = FinishDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                                    parameter1, parameter2, dimension, minTolerance, maxTolerance, dimensionName,\
                                                    color, index, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension LugT", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionLugT.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionLugT.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionLugT.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionLugT.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value
            ##### End LugT #####


            ##### LugT1 Inspect #####
            if GroupFinishDimensionInspect.instance.dimensionLugT1.enable:
                # LUG Dimension
                dimension = GroupFinishDimensionInspect.instance.dimensionLugT1.dimension
                minTolerance = GroupFinishDimensionInspect.instance.dimensionLugT1.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionLugT1.maxTolerance
                parameter1 = GroupFinishDimensionInspect.instance.dimensionLugT1.parameter1 # distance from top finish line to bottom of F
                parameter2 = GroupFinishDimensionInspect.instance.dimensionLugT1.parameter2 # height of measurement area
                index = 7

                color = (203,207,72)
                IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = LugT1DimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                                                    parameter1, parameter2, dimension, minTolerance, maxTolerance, index,\
                                                    color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT1_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT1_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT1_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension LugT1", color)

                # Mold result
                if DimensionOut >= GroupFinishDimensionInspect.instance.dimensionLugT1.maxAlarm or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionLugT1.minAlarm:
                    MoldResult = MOLD_RESULT.ALARM.value
                elif (DimensionOut >= GroupFinishDimensionInspect.instance.dimensionLugT1.maxWarning or \
                    DimensionOut <= GroupFinishDimensionInspect.instance.dimensionLugT1.minWarning) \
                    and MoldResult == MOLD_RESULT.PASS.value:
                    MoldResult = MOLD_RESULT.WARNING.value
            ##### End LugT #####

            ##### D Angle Inspect #####
            if GroupFinishDimensionInspect.instance.dimensionDAngle.enable:
                # D Angle
                # Find minimum angle of the underside of the D ring related to horizontal
                angle = GroupFinishDimensionInspect.instance.dimensionDAngle.dimension # locking ring depth
                minTolerance = GroupFinishDimensionInspect.instance.dimensionDAngle.minTolerance
                maxTolerance = GroupFinishDimensionInspect.instance.dimensionDAngle.maxTolerance                
                parameter1 = GroupFinishDimensionInspect.instance.dimensionDAngle.parameter1 # distance from top finish line to bottom D measurement region
                parameter2 = GroupFinishDimensionInspect.instance.dimensionDAngle.parameter2 # the inset distance from outer edge of the locking ring to the point where the locking ring height is to be measured
                parameter3 = GroupFinishDimensionInspect.instance.dimensionDAngle.parameter3 # height of measurement region

                color = (145,131,2)

                IsDefect, ImageOVL, AngleOut, DiffAngleOut = DAngleInspect(ImageOVL, LocationRegion, LocationRect,\
                                    parameter1, parameter2, parameter3, angle, minTolerance, maxTolerance,\
                                    color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP])
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_ANGLE_DIMENSION.name};Angle;{round(AngleOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_ANGLE_DIMENSION.name};Diff Angle;{round(DiffAngleOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if IsDefect:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_ANGLE_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "D Angle", color)

                # # Mold result
                # if AngleOut >= GroupFinishDimensionInspect.instance.dimensionDAngle.maxAlarm or \
                #     AngleOut <= GroupFinishDimensionInspect.instance.dimensionDAngle.minAlarm:
                #     MoldResult = MOLD_RESULT.ALARM.value
                # elif (AngleOut >= GroupFinishDimensionInspect.instance.dimensionDAngle.maxWarning or \
                #     AngleOut <= GroupFinishDimensionInspect.instance.dimensionDAngle.minWarning) \
                #     and MoldResult == MOLD_RESULT.PASS.value:
                #     MoldResult = MOLD_RESULT.WARNING.value

            ##### End D Angle #####

            print("Group Finish Dimension Inspect time: ", time.time() - t1)
        #### End Group Finish Dimension #####

        #### Flange Inspect ####
        if FlangeInspectParam.instance.enable:
            t1 = time.time()
            minImageNumber = FlangeInspectParam.instance.parameter2
            
            color = (0, 0, 255)
            IsDefect = False
            if TopInspectionShareData.flangeData.maxKnockoutConsecutiveImageNumber >= minImageNumber:
                IsDefect = True
                DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.FLANGE_DIMENSION.value}")
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Flange", (0, 0, 255))

            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.FLANGE_DIMENSION.name};Min Knockout;\
                    {round(TopInspectionShareData.flangeData.minKnockout, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.FLANGE_DIMENSION.name};Max Knockout;\
                    {round(TopInspectionShareData.flangeData.maxKnockout, config.FLOAT_NUMBER)};{not IsDefect}")
            
            # # Mold result
            # DimensionOut = TopInspectionShareData.flangeData.maxKnockout
            # if DimensionOut >= FlangeInspectParam.instance.maxAlarm or \
            #     DimensionOut <= FlangeInspectParam.instance.minAlarm:
            #     MoldResult = MOLD_RESULT.ALARM.value
            # elif (DimensionOut >= FlangeInspectParam.instance.maxWarning or \
            #     DimensionOut <= FlangeInspectParam.instance.minWarning) \
            #     and MoldResult == MOLD_RESULT.PASS.value:
            #     MoldResult = MOLD_RESULT.WARNING.value
            
            print("Flange Inspect time: ", time.time() - t1)
        #### End Flange Inspect ####

        #### Knockout Inspect ####
        if KnockoutInspectParam.instance.enable:
            t1 = time.time()
            maxImageNumber = KnockoutInspectParam.instance.parameter2
            
            color = (0, 0, 255)
            IsDefect = False
            if 0 < TopInspectionShareData.knockoutData.maxKnockoutConsecutiveImageNumber <= maxImageNumber:
                IsDefect = True
                DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.KNOCKOUT_DIMENSION.value}")
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Knockout", (0, 0, 255))

            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.KNOCKOUT_DIMENSION.name};Min Knockout;\
                               {round(TopInspectionShareData.knockoutData.minKnockout, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.KNOCKOUT_DIMENSION.name};Max Knockout;\
                                {round(TopInspectionShareData.knockoutData.maxKnockout, config.FLOAT_NUMBER)};{not IsDefect}")
            
            # # Mold result
            # DimensionOut = TopInspectionShareData.knockoutData.maxKnockout
            # if DimensionOut >= KnockoutInspectParam.instance.maxAlarm or \
            #     DimensionOut <= KnockoutInspectParam.instance.minAlarm:
            #     MoldResult = MOLD_RESULT.ALARM.value
            # elif (DimensionOut >= KnockoutInspectParam.instance.maxWarning or \
            #     DimensionOut <= KnockoutInspectParam.instance.minWarning) \
            #     and MoldResult == MOLD_RESULT.PASS.value:
            #     MoldResult = MOLD_RESULT.WARNING.value
            
            print("Flange Inspect time: ", time.time() - t1)
        #### End Flange Inspect ####
        
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
    except Exception as inst:
        DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.PROCESS_ERROR.value}")
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
    
def InspectMid(ImageTOP, ImageMID, ImageBOT, TopDetectionModel):
    ImageOVL = cv2.cvtColor(ImageMID, cv2.COLOR_GRAY2BGR)
    DefectCodes = set()
    DefectInfos = []
    OverlayInfos = []
    t = time.time()
    OvlStringSpace = 70
    OvlStringPos = [OvlStringSpace, OvlStringSpace]
    MoldResult = MOLD_RESULT.PASS.value
    try:
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
    except:
        DefectCodes.add(f"{TRACK_ID.MID.value};{DEFECT_NAME.PROCESS_ERROR.value}")
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
    
def InspectBot(ImageTOP, ImageMID, ImageBOT, ImageBOTTOP, DataStr, NonRoundShapeData: List[InspectNonRoundShapeData], NumberReaderData: NumberReaderData, mlCore: MLCore, ImageBotOVL):
    if ImageBotOVL is None:
        ImageOVL = cv2.cvtColor(ImageBOT, cv2.COLOR_GRAY2BGR)
    else:
        ImageOVL = ImageBotOVL.copy()
    DefectCodes = set()
    DefectInfos = []
    OverlayInfos = []
    t = time.time()
    OvlStringSpace = 70
    OvlStringPos = [OvlStringSpace, OvlStringSpace]
    MoldResult = MOLD_RESULT.PASS.value
    try:

        ZOOM_RATIO = 2
        imgSize = (int(ImageBOT.shape[1]), int(ImageBOT.shape[0]))
        zoomSize = (int(ImageBOT.shape[1]/ZOOM_RATIO), int(ImageBOT.shape[0]/ZOOM_RATIO))
        # lossPartHeight = 0 # mm

        # ImageBOTTop: see the top of the bottle at camera bottom
        # ImageBOT: see the bottom of the bottle at camera bottom
        if ImageBOTTOP is not None:
            ImageBOTTOPZoom = cv2.resize(ImageBOTTOP, zoomSize, interpolation=cv2.INTER_LINEAR)
            # calculate the height of bottle

            ##### Location #####
            t1 = time.time()
            MaxThreshold = 100
            isPass, ImageOVL, _, LocationRect = BotomLocation(ImageBOTTOPZoom, ImageOVL,\
                                    MaxThreshold, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.BOTTOM])
                                    
            if not isPass:
                return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
            
            BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
            bottleHeight = (BRIGHT - BLEFT)*ZOOM_RATIO*AppConfigParam.instance.resolution[TRACK_ID.BOTTOM] + \
                        CalculateLiftingMechanismPos(TRACK_ID.BOTTOM, HeightInspectParam.instance.height)
            
            # bottomTableMove = 620 # 620 mm to see the table = 158 pixel
            # bottleHeightInBottomImage = (ImageBOT.shape[1]-158)*AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]#
            bottleHeightInBottomImage = CalibCameraPositionParam.instance.maxBottleHeightInBottom
            if bottleHeight > bottleHeightInBottomImage:
                # need combine 2 image
                diffmm = bottleHeight - bottleHeightInBottomImage
                # lossPartHeight = int(diffmm/AppConfigParam.instance.resolution[TRACK_ID.BOTTOM])
                diffPixel = int(diffmm/AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]) + (ImageBOT.shape[1] - BRIGHT*ZOOM_RATIO)
                y = ImageBOT.shape[1] - diffPixel
                gap = ImageBOT.shape[1] - y
                ImageBOT = np.hstack((ImageBOT, ImageBOTTOP[:,y:ImageBOT.shape[1] - gap%4]))
                
            ImageOVL = cv2.cvtColor(ImageBOT, cv2.COLOR_GRAY2BGR)


            print("Location BottomTop time: ", time.time() - t1)
            ##### End Location #####

        zoomSize = (int(ImageBOT.shape[1]/ZOOM_RATIO), int(ImageBOT.shape[0]/ZOOM_RATIO))
        ImageBotZoom = cv2.resize(ImageBOT, zoomSize, interpolation=cv2.INTER_LINEAR)

        ##### Location #####
        t1 = time.time()
        MaxThreshold = 100
        isPass, ImageOVL, LocationRegion, LocationRect = BotomLocation(ImageBotZoom, ImageOVL,\
                                MaxThreshold, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.BOTTOM])
        if not isPass:
            pass
        print("Location time: ", time.time() - t1)
        ##### End Location #####

        ##### Weight
        if WeightInspectParam.instance.enable:
            try:
                dataSplit = DataStr.split('$')
                if len(dataSplit) >= 2:
                    weight = round(float(dataSplit[0]), config.FLOAT_NUMBER)
                    minWeight = WeightInspectParam.instance.weight - WeightInspectParam.instance.minTolerance
                    maxWeight = WeightInspectParam.instance.weight + WeightInspectParam.instance.maxTolerance
                    
                    IsDefect = False
                    if weight > maxWeight or weight < minWeight:
                        IsDefect = True
                        DefectCodes.add(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.WEIGHT.value}")
                        ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, f"Weight", (0, 0, 255))
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.WEIGHT.name};Weight;{round(weight, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.WEIGHT.name};Diff Weight;{round(weight - WeightInspectParam.instance.weight, config.FLOAT_NUMBER)};{not IsDefect}")

                    # Mold result
                    # if weight >= WeightInspectParam.instance.maxAlarm or \
                    #     weight <= WeightInspectParam.instance.minAlarm:
                    #     MoldResult = MOLD_RESULT.ALARM.value
                    # elif (weight >= WeightInspectParam.instance.maxWarning or \
                    #     weight <= WeightInspectParam.instance.minWarning) \
                    #     and MoldResult == MOLD_RESULT.PASS.value:
                    #     MoldResult = MOLD_RESULT.WARNING.value
            except:
                pass

        ##### Pushup
        if PushupBodyInspectParam.instance.enable:
            try:
                dataSplit = DataStr.split('$')
                if len(dataSplit) >= 2:
                    pushup = round(float(dataSplit[1]), config.FLOAT_NUMBER)
                    minPushup = PushupBodyInspectParam.instance.pushup - PushupBodyInspectParam.instance.minTolerance
                    maxPushup = PushupBodyInspectParam.instance.pushup + PushupBodyInspectParam.instance.maxTolerance
                    IsDefect = False
                    if pushup > maxPushup or pushup < minPushup:
                        IsDefect = True
                        DefectCodes.add(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.PUSHUP_DIMENSION.value}")
                        ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, f"Pushup", (0, 0, 255))
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.PUSHUP_DIMENSION.name};Pushup;{round(pushup, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.PUSHUP_DIMENSION.name};Diff Pushup;{round(pushup - PushupBodyInspectParam.instance.pushup, config.FLOAT_NUMBER)};{not IsDefect}")

                    # Mold result
                    # if pushup >= PushupBodyInspectParam.instance.maxAlarm or \
                    #     pushup <= PushupBodyInspectParam.instance.minAlarm:
                    #     MoldResult = MOLD_RESULT.ALARM.value
                    # elif (pushup >= PushupBodyInspectParam.instance.maxWarning or \
                    #     pushup <= PushupBodyInspectParam.instance.minWarning) \
                    #     and MoldResult == MOLD_RESULT.PASS.value:
                    #     MoldResult = MOLD_RESULT.WARNING.value

            except:
                pass

        ##### Glass Container Shape Inspect #####
        if NonRoundShapeInspectParam.instance.enable:
            t1 = time.time()
            color = (0, 255, 255)
            FinalDefect = False
                
            for i in range(NonRoundShapeInspectParam.instance.numberDimension):
                if NonRoundShapeInspectParam.instance.shape == 0: # rectangle
                    difference = round(NonRoundShapeData[i].shortSize - NonRoundShapeInspectParam.instance.dimensions[i].rectShrt, config.FLOAT_NUMBER)
                    IsDefect = False
                    if difference < NonRoundShapeInspectParam.instance.dimensions[i].minRectShrtTolerance*(-1) or difference > NonRoundShapeInspectParam.instance.dimensions[i].maxRectShrtTolerance:
                        IsDefect = True
                        FinalDefect = True
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};RecShrt{i+1};{round(NonRoundShapeData[i].shortSize, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diff RecShrt{i+1};{round(difference, config.FLOAT_NUMBER)};{not IsDefect}")

                    # Mold result
                    DimensionOut = NonRoundShapeData[i].shortSize
                    if DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxRectShrtAlarm or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minRectShrtAlarm:
                        MoldResult = MOLD_RESULT.ALARM.value
                    elif (DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxRectShrtWarning or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minRectShrtWarning) \
                        and MoldResult == MOLD_RESULT.PASS.value:
                        MoldResult = MOLD_RESULT.WARNING.value

                    difference = round(NonRoundShapeData[i].longSize - NonRoundShapeInspectParam.instance.dimensions[i].rectLong, config.FLOAT_NUMBER)
                    IsDefect = False
                    if difference < NonRoundShapeInspectParam.instance.dimensions[i].minRectLongTolerance*(-1) or difference > NonRoundShapeInspectParam.instance.dimensions[i].maxRectLongTolerance:
                        IsDefect = True
                        FinalDefect = True
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};RecLong{i+1};{round(NonRoundShapeData[i].longSize, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diff RecLong{i+1};{round(difference, config.FLOAT_NUMBER)};{not IsDefect}")

                    # Mold result
                    DimensionOut = NonRoundShapeData[i].longSize
                    if DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxRectLongAlarm or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minRectLongAlarm:
                        MoldResult = MOLD_RESULT.ALARM.value
                    elif (DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxRectLongWarning or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minRectLongWarning) \
                        and MoldResult == MOLD_RESULT.PASS.value:
                        MoldResult = MOLD_RESULT.WARNING.value

                    difference = round(NonRoundShapeData[i].diagonalSize - NonRoundShapeInspectParam.instance.dimensions[i].rectDiag, config.FLOAT_NUMBER)
                    IsDefect = False
                    if difference < NonRoundShapeInspectParam.instance.dimensions[i].minRectDiagTolerance*(-1) or difference > NonRoundShapeInspectParam.instance.dimensions[i].maxRectDiagTolerance:
                        IsDefect = True
                        FinalDefect = True
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};RecDiag{i+1};{round(NonRoundShapeData[i].diagonalSize, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diff RecDiag{i+1};{round(difference, config.FLOAT_NUMBER)};{not IsDefect}")    

                    # Mold result
                    DimensionOut = NonRoundShapeData[i].diagonalSize
                    if DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxRectDiagAlarm or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minRectDiagAlarm:
                        MoldResult = MOLD_RESULT.ALARM.value
                    elif (DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxRectDiagWarning or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minRectDiagWarning) \
                        and MoldResult == MOLD_RESULT.PASS.value:
                        MoldResult = MOLD_RESULT.WARNING.value

                elif NonRoundShapeInspectParam.instance.shape == 1: # square
                    difference = round(NonRoundShapeData[i].shortSize - NonRoundShapeInspectParam.instance.dimensions[i].sqrSide, config.FLOAT_NUMBER)
                    IsDefect = False
                    if difference < NonRoundShapeInspectParam.instance.dimensions[i].minSqrSideTolerance*(-1) or difference > NonRoundShapeInspectParam.instance.dimensions[i].maxSqrSideTolerance:
                        IsDefect = True
                        FinalDefect = True
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};SqrSide{i+1};{round(NonRoundShapeData[i].shortSize, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diff SqrSide{i+1};{round(difference, config.FLOAT_NUMBER)};{not IsDefect}")
                        
                    # Mold result
                    DimensionOut = NonRoundShapeData[i].shortSize
                    if DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxSqrSizeAlarm or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minSqrSizeAlarm:
                        MoldResult = MOLD_RESULT.ALARM.value
                    elif (DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxSqrSizeWarning or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minSqrSizeWarning) \
                        and MoldResult == MOLD_RESULT.PASS.value:
                        MoldResult = MOLD_RESULT.WARNING.value

                    difference = round(NonRoundShapeData[i].diagonalSize - NonRoundShapeInspectParam.instance.dimensions[i].sqrDiag, config.FLOAT_NUMBER)
                    IsDefect = False
                    if difference < NonRoundShapeInspectParam.instance.dimensions[i].minSqrDiagTolerance*(-1) or difference > NonRoundShapeInspectParam.instance.dimensions[i].maxSqrDiagTolerance:
                        IsDefect = True
                        FinalDefect = True
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};SqrDiag{i+1};{round(NonRoundShapeData[i].diagonalSize, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diff SqrDiag{i+1};{round(difference, config.FLOAT_NUMBER)};{not IsDefect}")    

                    # Mold result
                    DimensionOut = NonRoundShapeData[i].diagonalSize
                    if DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxSqrDiagAlarm or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minSqrDiagAlarm:
                        MoldResult = MOLD_RESULT.ALARM.value
                    elif (DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxSqrDiagWarning or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minSqrDiagWarning) \
                        and MoldResult == MOLD_RESULT.PASS.value:
                        MoldResult = MOLD_RESULT.WARNING.value

                elif NonRoundShapeInspectParam.instance.shape == 2: # oval
                    difference = round(NonRoundShapeData[i].shortSize - NonRoundShapeInspectParam.instance.dimensions[i].ovlShrt, config.FLOAT_NUMBER)
                    IsDefect = False
                    if difference < NonRoundShapeInspectParam.instance.dimensions[i].minOvlShrtTolerance*(-1) or difference > NonRoundShapeInspectParam.instance.dimensions[i].maxOvlShrtTolerance:
                        IsDefect = True
                        FinalDefect = True
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};OvlShrt{i+1};{round(NonRoundShapeData[i].shortSize, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diff OvlShrt{i+1};{round(difference, config.FLOAT_NUMBER)};{not IsDefect}")
                        
                    # Mold result
                    DimensionOut = NonRoundShapeData[i].shortSize
                    if DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxOvlShrtAlarm or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minOvlShrtAlarm:
                        MoldResult = MOLD_RESULT.ALARM.value
                    elif (DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxOvlShrtWarning or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minOvlShrtWarning) \
                        and MoldResult == MOLD_RESULT.PASS.value:
                        MoldResult = MOLD_RESULT.WARNING.value


                    difference = round(NonRoundShapeData[i].longSize - NonRoundShapeInspectParam.instance.dimensions[i].ovlLong, config.FLOAT_NUMBER)
                    IsDefect = False
                    if difference < NonRoundShapeInspectParam.instance.dimensions[i].minOvlLongTolerance*(-1) or difference > NonRoundShapeInspectParam.instance.dimensions[i].maxOvlLongTolerance:
                        IsDefect = True
                        FinalDefect = True
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};OvlLong{i+1};{round(NonRoundShapeData[i].longSize, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diff OvlLong{i+1};{round(difference, config.FLOAT_NUMBER)};{not IsDefect}")    
                    
                    # Mold result
                    DimensionOut = NonRoundShapeData[i].longSize
                    if DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxOvlLongAlarm or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minOvlLongAlarm:
                        MoldResult = MOLD_RESULT.ALARM.value
                    elif (DimensionOut >= NonRoundShapeInspectParam.instance.dimensions[i].maxOvlLongWarning or \
                        DimensionOut <= NonRoundShapeInspectParam.instance.dimensions[i].minOvlLongWarning) \
                        and MoldResult == MOLD_RESULT.PASS.value:
                        MoldResult = MOLD_RESULT.WARNING.value


                if FinalDefect:
                    DefectCodes.add(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, f"Non-round Shape Dimension {NonRoundShapeInspectParam.instance.dimensionsName[i]}", color)
            print("Non-round Shape Inspect time: ", time.time() - t1)
        ##### End Glass Container Shape #####

        ##### BodyR Dimension Inspect #####
        if BodyRInspectParam.instance.enable:
            t1 = time.time()
            color = (0, 102, 255)
            for i in range(BodyRInspectParam.instance.numberDimension):
                if BodyRInspectParam.instance.dimensions[i].enable:
                    height = BodyRInspectParam.instance.dimensions[i].height
                    dimensions = BodyRInspectParam.instance.dimensions[i].dimension
                    minTolerances = BodyRInspectParam.instance.dimensions[i].minTolerance
                    maxTolerances = BodyRInspectParam.instance.dimensions[i].maxTolerance

                    IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = BodyRInspect(ImageOVL, LocationRegion, LocationRect,\
                                    height, dimensions, minTolerances, maxTolerances, BodyRInspectParam.instance.dimensionsName[i], i, \
                                    color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.BOTTOM])
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.BODYR_DIMENSION.name};Dimension {BodyRInspectParam.instance.dimensionsName[i]};{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.BODYR_DIMENSION.name};Diff Dimension {BodyRInspectParam.instance.dimensionsName[i]};{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
                    if IsDefect:
                        DefectCodes.add(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.BODYR_DIMENSION.value}")
                        ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, f"Dimension {BodyRInspectParam.instance.dimensionsName[i]}", color)
                    
                    # Mold result
                    if DimensionOut >= BodyRInspectParam.instance.dimensions[i].maxAlarm or \
                        DimensionOut <= BodyRInspectParam.instance.dimensions[i].minAlarm:
                        MoldResult = MOLD_RESULT.ALARM.value
                    elif (DimensionOut >= BodyRInspectParam.instance.dimensions[i].maxWarning or \
                        DimensionOut <= BodyRInspectParam.instance.dimensions[i].minWarning) \
                        and MoldResult == MOLD_RESULT.PASS.value:
                        MoldResult = MOLD_RESULT.WARNING.value
            print("BodyR Dimension Inspect time: ", time.time() - t1)
        ##### End BodyR Dimension #####

        ##### Number Code Decode #####
        if NumberCodeDecodeParam.instance.enable:
            color = NumberCodeDecodeParam.instance.color
            
            if NumberReaderData.codeNumber == 0 and mlCore.bottomNumberReaderDetectionModel is not None:
                # call decode again
                BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect
                ROI = [int((BLEFT)*ZOOM_RATIO + NumberCodeDecodeParam.instance.bottomROI/AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]),
                    int(BTOP*ZOOM_RATIO), 
                    int((BLEFT)*ZOOM_RATIO + (NumberCodeDecodeParam.instance.bottomROI + NumberCodeDecodeParam.instance.heightROI)/AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]),
                    int(BBOTTOM*ZOOM_RATIO)]
                isPass, ImageOVL, NumberReaderData.codeNumber = mlCore.bottomNumberReaderDetectionModel.NumberReaderDecode(
                    ImageBOT, ImageOVL, ROI, 0.3, NumberCodeDecodeParam.instance.color)


            DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.CODE_NUMBER.name};Standard Code Number;{NumberCodeDecodeParam.instance.codeNumber};{True}")
            DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.CODE_NUMBER.name};Code Number;{NumberReaderData.codeNumber};{NumberReaderData.codeNumber == NumberCodeDecodeParam.instance.codeNumber}")

            if NumberCodeDecodeParam.instance.codeNumber == NumberReaderData.codeNumber:
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace,\
                    f"Standard Code: {NumberCodeDecodeParam.instance.codeNumber} --- Inspect Code: {NumberReaderData.codeNumber}", color)
            else:
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace,\
                    f"Standard Code: {NumberCodeDecodeParam.instance.codeNumber} --- Inspect Code: {NumberReaderData.codeNumber}", (0, 0, 255))
                DefectCodes.add(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.CODE_NUMBER.value}")
            
            NumberReaderData.Reset()
        ##### End Number Code Decode #####
        ImageOVL = ImageOVL[:imgSize[1], :imgSize[0], :]
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
    except:
        DefectCodes.add(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.PROCESS_ERROR.value}")
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult

def InspectNonRoundShape(ImageBOT, NonRoundShapeData: List[InspectNonRoundShapeData], NumberReaderData: NumberReaderData, mlCore: MLCore):
    ImageOVL = cv2.cvtColor(ImageBOT, cv2.COLOR_GRAY2BGR)
    DefectCodes = set()
    DefectInfos = []
    OverlayInfos = []
    t = time.time()
    OvlStringSpace = 140
    OvlStringPos = [OvlStringSpace, OvlStringSpace]
    try:
        ZOOM_RATIO = 2
        zoomSize = (int(ImageBOT.shape[1]/ZOOM_RATIO), int(ImageBOT.shape[0]/ZOOM_RATIO))
        ImageBotZoom = cv2.resize(ImageBOT, zoomSize, interpolation=cv2.INTER_LINEAR)

        ##### Location #####
        t1 = time.time()
        MaxThreshold = 100
        isPass, ImageOVL, LocationRegion, LocationRect = BotomLocation(ImageBotZoom, ImageOVL,\
                                MaxThreshold, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.BOTTOM])
        if not isPass:
            pass
        print("Location time: ", time.time() - t1)
        ##### End Location #####

        BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect # pixel/ZOOM_RATIO

        # Number reader decode
        if NumberReaderData.codeNumber == 0 and mlCore.bottomNumberReaderDetectionModel is not None and\
            NumberCodeDecodeParam.instance.enable:
            ROI = [int((BLEFT)*ZOOM_RATIO + NumberCodeDecodeParam.instance.bottomROI/AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]),
                int(BTOP*ZOOM_RATIO), 
                int((BLEFT)*ZOOM_RATIO + (NumberCodeDecodeParam.instance.bottomROI + NumberCodeDecodeParam.instance.heightROI)/AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]),
                int(BBOTTOM*ZOOM_RATIO)]
            isPass, ImageOVL, NumberReaderData.codeNumber = mlCore.bottomNumberReaderDetectionModel.NumberReaderDecode(
                ImageBOT, ImageOVL, ROI, 0.2, NumberCodeDecodeParam.instance.color)


            if NumberReaderData.codeNumber != 0:
                # store image
                NumberReaderData.image = ImageBOT
                NumberReaderData.imageOVL = ImageOVL

            DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.CODE_NUMBER.name};Standard Code Number;{NumberCodeDecodeParam.instance.codeNumber};{True}")
            DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.CODE_NUMBER.name};Code Number;{NumberReaderData.codeNumber};{NumberReaderData.codeNumber == NumberCodeDecodeParam.instance.codeNumber}")
            if NumberReaderData.codeNumber == NumberCodeDecodeParam.instance.codeNumber:
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace,\
                    f"Standard Code: {NumberCodeDecodeParam.instance.codeNumber} --- Inspect Code: {NumberReaderData.codeNumber}", NumberCodeDecodeParam.instance.color)
            else:
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace,\
                    f"Standard Code: {NumberCodeDecodeParam.instance.codeNumber} --- Inspect Code: {NumberReaderData.codeNumber}", (0, 0, 255))

        for i in range(NonRoundShapeInspectParam.instance.numberDimension):

            height = NonRoundShapeInspectParam.instance.dimensions[i].rectParameter
            if NonRoundShapeInspectParam.instance.shape == 0: # rectangle
                height = NonRoundShapeInspectParam.instance.dimensions[i].rectParameter
            elif NonRoundShapeInspectParam.instance.shape == 1: # square
                height = NonRoundShapeInspectParam.instance.dimensions[i].sqrParameter
            elif NonRoundShapeInspectParam.instance.shape == 2: # ovl
                height = NonRoundShapeInspectParam.instance.dimensions[i].ovlParameter

            bottleHeight = (BRIGHT - BLEFT)*ZOOM_RATIO*AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]
            if bottleHeight < HeightInspectParam.instance.height:
                diffmm = HeightInspectParam.instance.height - bottleHeight
                diff = height - diffmm
                if diff > 0:
                    height = diff

            color = (0, 255, 255)

            IsDefect, ImageOVL, DimensionOut = NonRoundShapeInspect(ImageOVL, LocationRegion, LocationRect,\
                            height, NonRoundShapeInspectParam.instance.dimensionsName[i], \
                            color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.BOTTOM])
            size = DimensionOut

            if True:#NonRoundShapeInspectParam.instance.enable:
                # GlassContainerShapeData.images.append(ImageBOT)

                if NonRoundShapeData[i].shortSize == 0 or size < NonRoundShapeData[i].shortSize:
                    NonRoundShapeData[i].shortSize = round(size, config.FLOAT_NUMBER)
                if NonRoundShapeData[i].diagonalSize == 0 or size > NonRoundShapeData[i].diagonalSize:
                    NonRoundShapeData[i].diagonalSize = round(size, config.FLOAT_NUMBER)

                if NonRoundShapeInspectParam.instance.shape == 0: # rectangle
                    # calculate curl of bottle
                    d = math.sqrt(NonRoundShapeInspectParam.instance.dimensions[i].rectLong**2 + NonRoundShapeInspectParam.instance.dimensions[i].rectShrt**2)
                    curlDimension = d - NonRoundShapeInspectParam.instance.dimensions[i].rectDiag
                    if curlDimension < 0:
                        curlDimension = 0

                    NonRoundShapeData[i].longSize =  round(math.sqrt((NonRoundShapeData[i].diagonalSize+curlDimension)**2 - \
                                                    NonRoundShapeData[i].shortSize**2), config.FLOAT_NUMBER)

                    if NonRoundShapeData[i].longSize == 0:
                        NonRoundShapeData[i].longSize = NonRoundShapeData[i].diagonalSize
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos,\
                            OvlStringSpace, f"RecShrt{i+1}: {NonRoundShapeData[i].shortSize}", (0, 0, 255))
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos,\
                            OvlStringSpace, f"RecLong{i+1}: {NonRoundShapeData[i].longSize}", (0, 0, 255))
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos,\
                            OvlStringSpace, f"RecDiag{i+1}: {NonRoundShapeData[i].diagonalSize}", (0, 0, 255))
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Short Size;{round(NonRoundShapeData[i].shortSize, config.FLOAT_NUMBER)};{True}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Long Size;{round(NonRoundShapeData[i].longSize, config.FLOAT_NUMBER)};{True}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diagonal Size;{round(NonRoundShapeData[i].diagonalSize, config.FLOAT_NUMBER)};{True}")
                    

                elif NonRoundShapeInspectParam.instance.shape == 1: # square
                    NonRoundShapeData[i].longSize = NonRoundShapeData[i].shortSize
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos,\
                            OvlStringSpace, f"SqrSide{i+1}: {NonRoundShapeData[i].shortSize}", (0, 0, 255))
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos,\
                            OvlStringSpace, f"SqrDiag{i+1}: {NonRoundShapeData[i].diagonalSize}", (0, 0, 255))
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Size;{round(NonRoundShapeData[i].shortSize, config.FLOAT_NUMBER)};{True}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Diagonal Size;{round(NonRoundShapeData[i].diagonalSize, config.FLOAT_NUMBER)};{True}")
                    


                elif NonRoundShapeInspectParam.instance.shape == 2: # oval
                    NonRoundShapeData[i].longSize = NonRoundShapeData[i].diagonalSize
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos,\
                            OvlStringSpace, f"OvlShrt{i+1}: {NonRoundShapeData[i].shortSize}", (0, 0, 255))
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos,\
                            OvlStringSpace, f"OvlLong{i+1}: {NonRoundShapeData[i].longSize}", (0, 0, 255))
                    
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Short Size;{round(NonRoundShapeData[i].shortSize, config.FLOAT_NUMBER)};{True}")
                    DefectInfos.append(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.NON_ROUND_SHAPE.name};Long Size;{round(NonRoundShapeData[i].longSize, config.FLOAT_NUMBER)};{True}")

        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, NonRoundShapeData, NumberReaderData
    except Exception as e:
        DefectCodes.add(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.PROCESS_ERROR.value}")
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, NonRoundShapeData, NumberReaderData

def InspectTopRotate(ImageTOP, ImageTopMask, TopInspectionShareData: TopInspectData):
    ImageOVL = cv2.cvtColor(ImageTOP, cv2.COLOR_GRAY2BGR)
    DefectCodes = set()
    DefectInfos = []
    OverlayInfos = []
    t = time.time()
    OvlStringSpace = 70
    OvlStringPos = [OvlStringSpace, OvlStringSpace]
    MoldResult = MOLD_RESULT.PASS.value
    try:
        ZOOM_RATIO = 1
        zoomSize = (int(ImageTOP.shape[1]/ZOOM_RATIO), int(ImageTOP.shape[0]/ZOOM_RATIO))
        ImageTopZoom = cv2.resize(ImageTOP, zoomSize, interpolation=cv2.INTER_LINEAR)

        ##### Location #####
        t1 = time.time()
        MaxThreshold = 100
        isPass, ImageOVL, LocationRegion, LocationRect = TopLocation(ImageTopZoom, \
                    ImageTopMask, ImageOVL, MaxThreshold, ZOOM_RATIO)
        if not isPass:
            pass
        print("Location time: ", time.time() - t1)
        ##### End Location #####

        BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect # pixel/ZOOM_RATIO

        #### S Dimension Inspect ####
        if GroupFinishDimensionInspect.instance.dimensionS1.enable:
            t1 = time.time()
            dimension = GroupFinishDimensionInspect.instance.dimensionS1.dimension
            minTolerance = GroupFinishDimensionInspect.instance.dimensionS1.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionS1.maxTolerance                
            parameter1 = GroupFinishDimensionInspect.instance.dimensionS1.parameter1 # thread height
            parameter2 = GroupFinishDimensionInspect.instance.dimensionS1.parameter2 # (T-E)/2 thread width
            parameter3 = 20 # distance from top finish line to bottom measurement region
            color = (95, 143, 222)
            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = SDimensionInspect(ImageOVL, LocationRegion, LocationRect,\
                    parameter1, parameter2, parameter3, dimension, minTolerance,\
                    maxTolerance, 0, color, ZOOM_RATIO, 
                    AppConfigParam.instance.resolution[TRACK_ID.TOP])

            # store data
            if TopInspectionShareData.sDimensionData.dimension == 0 or \
                (TopInspectionShareData.sDimensionData.dimension > DimensionOut and \
                 DimensionOut != 0):
                TopInspectionShareData.sDimensionData.dimension = DimensionOut

            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.S_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.S_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            
            diff = round(TopInspectionShareData.sDimensionData.dimension - dimension, config.FLOAT_NUMBER)
            if diff < minTolerance*(-1) or diff > maxTolerance: # current have defect
                DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.S_DIMENSION.value}")
                ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension S", color)
           
            print("S Dimension Inspect time: ", time.time() - t1)

        #### End S Dimension Inspect ####


        #### Flange Inspect ####
        if FlangeInspectParam.instance.enable:
            t1 = time.time()
            maxKnockout = GroupFinishDimensionInspect.instance.dimensionS1.parameter2*0.8 
            minKnockout = FlangeInspectParam.instance.parameter1 
            minImageNumber = FlangeInspectParam.instance.parameter2
            parameter3 = FlangeInspectParam.instance.parameter3 # Bottom of area
            parameter4 = FlangeInspectParam.instance.parameter4 # Top of area
            openingRatio = GroupFinishDimensionInspect.instance.dimensionS1.parameter1 # thread height


            color = (0, 0, 255)
            IsDefect, ImageOVL, MinKnockoutOut, MaxKnockoutOut, NumberDefect = KnockoutInspect(ImageOVL, LocationRegion, LocationRect,\
                                    parameter3, parameter4, openingRatio, minKnockout, maxKnockout, color, ZOOM_RATIO, 
                                    AppConfigParam.instance.resolution[TRACK_ID.TOP])
            if IsDefect:

                # store data
                if MaxKnockoutOut > TopInspectionShareData.flangeData.maxKnockout:
                    TopInspectionShareData.flangeData.maxKnockout = MaxKnockoutOut
                if MinKnockoutOut < TopInspectionShareData.flangeData.minKnockout or \
                    TopInspectionShareData.flangeData.minKnockout == 0:
                    TopInspectionShareData.flangeData.minKnockout = MinKnockoutOut

                TopInspectionShareData.flangeData.knockoutConsecutiveImageNumber += 1
                if TopInspectionShareData.flangeData.knockoutConsecutiveImageNumber > \
                    TopInspectionShareData.flangeData.maxKnockoutConsecutiveImageNumber:
                    TopInspectionShareData.flangeData.maxKnockoutConsecutiveImageNumber = \
                        TopInspectionShareData.flangeData.knockoutConsecutiveImageNumber
                
                # store image
                TopInspectionShareData.image = ImageTOP
                TopInspectionShareData.imageOVL = ImageOVL
                    
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.FLANGE_DIMENSION.name};Min Knockout;{round(MinKnockoutOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.FLANGE_DIMENSION.name};Max Knockout;{round(MaxKnockoutOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if TopInspectionShareData.flangeData.maxKnockoutConsecutiveImageNumber >= minImageNumber:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.FLANGE_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Flange", color)


            else:
                TopInspectionShareData.flangeData.knockoutConsecutiveImageNumber = 0

           
            print("Flange Inspect time: ", time.time() - t1)

        #### End Flange Inspect ####

        #### Knockout Inspect ####
        if KnockoutInspectParam.instance.enable:
            t1 = time.time()
            maxKnockout = GroupFinishDimensionInspect.instance.dimensionS1.parameter2*0.8
            minKnockout = KnockoutInspectParam.instance.parameter1 
            maxImageNumber = KnockoutInspectParam.instance.parameter2
            parameter3 = KnockoutInspectParam.instance.parameter3 # Bottom of area
            parameter4 = KnockoutInspectParam.instance.parameter4 # Top of area
            openingRatio = GroupFinishDimensionInspect.instance.dimensionS1.parameter1 # thread height


            color = (0, 0, 255)
            IsDefect, ImageOVL, MinKnockoutOut, MaxKnockoutOut, NumberDefect = KnockoutInspect(ImageOVL, LocationRegion, LocationRect,\
                                    parameter3, parameter4, openingRatio, minKnockout, maxKnockout, color, ZOOM_RATIO, 
                                    AppConfigParam.instance.resolution[TRACK_ID.TOP])
            if IsDefect:

                # store data
                if MaxKnockoutOut > TopInspectionShareData.knockoutData.maxKnockout:
                    TopInspectionShareData.knockoutData.maxKnockout = MaxKnockoutOut
                if MinKnockoutOut < TopInspectionShareData.knockoutData.minKnockout or \
                    TopInspectionShareData.knockoutData.minKnockout == 0:
                    TopInspectionShareData.knockoutData.minKnockout = MinKnockoutOut

                TopInspectionShareData.knockoutData.knockoutConsecutiveImageNumber += 1
                if TopInspectionShareData.knockoutData.knockoutConsecutiveImageNumber > \
                    TopInspectionShareData.knockoutData.maxKnockoutConsecutiveImageNumber:
                    TopInspectionShareData.knockoutData.maxKnockoutConsecutiveImageNumber = \
                        TopInspectionShareData.knockoutData.knockoutConsecutiveImageNumber
                    
                # store image
                TopInspectionShareData.image = ImageTOP
                TopInspectionShareData.imageOVL = ImageOVL

                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.KNOCKOUT_DIMENSION.name};Min Knockout;{round(MinKnockoutOut, config.FLOAT_NUMBER)};{not IsDefect}")
                DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.KNOCKOUT_DIMENSION.name};Max Knockout;{round(MaxKnockoutOut, config.FLOAT_NUMBER)};{not IsDefect}")
                if 0 < TopInspectionShareData.knockoutData.maxKnockoutConsecutiveImageNumber <= maxImageNumber:
                    DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.KNOCKOUT_DIMENSION.value}")
                    ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Knockout", color)
            else:
                TopInspectionShareData.knockoutData.knockoutConsecutiveImageNumber = 0

           
            print("Knockout Inspect time: ", time.time() - t1)

        #### End Knockout Inspect ####


        
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, TopInspectionShareData
    except Exception as inst:
        DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.PROCESS_ERROR.value}")
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, TopInspectionShareData

def InspectCorrection(ImageTOP, ImageTopMask, DataStr, CorrrectionInspectionShareData: CorrectinInspectData):
    ImageOVL = cv2.cvtColor(ImageTOP, cv2.COLOR_GRAY2BGR)
    DefectCodes = set()
    DefectInfos = []
    OverlayInfos = []
    t = time.time()
    OvlStringSpace = 70
    OvlStringPos = [OvlStringSpace, OvlStringSpace]
    MoldResult = MOLD_RESULT.PASS.value
    try:
        ZOOM_RATIO = 1
        zoomSize = (int(ImageTOP.shape[1]/ZOOM_RATIO), int(ImageTOP.shape[0]/ZOOM_RATIO))
        ImageTopZoom = cv2.resize(ImageTOP, zoomSize, interpolation=cv2.INTER_LINEAR)

        ##### Location #####
        if CorrrectionInspectionShareData.locationRegion is None:
            t1 = time.time()
            MaxThreshold = 100
            isPass, _, CorrrectionInspectionShareData.locationRegion\
                , CorrrectionInspectionShareData.locationRect = TopLocation(ImageTopZoom, \
                        ImageTopMask, ImageOVL, MaxThreshold, ZOOM_RATIO)
            if not isPass:
                pass
            print("Location time: ", time.time() - t1)
        ##### End Location #####

        BLEFT, BTOP, BRIGHT, BBOTTOM = CorrrectionInspectionShareData.locationRect # pixel/ZOOM_RATIO
        
        # draw overlay for finish line
        cv2.line(ImageOVL, (0, BTOP*ZOOM_RATIO), (ImageOVL.shape[1]-1, BTOP*ZOOM_RATIO), (255, 0, 0), config.OVLSIZE)

        # defect
        # extract data
        dataSplit = DataStr.split('$')
        if len(dataSplit) < 3:
            return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, CorrrectionInspectionShareData
        
        inspectDataInfo = dataSplit[2].split(',')
        if len(inspectDataInfo) < 5:
            return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, CorrrectionInspectionShareData
        defectIndex = DEFECT_NAME((int)(inspectDataInfo[0]))
        dimension = (float)(inspectDataInfo[1])
        parameter1 = (float)(inspectDataInfo[2]) # distance from top finish line to bottom of area
        parameter2 = (float)(inspectDataInfo[3]) # height of measurement area
        parameter3 = (float)(inspectDataInfo[4]) # height of measurement area

        if defectIndex == DEFECT_NAME.F_DIMENSION:
            minTolerance = GroupFinishDimensionInspect.instance.dimensionF.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionF.maxTolerance
            parameter2 = parameter1
            color = (0, 255, 255)
            index = 1
            dimensionName = "F"
            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                FinishDimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion, \
                    CorrrectionInspectionShareData.locationRect, parameter1, parameter2, dimension,\
                    minTolerance, maxTolerance, dimensionName, color, index, ZOOM_RATIO,\
                    AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.F_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.F_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension F", color)

        elif defectIndex == DEFECT_NAME.A_DIMENSION:
            # A Dimension
            minTolerance = GroupFinishDimensionInspect.instance.dimensionA.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionA.maxTolerance
            parameter2 = parameter1
            color = (0, 102, 255)
            index = 1
            dimensionName = "A"

            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                FinishDimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion, \
                    CorrrectionInspectionShareData.locationRect, parameter1, parameter2, dimension,\
                    minTolerance, maxTolerance, dimensionName, color, index, ZOOM_RATIO,\
                    AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.A_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.A_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension A", color)

        elif defectIndex == DEFECT_NAME.T_DIMENSION:
            # T Dimension
            minTolerance = GroupFinishDimensionInspect.instance.dimensionT.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionT.maxTolerance
            color = (0, 102, 255)
            index = 1
            dimensionName = "T"

            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                FinishDimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion, \
                    CorrrectionInspectionShareData.locationRect, parameter1, parameter2, dimension,\
                    minTolerance, maxTolerance, dimensionName, color, index, ZOOM_RATIO,\
                    AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.T_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.T_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension T", color)

        elif defectIndex == DEFECT_NAME.E_DIMENSION:
            # E Dimension
            minTolerance = GroupFinishDimensionInspect.instance.dimensionE.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionE.maxTolerance
            color = (84, 117, 17)
            index = 1
            dimensionName = "E"

            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                FinishDimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion, \
                    CorrrectionInspectionShareData.locationRect, parameter1, parameter2, dimension,\
                    minTolerance, maxTolerance, dimensionName, color, index, ZOOM_RATIO,\
                    AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.E_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.E_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension E", color)

        elif defectIndex == DEFECT_NAME.D_DIMENSION:
            # D Dimension
            minTolerance = GroupFinishDimensionInspect.instance.dimensionD.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionD.maxTolerance
            color = (49,78,108)

            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                DDimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion,\
                    CorrrectionInspectionShareData.locationRect, parameter1, parameter2,\
                    parameter3, dimension, minTolerance, maxTolerance,\
                    color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension D", color)

        elif defectIndex == DEFECT_NAME.B_DIMENSION:
            # B Dimension
            minTolerance = GroupFinishDimensionInspect.instance.dimensionB.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionB.maxTolerance
            color = (126, 90, 240)
            index = 1
            dimensionName = "B"

            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                FinishDimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion, \
                    CorrrectionInspectionShareData.locationRect, parameter1, parameter2, dimension,\
                    minTolerance, maxTolerance, dimensionName, color, index, ZOOM_RATIO,\
                    AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.B_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.B_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension B", color)


        elif defectIndex == DEFECT_NAME.H_DIMENSION:
            # H Dimension
            # Find distance from top to where correct diameter
            minTolerance = GroupFinishDimensionInspect.instance.dimensionH.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionH.maxTolerance                
            color = (210,71,175)

            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                HDimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion,\
                                CorrrectionInspectionShareData.locationRect,\
                                parameter1, parameter2, dimension, minTolerance, maxTolerance,\
                                color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.H_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.H_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension H", color)

        elif defectIndex == DEFECT_NAME.LUGT_DIMENSION:
            # LUG Dimension
            minTolerance = GroupFinishDimensionInspect.instance.dimensionLugT.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionLugT.maxTolerance
            color = (152, 190, 255)
            index = 1
            dimensionName = "LugT"

            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                FinishDimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion,\
                                    CorrrectionInspectionShareData.locationRect,\
                                    parameter1, parameter2, dimension, minTolerance, maxTolerance, dimensionName,\
                                    color, index, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension LugT", color)

        elif defectIndex == DEFECT_NAME.LUGT1_DIMENSION:
            # LUGT1 Dimension
            minTolerance = GroupFinishDimensionInspect.instance.dimensionLugT1.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionLugT1.maxTolerance
            index = 1
            color = (203,207,72)
            IsDefect, ImageOVL, DimensionOut, DiffDimensionOut = \
                LugT1DimensionInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion,\
                                CorrrectionInspectionShareData.locationRect,\
                                parameter1, parameter2, dimension, minTolerance, maxTolerance, index,\
                                color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT1_DIMENSION.name};Dimension;{round(DimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.LUGT1_DIMENSION.name};Diff Dimension;{round(DiffDimensionOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "Dimension LugT1", color)

        elif defectIndex == DEFECT_NAME.D_ANGLE_DIMENSION:
            # D Angle
            # Find minimum angle of the underside of the D ring related to horizontal
            angle = dimension # GroupFinishDimensionInspect.instance.dimensionDAngle.dimension # locking ring depth
            minTolerance = GroupFinishDimensionInspect.instance.dimensionDAngle.minTolerance
            maxTolerance = GroupFinishDimensionInspect.instance.dimensionDAngle.maxTolerance                
            color = (145,131,2)

            IsDefect, ImageOVL, AngleOut, DiffAngleOut = \
                DAngleInspect(ImageOVL, CorrrectionInspectionShareData.locationRegion,\
                            CorrrectionInspectionShareData.locationRect,\
                            parameter1, parameter2, parameter3, angle, minTolerance, maxTolerance,\
                            color, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.TOP], True)
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_ANGLE_DIMENSION.name};Angle;{round(AngleOut, config.FLOAT_NUMBER)};{not IsDefect}")
            DefectInfos.append(f"{TRACK_ID.TOP.value};{DEFECT_NAME.D_ANGLE_DIMENSION.name};Diff Angle;{round(DiffAngleOut, config.FLOAT_NUMBER)};{not IsDefect}")
            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, "D Angle", color)

        
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, CorrrectionInspectionShareData
    except Exception as inst:
        DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.PROCESS_ERROR.value}")
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, CorrrectionInspectionShareData
  
def Teach(ImageTOP):
    DefectInfos = []
    OverlayInfos = []
    return True, DefectInfos, OverlayInfos

def CalibrationTop(ImageTOP, ImageMID, ImageBOT, ImageTopMask):
    ImageOVL = cv2.cvtColor(ImageTOP, cv2.COLOR_GRAY2BGR)

    DefectCodes = set()
    DefectInfos = []
    OverlayInfos = []
    t = time.time()
    OvlStringSpace = 70
    OvlStringPos = [OvlStringSpace, OvlStringSpace]
    MoldResult = MOLD_RESULT.PASS.value
    try:
        ZOOM_RATIO = 1
        zoomSize = (int(ImageTOP.shape[1]/ZOOM_RATIO), int(ImageTOP.shape[0]/ZOOM_RATIO))
        ImageTopZoom = cv2.resize(ImageTOP, zoomSize, interpolation=cv2.INTER_LINEAR)

        ##### Location #####
        t1 = time.time()
        MaxThreshold = 100
        isPass, ImageOVL, LocationRegion, LocationRect = TopLocation(ImageTopZoom, \
                    ImageTopMask, ImageOVL, MaxThreshold, ZOOM_RATIO)
        if not isPass:
            pass
        print("Location time: ", time.time() - t1)
        ##### End Location #####

        BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect # pixel/ZOOM_RATIO

        ##### Find new resolution #####
        # find same fine group finish dimension
        dimension = CalibCameraPositionParam.instance.toolWidth
        parameter1 = 400 # distance from top finish line to bottom # pixel
        parameter2 = 200 # height of measurement area # pixel
        color = (0, 102, 255)
        isPass, ImageOVL, resolutionOut = CalibToolDimensionTopInspect(ImageOVL, LocationRegion, LocationRect,\
                                            parameter1, parameter2, dimension, color, ZOOM_RATIO)

        ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, f"Resolution (mm/pixel): {resolutionOut}", color)
        
        AppConfigParam.instance.resolution[TRACK_ID.TOP] = resolutionOut

        ##### Height Inspect #####
        t1 = time.time()

        CalibCameraPositionParam.instance.hideBottleHeight[TRACK_ID.TOP] = round((
            CalibCameraPositionParam.instance.toolHeight - (BBOTTOM - BTOP)*ZOOM_RATIO*\
            AppConfigParam.instance.resolution[TRACK_ID.TOP]), config.CALIBRATION_FLOAT_NUMBER)
        color = (255, 0, 0)

        # OVL
        x = 150
        cy = ImageOVL.shape[0] - int((BTOP + BBOTTOM)/2*ZOOM_RATIO)
        text = f'Height: {round(CalibCameraPositionParam.instance.toolHeight, config.FLOAT_NUMBER)}'
        textSize = cv2.getTextSize(text, config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
        ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_CLOCKWISE)
        cv2.putText(ImageOVL, text, (int(cy - textSize[0]/2) , x - 50), config.FONT_FAMILY, config.FONT_SIZE, color, config.OVLSIZE)
        ImageOVL = cv2.rotate(ImageOVL, cv2.ROTATE_90_COUNTERCLOCKWISE)

        print("Height Inspect time: ", time.time() - t1)
        ##### End Height #####

        DefectInfos.append(f"{AppConfigParam.instance.resolution[TRACK_ID.TOP]}")
        DefectInfos.append(f"{CalibCameraPositionParam.instance.hideBottleHeight[TRACK_ID.TOP]}")

        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
    except Exception as inst:
        DefectCodes.add(f"{TRACK_ID.TOP.value};{DEFECT_NAME.PROCESS_ERROR.value}")
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
    
def CalibrationBot(ImageTOP, ImageMID, ImageBOT, ImageBOTTOP):
    ImageOVL = cv2.cvtColor(ImageBOT, cv2.COLOR_GRAY2BGR)
    DefectCodes = set()
    DefectInfos = []
    OverlayInfos = []
    t = time.time()
    OvlStringSpace = 70
    OvlStringPos = [OvlStringSpace, OvlStringSpace]
    MoldResult = MOLD_RESULT.PASS.value
    try:

        ZOOM_RATIO = 2
        imgSize = (int(ImageBOT.shape[1]), int(ImageBOT.shape[0]))
        zoomSize = (int(ImageBOT.shape[1]/ZOOM_RATIO), int(ImageBOT.shape[0]/ZOOM_RATIO))

        # ImageBOTTop: see the top of the bottle at camera bottom
        # ImageBOT: see the bottom of the bottle at camera bottom

        if ImageBOT is not None:
            # find max bottle height in bottom view
            t1 = time.time()
            ImageBOTZoom = cv2.resize(ImageBOT, zoomSize, interpolation=cv2.INTER_LINEAR)

            MaxThreshold = 100
            isPass, ImageOVL, LocationRegion, LocationRect = BotomLocation(ImageBOTZoom, ImageOVL,\
                                    MaxThreshold, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.BOTTOM])
                                    
            if not isPass:
                return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
            
            print("Location time: ", time.time() - t1)

            BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect

            ##### Find new resolution #####
            # find same fine group finish dimension
            dimension = CalibCameraPositionParam.instance.toolWidth
            parameter1 = 400 # distance from top finish line to bottom # pixel
            parameter2 = 200 # height of measurement area # pixel
            color = (0, 102, 255)
            isPass, ImageOVL, resolutionOut = CalibToolDimensionBotInspect(ImageOVL, LocationRegion, LocationRect,\
                                                parameter1, parameter2, dimension, color, ZOOM_RATIO)

            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, f"Resolution (mm/pixel): {resolutionOut}", color)
            
            # update new resolution
            AppConfigParam.instance.resolution[TRACK_ID.BOTTOM] = resolutionOut


            # find max bottle height in bottom view # mm
            CalibCameraPositionParam.instance.maxBottleHeightInBottom = round((BRIGHT - BLEFT)*ZOOM_RATIO*\
                AppConfigParam.instance.resolution[TRACK_ID.BOTTOM], config.CALIBRATION_FLOAT_NUMBER) 

        if ImageBOTTOP is not None:
            ImageOVL = cv2.cvtColor(ImageBOTTOP, cv2.COLOR_GRAY2BGR)
            ImageBOTTOPZoom = cv2.resize(ImageBOTTOP, zoomSize, interpolation=cv2.INTER_LINEAR)
            
            ##### Location #####
            t1 = time.time()
            MaxThreshold = 100
            isPass, ImageOVL, LocationRegion, LocationRect = BotomLocation(ImageBOTTOPZoom, ImageOVL,\
                                    MaxThreshold, ZOOM_RATIO, AppConfigParam.instance.resolution[TRACK_ID.BOTTOM])
                                    
            if not isPass:
                return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
            
            print("Location time: ", time.time() - t1)

            
            BLEFT, BTOP, BRIGHT, BBOTTOM = LocationRect

            ##### Find new resolution #####
            # find same fine group finish dimension
            dimension = CalibCameraPositionParam.instance.toolWidth
            parameter1 = 400 # distance from top finish line to bottom # pixel
            parameter2 = 200 # height of measurement area # pixel
            color = (0, 102, 255)
            isPass, ImageOVL, resolutionOut = CalibToolDimensionBotInspect(ImageOVL, LocationRegion, LocationRect,\
                                                parameter1, parameter2, dimension, color, ZOOM_RATIO)

            ImageOVL, OvlStringPos = DrawOvlStr(ImageOVL, OvlStringPos, OvlStringSpace, f"Resolution (mm/pixel): {resolutionOut}", color)
            
            # update new resolution
            AppConfigParam.instance.resolution[TRACK_ID.BOTTOM] = resolutionOut


            ##### Height Inspect #####
            t1 = time.time()

            CalibCameraPositionParam.instance.hideBottleHeight[TRACK_ID.BOTTOM] = round((
                CalibCameraPositionParam.instance.toolHeight - (BRIGHT - BLEFT)*ZOOM_RATIO*\
                AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]), config.CALIBRATION_FLOAT_NUMBER)
            color = (255, 0, 0)

            # OVL

            y = max(int(BTOP - 100), 100)*ZOOM_RATIO
            x1 = BLEFT*ZOOM_RATIO
            x2 = BRIGHT*ZOOM_RATIO
            x = int((BLEFT + BRIGHT)/2)*ZOOM_RATIO
            cv2.arrowedLine(ImageOVL, [x1, y],\
                            [x2, y], (255, 0, 0), config.OVLSIZE, tipLength = 0.05)
            cv2.arrowedLine(ImageOVL, [x2, y],\
                            [x1, y], (255, 0, 0), config.OVLSIZE, tipLength = 0.05)
            text = f'Height: {round(CalibCameraPositionParam.instance.toolHeight, config.FLOAT_NUMBER)}'
            textSize = cv2.getTextSize(text, config.FONT_FAMILY, config.FONT_SIZE, config.OVLSIZE)[0]
            cv2.putText(ImageOVL, text, (int(x - textSize[0]/2), y - 50), config.FONT_FAMILY, config.FONT_SIZE, color, config.OVLSIZE)

            print("Height Inspect time: ", time.time() - t1)
            ##### End Height #####

        # add result to UI
        DefectInfos.append(f"{AppConfigParam.instance.resolution[TRACK_ID.BOTTOM]}")
        DefectInfos.append(f"{CalibCameraPositionParam.instance.hideBottleHeight[TRACK_ID.BOTTOM]}")
        DefectInfos.append(f"{CalibCameraPositionParam.instance.maxBottleHeightInBottom}")


        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult
    except:
        DefectCodes.add(f"{TRACK_ID.BOTTOM.value};{DEFECT_NAME.PROCESS_ERROR.value}")
        return ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult

def Inspect(ImageTOP, ImageMID, ImageBOT):

    # # call combine 3 image
    # imageCombine = ImageTOP
    # # call location
    # imageZoom, locationRegion, locationRect, ImageOVL, DefectInfos, OverlayInfos, DefectCodes = \
    #     BottleLocation(imageCombine)
    # # 
    # ImageOVL, DefectInfos, OverlayInfos, DefectCodes = InspectThread1(imageCombine, imageZoom,\
    #                     locationRegion, locationRect, ImageOVL)

    trackID = TRACK_ID.TOP
    imageTopMask = cv2.imread("TopMask.bmp", 0)
    if trackID == TRACK_ID.ALL or trackID == TRACK_ID.TOP:
        topInspectionShareData = TopInspectData()
        ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult = InspectTop(ImageTOP, ImageMID, ImageBOT, imageTopMask, topInspectionShareData, None)
    
    # if trackID == TRACK_ID.ALL or trackID == TRACK_ID.MID:
    #     ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult = InspectMid(ImageTOP, ImageMID, ImageBOT, None)

    if trackID == TRACK_ID.ALL or trackID == TRACK_ID.BOTTOM:
        nonRoundShapeData = []
        for i in range(NonRoundShapeInspectParam.instance.maxNumberDimension):
            nonRoundShapeData.append(InspectNonRoundShapeData())
        ImageOVL, DefectInfos, OverlayInfos, DefectCodes, MoldResult = InspectBot(ImageTOP, ImageMID, ImageBOT, ImageBOT, "0$0", nonRoundShapeData)

    return

def ReadRecipe(recipePath: str):
    # return True
    # pathSplit = recipePath.split("\\")
    # recipeName = pathSplit[-2]

    # read vision param
    visionParamPath = os.path.join(recipePath, "vision_parameter.vp")
    if not ReadVisionParam(visionParamPath):
        return False
    # read resolution
    configFilePath = os.path.join(os.path.expanduser("~"), "Bottle-Config", "config.json")
    if not ReadConfigData(configFilePath):
        return False
    
    # read calib camera position
    calibCameraPosFilePath = os.path.join(os.path.expanduser("~"), "Bottle-Config", "CalibCameraPosition.json")
    if not ReadCalibCameraPositionData(calibCameraPosFilePath):
        return False

    # process mold limit
    CalculateAlarm()


    # # read limit file
    # limitParamFilePath = os.path.join(recipePath, "limit_information.json")
    # if not ReadLimitParam(limitParamFilePath):
    #     return False

    # teachDataPath = os.path.join(recipePath, "TeachData.dat")
    # if not ReadTeachData(teachDataPath):
    #     return False
    return True

def UpdateCalibCameraPositionToFile():
    
    # write resolution
    configFilePath = os.path.join(os.path.expanduser("~"), "Bottle-Config", "config.json")
    WriteConfigData(configFilePath)
    
    # read calib camera position
    calibCameraPosFilePath = os.path.join(os.path.expanduser("~"), "Bottle-Config", "CalibCameraPosition.json")
    WriteCalibCameraPositionData(calibCameraPosFilePath)

    return True

def WarmingUp():
    return

