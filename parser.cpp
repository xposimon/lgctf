#include "includes/parser.h"
#include "includes/functions.h"
using namespace std;
using namespace boost;

parser::parser(string content)
{
    /*mem init*/
    memset(&_GET, 0, sizeof(_GET));
    memset(&_POST, 0, sizeof(_GET));
    memset(&_COOKIE, 0, sizeof(_GET));
    memset(&_REQUEST, 0, sizeof(_GET));
    memset(&_HEADER, 0, sizeof(_GET));
    memset(&_SESSION, 0, sizeof(_GET));
    
    /*pattern init*/
    pattern["method"] = "^(GET|POST|HEAD)\\s(/[A-Za-z0-9]*)(\\?(?:[A-Za-z0-9]+=?[A-Za-z0-9]+)(?:&[A-Za-z0-9]+=?[A-Za-z0-9]+)*)?\\sHTTP/(1.1|1.0|2.0)";
    pattern["header"] = "^[A-Za-z0-9\\-]+ *: *([^\\s]*)$";

    request_parse(content);
}


void parser::request_parse(string content)
{
    vector<string> lines;
    smatch result;
    split(lines, content, is_any_of("\n"),token_compress_on);
    vector<string>::iterator it = lines.begin();

    string request_method = trim(*it);
    re.assign(pattern["method"]);

    if (regex_match(request_method, result, re))
    {
        method = result[1];
        
    }
    else
    {
        //400 bad request
    }
    
    for (; it != lines.end(); it++)
    {
        
    }
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
