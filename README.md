# Param parser

Parser for command-line options, arguments.

## Purpose

This header file lets you define command-line interfaces. The program defines the parameters it needs - these are expected to be formatted as key/value pairs.
This module also generates a formatted message intended to be read by a third-party application wishing to use this information to generate an interface.

## Prerequisites

- CMake >= 3.12..3.26
- C++ >= 20
- Git

## Usage example

Let the following program be called `MyProgram`:
```cpp
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

/* Parse program arguments */
params.init_from_args(argc, argv);
/* Show args values */
params.show_values();

/* Using args value to do something */
int my_int = params["my_int"];
float my_float = params["my_float"];
int pow_res = my_float;
for (int i = 0; i < my_int - 1; i++)
    pow_res *= my_int;

std::cout << "pow(" << my_float << "," << my_int << "=" << pow_res << std::endl;
```

Call the `MyProgram` with some arguments:
```shell
$ MyProgram my_string=hello my_bool=true my_int=4 my_float=2 my_double=3 my_file=/path/to/file

--- show values
my_bool = false my_double = 0 my_file = 0 my_float = 2 my_int = 4 my_string = ""

--- out
pow(2,4)=16
```

Above, the first part concern the output of the method `params.show_values()` and the second is the result of our operations.

Get interface of `MyProgram`:
```shell
$ MyProgram --show-params

#This file contains reflexion information for calling a binary file
#name|type|value|possible_values|description|type_of_param
my_bool	bool	false	_undefined	A bool	_undefined	
my_double	double	0	_undefined	A double	_undefined	
my_file	file	0	_undefined	A file	_undefined	
my_float	float	0	_undefined	A float	_undefined	
my_int	int	0	_undefined	A integer	_undefined	
my_string	string		_undefined	A string	_undefined
``` 

This program call with `--show-params` output a computer readable list of parameters info that can be exploited to make a GUI.

## Use in your project

In order to use this lib in your project you can choose between including a shared library or source header directly. We recommend to include the shared lib.

### Get as shared lib

TODO (see if possible to get from release by CMakeList Download command)

### Get as header

TODO (see if possible to publish header and get from release by CMakeList Download command)

## Go further

If you want to get, compile and see this lib in action.

### Get

`git clone https://github.com/ultimaille/param-parser.git`

### Compile

At the project root:

`cmake -B build && cd build && make -j`

### Run

Go to `build/example` directory and run the `parameter-example` executable.