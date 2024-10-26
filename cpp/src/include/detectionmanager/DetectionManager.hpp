#ifndef DETECTIONMANAGER_HPP
#define DETECTIONMANAGER_HPP

#include "opencv2/opencv.hpp"
#include "apriltag/apriltag.h"
#include "apriltag/tag36h11.h"
#include "apriltag/apriltag_math.h"
#include "apriltag/apriltag_pose.h"


class DetectionManager{

    private:
        apriltag_detector_t* detector;// = apriltag_detector_create();
        apriltag_family_t* family;// = tag36h11_create();
        
    public:

        apriltag_detection_info_t info = {
            .det = nullptr,
            .tagsize = 0.13, //meters, 6.5 inches total outside 8 squares. 4.875 inches
            .fx = 0,
            .fy = 0,
            .cx = 0,
            .cy = 0
        };

        DetectionManager();
        DetectionManager(apriltag_detector_t* det, apriltag_family_t* fam);

        apriltag_detector_t* getDetector();
        apriltag_family_t* getFamily();

        void setIntrinsics(double fx, double fy, double cx, double cy);

        image_u8_t matToImage(cv::Mat mat);

        void process(zarray_t* detections);

        zarray_t* getDetections(cv::Mat frame);

        void clean();

};

#endif