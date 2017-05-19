#include "includes/database.h"

imysql::imysql()
{
    result = NULL;
}

void imysql::init()
{
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, mysql_addr, mysql_user, mysql_pass, mysql_dbname, 3306, NULL, 0))
    {
        error(string("500"), string("Cannot connect to the mysql."));
    }
}

imysql::~imysql()
{
    mysql_close(&conn);
}

void imysql::execute(string sql)
{
    mysql_query(&conn, sql.c_str());
    result = mysql_store_result(&conn);
}


int imysql::count_rows()
{
    if (result)
    return mysql_num_rows(result);
    return 0;
}


MYSQL_ROW imysql::get_next_row()
{
    return mysql_fetch_row(result);
}



