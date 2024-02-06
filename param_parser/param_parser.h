#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <typeinfo>

struct Parameters {

	// Structured param type "enum"
	struct ParamType {
		// Primitive types
		static constexpr const char* Int {"int"};
		static constexpr const char* Float {"float"};
		static constexpr const char* Double {"double"};
		static constexpr const char* Bool {"bool"};
		static constexpr const char* String {"string"};
		static constexpr const char* File {"file"};
		static constexpr const char* Enum {"enum"};
		// Attributes types
		static std::string vertices(std::string s, int dim) { return "vertices." + s + "." + std::to_string(dim); }
		static std::string facets(std::string s, int dim) { return "facets." + s + "." + std::to_string(dim); }
		static std::string edges(std::string s, int dim) { return "edges." + s + "." + std::to_string(dim); }
		static std::string cells(std::string s, int dim) { return "cells." + s + "." + std::to_string(dim); }
	};

#define ADD_FIELD(x) Param& x(std::string str) {  _##x=str; return *this; }\
	std::string _##x;
	
	struct Param {

		Param() {
			_type = "undefined";
			_value = "undefined";
			_description = "undefined";
			_possible_values = "undefined";
			_type_of_param = "undefined";
		}

		ADD_FIELD(type)				// should be one of "int","float","string","file","directory","bool","enum"
		ADD_FIELD(value)
		ADD_FIELD(description)
		ADD_FIELD(possible_values)		// string with values are separated by ','. For example "option1,option2,option3"
		ADD_FIELD(type_of_param)		// should be one of "basic" or "advanced" 
		
		Param & default_value(std::string str) {  _value=str; return *this; }

		
		operator int() {
			assert_type_equals(ParamType::Int);
			try { return std::stoi(_value); }
			catch (std::invalid_argument&) { throw_type_cast_error(_value, ParamType::Int); return -1; }
		}
		
		operator bool() {
			assert_type_equals(ParamType::Bool);
			return is("true");
		}

		operator float() {
			assert_type_equals(ParamType::Float);
			try { return std::stof(_value); }
			catch (std::invalid_argument&) { throw_type_cast_error(_value, ParamType::Float); return -1; }
		}
		operator double() {
			assert_type_equals(ParamType::Double);
			try { return std::stod(_value); }
			catch (std::invalid_argument&) { throw_type_cast_error(_value, ParamType::Double); return -1; }
		}
		operator std::string() { return _value; }

		
		inline bool is(std::string str) { return _value.compare(str) == 0; }

		// Eventually format value (e.g: quotes for string)
		inline std::string formatted_value() {
			if (_type.compare(ParamType::String) == 0)
				return "\"" + _value + "\"";
			else 
				return _value;
		}

		// Set value
		inline void set(std::string value) {
		    _value = value;
		}

		private:
			inline void assert_type_equals(const std::string type) {
				if (_type.compare(type) != 0)
					throw_type_cast_error(_type, type);
			}

			inline void throw_type_cast_error(const std::string source_type, const std::string target_type) {
				throw std::runtime_error("Unable to cast " + source_type + " into an " + target_type + ".");
			}

	};
#undef ADD_FIELD

    // Default constructor
    Parameters() {}

    // Init with serialized parameters string
    Parameters(std::string serialized_params) {

        std::istringstream s(serialized_params);
        std::string line;

        const std::string delimiter = ";";

        while (std::getline(s, line)) {

            std::size_t last_pos = 0;
            // Assume there is only 6 features per parameter
            // Doesn't check whether file is well formed
            std::string chunks[6];

            // Skip comments (begin by char #)
            if (line[0] == '#')
                continue;

            std::size_t pos = 0;
            std::map<std::string, std::string> kv;
            while ((pos = line.find(delimiter, last_pos)) != std::string::npos) {
                std::string chunk = line.substr(last_pos, pos - last_pos);
                
                std::size_t equal_pos = chunk.find("=");
                if (equal_pos == std::string::npos)
                    throw std::runtime_error("Malformed parameter string.");

                std::string key = chunk.substr(0, equal_pos);
                std::string val = chunk.substr(equal_pos + 1, chunk.length() - equal_pos - 1);

                kv[key] = val;
                last_pos = pos + 1;
            }

            // Add param
            auto param = add(kv["type"], kv["name"], kv["value"]);
            param._possible_values = kv["possible_values"];
            param._description = kv["description"];;
            param._type_of_param = kv["type_of_param"];;
        }

    }

	Param& add(std::string type, std::string name, std::string default_value) {
		if (data.find(name) != data.end())
			throw std::runtime_error("Duplicate parameter '" + name + "' found.");

		data[name] = Param();
		data[name]._type = type;
		data[name]._value = default_value;

		return data[name];
	}
	Param& operator[](std::string name) { return data[name]; }

	void init_from_string(const std::string& s) {
		int eq_pos = 0;
		for (std::size_t i = 0; i < s.size();i++) if (s[i] == '=') eq_pos = i;
		std::string var_name = s.substr(0, eq_pos);
		if (data.find(var_name) == data.end())
			std::cerr << "Argument " << var_name << " is not defined for this binary\n";
		else {
			std::cout << s.substr(eq_pos + 1, s.size());
			data[s.substr(0, eq_pos)]._value = s.substr(eq_pos + 1, s.size());
		}
	}

    std::string str_values() {
        std::string s;
		for (auto it : data)
			s += it.first + "=" + it.second.formatted_value() + " ";

        return s;
    }

	void show_values() {
	    std::cerr << str_values();
	}

	void init_from_args(int argc, char** argv) {
		// export parameters "API"
		if (argc > 1 && std::string("--show-params").compare(argv[1]) == 0) {
			std::cout << "#This file contains reflexion information for calling a binary file\n";
			for (auto it : data) {
			std::cout
			    << "name=" << it.first << ";"
			    << "type=" << it.second._type << ";"
			    << "value=" << it.second._value << ";"
			    << "possible_values=" << it.second._possible_values << ";"
			    << "description=" << it.second._description << ";"
			    << "type_of_param=" << it.second._type_of_param
			    << std::endl;
			}
			exit(EXIT_SUCCESS);
		}

		// read arguments from command line
		for (int p = 0; p < argc - 1;p++) init_from_string(argv[p + 1]);
	}

	// the key is the parameter's name
	std::map<std::string, Param> data;
};

#endif