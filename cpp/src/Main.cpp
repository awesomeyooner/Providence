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

    detector.setIntrinsics(
        730.0688629, 
        730.2649748, 
        674.9147146, 
        545.0855588
    );

    double coeffs[8] = {0.03080258043, -0.06523055331, 0.0003025805212, -4.177400726e-05, 0.06055868742, -0.01789081457, 0.01539022107, 0.03832702575};

    detector.setDistortionCoefficients(
        coeffs
    );

    if(!camera.isOpened())
        return -1;

    while(true){

        camera.updateFramerate();

        if(camera.getFramerate() > 30)
            continue;

        cv::Mat frame = camera.getFrame();

        cv::putText(frame, std::to_string(camera.getFramerate()), cv::Point(0, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2, cv::LINE_AA);

        //code goes here
        detector.process(&frame);

        if(!camera.show(frame))
            break;

        //std::cout << camera.getFramerate() << std::endl;

        if(cv::waitKey(10) == 27)
            break;
    }

    camera.release();

    return 0;
}