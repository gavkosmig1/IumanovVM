#pragma once

#ifndef Variable_h
#define Variable_h

#include "std_lib_facilities.h"

struct Variable
{
    string name;
    double value;

    Variable(string n, double v);
};

#endif
