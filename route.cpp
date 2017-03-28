#include<string.h>
#include<functional>
#include "includes/route.h"
using namespace std;

route::route()
{
    memset(in_raw_data, 0, sizeof(in_raw_data));
    memset(out_raw_data, 0, sizeof(out_raw_data));
}

route::~route()
{
}

function<void()> route::trace(string path)
{

}
