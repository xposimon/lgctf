#include "includes/server.h"

server app;

bool checkLogin()
{
    if (app._COOKIE.find(string("sessionid"))!=app._COOKIE.end())
    {
        if (app.session_schedule.find(app._COOKIE[string("sessionid")]))
        {
            app._SESSION.load(app._COOKIE[string("sessionid")]);
            cout<<app._SESSION[string("test")];
            return true;
        }
    }
    return false;
}

string index()
{
    map<string,string> none;
    if(!checkLogin())
    {
        render newrender;
        return newrender.render_from_template(string("login.html"), none);//state 302 is standard
    }
    render newrender;
    return newrender.render_from_template(string("index.html"), none);
}

int main()
{
    
    app._route.bind_path(string("/"), index);
    app._route.bind_path(string("/index"), index);
    app.Listen();
    return 0;
}
