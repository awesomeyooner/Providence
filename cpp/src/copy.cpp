#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char** argv){
    
    VideoCapture cap(0);

    if(!cap.open(0))
        return -1;

    while(true){
        Mat frame;

        cap >> frame;

        if(frame.empty())
            break;

        imshow("frame", frame);

        if(waitKey(10) == 27)
            break;
    }


    return 0;
}