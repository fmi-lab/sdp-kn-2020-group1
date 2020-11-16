#ifndef __STACKQUEUE__
#define __STACKQUEUE__
#include<iostream>
#include<stack>
#include<exception>

class StackQueue {
    std::stack<int> pushStack;
    std::stack<int> popStack;
    void preparePop();
    void preparePush();
    public:
    StackQueue(const StackQueue&);
    void push_back(const int&);
    void pop_front();
    int front();
    int back();
    size_t size() const;
    bool empty() const;
};
#endif