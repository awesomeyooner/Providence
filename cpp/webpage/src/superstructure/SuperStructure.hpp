#ifndef SUPERSTRUCTURE_HPP
#define SUPERSTRUCTURE_HPP

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

class SuperStructure{

    public:

        SuperStructure();

        void loop();
};

#endif