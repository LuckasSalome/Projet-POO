#pragma once

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Items {
public:
    virtual string getNameItem() const = 0;
    virtual string getDescItem() const = 0;
    virtual map<string, int> getStatItem() const = 0;
    virtual ~Items() = default;
};
