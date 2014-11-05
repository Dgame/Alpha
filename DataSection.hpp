#ifndef ALPHA_DATA_SECTION
#define ALPHA_DATA_SECTION

#include <string>
#include <map>
#include <iostream>

char unescape_char(char c);
std::string escape_str(const std::string&);

std::string make_unique_label();

struct DataSection {
	std::map<std::string, std::string> data_sections;

    void addDataSection(const std::string&, const std::string&);
    void writeDataSections(std::ostream&) const;
};

#endif