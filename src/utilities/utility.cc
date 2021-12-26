#include "utility.h"

namespace chem {
namespace utility {

std::vector<std::string> split_string(std::string str, const std::string& delimiter) {
    std::vector<std::string> split;

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        split.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    split.push_back(str);

    return split;
}

}  // namespace utility
}  // namespace chem
