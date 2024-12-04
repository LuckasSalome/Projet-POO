#pragma once

#include <string>
#include <map>

class Entity {
public : 
    virtual std::string getName() = 0;
    virtual std::string getDesc() = 0;
    virtual std::map<std::string, int> getStat() = 0;
    virtual bool getAlive() = 0;

};