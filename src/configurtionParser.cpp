#include "configurationParser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

ConfigurationParser::ConfigurationParser(string filename)
{

    fstream config_file;
    config_file.open(filename, ios::in);
    if (!config_file)
    {
        throw "Configuration file not found";
    }

    string line;
    while (getline(config_file, line))
    {
        istringstream config_line(line);
        string key;
        if (getline(config_line, key, '='))
        {
            string value;
            if (getline(config_line, value))
            {
                // remove white space
                key.erase(remove(key.begin(), key.end(), ' '), key.end());

                parametre[key] = value;
            }
        }
    }
    config_file.close();
}

ConfigurationParser::~ConfigurationParser()
{
}

bool ConfigurationParser::propertyExist(string key)
{
    return parametre.find(key) != parametre.end();
}
string ConfigurationParser::removeWhiteSpace(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}