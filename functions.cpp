#include "includes/functions.h"
using namespace std;

void toLowerString(string &str)
{
    transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
}
