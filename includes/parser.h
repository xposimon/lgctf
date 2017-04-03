#ifndef _parser_h
#define _parser_h
#include<cstring>
#include<map>
#include<vector>
#include<boost/regex.hpp>
#include<boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

class parser
{
public:
    parser();
    parser(string content);
    void request_parse(string content);
    map<string, string> get(string env_name);
private:
    map<string, string> _GET, _POST, _REQUEST, _COOKIE, _HEADER;
    map<string, string> pattern;
    string method;
    regex re;
};

#endif // _parser_h
