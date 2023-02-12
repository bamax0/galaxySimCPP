#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <sstream>
#include <iostream>
#include <map>

class ConfigurationParser
{
private:
    std::map<std::string, std::string> parametre;

    std::string removeWhiteSpace(std::string str);

public:
    ConfigurationParser(std::string filename);
    ~ConfigurationParser();
    bool propertyExist(std::string key);

    template <class T>
    T getValue(std::string key)
    {
        if (propertyExist(key))
        {
            std::istringstream ss(parametre[key]);
            T num;
            ss >> num;
            return num;
        }
        return T();
    }
};

#endif