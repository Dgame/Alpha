#ifndef ALPHA_UTIL_HPP
#define ALPHA_UTIL_HPP

#include <string>
#include <sstream>

namespace std {
	template <typename T>
	inline std::string to_string(T value)
	{
		//create an output string stream
		std::ostringstream os ;
		//throw the value into the string stream
		os << value ;
		//convert the string stream into a string and return
		return os.str() ;
	}
}


#endif