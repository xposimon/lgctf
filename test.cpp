#include<cstring>
#include<iostream>
#include<fstream>
#include<boost/regex.hpp>
#include<cstring>
#include<iostream>
using namespace std;

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

int main(){
    
    string test="40";
    cout<<hex_to_dec(test);
}
