import config
from config import DebugLog
from struct_define import *
import threading
import sys, os
import time
from manage_thread import ManageThread
from Communication.tcp_server import TCPServer
# from Inspection.inspection_core import ReadRecipe, WarmingUp, Inspection


def main():
    packageInfo = PackageInfo()
    inspectEvent = threading.Event()
    tcpServer = TCPServer("127.0.0.2", config.PORT, inspectEvent, packageInfo)

    manageThread = ManageThread(tcpServer)


    # Process Inspection
    while tcpServer.inCommingConnectThread.is_alive() and tcpServer.isRun:
        inspectEvent.wait()

        

        if packageInfo.command == TCP_COMMAND.DISCONNECT:
            break
        elif packageInfo.command == TCP_COMMAND.TEACH:
            DebugLog("Main", f"{packageInfo.command}")
        
            manageThread.Teach(packageInfo)
        elif packageInfo.command == TCP_COMMAND.INSPECT or \
            packageInfo.command == TCP_COMMAND.VALIDATION_INSPECT or\
            packageInfo.command == TCP_COMMAND.CALIBRATION_INSPECT:
            DebugLog("Main", f"{packageInfo.command}")
            manageThread.Inspect(packageInfo)
        
        elif packageInfo.command == TCP_COMMAND.NON_ROUND_SHAPE_INSPECT or \
                    packageInfo.command == TCP_COMMAND.NON_ROUND_SHAPE_INSPECT_START:
            DebugLog("Main", f"{packageInfo.command}")
            manageThread.GlassContainerShapeInspect(packageInfo)
        
        elif packageInfo.command == TCP_COMMAND.TOP_INSPECT or \
                packageInfo.command == TCP_COMMAND.TOP_INSPECT_START or \
                packageInfo.command == TCP_COMMAND.CORRECTION_FIRST_INSPECT or \
                packageInfo.command == TCP_COMMAND.CORRECTION_INSPECT:
            DebugLog("Main", f"{packageInfo.command}")
            manageThread.TopInspect(packageInfo)

        elif packageInfo.command == TCP_COMMAND.CHANGE_RECIPE:
            DebugLog("Main", f"Change Recipe Path: {packageInfo.dataStr}")
            if os.path.exists(packageInfo.dataStr):
                manageThread.LoadRecipe(packageInfo.dataStr)
            else:
                inspectOutputInfo = InspectOutputInfo()
                inspectOutputInfo.command = TCP_COMMAND.CHANGE_RECIPE_DONE
                inspectOutputInfo.dataStr = "False"
                tcpServer.Send(inspectOutputInfo)

        inspectEvent.clear()

if __name__ == "__main__":
    main()