# 2017/3/29
Fix the issue that the binded port is different from the port inputed.  
It's because different endians, Ubuntu uses little-endian, so htons is needed to change port to big-endian.

# 2017/4/17
The parser to parse parameters is finished. 
Server can parse requests and send back response.  
Remove initialize of _GET, _POST, _HEADER, _REQUEST, _COOKIE. Memset will cause the removal of the map objects.  
And fix some problems with references invoke a temporary varible or a const variable.  

# 2017/4/20
Render is finished with simple replace_regex.(variable support)

# 2017/5/14
Session , error, route and log are finished. The rest job is the access_log and the logistic part.

# 2017/5/15
Fix some problems in route(trace for common file). Now the the website can be viewed without images. Database is considered to be the functions used in app.cpp.

# 2017/5/17
The session is a difficult part. The multiprocess contradicts with the sharing of session_schedule. And there is unkown pro that the session_tmp file cannot be written into 
sub dir. 

# 2017/5/21 
The first stage of the program is finished (as a homework). But there is an interest to fix the functions of the server, if relax and willing.