#include "src/include/cameramanager/CameraManager.hpp"
#include "src/include/detectionmanager/DetectionManager.hpp"
#include "src/include/servermanager/ServerManager.hpp"
#include "src/include/systemmanager/SystemManager.hpp"
#include "src/include/superstructure/SuperStructure.hpp"
#include <thread>
#include <atomic>

std::atomic<bool> running(true);

int main() {
    ServerManager servermanager;

    std::thread superloop(&ServerManager::loop, servermanager);

    servermanager.initialize();
    superloop.join();

    return 0;
}
