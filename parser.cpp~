#include "includes/parser.h"
#include "includes/functions.h"
using namespace std;
using namespace boost;

parser::parser()
{
    /*mem init*/
    memset(&_GET, 0, sizeof(_GET));
    memset(&_POST, 0, sizeof(_GET));
    memset(&_COOKIE, 0, sizeof(_GET));
    memset(&_REQUEST, 0, sizeof(_GET));
    memset(&_HEADER, 0, sizeof(_GET));
    
    /*pattern init*/
    pattern["method"] = "^(GET|POST|HEAD)\\s(/[A-Za-z0-9]*)(\\?(?:[A-Za-z0-9]+=?[A-Za-z0-9]+)(?:&[A-Za-z0-9]+=?[A-Za-z0-9]+)*)?\\sHTTP/(1.1|1.0|2.0)";
    pattern["header"] = "^[A-Za-z0-9\\-]+ *: *([^\\s]*)$";

}

void parser::parse_params(string method,string params)
{
    vector<string> parsed_params;
    regex para_pattern("([A-Za-z0-9]+)=([A-Za-z0-9]+)");
    smatch result;
    map<string, string> *para;

    if (method == "GET" || method == "get") para = &_GET;
    else if (method == "POST" || method == "post") para = &_POST;

    string::const_iterator start = params.begin();
    string::const_iterator end = params.end();
    while ( regex_search(start, end, result, para_pattern))
    {
        (*para)[result[1]] = result[2];
        _REQUEST[result[1]] = result[2];
        start = result[0].second;
    }

    return;
}


void parser::request_parse(string content)
{
    string params, path
    vector<string> lines;
    smatch result;
    split(lines, content, is_any_of("\n"),token_compress_on);
    vector<string>::iterator it = lines.begin();

    string request_method = trim(*it);
    re.assign(pattern["method"]);

    if (regex_match(request_method, result, re))
    {
        method = result[1];
        path = result[2];
	params = result[3];
	http_version = result[4];
	parse_params(method, params);
    }
    else
    {
        //400 bad request
    }
    
    it++;
    re.assign(pattern["header"]);
    for (; it != lines.end(); it++)
    {
        string tmp = trim(*it);
        
        if ( regex_match(tmp, result, re))
        {
            _HEADER[result[1]] = result[2];
            toLowerString(tmp=result[1]);
            if (tmp == "cookie")
            {
                _COOKIE[result[1]] = result[2];
                _REQUEST[result[1]] = result[2];
            }
        }
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
