#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include "param_parser.h"
#include "param_handler.h"

int main(int argc, char** argv) {

    std::string executable_path = std::string(argv[1]);
    auto params = request_executable(executable_path);

    // List fetched parameters
    for (auto const [key, val] : params.data) {
        std::cout << key << ":" << val._type << std::endl;
        std::string v;
        std::cin >> v;
        params[key]._value = v;
    }

    //std
//    params.set()

    call_executable(executable_path, params);

    return 0;
}