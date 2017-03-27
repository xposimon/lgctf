#include<cstdio>
#include<iostream>
#include<map>
#include<cstring>
#include<functional>
using namespace std;
class A;


class A{
public:
    A(){
        a = 10;
    }
    int a;
    std::function<void()> test;
    std::function<void()> bind_path(string name){
        return [=]{cout<<name;};
    }
};


int main(){
    A atest;
    atest.test = atest.bind_path((string)"yes!");
    atest.test();
    return 0;
}
