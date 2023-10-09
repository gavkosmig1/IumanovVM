#ifndef SCHEME_H
#define SCHEME_H

#include <map>
#include<iostream>
#include <string>
#include <logic_elements.h>

class Scheme{
public:
    void Read(std::istream& is)
private:
    std::map<std::string, Logic::Element> ReadScheme(std::istream& is);
}

#endif