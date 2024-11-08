#include "DetectionManager.hpp"

DetectionManager::DetectionManager() : DetectionManager::DetectionManager(apriltag_detector_create(), tag36h11_create()){
    //use detector. to see everything
}

DetectionManager::DetectionManager(apriltag_detector_t* det, apriltag_family_t* fam) : detector(det), family(fam){
    detector->quad_decimate = 1.0;    // Decimation factor for faster detection at lower resolutions
    detector->quad_sigma = 0.0;       // Gaussian blur for noise reduction
    detector->nthreads = 4;           // Number of CPU threads to use
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

void DetectionManager::setDistortionCoefficients(double coeffs[8]){
    std::memcpy(distCoeffs, coeffs, sizeof(distCoeffs));
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

void DetectionManager::process(cv::Mat* frame){
    cv::Mat gray;

    cv::cvtColor(*frame, gray, cv::COLOR_BGR2GRAY);

    zarray_t* detections = getDetections(gray);

    for(int i = 0; i < zarray_size(detections); i++){
        apriltag_detection_t* detection;

        zarray_get(detections, i, &detection);

        info.det = detection;

        apriltag_pose_t pose;

        double error = estimate_tag_pose(&info, &pose);

        drawBox(frame, pose);
        putID(frame, detection);
    }
}

void DetectionManager::poseToMat(apriltag_pose_t pose, cv::Mat* rvec, cv::Mat* tvec){
    cv::Mat R = (cv::Mat_<double>(3, 3) << 
        pose.R->data[0], pose.R->data[1], pose.R->data[2],
        pose.R->data[3], pose.R->data[4], pose.R->data[5],
        pose.R->data[6], pose.R->data[7], pose.R->data[8]
    );

    *tvec = (cv::Mat_<double>(3, 1) << pose.t->data[0], pose.t->data[1], pose.t->data[2]);

    cv::Rodrigues(R, *rvec);
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

void DetectionManager::annotate(cv::Mat* frame, apriltag_detection_t* detection){

    drawCorners(frame, detection);

    putID(frame, detection);
}

void DetectionManager::putID(cv::Mat* frame, apriltag_detection_t* detection){
    cv::Point center(detection->c[0], detection->c[1]);
    cv::putText(*frame, std::to_string(detection->id), center, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255), 4, cv::LINE_AA);
}

void DetectionManager::drawCorners(cv::Mat* frame, apriltag_detection_t* detection){
    auto corners = detection->p;

    cv::Point one(corners[0][0], corners[0][1]);
    cv::Point two(corners[1][0], corners[1][1]);
    cv::Point three(corners[2][0], corners[2][1]);
    cv::Point four(corners[3][0], corners[3][1]);

    cv::line(*frame, one, two, cv::Scalar(255, 0, 0), 2, cv::LINE_8);
    cv::line(*frame, two, three, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
    cv::line(*frame, three, four, cv::Scalar(0, 0, 255), 2, cv::LINE_8);
    cv::line(*frame, four, one, cv::Scalar(0, 255, 255), 2, cv::LINE_8);
}

void DetectionManager::drawBox(cv::Mat* frame, apriltag_pose_t pose){

    double box_height = info.tagsize * 0.5; // Define box height as half the tag size

    std::vector<cv::Point3f> box_points = {
        {-info.tagsize / 2, -info.tagsize / 2, 0},
        { info.tagsize / 2, -info.tagsize / 2, 0},
        { info.tagsize / 2,  info.tagsize / 2, 0},
        {-info.tagsize / 2,  info.tagsize / 2, 0},
        {-info.tagsize / 2, -info.tagsize / 2, -box_height},
        { info.tagsize / 2, -info.tagsize / 2, -box_height},
        { info.tagsize / 2,  info.tagsize / 2, -box_height},
        {-info.tagsize / 2,  info.tagsize / 2, -box_height}
    };

    cv::Mat rvec, tvec;

    poseToMat(pose, &rvec, &tvec);

    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 
        info.fx, 0, info.cx,
        0, info.fy, info.cy,
        0, 0, 1
    );

    cv::Mat coeffs(1, 8, CV_64F, distCoeffs);

    std::vector<cv::Point2f> image_points;
    projectPoints(box_points, rvec, tvec, cameraMatrix, coeffs, image_points);

    cv::line(*frame, image_points[0], image_points[1], cv::Scalar(0, 255, 0), 2);
    cv::line(*frame, image_points[1], image_points[2], cv::Scalar(0, 255, 0), 2);
    cv::line(*frame, image_points[2], image_points[3], cv::Scalar(0, 255, 0), 2);
    cv::line(*frame, image_points[3], image_points[0], cv::Scalar(0, 255, 0), 2);

    // Draw the top of the box
    cv::line(*frame, image_points[4], image_points[5], cv::Scalar(255, 0, 0), 2);
    cv::line(*frame, image_points[5], image_points[6], cv::Scalar(255, 0, 0), 2);
    cv::line(*frame, image_points[6], image_points[7], cv::Scalar(255, 0, 0), 2);
    cv::line(*frame, image_points[7], image_points[4], cv::Scalar(255, 0, 0), 2);

    // Draw the vertical edges
    cv::line(*frame, image_points[0], image_points[4], cv::Scalar(0, 0, 255), 2);
    cv::line(*frame, image_points[1], image_points[5], cv::Scalar(0, 0, 255), 2);
    cv::line(*frame, image_points[2], image_points[6], cv::Scalar(0, 0, 255), 2);
    cv::line(*frame, image_points[3], image_points[7], cv::Scalar(0, 0, 255), 2);
}

void DetectionManager::clean(){
    apriltag_detector_destroy(detector);
    tag36h11_destroy(family);
}