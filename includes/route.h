#ifndef _route_h
#define _route_h
#include<cstring>
#include<functional>
#include<map>
#include "parser.h"
#include "config.h"
#include "error.h"
#include<boost/regex.hpp>
#include<boost/algorithm/string.hpp>
using namespace boost;
using namespace std;

class route
{
public:
    route();
    ~route();
    string trace(string path, map<string,string> &headers);
    // routes function can only be string function(), (return string, no parameters)
    void bind_path(string path, string(*dealer)());
private:
    string in_raw_data;
    string out_raw_data;
    map< string, std::function<string()>*> routes;
};

#endif // _route_h
