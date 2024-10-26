#include "DetectionManager.hpp"

DetectionManager::DetectionManager() : DetectionManager::DetectionManager(apriltag_detector_create(), tag36h11_create()){
    //use detector. to see everything
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

        std::cout << detection->id << std::endl;
    }
}

image_u8_t DetectionManager::matToImage(cv::Mat mat){

    image_u8_t image = {
        .width = mat.cols,
        .height = mat.rows,
        .stride = mat.cols,
        .buf = mat.data
    };

    return image;
}

cv::Mat DetectionManager::annotate(cv::Mat frame, zarray_t* detections){

    for(int i = 0; i < zarray_size(detections); i++){
        apriltag_detection_t* detection;

        zarray_get(detections, i, &detection);

        auto corners = detection->p;

        cv::Point center(detection->c[0], detection->c[1]);

        cv::Point one(corners[0][0], corners[0][1]);
        cv::Point two(corners[1][0], corners[1][1]);
        cv::Point three(corners[2][0], corners[2][1]);
        cv::Point four(corners[3][0], corners[3][1]);

        cv::line(frame, one, two, cv::Scalar(255, 0, 0), 2, cv::LINE_8);
        cv::line(frame, two, three, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
        cv::line(frame, three, four, cv::Scalar(0, 0, 255), 2, cv::LINE_8);
        cv::line(frame, four, one, cv::Scalar(0, 255, 255), 2, cv::LINE_8);

        cv::putText(frame, std::to_string(detection->id), center, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 4, cv::LINE_AA);
        
    }

    return frame;
}

void DetectionManager::clean(){
    apriltag_detector_destroy(detector);
    tag36h11_destroy(family);
}