#include "txtlogger.h"


void TextLogger::glog(std::string s) {
    gamelog.push_back(s);
}
