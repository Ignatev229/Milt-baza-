import socket
import threading
import numpy as np
from PIL import Image
from datetime import datetime
from config import DebugLog
from struct_define import *

class TCPServer():
    def __init__(self, IPAddress: str, Port: int, InspectEvent: threading.Event, packageInfo: PackageInfo) -> None:
        self.inspectEvent = InspectEvent
        self.packageInfo = packageInfo
        self.inspectEvent.clear()
        self.isRun = True

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.bind((IPAddress, Port))
        self.socket.listen(1)
        DebugLog("TCPServer", f"Listening on {(IPAddress, Port)}")

        # create thread while for connect
        self.client = None
        self.inCommingConnectThread = threading.Thread(target=self.InCommingConnection)
        self.inCommingConnectThread.daemon = True
        self.inCommingConnectThread.start()

        pass

    
    def InCommingConnection(self):
        self.client, addr = self.socket.accept()
        try:
            DebugLog("TCPServer", f"Connected by {addr}")
            while True:
                contentLength = self.client.recv(4)
                messageLenght = int.from_bytes(contentLength, "little")
                size = messageLenght - 4
                data = contentLength
                while size > 0:
                    receive = self.client.recv(size)
                    size = size - len(receive)
                    data = data + receive
                
                if not self.Decode(data):
                    continue
                if self.packageInfo.command == TCP_COMMAND.DISCONNECT:
                    self.isRun = False
                    self.inspectEvent.set()
                    break
                # elif self.packageInfo.command == TCP_COMMAND.INSPECT or \
                #     self.packageInfo.command == TCP_COMMAND.CHANGE_RECIPE or \
                #         self.packageInfo.command == TCP_COMMAND.TEACH:
                #     self.inspectEvent.set()
                else:
                    self.inspectEvent.set()
                    # self.Send(TCP_COMMAND.INSPECT_DONE, "-1")
        except:
            DebugLog("TCPServer", f"Close connect {addr}")
        self.isRun = False
        self.inspectEvent.set()
        self.client.close()

    def Decode(self, data):
        # buffer length = 4, function index = 4, isStepDebug = 2, 
        # width = 4, height = 4, channel = 2, image byte
        # width = 4, height = 4, channel = 2, image byte
        # width = 4, height = 4, channel = 2, image byte
        # data str

        try:
            headerLength = 14
            length = int.from_bytes(data[0:4], "little")
            self.packageInfo.command = TCP_COMMAND(int.from_bytes(data[4:8], "little"))
            self.packageInfo.isStepDebug = int.from_bytes(data[8:10], "little")
            self.packageInfo.numberImage = int.from_bytes(data[10:14], "little")
            currentIndex = headerLength
            self.packageInfo.images.clear()

            # for inspection
            for i in range(self.packageInfo.numberImage):
                width = int.from_bytes(data[currentIndex:currentIndex+4], "little")
                currentIndex += 4
                height = int.from_bytes(data[currentIndex:currentIndex+4], "little")
                currentIndex += 4
                channel = int.from_bytes(data[currentIndex:currentIndex+2], "little")
                currentIndex += 2
                imageLength = width*height*channel

                image = np.frombuffer(data[currentIndex:currentIndex+imageLength], np.uint8)
                self.packageInfo.images.append(image.reshape(height, width))
                # image = Image.frombytes("L", (width, height), data[currentIndex:currentIndex+imageLength])
                # self.packageInfo.images.append(np.array(image)) 
                currentIndex += imageLength
            # read plc info like weight,...
            # read recipe path when change recipe
            self.packageInfo.dataStr = data[currentIndex:length].decode("utf-8") 
            
            if self.packageInfo.command == TCP_COMMAND.DISCONNECT:
                return True
            print("Receive: ", self.packageInfo.command, datetime.now().time())

        except:
            DebugLog("TCPServer", f"Decode message error")
            return False

        return True
    
    def Send(self, inspectOutputInfo: InspectOutputInfo):
        if self.client is None or not self.isRun:
            return
        # buffer length = 4, function index = 4, 
        # width = 4, height = 4, channel = 2,
        # width = 4, height = 4, channel = 2,
        # width = 4, height = 4, channel = 2,
        # 3 image byte, data str

        imageByte = bytes()
        for i in range(len(inspectOutputInfo.imageOVLs)):
            imageByte += inspectOutputInfo.imageOVLs[i].shape[1].to_bytes(4, 'little')
            imageByte += inspectOutputInfo.imageOVLs[i].shape[0].to_bytes(4, 'little')
            imageByte += inspectOutputInfo.imageOVLs[i].shape[2].to_bytes(2, 'little')
            imageByte += inspectOutputInfo.imageOVLs[i].tobytes()

        dataStrByte = bytes(inspectOutputInfo.dataStr, 'utf-8')
        functionIndex = int(inspectOutputInfo.command.value).to_bytes(4, 'little')

        data_byte = functionIndex + imageByte + dataStrByte
        length = 4 + len(data_byte)
        data_byte = length.to_bytes(4, 'little') + data_byte
        self.client.sendall(data_byte)

        DebugLog("TCPServer", f"Send to client: {inspectOutputInfo.command} {datetime.now().time()}")
