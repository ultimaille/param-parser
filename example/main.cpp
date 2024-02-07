#include <iostream>
#include <param_parser/param_parser.h>

int main(int argc, char** argv) {

    // Create parameters
    Parameters params;

    // Add program parameters
    /* params.add(type, name, default_value) */
    params.add("string", "my_string", "").description("A string");
    params.add("bool", "my_bool", "false").description("A bool");
    params.add("int", "my_int", "0").description("A integer");
    params.add("float", "my_float", "0").description("A float");
    params.add("double", "my_double", "0").description("A double");
    params.add("file", "my_file", "0").description("A file");
    /* Parse program arguments and bind to parameters */
    params.init_from_args(argc, argv);
    /* Show args values */
    params.show_values();

    //std::cout << params["my_int"];

    /* Using args value to do something */
    /* Here computing the pow(my_float, my_int) */
    int my_int = params["my_int"];
    float my_float = params["my_float"];
    float pow_res = my_float;
    for (int i = 0; i < my_int - 1; i++)
        pow_res *= my_float;

    std::cout << "pow(" << my_float << "," << my_int << ")" << "=" << pow_res << std::endl;
    
    return 0;
}