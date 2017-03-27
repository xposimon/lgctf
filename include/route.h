#ifndef _route_h
#define _route_h
#include<cstring>
#include "includes/parser.h"
#include "includes/config.h"

typedef void(*route_function)();

class route
{
public:
    route();
    ~route();
    string trace(string path);
    route_function bind_path(string path);
private:
    string in_raw_data;
    string out_raw_data;
};

#endif // _route_h
