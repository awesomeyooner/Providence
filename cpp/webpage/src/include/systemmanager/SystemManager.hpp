#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>
#include <fstream>
#include <vector>

class SystemManager{

    public:
        SystemManager();

        static std::vector<int> getTemps();
        static double getAverageTemp();
        
        static void printTemps();

        static float getCpuUsage();

        static void printCpuUsage();

    private:


};

#endif