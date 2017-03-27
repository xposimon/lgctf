#include "includes/server.h"
#include<iostream>
#include<sys/socket>

server::server(int port, int ip_address){

    // Create socket
    if ((socket_fd = socket(DEFAULT_FAMILY, SOCK_STREAM, 0)) == -1)
    {
        cerr<<"Fail to create sockets!";
        exit(0);
    }

    /* Initialize memory*/
    memset(sockaddr, 0, sizeof(sockaddr));
    memset(_GET, 0, sizeof(_GET));
    memset(_POST, 0, sizeof(_GET));
    memset(_COOKIE, 0, sizeof(_GET));
    memset(_REQUEST, 0, sizeof(_GET));
    memset(_HEADER, 0, sizeof(_GET));
    memset(_SESSION, 0, sizeof(_GET));

    // Initialize IP address
    sockaddr.sin_family = DEFAULT_FAMILY;
    sockaddr.sin_addr.s_addr = htonl(ip_address);
    sockaddr.sin_port = port;

    // Bind socket with address
    if (bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1)
    {
        cerr<<"Fail to bind socket with address!";
        exit(0);
    }
}

void server::listen()
{
    if (listen(socket_fd, MAX_CONNECTIONS) == -1)
    {
        cerr<<"Fail to listen!";
        exit(0);
    }
    cout<<"The server is running, listening on port: "<<port<<endl;

}
