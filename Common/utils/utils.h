#ifndef LANDING_UTILS_H
#define LANDING_UTILS_H

#include <string>
#include <vector>
#include <regex>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include "Point.h"
#elif defined (__linux) || defined (__APPLE__)
#include <signal.h>
#include <unistd.h>

#endif
namespace utils
{
    const std::string getNowTime();
    const std::vector<std::string> regexSplit(const std::string &str, const std::string &delimiter);
    void sleep(int microseconds);
    void transformUTCtoBJC(int &year, int &month, int &day, int &hour, int &minute, int &second);
    Point getObjectPosition(simxInt handle, simxInt client_id);
};


#endif //LANDING_UTILS_H
