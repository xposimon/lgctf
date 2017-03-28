# 2017/3/29
Fix the issue that the binded port is different from the port inputed.
It's because different endians, Ubuntu uses little-endian, so htons is needed to change port to big-endian.
