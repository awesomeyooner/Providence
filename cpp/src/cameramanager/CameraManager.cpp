#include "CameraManager.hpp"

CameraManager::CameraManager(int index) : cap(index) {}
CameraManager::CameraManager(int index, cv::VideoCaptureAPIs type) : cap(index, type) {}

bool CameraManager::setProperty(cv::VideoCaptureProperties property, double value, bool print){
    cap.set(property, value);
    
    if(print)
        std::cout << cap.get(property) << std::endl;

    return cap.get(property) == value;
}

bool CameraManager::isOpened(){
    return cap.isOpened();
}

void CameraManager::release(){
    cap.release();
}