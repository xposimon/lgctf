#include "includes/parser.h"
#include "includes/functions.h"
using namespace std;
using namespace boost;

parser::parser()
{  
    /*pattern init*/
    pattern["method"] = "^(GET|POST|HEAD)\\s(/[A-Za-z0-9\\.]*)(\\?(?:[A-Za-z0-9]+=?[A-Za-z0-9]+)(?:&[A-Za-z0-9]+=?[A-Za-z0-9]+)*)?\\sHTTP/(1.1|1.0|2.0)$";
    pattern["header"] = "^([A-Za-z0-9\\-]+) *: *([^\\s]*)$";

}

void parser::parse_params(string method,string params)
{
    vector<string> parsed_params;
    regex para_pattern("([A-Za-z0-9]+)=([A-Za-z0-9]+)");
    smatch result;
    map<string, string> *para;

    if (method == "GET") para = &_GET;
    else if (method == "POST") para = &_POST;
	else if (method == "COOKIE") para = &_COOKIE;
	
    string::const_iterator start = params.begin();
    string::const_iterator end = params.end();
    while ( regex_search(start, end, result, para_pattern))
    {
        (*para)[result[1].str()] = result[2].str();
        _REQUEST[result[1].str()] = result[2].str();
        start = result[0].second;
    }

    return;
}


void parser::request_parse(string content)
{
    string params, tmp;
    vector<string> lines;
    smatch result;
    split(lines, content, is_any_of("\n"),token_compress_on);
    vector<string>::iterator it = lines.begin();

    string request_method = trim(*it);
    re.assign(pattern["method"]);
    //cout<<request_method<<endl;

    if (regex_match(request_method, result, re))
    {
        //cout<<result[0]<<endl;
        method = result[1];
        path = result[2];
	    params = result[3];
	    http_version = result[4];
	    parse_params(string("GET"), params);

        //cout<<_GET["id"]<<endl;
    }
    else
    {
        //400 bad request
    }
    
    it++;
    re.assign(pattern["header"]);
    for (; it != lines.end(); it++)
    {
        tmp = trim(*it);
        //cout<<tmp<<endl;
        if ( regex_match(tmp, result, re))
        {
            _HEADER[result[1].str()] = result[2].str();
            toLowerString(tmp=result[1]);
            cout<<tmp<<endl;
            if (tmp == "cookie")
            {
		cout<<tmp<<endl;
                parse_params(string("COOKIE"), result[2].str());
            }
        }
        else if (method == "POST" && regex_search(tmp, result, regex("^([A-Za-z0-9]+)=([A-Za-z0-9]+)")))
        {
            parse_params(string("POST"), tmp);
        }
	}
}



map<string, string> parser::get(string env)
{
    string env_name = env;
    
    toLowerString(env_name);
    
    if (env_name == "get")return _GET;
    else if (env_name == "post")return _POST;
    else if (env_name=="request")return _REQUEST;
    else if (env_name=="header")return _HEADER;
    else if (env_name=="cookie")return _COOKIE;
    else{
            cerr<<"Not defined environment variable!";
            return _HEADER;
        }
}


