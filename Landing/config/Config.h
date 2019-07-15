#ifndef LANDING_CONFIG_H
#define LANDING_CONFIG_H

#include <string>
#include <mutex>
#include <map>
#include <sstream>

typedef std::map<std::string, std::map<std::string, std::string>> setting_type;

class Config
{
public:

    static setting_type readConfig(const std::string &file);

    const std::string getStringParam(const std::string &class_name, const std::string &param_name);

    const float getFloatParam(const std::string &class_name, const std::string &param_name);

    const int getIntParam(const std::string &class_name, const std::string &param_name);

    static Config *Instance();

private:
    Config(const std::string &file);
    setting_type settings;
};

template <class Type>
Type convertString(const std::string& str);

#endif //LANDING_CONFIG_H
