#include <iostream>
#include "utils.h"
#include "../vrep/extApiPlatform.h"

const std::string utils::getNowTime()
{
    time_t sys_time;
    time(&sys_time);
    struct tm *p;
    p = gmtime(&sys_time);
    int year = 1900 + p->tm_year;
    int month = 1 + p->tm_mon;
    int day = p->tm_mday;
    int hour = p->tm_hour;
    int minute = p->tm_min;
    int second = p->tm_sec;
    transformUTCtoBJC(year, month, day, hour, minute, second);
    char time_str[1024];
    sprintf(time_str, "%4d/%02d/%02d/%02d:%02d:%02d", year, month, day, hour, minute, second);
    return std::string(time_str);
}

const std::vector<std::string> utils::regexSplit(const std::string &str, const std::string &delimiter)
{
    std::vector<std::string> res;
    std::string::size_type pos1, pos2;
    size_t len = str.length();
    pos2 = str.find(delimiter);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        res.emplace_back(str.substr(pos1, pos2 - pos1));
        pos1 = pos2 + delimiter.size();
        pos2 = str.find(delimiter, pos1);
    }
    if (pos1 != len)
        res.emplace_back(str.substr(pos1));
    return res;
}

void utils::sleep(int microseconds)
{
#ifdef __WIN32
    Sleep(DWORD(microseconds));
#elif __linux
    usleep(microseconds);
#endif
}

void utils::transformUTCtoBJC(int &year, int &month, int &day, int &hour, int &minute, int &second)
{
    int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 30, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) mon[2] = 29;
    else mon[2] = 28;

    hour += 8;

    if (hour == 24 && minute != 0)
    {
        day += 1;
        hour = 0;
    } else if (hour > 24)
    {
        day += 1;
        hour -= 24;
    }

    if (day > mon[month])
    {
        day -= mon[month];
        month += 1;
    }

    if (month > 12)
    {
        year += 1;
        month -= 12;
    }
}

Point utils::getObjectPosition(simxInt handle, simxInt client_id)
{
    simxFloat pos[3];
    simxGetObjectPosition(client_id, handle, -1, pos, simx_opmode_buffer);
    return Point(pos[0], pos[1], pos[2]);
}
