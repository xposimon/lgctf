#!/bin/bash
g++ -std=c++11 server.cpp app.cpp functions.cpp parser.cpp session.cpp route.cpp render.cpp error.cpp includes/heap.h Log.cpp database.cpp -lboost_regex -lmysqlclient -I/usr/include/mysql/ -L/usr/lib/mysql -o app
