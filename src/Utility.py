import cv2

class Constants:
    FX = 1124.788037
    FY = 1124.855575
    CX = 667.3219574
    CY = 344.2211286

    TAG_SIZE = 0.4 # meters

    CAMERA_INFO = (FX, FY, CX, CY)

def null_method(x):
    pass

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