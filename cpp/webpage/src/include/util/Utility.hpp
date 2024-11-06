#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>

namespace Utility{

    static inline bool ends_with(std::string const & value, std::string const & ending){
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    static std::string readFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file) return "";
        return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
    }

};

#endif