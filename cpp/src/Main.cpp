#include "opencv2/opencv.hpp"
//#include "libs/crow.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>
#include <fstream>
#include "systemmanager/SystemManager.hpp"
#include "cameramanager/CameraManager.hpp"

void setProperty(cv::VideoCapture* capture, cv::VideoCaptureProperties property, double value){
    capture->set(property, value);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << capture->get(property) << std::endl;
}

int main(int argc, char** argv){
    CameraManager camera(2, cv::CAP_V4L2);
    // cv::VideoCapture cap(2, cv::CAP_V4L2);

    auto previous = std::chrono::high_resolution_clock::now();
    double framerate = 0;

    if(!camera.isOpened())
        return -1;

    // camera.setProperty(cv::CAP_PROP_FRAME_WIDTH, 1280, true);
    setProperty(&cap, cv::CAP_PROP_FRAME_WIDTH, 1280);
    setProperty(&cap, cv::CAP_PROP_FRAME_HEIGHT, 720);
    setProperty(&cap, cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));
    setProperty(&cap, cv::CAP_PROP_FPS, 30);
    // cap.set(cv::CAP_PROP_FRAME_WIDTH,1280);
    // cap.set(cv::CAP_PROP_FRAME_HEIGHT,720);
    // cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));
    // cap.set(cv::CAP_PROP_FPS, 30);

    // std::cout << cap.get(cv::CAP_PROP_FPS) << std::endl;
    // std::cout << (char)cap.get(cv::CAP_PROP_FOURCC) << std::endl;
    // std::cout << cap.get(cv::CAP_PROP_EXPOSURE) << std::endl;
    std::cout << "==================" << std::endl;

    while(true){

        auto now = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - previous).count();

        framerate = 1 / (delta / 1000000.0);

        if(framerate > 30)
            continue;

        previous = std::chrono::high_resolution_clock::now();

        cv::Mat frame;

        cap >> frame;

        if(frame.empty())
            break;

        cv::imshow("frame", frame);

        //std::cout << framerate << std::endl;

        if(cv::waitKey(10) == 27)
            break;
    }

    cap.release();

    return 0;
}