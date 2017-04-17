# 2017/3/29
Fix the issue that the binded port is different from the port inputed.
It's because different endians, Ubuntu uses little-endian, so htons is needed to change port to big-endian.

# 2017/4/17
The parser to parse parameters is finished. 
Server can parse requests and send back response.
Remove initialize of _GET, _POST, _HEADER, _REQUEST, _COOKIE. Memset will cause the removal of the map objects.
And fix some problems with references invoke a temporary varible or a const variable.
