from util import DetectionManager
import cv2
from util import Utility
from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

detector = DetectionManager()

cap = cv2.VideoCapture(2)

while(True):
    ret, frame = cap.read()

    if(ret):
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        tags = detector.getTags(gray)

        

        for tag in tags:
            Utility.draw_box(frame, tag.corners)
            print(tag.pose_R)


        cv2.imshow("frame", frame)


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
    
cap.release()
cv2.destroyAllWindows()