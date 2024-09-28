#include "json_handler.h"
#include "fstream"
#include <iostream>

void JSONHandler::ExportJSON(std::string path, json data) {
    
    // export json file
    std::ofstream json_file("../resources/data/" + path, std::ios::out);
    if (json_file.is_open()) {
        json_file << data.dump();

        // close
        json_file.close();
    }
}

json JSONHandler::ImportJSON(std::string path) {
    json data;

    // import json file
    std::fstream json_file("../resources/data/" + path, std::ios::in);
    if (json_file.is_open()) {
        json_file >> data;

        // close
        json_file.close();
    }

    return data;
}
