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

int to_Int(string num)
{
    int tmp = 0;
    int _size = num.size();
    for (int i = 0; i < _size; i++)
    {
        tmp += num[i]-'0';
        if (i != _size-1) tmp *= 10;
    }
    return tmp;
}

int hex_char_value(char c)     
{     
    if(c >= '0' && c <= '9')     
        return c - '0';     
    else if(c >= 'a' && c <= 'f')     
        return (c - 'a' + 10);     
    else if(c >= 'A' && c <= 'F')     
        return (c - 'A' + 10);     
    assert(0);     
    return 0;     
}     

int smallpow(int base, int power)
{
    int tmp = 1;
    int count = power;
    while ( power-- > 0)
    {
        tmp *= base;
    }
    return tmp;
}

int hex_to_dec(string hex)     
{     
    int result = 0;     
    int len = hex.size();
    for(int i = 0; i < len; i++)     
    {     
        result += smallpow(16, len-i-1) * hex_char_value(hex[i]);     
    }     
    return result;     
}   

string urlDecode(string str)
{
    string decoded = str;
    
    regex para_pattern("%([\\dA-Fa-f]{2})");
    regex replace;
    replace.assign("\\+");
    string t = " ";
    replace_all_regex(decoded, replace, t);
    smatch result;
    string::const_iterator start = str.begin();
    string::const_iterator end = str.end();
    while ( regex_search(start, end, result, para_pattern))
    {
        int code = hex_to_dec(result[1].str());
        char tmp = char(code);
        string to_replace = "";
        to_replace += tmp;
        
        replace.assign("%"+result[1].str());
        replace_all_regex(decoded, replace, to_replace);
        start = result[0].second;
    }
    return decoded;
}

