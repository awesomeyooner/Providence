#include "opencv2/opencv.hpp"
//#include "libs/crow.h"
#include <iostream>
#include <ctime>

int main(int argc, char** argv){
    cv::VideoCapture cap(4, cv::CAP_V4L2);

    auto previous = std::chrono::high_resolution_clock::now();
    double framerate = 0;

    if(!cap.isOpened())
        return -1;

    cap.set(cv::CAP_PROP_FPS, 120.0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH,1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT,720);
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));

    std::cout << cap.get(cv::CAP_PROP_FPS) << std::endl;
    std::cout << "==================" << std::endl;

    while(true){

        auto now = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - previous).count();

        framerate = 1 / (delta / 1000000.0);

        if(framerate > 60)
            continue;

        previous = std::chrono::high_resolution_clock::now();

        cv::Mat frame;

        cap >> frame;

        if(frame.empty())
            break;

        cv::imshow("frame", frame);

        std::cout << framerate << std::endl;

        if(cv::waitKey(10) == 27)
            break;
    }

    cap.release();

    return 0;
}