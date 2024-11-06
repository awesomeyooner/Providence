#ifndef CAMERAMANAGER_HPP
#define CAMERAMANAGER_HPP

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>
#include <fstream>
#include <vector>
#include "opencv2/opencv.hpp"

class CameraManager{

    public:
        cv::VideoCapture cap;

        CameraManager(int index);
        CameraManager(int index, cv::VideoCaptureAPIs type);

        void config();

        bool isOpened();

        bool setProperty(cv::VideoCaptureProperties property, double value, bool print);
        double getProperty(cv::VideoCaptureProperties property, bool print);

        cv::Mat getFrame();
        cv::Mat getFrameGray();
        bool show();
        bool show(cv::Mat frame);

        double getFramerate();
        void updateFramerate();

        void release();
        void reopen();

    private:
        int index;

        double framerate = 0;
        std::chrono::_V2::system_clock::time_point previousTimestamp = std::chrono::high_resolution_clock::now();
};

#endif