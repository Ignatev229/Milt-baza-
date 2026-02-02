try:
    from ultralytics import YOLO
    import torch
except:
    pass
import cv2
import numpy as np
from struct_define import NumberCodeLUT
import config


class NumberReaderDecode:
    def __init__(self, model_path, device="cpu"):
        #LOAD MODEL
        if torch.cuda.is_available():
            self.device = 0
        else:
            self.device = "cpu"
        print("DEVICE: ", self.device)
        self.model = YOLO(model_path)
        
        # Get all class names
        self.class_names = []
        for class_id, class_name in self.model.names.items():
            class_name = class_name.replace("{", "").replace("}", "").replace("'", "").split(": ")[-1]
            self.class_names.append(class_name)
        # red, blue, 
        self.class_colors = [(255, 0, 0), (0, 0, 255), (85, 1151, 223), (82, 23, 68), (0, 235, 255), (77, 64, 22), (200, 182, 239)]

        print("Prediction class: {}".format(self.class_names))
        print("Finish load model")

    def inference(self, image, conf=0.3):
        print("Start inference")
        results = self.model.predict(source=image, iou = 0.1, device = self.device, conf = conf)
        bboxes = results[0].boxes.xyxy.detach().cpu().numpy()
        pred_classes = results[0].boxes.cls.detach().cpu().numpy()
        pred_scores = results[0].boxes.conf.detach().cpu().numpy()
        print("Return result: {} {}".format(pred_classes, pred_scores))
        return pred_classes, pred_scores, bboxes
    
    def visual_image(self, image, anchor_left, anchor_top, pred_classes, pred_scores, bboxes, font_size, font_thickness):
        for k in range(len(pred_classes)):
            class_id  = int(pred_classes[k])
            confidence = pred_scores[k]
            color = self.class_colors[class_id]
            x1, y1, x2, y2 = map(int, bboxes[k])  # Convert to integers
            x1 += anchor_left
            x2 += anchor_left
            y1 += anchor_top
            y2 += anchor_top
            # Draw bounding box
            cv2.rectangle(image, (x1, y1), (x2, y2), color, font_thickness)  # Green box
        
            # Add label and confidence
            label = f"{self.class_names[class_id]}: {confidence:.2f}"
            cv2.putText(image, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, font_size, color, font_thickness)
        return image
    
    def NumberReaderDecode(self, Image, ImageOVL, ROI, Conf, Color):
        CodeNumber = 0
        IsPass = False

        PlacesNumber = 13
        DotNumber = 9
        codeIndex = [0]*PlacesNumber

        BLEFT, BTOP, BRIGHT, BBOTTOM = ROI
        crop_img = Image[BTOP:BBOTTOM, BLEFT:BRIGHT]
        equalized_img = cv2.equalizeHist(crop_img)
        equalized_rgb_img = cv2.cvtColor(equalized_img, cv2.COLOR_GRAY2BGR)
        pred_classes, pred_scores, bboxes = self.inference(equalized_rgb_img, Conf)
        
        # remove box outside the code line
        median_left = np.median(bboxes[:, 0]) - 15
        median_right = np.median(bboxes[:, 2]) + 15
        cx = (bboxes[:, 0] + bboxes[:, 2])/2
        index = np.where((cx > median_left) & (cx < median_right))
        bboxes = bboxes[index]
        pred_scores = pred_scores[index]
        pred_classes = pred_classes[index]
        if len(pred_classes) == DotNumber:
            left = int(np.amin(bboxes[:, 0]))
            top = int(np.amin(bboxes[:, 1]))
            right = int(np.amax(bboxes[:, 2]))
            bottom = int(np.amax(bboxes[:, 3]))
            dot_height = (bottom - top)/PlacesNumber

            for k in range(len(bboxes)):
                cx = (bboxes[k][0] + bboxes[k][2])/2
                cy = (bboxes[k][1] + bboxes[k][3])/2
                idx = ((cy-top)/dot_height)
                ratio = idx*10-int(idx)*10
                if ratio >= 9.2 or ratio <= 0.8:
                    # untrustworthy
                    break

                idx = int(idx)
                codeIndex[idx] = 1
                y1 = int(top + idx*dot_height)
                y2 = int(top + (idx+1)*dot_height)
                cv2.rectangle(ImageOVL, (left + BLEFT, y1 + BTOP), (right + BLEFT, y2 + BTOP), Color, config.OVLSIZE)  # blue box

            for k in range(PlacesNumber):
                if codeIndex[k] == 0:
                    y1 = int(top + k*dot_height)
                    y2 = int(top + (k+1)*dot_height)
                    cv2.rectangle(ImageOVL, (left + BLEFT, y1 + BTOP), (right + BLEFT, y2 + BTOP), (0, 0, 255), config.OVLSIZE)  # yellow box
            key = "".join(str(i) for i in codeIndex)
            if key in NumberCodeLUT:
                CodeNumber = NumberCodeLUT[key]
                IsPass = True

        cv2.rectangle(ImageOVL, (BLEFT, BTOP), (BRIGHT, BBOTTOM), Color, config.OVLSIZE)  # blue box

        # ImageOVL = self.visual_image(ImageOVL, BLEFT, BTOP, pred_classes, pred_scores, bboxes, 1.2, 2)
        # equalized_rgb_img = self.visual_image(equalized_rgb_img, 0, 0, pred_classes, pred_scores, bboxes, 1.2, 2)
        return IsPass, ImageOVL, CodeNumber
    
