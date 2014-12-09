#include "Labels.hpp"
#include <sstream>

std::string Labels::addStr(const std::string& str, const std::string& prefix) {
    std::stringstream buf;
    buf << 'L' << '_' << _labels.size() << '_' << prefix;

    const std::string label = buf.str();
    _labels[label] = str;

    return label;
}

void Labels::eval(std::ostream& out) const {
    for (auto& pair : _labels) {
        out << pair.first << ':' << std::endl;
        out << "\t.ascii\t\"" << pair.second << "\\0\"" << std::endl;
    }
}