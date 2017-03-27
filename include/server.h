#ifndef _server_h
#define _server_h
#define DEFAULT_PORT 80
#define DEFAULT_FAMALY AF_INET
#include<sys/socket.h>
#include<cstdio>
#include<map>
#include<cstring>

class server{
public:
    server();
    server(int port, char* ip_address);
    ~server();
    int listen();
    void (*process)();
    map<string, string> get();
    map<string, string> post();
    map<string, string> request();
    map<string, string> cookie();
    map<string, string> header();
private:
    struct sockaddr_in sockaddr;
    int socket_fd;
    char buff[4096];
    map<string, string> _GET, _POST, _REQUEST, _COOKIE, _HEADER;
};

#endif // _server_h
