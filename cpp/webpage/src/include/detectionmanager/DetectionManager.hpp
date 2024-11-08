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

        double distCoeffs[8];

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
        void setDistortionCoefficients(double coeffs[8]);

        image_u8_t matToImage(cv::Mat mat);

        void process(zarray_t* detections);
        void process(cv::Mat* frame);
        void process(cv::Mat* frame, double* x, double* y, double* z);

        void poseToMat(apriltag_pose_t pose, cv::Mat* rvec, cv::Mat* tvec);

        zarray_t* getDetections(cv::Mat frame);

        void annotate(cv::Mat* frame, apriltag_detection_t* detection);
        void putID(cv::Mat* frame, apriltag_detection_t* detection);
        void drawCorners(cv::Mat* frame, apriltag_detection_t* detection);
        void drawBox(cv::Mat* frame, apriltag_pose_t pose);

        void clean();

};

#endif