#include "utils.h"
#include <windows.h>
const std::string utils::getNowTime()
{
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    char time[1024];
    sprintf(time, "%4d/%02d/%02d/%02d:%02d:%02d",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond);
    return std::string(time);
}
