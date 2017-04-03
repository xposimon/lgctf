#include<boost/regex.hpp>
#include "includes/parser.h"
#include "includes/functions.h"
using namespace std;

void parser::request_parse(string content)
{

}

void parser::init()
{
    memset(&_GET, 0, sizeof(_GET));
    memset(&_POST, 0, sizeof(_GET));
    memset(&_COOKIE, 0, sizeof(_GET));
    memset(&_REQUEST, 0, sizeof(_GET));
    memset(&_HEADER, 0, sizeof(_GET));
    memset(&_SESSION, 0, sizeof(_GET));
}

parser::parser()
{
    init();
}

parser::parser(string content)
{
    init();
    request_parse(content);
}

map<string, string> get(string env_name)
{
    toLowerString(env_name);
    switch (env_name)
    {
        case "get":
        {return _GET;break;}
        case "post":
        {return _POST;break;}
        case "request":
        {return _REQUEST;break;}
        case "header":
        {return _HEADER;break;}
        case "cookie":
        {return _COOKIE;break;}
        default:
        {
            cerr<<"Not defined environment variable!";
            return ;
        }
    }
}
