# Introduction 

Param parser is oriented to geometry processing: some parameter types are related to input model, attributes of primitives. Although not required, command-line interfaces are intended to be interpreted by a third-party application like a modeler (e.g: Graphite using [graphite add-on loader](https://github.com/ultimaille/graphite-addon-loader)).



:warning: We name **client** a third-part application which use a program - that implement a command-line interface with param parser  - as an add-on. A client is usually a modeler.

# Initialization

```cpp
// Declare parameters
Parameters params;
// Set help message
params.help = "This program aims to demonstrate the use of param parser.";

// Declare parameters
// ...
// ...
// ...

// Parse program arguments and bind to parameters
params.init_from_args(argc, argv);
```

# Declare parameter

To add a parameter you need to specify its **type**, **name** and **default value**. 

 - Type must be described by a string or using `Parameters::Type`
 - All values must be described by a string (e.g: see `bool` type).

```cpp
params.add(Parameters::Type::String, "my_string", "")
// can be written as
// params.add("string", "my_string", "")

params.add(Parameters::Type::Bool, "my_bool", "true")
// can be written as
// params.add("bool", "my_bool", "true")
```

## List of parameter types

### Standard

 - `int`: expect a `int`
 - `float`: expect a `float`
 - `double`: expect a `double`
 - `bool`: expect a `bool` {`false`, `true`}
 - `string`: expect a `string`
 - `file`: expect a file path
 - **`input`**: automatically set by the client (e.g: a modeler) by the path of the current model

### Attributes

 - `vertices.int`: expect the name of `vertice` attribute of type `int` as value
 - `vertices.float`: expect the name of `vertice` attribute of type `float` as value
 - `vertices.double`: expect the name of `vertice` attribute of type `double` as value
 - `vertices.bool`: expect the name of `vertice` attribute of type `bool` as value
 - `facets.int`: expect the name of `facets` attribute of type `int` as value
 - `facets.float`: expect the name of `facets` attribute of type `float` as value
 - `facets.double`: expect the name of `facets` attribute of type `double` as value
 - `facets.bool`: expect the name of `facets` attribute of type `bool` as value
 - `edges.int`: expect the name of `edges` attribute of type `int` as value
 - `edges.float`: expect the name of `edges` attribute of type `float` as value
 - `edges.double`: expect the name of `edges` attribute of type `double` as value
 - `edges.bool`: expect the name of `edges` attribute of type `bool` as value
 - `cells.int`: expect the name of `cells` attribute of type `int` as value
 - `cells.float`: expect the name of `cells` attribute of type `float` as value
 - `cells.double`: expect the name of `cells` attribute of type `double` as value
 - `cells.bool`: expect the name of `cells` attribute of type `bool` as value

## Special parameters

Some parameter names are reserved. These special parameters may be interpreted and automatically set by the client (modeler, e.g: Graphite).

 - `result_path`: client set this parameter value with a path that you must use to put your results files.
 - `run_from`: the name of the client that call the program, empty if the program is run in standalone mode

These parameters are declared automatically. You can get their values by using the following functions:

```cpp
std::string result_path = params.result_path();
std::string run_from = params.run_from();
```

## Parameter metadata

Using builder pattern, you can add some data to your parameter.

 - `description(string desc)` 

add a description to a parameter. This description will be showed as a label or tooltip text by the client modeler.

Example:

```cpp
params.add(Parameters::Type::String, "my_string", "").description("A string !");
```

- `type_of_param(string type)` 

Specify a visibilty and a role to your parameter. 

With `type` belongs to {`basic`, `advanced`, `system`}. 

 - `basic` will be show to the user
 - `advanced` will be show under a foldout menu
 - `system` will be hide to the user

By default a parameter is of `basic` type.

Example:

```cpp
params.add(Parameters::Type::String, "my_string", "").type_of_param(Parameters::Kind::advanced);
// can be written as 
// params.add(Parameters::Type::String, "my_string", "").type_of_param("advanced");
```

 - `possible_values(string values)`

 Constraint parameter to a set of possible values. Client should interpret this as a choice list (combo box).

Example:

```cpp
params.add(Parameters::Type::String, "my_enum", "x").possible_values("x,y,z");
```

 :exclamation: Possible values must be separated by a comma.

# Get parameter value

To get a parameter value just use indexation:

```cpp
std::string my_string = params["my_string"];
int my_int = params["my_int"];
// ...
```

An implicit conversion was made between the parameter type and the variable type - provided they are consistent.