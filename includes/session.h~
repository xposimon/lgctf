#ifndef _session_h
#define _session_h
#include<cstring>
#include<fstream>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include "heap.h"
#include "functions.h"
#include "config.h"
#include<boost/regex.hpp>
#include<boost/algorithm/string.hpp>
using namespace std;
using namespace boost;
typedef map<string, string> mss;

class session
{
public:
	session();
	void load(string session_id);
	void save(string session_id, heap<string> &schedule, int expire_time = 60);
	string newSession();
	string serialize(mss &session_map);
	mss unserialize(string &content);
	string & operator [](char *s);
	string & operator [](string s);
private:
	mss cache;
        string no_element;
};


#endif
