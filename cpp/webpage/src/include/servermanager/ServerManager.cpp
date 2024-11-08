#include "ServerManager.hpp"

using namespace Utility;

std::shared_ptr<cv::Mat> sharedFrame = std::make_shared<cv::Mat>();
std::mutex frameMutex;

//sendable values
double tx, ty, tz = 0;
double rx, ry, rz = 0;

double framerate = 0;

void ServerManager::loop(){
    CameraManager camera(2, cv::CAP_V4L2);
    DetectionManager detector;

    detector.setIntrinsics(
        730.0688629, 
        730.2649748, 
        674.9147146, 
        545.0855588
    );

    double coeffs[8] = {0.03080258043, -0.06523055331, 0.0003025805212, -4.177400726e-05, 0.06055868742, -0.01789081457, 0.01539022107, 0.03832702575};

    detector.setDistortionCoefficients(
        coeffs
    );

    if(!camera.isOpened())
        return;

    while(true){

        camera.updateFramerate();

        if(camera.getFramerate() > 30)
            continue;

        cv::Mat frame = camera.getFrame();

        framerate = camera.getFramerate();
        cv::putText(frame, std::to_string(framerate), cv::Point(0, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2, cv::LINE_AA);

        //code goes here
        detector.process(&frame, &tx, &ty, &tz, &rx, &ry, &rz);

        std::lock_guard<std::mutex> lock(frameMutex);
        *sharedFrame = frame.clone();

        if(!camera.show(frame))
            break;

        //std::cout << camera.getFramerate() << std::endl;

        if(cv::waitKey(10) == 27)
            break;
    }

    camera.release();
}

void ServerManager::initialize(){
    crow::SimpleApp app;

   
    app.route_dynamic("/framerate")([](){
        crow::json::wvalue data;
        data["framerate"] = std::round(framerate);

        return crow::response(data); 
    });

    app.route_dynamic("/pose")([](){
        crow::json::wvalue data;
        
            data["translation"]["x"] = tx;
            data["translation"]["y"] = ty;
            data["translation"]["z"] = tz;

            data["rotation"]["x"] = rx;
            data["rotation"]["y"] = ry;
            data["rotation"]["z"] = rz;

        return crow::response(data); 
    });

    app.route_dynamic("/image")([](){
        crow::response response;

        response.code = 200;
        response.set_header("Content-Type", "image/jpeg");

        std::vector<uchar> buffer;

            cv::Mat frame;

            {
                std::lock_guard<std::mutex> lock(frameMutex);

                frame = sharedFrame->clone();

                if(frame.empty())
                    frame = cv::imread("../public/picture.jpg");
            }

            cv::imencode(".jpg", frame, buffer);
            
            std::string encodedFrame(buffer.begin(), buffer.end());

            response.write(encodedFrame);

            return response;
    });
    
    CROW_ROUTE(app, "/stats")([]{
            crow::json::wvalue data;
            data["cpu"] = SystemManager::getCpuUsage();
            data["temp"] = SystemManager::getAverageTemp();

            return crow::response(data); 
        });

    CROW_ROUTE(app, "/")([](const crow::request&, crow::response& response) {
        std::ifstream file("../public/index.html");
        if (file) {
            std::ostringstream contents;
            contents << file.rdbuf();
            file.close();
            response.set_header("Content-Type", "text/html");
            response.write(contents.str());
        } else {
            response.code = 404;
            response.write("404: File not found");
        }
        response.end();
    });

    CROW_ROUTE(app, "/test")
    ([]() {
        return "Test route is working!";
    });

    CROW_ROUTE(app, "/<path>")([](const crow::request&, crow::response& response, std::string path) {
        std::string file_path = "../public/" + path;
        //std::string file_path = "../" + path;
        if (std::filesystem::exists(file_path)) {
            std::ifstream file(file_path, std::ios::binary);
            std::ostringstream contents;
            contents << file.rdbuf();
            file.close();

            // Set the correct Content-Type based on file extension
            if (ends_with(path, ".js")) {
                response.set_header("Content-Type", "application/javascript");
            } else if (ends_with(path, ".css")) {
                response.set_header("Content-Type", "text/css");
            } else if (ends_with(path, ".html")) {
                response.set_header("Content-Type", "text/html");
            } // Add more types if needed

            response.write(contents.str());
        } else {
            response.code = 404;
            response.write("404: File not found");
        }
        response.end();
    });

    app.add_static_dir();

    // Start the server
    app.port(8080).multithreaded().run();
}
