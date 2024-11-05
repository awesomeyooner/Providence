#define CROW_MAIN
#define CROW_STATIC_DIRECTORY "public/"
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <fstream>
#include <string>
#include <iostream>
// #include <http_response.h>

// Function to read a file and return its contents as a string
std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) return "";
    return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main() {
    crow::SimpleApp app;

    // Route to serve the main HTML file
    // CROW_ROUTE(app, "/")([](const crow::request&, crow::response& response) {
    //     response.set_static_file_info_unsafe("../public/index.html");
    //     response.end();
    // });

    CROW_ROUTE(app, "/")([](const crow::request&, crow::response& res) {
        std::ifstream file("../public/index.html");
        if (file) {
            std::ostringstream contents;
            contents << file.rdbuf();
            file.close();
            res.set_header("Content-Type", "text/html");
            res.write(contents.str());
        } else {
            res.code = 404;
            res.write("404: File not found");
        }
        res.end();
    });

    CROW_ROUTE(app, "/<path>")([](const crow::request&, crow::response& res, std::string path) {
        std::string file_path = "../public/" + path;
        if (std::filesystem::exists(file_path)) {
            std::ifstream file(file_path, std::ios::binary);
            std::ostringstream contents;
            contents << file.rdbuf();
            file.close();

            // Set the correct Content-Type based on file extension
            if (ends_with(path, ".js")) {
                res.set_header("Content-Type", "application/javascript");
            } else if (ends_with(path, ".css")) {
                res.set_header("Content-Type", "text/css");
            } else if (ends_with(path, ".html")) {
                res.set_header("Content-Type", "text/html");
            } // Add more types if needed

            res.write(contents.str());
        } else {
            res.code = 404;
            res.write("404: File not found");
        }
        res.end();
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
