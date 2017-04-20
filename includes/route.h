#ifndef _route_h
#define _route_h
#include<cstring>
#include<functional>
#include "parser.h"
#include "config.h"
using namespace std;

class route
{
public:
    route();
    ~route();
    string trace(string path);
    // routes function can only be string function(), (return string, no parameters)
    void bind_path(string path, *function<string()> dealer);
private:
    string in_raw_data;
    string out_raw_data;
    map< string, *function<string()> > routes;
};

#endif // _route_h
