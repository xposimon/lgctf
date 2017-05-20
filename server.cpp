#include<iostream>
#include<cstdio>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "includes/server.h"

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
    
    config_header[string("Server")] = string("mini_server 0.1");
    config_header[string("Content-Type")] = string("text/html; charset=utf-8");
    config_header[string("Connection")] =  string("keep-alive");
    response_header = config_header;
}


server::~server()
{
    close(socket_fd);
    while(!session_schedule.isEmpty())
    {
        string filename = SESSION_PATH + session_schedule.dequeue();
        remove(filename.c_str());
    }
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
    struct sockaddr_in clientaddr;
    socklen_t sin_size = sizeof(clientaddr);
    while(1)
    {
        if ((connect_fd = accept(socket_fd, (struct sockaddr*)&clientaddr, &sin_size)) == -1)
        {
            cerr<<"Fail to accept raw_data!";
            continue;
        }
        memset(buff, 0, sizeof(buff));
        int end_position = recv(connect_fd, buff, MAX_BUFFER, 0);        
        session_manager();
	string response = get_response(string(buff)); // TODO multiprocess communication! a difficult part.
        if (!fork())
        {
            string ip_info = inet_ntoa(clientaddr.sin_addr);
            string tmp = string(buff);
            int first_line = tmp.find("\n");
            Log newlog;
            newlog.access_log(ip_info + " " + tmp.substr(0, first_line));
            
            if (send(connect_fd, response.c_str(), response.size(),0) == -1)
                cerr<<"Fail to send message!";
            close(connect_fd);
            exit(0);
        }
        buff[end_position] = '\0';
        cout<<"Receive message: \n"<<buff<<endl;
        close(connect_fd);
    }
}


void server::session_manager()
{
	if (session_schedule.isEmpty())return;
	int now = time(NULL);
        int first = session_schedule.peek();
	while(!session_schedule.isEmpty() && now > first)
	{
		string filename = SESSION_PATH + session_schedule.dequeue();
                remove(filename.c_str());
		first = session_schedule.peek();
	}
}

void server::add_response_header(string key, string value)
{
    response_header[key] = value;
}

string server::add_header(string response, string version)
{
    string tmp = "HTTP/" + version + " 200 OK\r\n";
    for (map<string, string>::iterator itr = response_header.begin(); itr != response_header.end(); itr++)
    {
        tmp += itr->first + ": " + itr->second + "\r\n";
    }
    tmp += "Content-Length: " + to_string(response.size()) + "\r\n\r\n" + response;
    return tmp;
}

void server::set_cookie(string key, string value)
{
    add_response_header(string("Set-Cookie"), key+"="+value+";");
}

string server::get_response(string content)
{
    _parser.request_parse(content);
    _GET = _parser.get("get"); _POST = _parser.get("post");
    _COOKIE = _parser.get("cookie"); _HEADER = _parser.get("header");
    _REQUEST = _parser.get("request");

    response_header = config_header;
    string response;
    response = _route.trace(_parser.path, response_header);
    return add_header(response, _parser.http_version);
}
