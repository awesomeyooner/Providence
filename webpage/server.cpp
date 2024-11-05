#define CROW_MAIN
#include "public/libs/cpp/crow.h"
#include <fstream>

// Function to read a file and return its contents as a string
std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) return "";
    return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

int main() {
    crow::SimpleApp app;

    // Route to serve the main HTML file
    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load_text("fancypage.html");
        return page;
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

    // Start the server
    app.port(8080).multithreaded().run();
}
