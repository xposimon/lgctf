#ifndef _server_h
#define _server_h
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<cstdio>
#include<map>
#include<cstring>
#include<cstdlib>
#include <unistd.h>
#include "config.h"
//#include "route.h"
using namespace std;

// Functions to deal with different routes



class server{

public:
    server(int port = DEFAULT_PORT, int ip_address = INADDR_ANY);
    ~server();
    void Listen(); // Listen to a port, and parse the raw_data in HTTP
    string get_response(string content);
	map<string, string> _GET, _POST, _REQUEST, _COOKIE, _HEADER;
	//session _SESSION;
private:
    struct sockaddr_in sockaddr;
    char buff[MAX_BUFFER];
    int socket_fd, connect_fd;
    //route _route;
};

#endif // _server_h
