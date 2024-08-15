from pupil_apriltags import Detector
from Utility import Constants


class DetectionManager:

    def __init__(self):
        self.fx = Constants.FX
        self.fy = Constants.FY
        self.cx = Constants.CX
        self.cy = Constants.CY

        self.tagSize = Constants.TAG_SIZE

        self.detector = Detector(
            families='tag36h11',
            nthreads=4,
            quad_decimate=1.0,
            quad_sigma=0.0,
            refine_edges=1,
            decode_sharpening=0.25,
            debug=0
        )


    def getPose(self, image):
        detection = self.detector.detect(
            img=image,
            estimate_tag_pose=True,
            camera_params=Constants.CAMERA_INFO,
            tag_size=self.tagSize
        )

        return detection