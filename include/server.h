#ifndef _server_h
#define _server_h
#include<sys/socket.h>
#include<cstdio>
#include<map>
#include<cstring>
#include "includes/config.h"
#include "includes/route.h"

// Functions to deal with different routes

extern map<string, string> _GET, _POST, _REQUEST, _COOKIE, _HEADER, _SESSION;

class server{

public:
    server(int port = DEFAULT_PORT, int ip_address = INADDR_ANY);
    ~server();
    void listen();

private:
    struct sockaddr_in sockaddr;
    int socket_fd;
    route _route;
};

#endif // _server_h
