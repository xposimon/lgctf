#include "includes/database.h"

imysql::imysql()
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, mysql_addr, mysql_user, mysql_pass, mysql_dbname, mysql_port, NULL, 0))
    {
        error(string("500"), string("Cannot connect to the mysql."));
    }
}

imysql::~imysql()
{
    mysql_close(conn);
}


