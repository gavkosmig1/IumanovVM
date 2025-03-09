#pragma once

#include "std_lib_facilities.h"
#include <algorithm>
#include <map>
#include <sstream>

void ThrowEmptyStringError ();

void ThrowBadFormatError (const string& val);

void ThrowOutOfRangeOrBadFormatError (const string& val);

void ThrowBadConversionError (const string& romeVal, const unsigned correctVal, unsigned conversionResult);

const unsigned BAD_VALUE = (unsigned)-1;
typedef pair<string, unsigned> RomeDecPair;
typedef map<string, unsigned> Table;
Table g_table;

void InitTables ();

bool StartsWith (const string& romeVal, const string& pattern);

string GetFirstRomeValue (const string& romeVal);

unsigned RomeToDec (const string& romeVal);

void CheckConversion (const RomeDecPair& test);