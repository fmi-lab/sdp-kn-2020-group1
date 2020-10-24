#include<iostream>
#include<vector>

template<class T>
class Stack {
    std::vector<T> container;
    size_t topOfStack;
    public:
    void push(const T& element);
    void pop();
    size_t size() const;
    bool empty() const;
    T top() const;
};


template<class T>
void Stack<T>::push(const T& element) {
    container.push_back(element);
    topOfStack++;
}

template<class T>
void Stack<T>::pop() {
    if (!container.empty()) {
        topOfStack--;
        container.pop_back();
    }
}

template<class T>
size_t Stack<T>::size() const {
    return container.size();
}

template<class T>
bool Stack<T>::empty() const {
    return container.empty();
}

template<class T>
T Stack<T>::top() const {
    container[topOfStack];
}
