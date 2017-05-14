#include "includes/server.h"

string index()
{
    return "Hello, visitor!";
}

int main()
{
    server app;
    app._route.bind_path(string("/index"), index);
    app.Listen();
    return 0;
}
