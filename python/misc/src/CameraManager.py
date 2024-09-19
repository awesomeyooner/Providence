import cv2
import os
import time

class CameraManager:

    def __init__(self, index):
        self.camera = cv2.VideoCapture(index)
        self.framerate = 0
        self.framerate_limit = 30
        self.prev_time = 0

    def getFPS(self):
        pass

    def setFramerateLimit(self):
        pass
    

