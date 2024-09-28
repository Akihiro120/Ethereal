#pragma once
#include "nholmann_json.h"

using json = nlohmann::json;
class JSONHandler {
public:
    static void ExportJSON(std::string path, json data);
    static json ImportJSON(std::string path);

private:
    JSONHandler() = default;

    // get singleton pattern
    static JSONHandler Get() {
        static JSONHandler instance;
        return instance;
    }
};
