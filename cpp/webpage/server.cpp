#include "src/include/cameramanager/CameraManager.hpp"
#include "src/include/detectionmanager/DetectionManager.hpp"
#include "src/include/servermanager/ServerManager.hpp"
#include "src/include/systemmanager/SystemManager.hpp"
#include "src/superstructure/SuperStructure.hpp"
#include <thread>
#include <atomic>

std::atomic<bool> running(true);

int main() {
    CameraManager camera(4, cv::CAP_V4L2);
    DetectionManager detector;
    ServerManager server;

    std::thread superloop()
}
