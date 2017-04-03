#ifndef _parser_h
#define _parser_h
#include<cstring>
#include<map>
using namespace std;

class parser
{
public:
    parser();
    parser(string content);
    void request_parse(string content);
    void init();
    map<string, string> get(string env_name);
private:
    map<string, string> _GET, _POST, _REQUEST, _COOKIE, _HEADER;
};

#endif // _parser_h
