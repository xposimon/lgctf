#include "includes/error.h"
#include<iostream>
using namespace std;
string error(string state, string message)
{
    cout<<"An error occurs! The state is "<<state<<endl;
    string tmp = "State: " + state + "\r\n";
    if (message.size()!=0) tmp += message + "\r\n";
    tmp += "\r\n";
  
    Log Error_log;
    Error_log.error_log(tmp);
  
    render nrend;
    map<string, string> none;
    return nrend.render_from_template(string(TEMPLATE_PATH + state), none);
}
