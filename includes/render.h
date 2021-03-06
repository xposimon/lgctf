#ifndef _render_h
#define _render_h
#include<cstring>
#include<map>
#include<iostream>
#include<fstream>
#include<boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>
#include "config.h"

using namespace std;
using namespace boost;

class render
{
public:
    render();
    ~render();
    string &render_from_string(string &content, map<string, string> param);
    string render_from_template(string temp_name, map<string, string> param);
private:
    map<string, string> temp_pattern;
};

#endif // _render_h
