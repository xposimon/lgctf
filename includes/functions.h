#ifndef _functions_h
#define _functions_h
#include<cctype>
#include<cstring>
#include<algorithm>
#include<boost/regex.hpp>
#include<boost/algorithm/string.hpp>
#include<boost/algorithm/string_regex.hpp>
using namespace std;
using namespace boost;

void toLowerString(string &str);

string &ltrim(string &s);
string &rtrim(string &s);
string &Trim(string &s);
string generate_name();
string to_String(int n);
int to_Int(string num);
string urlDecode(string str);
int hex_to_dec(string hex);
int smallpow(int base, int power);
int hex_char_value(char c);

#endif // _functions_h
