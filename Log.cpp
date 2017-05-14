#include "includes/Log.h"
#include<iostream>
using namespace std;

void Log::error_log(string message)
{
    string time_log;
    string tmp = string(LOG_PATH);
    string filename;
    ofstream out_log;
    time_t tt = time(NULL);
    tm* t= localtime(&tt);
    time_log = to_String(t->tm_hour) + ":" + to_String(t->tm_min) + ":" + to_String(t->tm_sec) + "\r\n"; 

    filename = to_String(t->tm_year + 1900) + "-" + to_String(t->tm_mon + 1) + "-" + to_String(t->tm_mday);
    out_log.open((tmp + filename).c_str(), ios::app);
    out_log<<time_log<<message;
    out_log.close();
}

void Log::access_log(string message)
{

}
