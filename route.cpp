#include "includes/route.h"

route::route()
{
}

route::~route()
{
}

string route::trace(string path)
{
    if (map.count(path)>0)
        return (*routes[path])();
    else
    {
        // no path error
    }
}

void route::bind_path(string path, *function<string()>)
{
    if (!dealer)
        routes[path] = dealer;
    else
    {
        // null pointer error
    }
}
