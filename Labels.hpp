#ifndef ALPHA_LABEL_HPP
#define ALPHA_LABEL_HPP

#include <ostream>
#include <string>
#include <map>

class Labels {
private:
	std::map<std::string, std::string> _labels;

public:
	std::string addStr(const std::string&, const std::string& = "");
	void eval(std::ostream&) const;
};

#endif