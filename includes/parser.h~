#ifndef _parser_h
#define _parser_h
#include<cstring>
#include<map>
#include<vector>
#include<iostream>
#include<boost/regex.hpp>
#include<boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

class parser
{
public:
    parser();
    void request_parse(string content);
    map<string, string> get(string env);
    void parse_params(string method, string params);
private:
    map<string, string> _GET, _POST, _REQUEST, _COOKIE, _HEADER;
    map<string, string> pattern;
    string method, path, http_version;
    regex re;
};

#endif // _parser_h
