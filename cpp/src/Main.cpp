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

int main(int argc, char** argv){
    CameraManager camera(2, cv::CAP_V4L2);
    DetectionManager detect;

    if(!camera.isOpened())
        return -1;

    while(true){

        camera.updateFramerate();

        if(camera.getFramerate() > 30)
            continue;
    
        if(!camera.show())
            break;

        std::cout << camera.getFramerate() << std::endl;

        if(cv::waitKey(10) == 27)
            break;
    }

    camera.release();

    return 0;
}