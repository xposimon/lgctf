#include "includes/functions.h"
using namespace std;

void toLowerString(string &str)
{
    transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
}

string &ltrim(string &s) 
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

string &rtrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

string &trim(string &s)
{
    return ltrim(rtrim(s));
}

