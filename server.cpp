#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include "includes/server.h"
#include "includes/parser.h"

server::server(int port, int ip_address){

    // Create socket
    if ((socket_fd = socket(DEFAULT_FAMILY, SOCK_STREAM, 0)) == -1)
    {
        cerr<<"Fail to create sockets!";
        exit(0);
    }

    memset(&sockaddr, 0, sizeof(sockaddr));
    // Initialize IP address
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr.sin_port = htons(12345);

    // Bind socket with address
    if (bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1)
    {
        cerr<<"Fail to bind socket with address!";
        exit(0);
    }
}


server::~server()
{
    close(socket_fd);
}


void server::Listen()
{
    if (listen(socket_fd, MAX_CONNECTIONS) == -1)
    {
        cerr<<"Fail to listen!";
        exit(0);
    }
    cout<<socket_fd;
    cout<<"The server is running, listening on port: "<<ntohs(sockaddr.sin_port)<<endl;

    while(1)
    {
        if ((connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1)
        {
            cerr<<"Fail to accept raw_data!";
            continue;
        }
        
        int end_position = recv(connect_fd, buff, MAX_BUFFER, 0);
        string response = get_response(string(buff));
        //cout<<"The answer len is: "<<response.size()<<endl; 
        if (!fork())
        {
            if (send(connect_fd, response.c_str(), response.size()+1,0) == -1)
                cerr<<"Fail to send message!";
            close(connect_fd);
            exit(0);
        }
        buff[end_position] = '\0';
        cout<<"Receive message: \n"<<buff<<endl;
        close(connect_fd);
    }
}


string server::get_response(string content)
{
    parser server_parser;
    string answer = "The response of get['id'] is: ";

    server_parser.request_parse(content);
    answer += server_parser.get(string("get"))["id"]; 
    
    return answer; 
}
