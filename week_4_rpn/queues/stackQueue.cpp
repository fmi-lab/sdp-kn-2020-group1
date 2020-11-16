#include "stackQueue.h"

StackQueue::StackQueue(const StackQueue& other): pushStack{other.pushStack}, popStack{other.popStack} {
    // std::stack<int> otherPop{other.popStack};
    // std::stack<int> otherPush{other.pushStack};
    // while(!otherPop.empty()) {
    //     pushStack.push(otherPop.top());
    //     otherPop.pop();
    // }
    // while(!otherPush.empty()) {
    //     pushStack.push(otherPush.top());
    //     otherPush.pop();
    // }
}

void StackQueue::push_back(const int& element) {
    pushStack.push(element);
}

void StackQueue::preparePop() {
    if (popStack.empty()) {
        while(!pushStack.empty()) {
            popStack.push(pushStack.top());
            pushStack.pop();
        }
    }
}

void StackQueue::preparePush() {
    if (pushStack.empty()) {
        while(!popStack.empty()) {
            pushStack.push(popStack.top());
            popStack.pop();
        }
    }
}

void StackQueue::pop_front() {
    preparePop();
    popStack.pop();
}

int StackQueue::front() {
    if (empty()) {
        throw std::runtime_error("No elements!");
    }
    preparePop();
    return popStack.top();
}

int StackQueue::back() {
    if (empty()) {
        throw std::runtime_error("No elements!");
    }
    preparePush();
    return pushStack.top();
}

size_t StackQueue::size() const {
    return pushStack.size() + popStack.size();
}

bool StackQueue::empty() const {
    return pushStack.empty() && popStack.empty();
}