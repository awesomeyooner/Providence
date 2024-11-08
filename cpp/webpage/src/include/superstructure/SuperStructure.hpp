#ifndef SUPERSTRUCTURE_HPP
#define SUPERSTRUCTURE_HPP

#include "opencv2/opencv.hpp"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>
#include <fstream>
#include "apriltag/apriltag.h"
#include "apriltag/tag36h11.h"
#include "apriltag/apriltag_math.h"
#include "apriltag/apriltag_pose.h"
#include "../cameramanager/CameraManager.hpp"
#include "../detectionmanager/DetectionManager.hpp"

class SuperStructure{

    public:

        cv::Mat latestFrame;

        void loop();
};

#endif