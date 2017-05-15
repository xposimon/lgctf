#include "includes/server.h"

string index()
{
    map<string,string> none;
    render newrender;
    return newrender.render_from_template(string("index.html"), none);
}

int main()
{
    server app;
    app._route.bind_path(string("/"), index);
    app._route.bind_path(string("/index"), index);
    app.Listen();
    return 0;
}
