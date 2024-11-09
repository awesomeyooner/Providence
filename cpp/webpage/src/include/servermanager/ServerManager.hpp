#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#define CROW_MAIN
#define CROW_STATIC_DIRECTORY "public/"
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <fstream>
#include <string>
#include <iostream>
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
#include "mrcal/mrcal.h"
#include "../cameramanager/CameraManager.hpp"
#include "../detectionmanager/DetectionManager.hpp"
#include "../util/Utility.hpp"
#include "../systemmanager/SystemManager.hpp"

class ServerManager{

    public:

        void initialize();

        void loop();

    private:


};

#endif