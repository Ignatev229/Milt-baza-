import config
from config import DebugLog
from struct_define import *
from Communication.tcp_server import TCPServer
from inspect_thread import InspectThread
from Inspection.inspection_core import Teach, ReadRecipe, WarmingUp, UpdateCalibCameraPositionToFile
# from Inspection.vision_param import TeachData
import time
import cv2
import os

class ManageThread():
    def __init__(self, tcpServer: TCPServer) -> None:
        super(ManageThread, self).__init__()
        self.inspThread = []
        self.tcpServer = tcpServer
        for i in range(config.NUMBER_PROCESS):
            p =  InspectThread(i)
            p.start()
            self.inspThread.append(p)
        WarmingUp()
        WarmingUp()
        pass

    def Inspect(self, input: PackageInfo):
        # Process general
        t1 = time.time()
        
        data = input.images
        data.append(input.dataStr)
        data.append(input.command)
        for i in range(config.NUMBER_PROCESS):
            self.inspThread[i].Inspect(data)

        # wait for all thread complete and send to client
        for i in range(config.NUMBER_PROCESS):
            self.inspThread[i].isFinishInspectEvent.wait()

        defectInfos = []
        overlayInfos = []
        defectCodes = []
        imageOVLs = []
        moldResults = []
        for i in range(config.NUMBER_PROCESS):
            defectInfos += self.inspThread[i].resultManager["DEFECT_INFO"]
            overlayInfos += self.inspThread[i].resultManager["OVERLAY_INFO"]
            defectCodes += list(self.inspThread[i].resultManager["DEFECT_CODE"])
            imageOVLs.append(self.inspThread[i].resultManager["IMAGE_OVL"])
            moldResults.append(self.inspThread[i].resultManager["MOLD_RESULT"])

        moldResult = max(moldResults)
        moldResult = MOLD_RESULT.PASS.value

        defectInfos = "$".join(defectInfos)
        # overlayInfos = "$".join(overlayInfos) 
        defectCodes = "$".join(defectCodes) 


        # dataStr = f"{defectCodes}&{defectInfos}&{overlayInfos}"
        dataStr = f"{defectCodes}&{defectInfos}&{moldResult}"


        inspectOutputInfo = InspectOutputInfo()
        if(input.command == TCP_COMMAND.INSPECT):
            inspectOutputInfo.command = TCP_COMMAND.INSPECT_DONE
        elif(input.command == TCP_COMMAND.VALIDATION_INSPECT):
            inspectOutputInfo.command = TCP_COMMAND.VALIDATION_INSPECT_DONE
        elif(input.command == TCP_COMMAND.CALIBRATION_INSPECT):
            inspectOutputInfo.command = TCP_COMMAND.CALIBRATION_INSPECT_DONE
            # if success 2 camera write to temp file
            # if defectCodes == '':
            #     # pass
            #     UpdateCalibCameraPositionToFile()
                


        inspectOutputInfo.dataStr = dataStr
        inspectOutputInfo.imageOVLs = imageOVLs

        self.tcpServer.Send(inspectOutputInfo)
        print("---Total inspection time: ", time.time() - t1)

    def GlassContainerShapeInspect(self, input: PackageInfo):
        # only inspect bottom image
        t1 = time.time()
        
        data = input.images
        data.append(input.dataStr)
        data.append(input.command)
        self.inspThread[TRACK_ID.BOTTOM.value].Inspect(data)

        # wait for all thread complete and send to client
        self.inspThread[TRACK_ID.BOTTOM.value].isFinishInspectEvent.wait()

        defectInfos = []
        overlayInfos = []
        defectCodes = []
        imageOVLs = []

        defectInfos += self.inspThread[TRACK_ID.BOTTOM.value].resultManager["DEFECT_INFO"]
        overlayInfos += self.inspThread[TRACK_ID.BOTTOM.value].resultManager["OVERLAY_INFO"]
        defectCodes += list(self.inspThread[TRACK_ID.BOTTOM.value].resultManager["DEFECT_CODE"])
        imageOVLs.append(self.inspThread[TRACK_ID.BOTTOM.value].resultManager["IMAGE_OVL"])

        defectInfos = "$".join(defectInfos)
        defectCodes = "$".join(defectCodes) 

        dataStr = f"{defectCodes}&{defectInfos}"

        inspectOutputInfo = InspectOutputInfo()
        inspectOutputInfo.command = TCP_COMMAND.NON_ROUND_SHAPE_INSPECT_DONE
        inspectOutputInfo.dataStr = dataStr
        inspectOutputInfo.imageOVLs = imageOVLs

        self.tcpServer.Send(inspectOutputInfo)
        print("---Glass container shape inspection time: ", time.time() - t1)

    def TopInspect(self, input: PackageInfo):
        # only inspect top image
        t1 = time.time()
        
        data = input.images # 1 image
        data.append(input.dataStr)
        data.append(input.command)
        self.inspThread[TRACK_ID.TOP.value].Inspect(data)

        # wait for all thread complete and send to client
        self.inspThread[TRACK_ID.TOP.value].isFinishInspectEvent.wait()

        defectInfos = []
        overlayInfos = []
        defectCodes = []
        imageOVLs = []

        defectInfos += self.inspThread[TRACK_ID.TOP.value].resultManager["DEFECT_INFO"]
        overlayInfos += self.inspThread[TRACK_ID.TOP.value].resultManager["OVERLAY_INFO"]
        defectCodes += list(self.inspThread[TRACK_ID.TOP.value].resultManager["DEFECT_CODE"])
        imageOVLs.append(self.inspThread[TRACK_ID.TOP.value].resultManager["IMAGE_OVL"])

        defectInfos = "$".join(defectInfos)
        defectCodes = "$".join(defectCodes) 

        dataStr = f"{defectCodes}&{defectInfos}"

        inspectOutputInfo = InspectOutputInfo()
        if input.command == TCP_COMMAND.TOP_INSPECT:
            inspectOutputInfo.command = TCP_COMMAND.TOP_INSPECT_DONE
        else:
            inspectOutputInfo.command = TCP_COMMAND.CORRECTION_INSPECT_DONE

        inspectOutputInfo.dataStr = dataStr
        inspectOutputInfo.imageOVLs = imageOVLs

        self.tcpServer.Send(inspectOutputInfo)
        print("---Top inspection time: ", time.time() - t1)

    def Teach(self, input: PackageInfo):
        isTeachSuccess, defectInfos, overlayInfos = Teach(input.imageTOP)
        # print(isTeachSuccess, defectInfos, overlayInfos)
        defectInfos = "$".join(defectInfos)
        overlayInfos = "$".join(overlayInfos) 
        dataStr = f"{isTeachSuccess}&{defectInfos}&{overlayInfos}"
        
        inspectOutputInfo = InspectOutputInfo()
        inspectOutputInfo.command = TCP_COMMAND.TEACH_DONE
        inspectOutputInfo.dataStr = dataStr
        self.tcpServer.Send(inspectOutputInfo)

    def LoadRecipe(self, recipePath):
        # for i in range(config.NUMBER_PROCESS):
        #     self.inspThread[i].LoadRecipe(recipePath)
        inspectOutputInfo = InspectOutputInfo()
        inspectOutputInfo.command = TCP_COMMAND.CHANGE_RECIPE_DONE
        if ReadRecipe(recipePath):
            inspectOutputInfo.dataStr = "True"
        else:
            inspectOutputInfo.dataStr = "False"
        self.tcpServer.Send(inspectOutputInfo)


    def Kill(self):
        for i in range(config.NUMBER_PROCESS):
            self.inspThread[i].Kill()

