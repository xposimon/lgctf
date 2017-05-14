#include "includes/route.h"

route::route()
{
}

route::~route()
{
    for (map< string, std::function<string()>*>::iterator itr = routes.begin(); itr != routes.end(); itr++)
    {
        delete itr->second;
    }
    routes.clear();
}

string route::trace(string path)
{
    if (routes.count(path)>0)
        return (*routes[path])();
    else
    {
        return error(string("404"));
    }
}

void route::bind_path(string path, string(*dealer)())
{
    std::function<string()> *t = new std::function<string()>;
    *t = std::function<string()>(dealer);
    routes[path] = t;
}
