#include <iostream>
#include <param_parser/param_parser.h>

int main(int argc, char** argv) {

    // Create parameters
    Parameters params;

    params.help = "This program aims to demonstrate the use of param parser.";

    // Add program parameters
    /* params.add(type, name, default_value) */
    params.add(Parameters::Type::String, "my_string", "").description("A string");
    params.add(Parameters::Type::Bool, "my_bool", "false").description("A bool");
    params.add(Parameters::Type::Int, "my_int", "0").description("A integer");
    params.add(Parameters::Type::Float, "my_float", "0").description("A float");
    params.add(Parameters::Type::Double, "my_double", "0").description("A double");
    params.add(Parameters::Type::File, "my_file", "0").description("A file").type_of_param(Parameters::Kind::advanced);
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