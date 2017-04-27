#ifndef _session_h
#define _session_h
#include<cstring>
using namespace std;

class session
{
public:
	session();
	map<string ,string> & operator [](char *s);
	map<string, string> & operator [](string s);
private:
	map<string, string> cache;
}


#endif