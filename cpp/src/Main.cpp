#include "opencv2/opencv.hpp"
//#include "libs/crow.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>
#include <fstream>
#include "include/systemmanager/SystemManager.hpp"
#include "include/cameramanager/CameraManager.hpp"
#include "include/detectionmanager/DetectionManager.hpp"
#include "apriltag/apriltag.h"
#include "apriltag/tag36h11.h"
#include "apriltag/apriltag_math.h"
#include "apriltag/apriltag_pose.h"

int main(int argc, char** argv){
    CameraManager camera(4, cv::CAP_V4L2);
    DetectionManager detector;

    // detector.setIntrinsics(
    //     730.0688629, 
    //     730.2649748, 
    //     674.9147146, 
    //     545.0855588
    // );

    if(!camera.isOpened())
        return -1;

    while(true){

        camera.updateFramerate();

        if(camera.getFramerate() > 30)
            continue;

        cv::Mat mat = camera.getFrame();

        image_u8_t image = detector.matToImage(mat);

        // image_u8_t image = {
        //         .width = mat.cols,
        //         .height = mat.rows,
        //         .stride = mat.cols,
        //         .buf = mat.data
        //     };
        //code goes here
        // zarray_t* detections = apriltag_detector_detect(detector.getDetector(), &image);
        zarray_t* detections = apriltag_detector_detect(detector.getDetector(), &image);
        //detector.matToImage(camera.getFrame());
        //detector.getDetections(camera.getFrame());
        //apriltag_detections_destroy(detections);
        //detector.process(detections);
    
        if(!camera.show())
            break;

        std::cout << camera.getFramerate() << std::endl;

        if(cv::waitKey(10) == 27)
            break;
    }

    camera.release();

    return 0;
}