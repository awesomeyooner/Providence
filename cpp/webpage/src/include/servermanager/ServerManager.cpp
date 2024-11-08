#include "ServerManager.hpp"

using namespace Utility;

ServerManager::ServerManager(SuperStructure *instance) : superstructure(instance){

}

void ServerManager::loop(){
    
}

void ServerManager::initialize(){
    crow::SimpleApp app;

    cv::Mat *frame = &superstructure->latestFrame;
    // Route to serve the main HTML file
    // CROW_ROUTE(app, "/")([](const crow::request&, crow::response& response) {
    //     response.set_static_file_info_unsafe("../public/index.html");
    //     response.end();
    // });

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

    CROW_ROUTE(app, "/<path>")([](const crow::request&, crow::response& response, std::string path) {
        std::string file_path = "../public/" + path;
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

    CROW_ROUTE(app, "/video")([](){
        crow::response response;

        response.code = 200;
        response.set_header("Content-Type", "multipart/x-mixed-replace; boundary=frame");

        while(true){
            std::vector<uchar> buffer;

            cv::imencode(".jpg", &frame)
        }
    });

    // Route to serve other static files (JS, CSS, etc.)
    CROW_ROUTE(app, "/<string>")([](const std::string& filename) {
        return readFile("public/" + filename);
    });

    CROW_ROUTE(app, "/src/<string>")([](const std::string& filename) {
        return readFile("public/src/" + filename);
    });

    CROW_ROUTE(app, "/libs/<string>")([](const std::string& filename) {
        return readFile("public/libs/" + filename);
    });

    app.add_static_dir();

    // Start the server
    app.port(8080).multithreaded().run();
}
