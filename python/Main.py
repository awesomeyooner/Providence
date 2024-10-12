from src.util.DetectionManager import DetectionManager
import cv2
import src.util.Utility
from src.util import Utility
from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt
import time

detector = DetectionManager()

cap = cv2.VideoCapture(0)

previous = time.time()

while(True):
    ret, frame = cap.read()

    if(ret):

        framerate = 1 / (time.time() - previous)

        if(framerate > 5):
            continue

        print(framerate)

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        tags = detector.getTags(gray)

        

        for tag in tags:
            Utility.draw_box(frame, tag.corners)
            print(tag.pose_R)


        cv2.imshow("frame", frame)

        previous = time.time()


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
    
cap.release()
cv2.destroyAllWindows()