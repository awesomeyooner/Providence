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

        bool isOpened();

        bool setProperty(cv::VideoCaptureProperties property, double value, bool print);

        void release();

    private:
        

};

#endif