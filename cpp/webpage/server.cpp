#define CROW_MAIN
#include <crow.h>
#include <fstream>
// #include <http_response.h>

// Function to read a file and return its contents as a string
std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) return "";
    return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

int main() {
    crow::SimpleApp app;

    // Route to serve the main HTML file
    CROW_ROUTE(app, "/")([](const crow::request&, crow::response& response) {
        response.set_static_file_info_unsafe("../public/index.html");
        response.end();
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
