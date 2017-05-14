#ifndef HEAP_H
#define HEAP_H
#include<vector>
#include<iostream>
using namespace std;

template <typename T>
class heap
{
public:
    class node
    {
    public:
        T value;
        int priority;
    };
    heap();
    int size() const;
    bool isEmpty() const;
    bool clear();
    bool enqueue(T value);
    T dequeue();
    int peek();
    bool enqueue(T value, int priority);
    void upFix(int n);
    void downFix(int n);
    vector<node> data;
};


// implementation
template<typename T>
heap<T>::heap()
{}

template<typename T>
int heap<T>::size() const
{
    return data.size();
}

template<typename T>
bool heap<T>::isEmpty() const
{
    return (data.size()==0);
}

template<typename T>
bool heap<T>::clear()
{
    data.clear();
}

template<typename T>
bool heap<T>::enqueue(T value, int priority)
{
    node tmp;
    tmp.priority = priority;
    tmp.value = value;
    data.push_back(tmp);
    upFix(data.size()-1);
    return 1;
}

template<typename T>
T heap<T>::dequeue()
{
    if (isEmpty()){cerr<<"There is no element.";exit(0);}
    T value = data[0].value;
    data[0] = data[data.size()-1];
    data.pop_back();
    downFix(0);
    return value;
}

template<typename T>
int heap<T>::peek()
{
    if (isEmpty()){cerr<<"There is no element.";exit(0);}
    return data[0].priority;
}

template<typename T>
void heap<T>::upFix(int n)
{
    int i = n, father;
    node tmp = data[n];
    while(i > 0)
    {
        father = (i-1)/2;
        if (data[father].priority > tmp.priority)
        {
            data[i] = data[father];
            i = father;
        }
        else break;
    }
    data[i] = tmp;
}

template<typename T>
void heap<T>::downFix(int n)
{
    int i = n, left, right, next;
    node tmp = data[n];
    while (1)
    {
        left = (i<<1) + 1;
        right = (i<<1) + 2;
        if (left >= data.size())break;
        else if (right >= data.size() && left < data.size())next = left;
        else next = (data[left].priority < data[right].priority)?left:right;

        if (data[next].priority <= tmp.priority)
        {
            data[i] = data[next];
            i = next;
        }
        else break;
    }
    data[i] = tmp;
}



#endif // HEAP_H
