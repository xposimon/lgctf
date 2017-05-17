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
#include "heap.h"
#include "session.h"
#include "parser.h"
#include "render.h"
#include "route.h"
#include "Log.h"
using namespace std;

// Functions to deal with different routes

class server{

public:
    server(int port = DEFAULT_PORT, int ip_address = INADDR_ANY);
    ~server();
    void Listen(); // Listen to a port, and parse the raw_data in HTTP
	void session_manager(); // Manage the life period of sessions
    string get_response(string content);
    void add_response_header(string key, string value);
	map<string, string> _GET, _POST, _REQUEST, _COOKIE, _HEADER;
	session _SESSION;
	heap<string> session_schedule;
	route _route;
private:
    struct sockaddr_in sockaddr;
    char buff[MAX_BUFFER];
    int socket_fd, connect_fd;
    parser _parser;
    map<string, string> response_header, config_header;
    string add_header(string response, string version);
};

#endif // _server_h
