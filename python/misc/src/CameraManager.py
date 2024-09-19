import cv2
import os
import time
import numpy as np
from Constants import CameraConstants

class CameraManager:

    def __init__(self, index, framerate_limit = 30):
        self.camera = cv2.VideoCapture(index)
        
        self.camera.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
        self.camera.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

        self.framerate = 0
        self.framerate_limit = framerate_limit
        self.prev_time = 0

    def getFPS(self):
        return round(self.framerate, 2)
    
    def getFramerateLimit(self):
        return self.framerate_limit

    def setFramerateLimit(self, newLimit):
        self.framerate_limit = newLimit

    def isWithinFramerateLimit(self):
        fps = 1 / (time.time() - self.prev_time)
        return fps > self.framerate_limit

    def getFrame(self):
        # if(self.isWithinFramerateLimit()):
        #     self.framerate = 1 / (time.time() - self.prev_time)
        #     self.prev_time = time.time()

        #     return self.camera.read()
        # else:
        #     return False, self.camera.read()[1]
        return True, CameraConstants.BLANK
    
    def getCompressedFrame(self):
        ret, image = self.getFrame()
        return ret, self.compressFrame(image)
    
    def compressFrame(self, image):
        buffer = cv2.imencode('.jpg', image)[1]
        frameFile = buffer.tobytes()

        return frameFile
    
    def release(self):
        self.release()


