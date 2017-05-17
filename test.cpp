#include<cstring>
#include<iostream>
#include<fstream>
#include<boost/regex.hpp>
#include<boost/algorithm/string.hpp>
#include<cstring>
#include<map>
using namespace std;
using namespace boost;
int main(){
    string content = "{\"test\":\"123\"}";
regex para_pattern("{\"([A-Za-z0-9_]+)\":\"([A-Za-z0-9_]+)\"}");
    smatch result;
    map<string,string> para;

    string::const_iterator start = content.begin();
    string::const_iterator end = content.end();
    cout<<content;
    while ( regex_search(start, end, result, para_pattern))
    {
        cout<<result[0];
        para[result[1].str()] = result[2].str();
        start = result[0].second;
    }
}
