#include "DataSection.hpp"
#include "types.hpp"
#include "util.hpp"

char unescape_char(char c) {
    switch (c) {
        case 'n':
            return '\n';
        case 't':
            return '\t';
        case '\\':
            return '\\';
        case '\"':
            return '\"';
    }

    std::cerr << "Unknown escape sequence \\" << c << std::endl;

    return c;
}

std::string escape_str(const std::string& in) {
    std::string out;
    for(u32_t i = 0; i < in.length(); i++) {
        switch (in[i]) {
            case '\n':
                out += "\\n";
            break;
            case '\t':
                out += "\\t";
            break;
            case '\\':
                out += "\\\\";
            break;
            default:
                out += in[i];
        }
    }

    return out;
}

std::string make_unique_label(std::string prefix) {
    static u32_t label_num = 0;

    label_num += 1;
    prefix = prefix + ((label_num < 10) ? "_0" : "_");

    return "L" + prefix + std::to_string(label_num);
}

void DataSection::addDataSection(const std::string& label, const std::string& data) {
    this->data_sections.insert(std::make_pair(label, data));
}

void DataSection::writeDataSections(std::ostream& out) const {
    out << ".data" << std::endl;
    for (auto& pair : this->data_sections) {
        out << "\t" << pair.first << ':';
        out << "\t.ascii \"" << pair.second << "\\0\"" << std::endl;
    }
}