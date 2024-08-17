import cv2
import numpy as np
import math

class Constants:
    FX = 1124.788037
    FY = 1124.855575
    CX = 667.3219574
    CY = 344.2211286

    TAG_SIZE = 0.17 # meters

    CAMERA_INFO = (FX, FY, CX, CY)

def null_method(x):
    pass

def euler_to_quaternion(r):
    (yaw, pitch, roll) = (r[0], r[1], r[2])
    qx = np.sin(roll/2) * np.cos(pitch/2) * np.cos(yaw/2) - np.cos(roll/2) * np.sin(pitch/2) * np.sin(yaw/2)
    qy = np.cos(roll/2) * np.sin(pitch/2) * np.cos(yaw/2) + np.sin(roll/2) * np.cos(pitch/2) * np.sin(yaw/2)
    qz = np.cos(roll/2) * np.cos(pitch/2) * np.sin(yaw/2) - np.sin(roll/2) * np.sin(pitch/2) * np.cos(yaw/2)
    qw = np.cos(roll/2) * np.cos(pitch/2) * np.cos(yaw/2) + np.sin(roll/2) * np.sin(pitch/2) * np.sin(yaw/2)
    return [qx, qy, qz, qw]

def quaternion_to_euler(q):
    (x, y, z, w) = (q[0], q[1], q[2], q[3])
    t0 = +2.0 * (w * x + y * z)
    t1 = +1.0 - 2.0 * (x * x + y * y)
    roll = math.atan2(t0, t1)
    t2 = +2.0 * (w * y - z * x)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    pitch = math.asin(t2)
    t3 = +2.0 * (w * z + x * y)
    t4 = +1.0 - 2.0 * (y * y + z * z)
    yaw = math.atan2(t3, t4)
    return [yaw, pitch, roll]

def rot_matrix_to_euler(matrix):
    x = math.atan2(matrix[2][1], matrix[2][2])
    y = math.atan2(
        -matrix[2][0], 
        math.sqrt(
            math.pow(matrix[2][1], 2) 
            +
            math.pow(matrix[2][2], 2)
        )
    )
    z = math.atan2(matrix[1][0], matrix[0][0])

    return (x, y, z)

def put_text(frame, text, x, y):
    cv2.putText(
            img = frame, 
            text = str(text), 
            org = (x, y), 
            fontFace = cv2.FONT_HERSHEY_SIMPLEX, 
            fontScale = 1,
            thickness = 3,
            lineType = cv2.LINE_AA,   
            color = (0, 0, 255)
        )
    
def draw_box(frame, corners):
    firstX = 0
    firstY = 0

    prevX = 0
    prevY = 0

    for corner in corners:
        x = corner[0]
        y = corner[1]

        if(prevX == 0 and prevY == 0):
            prevX = x
            prevY = y

            firstX = x
            firstY = y
            continue
        
    
        draw_line(frame, x, y, prevX, prevY)

        prevX = x
        prevY = y

    draw_line(frame, firstX, firstY, prevX, prevY)

def draw_boxes(frame, tags):
    for tag in tags:
        draw_box(frame, tag.corners)

def draw_line(frame, x1, y1, x2, y2):
    cv2.line(
            frame, 
            (int(x1), int(y1)),
            (int(x2), int(y2)),
            (0, 0, 255), 
            5
        )

class Trackbar:

    def __init__(self, bar_name, frame_name, default, upper):
        self.bar_name = bar_name
        self.frame_name = frame_name
        self.upper = upper
        self.default = default

        cv2.createTrackbar(bar_name, frame_name, default, upper, null_method)

    def get(self):
        return cv2.getTrackbarPos(self.bar_name, self.frame_name)
    
    def get_percent(self):
        return self.get() / self.upper