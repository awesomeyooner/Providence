#include "opencv2/opencv.hpp"

int main(int argc, char** argv){
    
    cv::VideoCapture cap(0);

    if(!cap.open(0))
        return -1;

    while(true){
        cv::Mat frame;

        cap >> frame;

        if(frame.empty())
            break;

        cv::imshow("frame", frame);

        if(cv::waitKey(10) == 27)
            break;
    }


    return 0;
}