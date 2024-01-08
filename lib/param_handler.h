#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include "param_parser.h"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

Parameters request_params(std::string executable_path) {
    // Call executable request its parameters
    std::string stdout = exec((executable_path + " --show-params 2>&1").c_str());

    // Create parameters
    Parameters params(stdout);
    return params;
}

inline std::string call(std::string executable_path, Parameters params) {
    return exec((executable_path + " " + params.str_values()).c_str());
}