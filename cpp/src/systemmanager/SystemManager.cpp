#include "SystemManager.hpp"

SystemManager::SystemManager(){}

std::vector<int> SystemManager::getTemps(){
    std::vector<int> temperatures;
    for (int i = 0; i < 10; ++i) { // Check up to 10 thermal zones
        std::string path = "/sys/class/thermal/thermal_zone" + std::to_string(i) + "/temp";
        std::ifstream file(path);
        if (file.is_open()) {
            int temp;
            file >> temp; // Read temperature in millidegrees Celsius
            temperatures.push_back(temp / 1000); // Convert to degrees Celsius
        }
    }
    return temperatures;
}

void SystemManager::printTemps(){
    std::vector<int> temps = getTemps();

    for(int i = 0; i < temps.size(); i++){
        if(temps[i] != 0)
            std::cout << "Thermal Zone " << i << ": " << temps[i] << " °C\n";
    }
}

float SystemManager::getCpuUsage(){

    std::ifstream file("/proc/stat");
    std::string line;
    if (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string cpu;
        unsigned long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
        ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

        unsigned long total = user + nice + system + idle + iowait + irq + softirq + steal;
        unsigned long used = total - idle;

        return (static_cast<float>(used) / total) * 100.0f; // Return CPU usage as a percentage
    }
    return 0.0f; // Return 0.0 if unable to read

}

void SystemManager::printCpuUsage(){
    std::cout << "CPU Usage: " << getCpuUsage() << "%" << std::endl;
}


