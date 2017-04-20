#include <assert.h>
#include <iostream>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <iomanip>
#include <map>
using namespace std;
using namespace boost;

int main()
{
    vector<string> parsed_params;
    regex para_pattern("([A-Za-z0-9]+)=([A-Za-z0-9]+)");
    smatch result;
    map<string, string> para;
    string params;
    params = "?id=1&name=simon&user=xpo";
    string tmp = params;
    replace_all_regex(tmp, para_pattern, string("wahoo"));
    cout<<tmp<<endl;

}
