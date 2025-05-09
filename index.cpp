// Version 0.1

#include <iostream>
#include "dependencies/httplib.h"
#include "dependencies/json.hpp"

int main() {
    int port = 8080;
    std::string url = "localhost";
    std::cout << "What IP would you like the server to be hosted on? (think localhost, 127.0.0.1, and do not include port) \n";
    std::cin >> url;
    std::cout << "What port would you like to use? \n";
    std::cin >> port;

    httplib::Client cli("http://localhost:11434");
    httplib::Server svr;

    svr.Get("/:path", [&](const httplib::Request& req, httplib::Response& htpres) {
        auto path = req.path_params.at("path");
        // Construct JSON payload
        std::string json_payload = R"({
            "model": "html_generator",
            "prompt": "/)" + path + R"(",
            "stream": false
        })";

        // Set Content-Type header to application/json
        httplib::Headers headers = {
            {"Content-Type", "application/json"}
        };

        // Send POST request with JSON payload
        httplib::Result res = cli.Post("/api/generate", headers, json_payload, "application/json");

        if (!res || res->status != 200) {
            std::cout << "Non 200 result or request failed";
            htpres.set_content("An error occured and we couldn't get the response. Apologizes.", "text/plain");
        } else {
            std::cout << res->body;
            std::string jsonString = res->body;

            try {
                // Parse the JSON string
                nlohmann::json parsedJson = nlohmann::json::parse(jsonString);

                // Extract the "response" parameter
                if (parsedJson.contains("response")) {
                    std::string response = parsedJson["response"];
                    std::cout << "Extracted response: " << response << std::endl;
                    htpres.set_content(response, "text/html");
                } else {
                    // Handle errors
                    std::cerr << "'response' key not found in JSON!" << std::endl;
                    htpres.set_content("An error occured and we couldn't get the response. Apologizes.", "text/plain");
                }
            } catch (const nlohmann::json::parse_error& e) {
                // Handle errors
                std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
                htpres.set_content("An error occured and we couldn't get the response. Apologizes.", "text/plain");
            }
        }

    });

    // Start server on port 8080
    std::cout << "Starting server on " + url + ":" + std::to_string(port) + "\n";
    svr.listen(url, port);

}
