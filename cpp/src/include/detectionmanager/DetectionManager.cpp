#include "DetectionManager.hpp"

DetectionManager::DetectionManager() : detector(apriltag_detector_create()), family(tag36h11_create()){
    //use detector. to see everything
    apriltag_detector_add_family(detector, family);
}

DetectionManager::DetectionManager(apriltag_detector_t* det, apriltag_family_t* fam) : detector(det), family(fam){
    detector->quad_decimate = 1.0;    // Decimation factor for faster detection at lower resolutions
    detector->quad_sigma = 0.0;       // Gaussian blur for noise reduction
    detector->nthreads = 1;           // Number of CPU threads to use
    detector->refine_edges = 1;       // Refine edges to improve accuracy

    apriltag_detector_add_family(detector, family);
}

apriltag_detector_t* DetectionManager::getDetector(){
    return detector;
}

apriltag_family_t* DetectionManager::getFamily(){
    return family;
}

void DetectionManager::setIntrinsics(double fx, double fy, double cx, double cy){
    info.fx = fx;
    info.fy = fy;
    info.cx = cx;
    info.cy = cy;
}

zarray_t* DetectionManager::getDetections(cv::Mat mat){
    image_u8_t image = matToImage(mat);

    return apriltag_detector_detect(detector, &image);
}

void DetectionManager::process(zarray_t* detections){
    for(int i = 0; i < zarray_size(detections); i++){
        apriltag_detection_t* detection;

        zarray_get(detections, i, &detection);

        info.det = detection;

        apriltag_pose_t pose;

        double error = estimate_tag_pose(&info, &pose);

        std::cout << "spotted!" << std::endl;
    }
}

image_u8_t DetectionManager::matToImage(cv::Mat mat){

    cv::Mat gray;
    
    cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);

    image_u8_t image = {
        .width = gray.cols,
        .height = gray.rows,
        .stride = gray.cols,
        .buf = gray.data
    };

    return image;
}

void DetectionManager::clean(){
    apriltag_detector_destroy(detector);
    tag36h11_destroy(family);
}