#include "CameraManager.hpp"

CameraManager::CameraManager(int index) : cap(index) {
    config();
}
CameraManager::CameraManager(int index, cv::VideoCaptureAPIs type) : cap(index, type) {
    config();
}

void CameraManager::config(){
    setProperty(cv::CAP_PROP_FRAME_WIDTH, 1280, true);
    setProperty(cv::CAP_PROP_FRAME_HEIGHT, 960, true);
    setProperty(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'), true);
    setProperty(cv::CAP_PROP_FPS, 30, true);
}

bool CameraManager::setProperty(cv::VideoCaptureProperties property, double value, bool print){
    cap.set(property, value);
    
    if(print)
        std::cout << cap.get(property) << std::endl;

    return cap.get(property) == value;
}

bool CameraManager::isOpened(){
    return cap.isOpened();
}

cv::Mat CameraManager::getFrame(){

    previousTimestamp = std::chrono::high_resolution_clock::now();

    cv::Mat frame;
    cap >> frame;

    return frame;
}

double CameraManager::getFramerate(){
    return framerate;
}

void CameraManager::updateFramerate(){
    auto now = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - previousTimestamp).count();

    framerate = 1 / (delta / 1000000.0);
}

bool CameraManager::show(){
    cv::Mat frame = getFrame();

    if(frame.empty())
        return false;

    cv::imshow("frame", frame);

    return true;
}

void CameraManager::release(){
    cap.release();
}