#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <param_parser/param_parser.h>
#include <param_parser/param_handler.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Program path expected as first argument." << std::endl;
        return 0;
    }

    std::string executable_path = std::string(argv[1]);
    // Request params of a given exe
    auto params = request_params(executable_path);

    // List fetched parameters
    for (auto const & [key, val] : params.data) {
        std::cout << key << ":" << val._type << " (" << val._type_of_param << ")" << std::endl;
        std::string v;
        std::cin >> v;
        params[key].set(v);
    }

    // Call executable with set parameters
    std::cout << "execute " << executable_path << std::endl;
    std::cout << "------" << std::endl;
    std::cout << call(executable_path, params) << std::endl;
    std::cout << "------" << std::endl;

    return 0;
}