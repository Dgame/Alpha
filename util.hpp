#ifndef ALPHA_UTIL_HPP
#define ALPHA_UTIL_HPP

#include <string>
#include <sstream>

namespace std {
	template <typename T>
	inline std::string to_string(const T& value) {
		//create an output string stream
		std::ostringstream os ;
		//throw the value into the string stream
		os << value ;
		//convert the string stream into a string and return
		return os.str() ;
	}
}

namespace out {
	template <typename T>
	void print(std::ostream& out, const T& value) {
		out << value << std::endl;
	}
	 
	template <typename T, typename... Args>
	void print(std::ostream& out, const T& value, Args&& ...args) {
	    out << value;
	    print(out, args...);
	}
}

#endif