#pragma once
#include <string>
#include <vector>

struct TextLogger {

    std::vector<std::string> gamelog;
    void glog(std::string s);
};
