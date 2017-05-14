#include "includes/functions.h"
#include<iostream>
using namespace std;

void toLowerString(string &str)
{
    transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
}

string &ltrim(string &s) 
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

string &rtrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

string &Trim(string &s)
{
    return ltrim(rtrim(s));
}

string generate_name()
{
	srand(time(NULL));
	string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFHHIJKLMNOPQRSTUVWXYZ";
	string gen = "";
	for(int i = 0; i<20; i++)
	{
		gen += characters[rand()%62];
	}
	return gen;
}

string to_String(int n)
{
    string tmp = "";
    int ca = n;
    while (ca>0)
    {
        tmp = (char)('0'+ca%10) + tmp;
        ca /= 10;
        
    }
    
    return tmp;
}


