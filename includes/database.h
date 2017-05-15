#ifndef database_h
#define database_h
#include<iostream>
#include<vector>
#include<mysql.h>
#include "config.h"
#include "error.h"
using namespace std;

class imysql
{
public: 
    imysql();
    ~imysql();

private:
    MYSQL *conn;
}


#endif
