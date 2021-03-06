#ifndef database_h
#define database_h
#include<iostream>
#include<vector>
#include<mysql.h>
#include "config.h"
#include "error.h"
#include "functions.h"
using namespace std;

class imysql
{
public: 
    imysql();
    ~imysql();
    void init();
    void execute(string sql);
    int count_rows();
    MYSQL_ROW get_next_row();
private:
    MYSQL conn;
    MYSQL_RES *result;
};


#endif
