#include "src/include/cameramanager/CameraManager.hpp"
#include "src/include/detectionmanager/DetectionManager.hpp"
#include "src/include/servermanager/ServerManager.hpp"
#include "src/include/systemmanager/SystemManager.hpp"
#include "src/include/superstructure/SuperStructure.hpp"
#include <thread>
#include <atomic>

std::atomic<bool> running(true);

int main() {
    SuperStructure superstructure;
    ServerManager servermanager(&superstructure);

    std::thread superloop(&SuperStructure::loop, &superstructure);

    servermanager.initialize();
    superloop.join();

    return 0;
}
