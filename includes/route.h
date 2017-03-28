#ifndef _route_h
#define _route_h
#include<cstring>
#include<functional>s
#include "parser.h"
#include "config.h"

class route
{
public:
    route();
    ~route();
    string trace(string path);
    std::function<void()> bind_path(string path);
private:
    string in_raw_data;
    string out_raw_data;
};

#endif // _route_h
