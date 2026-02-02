
import threading
import time
import cv2
from queue import Queue
import config
from config import DebugLog
from struct_define import *
from Inspection.lib import*
from Inspection.inspection_core import InspectTop, InspectMid, InspectBot, CalibrationTop, CalibrationBot,\
    InspectNonRoundShape, InspectTopRotate, InspectCorrection, MLCore

class InspectThread(threading.Thread):
    def __init__(self, id:int) -> None:
        super(InspectThread, self).__init__()
        self.daemon = True
        self.isRun = threading.Event()
        self.startEvent = threading.Event()
        self.isFinishInspectEvent = threading.Event()
        self.isFinishInspectEvent.clear()
        self.input = Queue()
        self.output = Queue()
        self.id = id
        self.infoManager = {}
        self.infoManager["RECIPE_PATH"] = ""
        self.resultManager = {}
        self.shareData = {} # for middle camera
        self.shareData["IS_MODEL_LOADED"] = False
        self.nonRoundShapeData = []
        for i in range(NonRoundShapeInspectParam.instance.maxNumberDimension):
            self.nonRoundShapeData.append(InspectNonRoundShapeData()) # only for inspection non round shape of bottom image
        self.topInspectData = TopInspectData() # only for inspection knockout of top image
        self.correctionInspectData = CorrectinInspectData() # only for inspect correction
        self.numberReaderData = NumberReaderData() # for check number code in bottom 2 image
        pass

    def run(self):
        self.isRun.set()
        try:
            DebugLog("InspectThread", f"Start thread")
            self.isRun.set()
            ImageTopMask = cv2.imread("TopMask.bmp", 0)
            mlCore = None
            if self.id == 0:
                # load yolo detection model for bottom cam
                mlCore = MLCore(self.id)
                self.shareData["IS_MODEL_LOADED"] = mlCore.isLoadModelSuccess

            while self.isRun.is_set():
                # wait for run again
                self.startEvent.wait()
                if not self.isRun.is_set():
                    self.startEvent.clear()
                    break

                # call inspect
                data = self.input.get()
                command = data[-1]
                ImageBOTTOP = None
                ImageTOPOVL = None # store the flange and knockout ovl
                ImageBOTOVL = None # stor code number ovl
                if command == TCP_COMMAND.INSPECT or command == TCP_COMMAND.VALIDATION_INSPECT\
                    or command == TCP_COMMAND.CALIBRATION_INSPECT:
                    if(len(data) == 4):
                        ImageBOT, ImageTOP, dataStr, command  = data # for offline
                    else:
                        ImageBOTTOP, ImageBOT, ImageTOP, dataStr, command  = data # for online
                        # Top image get the image have flange and knockout defect 
                        if self.topInspectData.image is not None and self.id == 1:
                            ImageTOP = self.topInspectData.image
                            ImageTOPOVL = self.topInspectData.imageOVL

                        # BottomBot image get the image have defect code
                        if self.numberReaderData.image is not None and self.id == 0: # bot camera
                            ImageBOT = self.numberReaderData.image
                            ImageBOTOVL = self.numberReaderData.imageOVL
                        
                    ImageMID = None

                elif command == TCP_COMMAND.NON_ROUND_SHAPE_INSPECT or \
                        command == TCP_COMMAND.NON_ROUND_SHAPE_INSPECT_START:
                    ImageBOT, dataStr, command  = data
                elif command == TCP_COMMAND.TOP_INSPECT or \
                        command == TCP_COMMAND.TOP_INSPECT_START or \
                        command == TCP_COMMAND.CORRECTION_FIRST_INSPECT or \
                        command == TCP_COMMAND.CORRECTION_INSPECT:
                    ImageTOP, dataStr, command  = data



                defectInfo = []
                overlayInfos = []
                defectCodes = []

                if(command == TCP_COMMAND.INSPECT or command == TCP_COMMAND.VALIDATION_INSPECT):
                    if self.id == 1:
                        imageOVL, defectInfo, overlayInfos, defectCodes, moldResult = InspectTop(ImageTOP, ImageMID, ImageBOT, ImageTopMask, self.topInspectData, ImageTOPOVL)
                    elif self.id == 0:
                        imageOVL, defectInfo, overlayInfos, defectCodes, moldResult = InspectBot(ImageTOP, ImageMID, ImageBOT, ImageBOTTOP, dataStr, self.nonRoundShapeData, self.numberReaderData, mlCore, ImageBOTOVL)
                
                elif command == TCP_COMMAND.CALIBRATION_INSPECT:
                    if self.id == 1:
                        imageOVL, defectInfo, overlayInfos, defectCodes, moldResult = CalibrationTop(ImageTOP, ImageMID, ImageBOT, ImageTopMask)
                    elif self.id == 0:
                        imageOVL, defectInfo, overlayInfos, defectCodes, moldResult = CalibrationBot(ImageTOP, ImageMID, ImageBOT, ImageBOTTOP)

                elif command == TCP_COMMAND.NON_ROUND_SHAPE_INSPECT or\
                        command == TCP_COMMAND.NON_ROUND_SHAPE_INSPECT_START:
                    if command == TCP_COMMAND.NON_ROUND_SHAPE_INSPECT_START:
                        for i in range(NonRoundShapeInspectParam.instance.maxNumberDimension):
                            self.nonRoundShapeData[i].Reset()
                        self.numberReaderData.Reset()
                    # call glass container shape inspect
                    moldResult = ""
                    imageOVL, defectInfo, overlayInfos, defectCodes, self.nonRoundShapeData, self.numberReaderData = \
                        InspectNonRoundShape(ImageBOT, self.nonRoundShapeData, self.numberReaderData, mlCore)
                    pass
                elif command == TCP_COMMAND.TOP_INSPECT or\
                        command == TCP_COMMAND.TOP_INSPECT_START:
                    if command == TCP_COMMAND.TOP_INSPECT_START:
                        self.topInspectData.Reset()
                    # call top inspect for flange, knockout
                    moldResult = ""
                    imageOVL, defectInfo, overlayInfos, defectCodes, self.topInspectData = \
                        InspectTopRotate(ImageTOP, ImageTopMask, self.topInspectData)
                    pass
                elif command == TCP_COMMAND.CORRECTION_INSPECT or\
                        command == TCP_COMMAND.CORRECTION_FIRST_INSPECT:
                    if command == TCP_COMMAND.CORRECTION_FIRST_INSPECT:
                        self.correctionInspectData.Reset()
                    # call correction inspect
                    moldResult = ""
                    imageOVL, defectInfo, overlayInfos, defectCodes, self.correctionInspectData = \
                        InspectCorrection(ImageTOP, ImageTopMask, dataStr, self.correctionInspectData)
                    

                self.resultManager["IMAGE_OVL"] = imageOVL
                self.resultManager["DEFECT_INFO"] = defectInfo
                self.resultManager["OVERLAY_INFO"] = overlayInfos
                self.resultManager["DEFECT_CODE"] = defectCodes
                self.resultManager["MOLD_RESULT"] = moldResult

                self.isFinishInspectEvent.set()
                # clear event
                self.startEvent.clear()
                # time.sleep(0.01)

        except:
            self.Kill()
            DebugLog("InspectThread", f"Crash thread {self.id}")

        DebugLog("InspectThread", f"End thread {self.id}")
        
    def Inspect(self, input):
        if not self.isRun.is_set():
            DebugLog("InspectThread", f"Thread already killed")
            return
        self.isFinishInspectEvent.clear()
        self.input.put(input)
        self.startEvent.set()
        
    def Kill(self):
        self.isRun.clear()
        self.startEvent.set()
        
