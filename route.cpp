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

string route::trace(string path, map<string,string> &headers)
{
    if (routes.count(path)>0)
        return (*routes[path])();
    else
    {
    // images, videos, files should be different
        regex file_pattern(".*((.js)|(.css))$");
        smatch result;
        cout<<"!!!!!!"<<path;
        if (regex_match(path, result, file_pattern))
        {
            render newrender;
            map<string,string> none;
            headers["Content-Type"]="text/plain; charset=utf-8";
            string tmp = newrender.render_from_template(string("../"+path), none);
            if (!tmp.empty()) return tmp;
        }
        return error(string("404"), path);
    }
}

void route::bind_path(string path, string(*dealer)())
{
    std::function<string()> *t = new std::function<string()>;
    *t = std::function<string()>(dealer);
    routes[path] = t;
}
