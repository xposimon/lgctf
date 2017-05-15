#include "includes/Log.h"
#include<iostream>
using namespace std;

void Log::file_write(string path, string message)
{
    ofstream out_log;
    out_log.open(path.c_str(), ios::app);
    out_log<<message;
    out_log.close();
}

void Log::error_log(string message)
{
    string time_log;
    string tmp = string(LOG_PATH);
    string filename;
    
    time_t tt = time(NULL);
    tm* t= localtime(&tt);
    time_log = to_String(t->tm_hour) + ":" + to_String(t->tm_min) + ":" + to_String(t->tm_sec) + "\r\n"; 

    filename = to_String(t->tm_year + 1900) + "-" + to_String(t->tm_mon + 1) + "-" + to_String(t->tm_mday);
    
    file_write(tmp+"error_log/"+filename, time_log+message);
}

void Log::access_log(string message)
{
    string time_log;
    string tmp = string(LOG_PATH);
    string filename;
    
    time_t tt = time(NULL);
    tm* t= localtime(&tt);
    time_log = to_String(t->tm_hour) + ":" + to_String(t->tm_min) + ":" + to_String(t->tm_sec) + "\r\n"; 

    filename = to_String(t->tm_year + 1900) + "-" + to_String(t->tm_mon + 1) + "-" + to_String(t->tm_mday);
    
    file_write(tmp+"access_log/"+filename, time_log+message);
}
