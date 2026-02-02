from enum import Enum


class TRACK_ID(Enum):
    ALL = -1
    BOTTOM = 0
    TOP = 1


class TCP_COMMAND(Enum):
    NONE = 0
    DISCONNECT = 1
    TEACH = 2
    TEACH_DONE = 3
    INSPECT = 4
    INSPECT_DONE = 5
    CHANGE_RECIPE = 6
    CHANGE_RECIPE_DONE = 7
    NON_ROUND_SHAPE_INSPECT_START = 8 # FIRST inspect
    NON_ROUND_SHAPE_INSPECT = 9 
    NON_ROUND_SHAPE_INSPECT_DONE = 10

    TOP_INSPECT_START = 11 # FIRST inspect
    TOP_INSPECT = 12 
    TOP_INSPECT_DONE = 13

    VALIDATION_INSPECT = 14
    VALIDATION_INSPECT_DONE = 15

    CALIBRATION_INSPECT = 16
    CALIBRATION_INSPECT_DONE = 17

    CORRECTION_FIRST_INSPECT = 18
    CORRECTION_INSPECT = 19
    CORRECTION_INSPECT_DONE = 20

    TOTAL_COMMAND = 21

class DEFECT_NAME(Enum):
    PROCESS_ERROR = -1
    PASS = 0
    HEIGHT = 1
    WEIGHT = 2
    NON_ROUND_SHAPE = 3
    BODYR_DIMENSION = 4
    LEAN = 5
    TILT = 6
    F_DIMENSION = 7
    A_DIMENSION = 8
    T_DIMENSION = 9
    E_DIMENSION = 10
    D_DIMENSION = 11
    B_DIMENSION = 12
    S_DIMENSION = 13
    H_DIMENSION = 14
    LUGT_DIMENSION = 15
    LUGT1_DIMENSION = 16
    D_ANGLE_DIMENSION = 17
    FLANGE_DIMENSION = 18
    KNOCKOUT_DIMENSION = 19
    PUSHUP_DIMENSION = 20
    INSIDE_NECK = 21
    WALL_THICKNESS = 22
    CODE_NUMBER = 23

class MOLD_RESULT(Enum):
    PASS = 1
    WARNING = 2
    ALARM = 3   

class PackageInfo():
    def __init__(self) -> None:
        self.command = TCP_COMMAND.NONE
        self.images = [] # bottom1, bottom2, mid, top
        self.isStepDebug = False
        self.numberImage = 0
        self.dataStr = "" # for change recipe

class InspectOutputInfo():
    def __init__(self) -> None:
        self.command = TCP_COMMAND.NONE
        self.imageOVLs = []
        self.dataStr = "" # defect info and defect code

class InspectNonRoundShapeData():
    # This data for non round shape in bottom camera
    def __init__(self) -> None:
        self.Reset()

    def Reset(self):
        self.images = [] #
        self.imageOVLs = []
        self.shortSize = 0
        self.longSize = 0
        self.diagonalSize = 0

class NumberReaderData():
    # This data for non round shape in bottom camera
    def __init__(self) -> None:
        self.Reset()

    def Reset(self):
        self.image = None #
        self.imageOVL = None
        self.codeNumber = 0
        # self.codeIndex = 

class KnockoutInspectData():
    # This data for flange, knockout
    def __init__(self) -> None:
        self.Reset()

    def Reset(self):
        self.minKnockout = 0
        self.maxKnockout = 0
        self.knockoutConsecutiveImageNumber = 0
        self.maxKnockoutConsecutiveImageNumber = 0

class SDimensionInspectData():
    # This data for S dimension
    def __init__(self) -> None:
        self.Reset()

    def Reset(self):
        self.dimension = 0
        
class TopInspectData():
    # This data for flange, knockout
    def __init__(self) -> None:
        self.knockoutData = KnockoutInspectData()
        self.flangeData = KnockoutInspectData()
        self.sDimensionData = SDimensionInspectData()
        self.Reset()

    def Reset(self):
        self.image = None #
        self.imageOVL = None
        self.knockoutData.Reset()
        self.flangeData.Reset()
        self.sDimensionData.Reset()

class CorrectinInspectData():
    # This data for correction inspect
    def __init__(self) -> None:
        self.Reset()

    def Reset(self):
        self.image = None #
        self.locationRegion = None
        self.locationRect = None
        self.imageOVL = None

NumberCodeLUT = {
    '1111110010011': 1, '1110010101111': 31, '1100111001111': 61, 
    '1111101010011': 2, '1101101001111': 32, '1101001110111': 62, 
    '1111101001011': 3, '1110011100111': 33, '1110100110111': 63, 
    '1111100110011': 4, '1110110100111': 34, '1101101010111': 64, 
    '1111100101011': 5, '1110110011011': 35, '1101011100111': 65, 
    '1111100100111': 6, '1110110010111': 36, '1100111110011': 66, 
    '1111011010011': 7, '1110101110011': 37, '1101111010011': 67, 
    '1111011001011': 8, '1110101101011': 38, '1101111001011': 68, 
    '1111010110011': 9, '1101110011011': 39, '1100111011011': 69, 
    '1100100111111': 10, '1100110011111': 40, '1100101101111': 70, 
    '1111001001111': 11, '1101100101111': 41, '1101011001111': 71, 
    '1111010101011': 12, '1110101001111': 42, '1100110110111': 72, 
    '1111010100111': 13, '1110010110111': 43, '1100111010111': 73, 
    '1111010011011': 14, '1101101011011': 44, '1101110010111': 74, 
    '1111010010111': 15, '1110101100111': 45, '1101101100111': 75, 
    '1111001110011': 16, '1110101011011': 46, '1100101111011': 76, 
    '1111001101011': 17, '1110100111011': 47, '1101011011011': 77, 
    '1111001100111': 18, '1110011110011': 48, '1101110110011': 78, 
    '1101110101011': 19, '1101100111011': 49, '1101011110011': 79, 
    '1100101011111': 20, '1101010011111': 50, '1101001101111': 80, 
    '1101010101111': 21, '1110100101111': 51, '1110011001111': 81, 
    '1110101010111': 22, '1100101110111': 52, '1101010110111': 82, 
    '1111001011011': 23, '1101100110111': 53, '1101011010111': 83, 
    '1111001010111': 24, '1110011010111': 54, '1100111100111': 84, 
    '1110111010011': 25, '1101011101011': 55, '1101110100111': 85, 
    '1110111001011': 26, '1110011101011': 56, '1101001111011': 86, 
    '1110110110011': 27, '1110011011011': 57, '1100110111011': 87, 
    '1110110101011': 28, '1110010111011': 58, '1101101101011': 88, 
    '1101010111011': 29, '1101101110011': 59, '1100111101011': 89, 
    '1101001011111': 30, '1110010011111': 60, '1100110101111': 99}