#ifndef log_h
#define log_h
#include<cstring>
#include<fstream>
#include<ctime>
#include "config.h"
#include "functions.h"
using namespace std;

class Log
{
public:
    void error_log(string message);
    void access_log(string message);
};

#endif
