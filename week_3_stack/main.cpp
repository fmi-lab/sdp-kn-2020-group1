#include <iostream>
#include <stack>
#include <string>

int fibb(int n)
{
    if (n <= 2)
    {
        return 1;
    }
    return fibb(n - 1) + fibb(n - 2);
}

int fibbIter(int n)
{
    std::stack<int> s;
    s.push(1);
    s.push(1);
    while (n > 2)
    {
        int second = s.top();
        s.pop();
        int first = s.top();
        s.pop();
        s.push(second);
        s.push(first + second);
        n--;
    }
    return s.top();
}

struct State
{
    int last;
    int previous;
    int iterNum;
};

int fibIterState(int n)
{
    std::stack<State> s;
    s.push({1, 0, 1});
    while (n > 1)
    {
        auto [last, previous, iterNum] = s.top();
        s.pop();
        s.push({(last + previous), last, iterNum++});
        n--;
    }
    return s.top().last;
}
// 1 1 2 3 5
int main()
{

    std::string res = "asdf";
    for(char element : res) {
        std::cout << element << " ";
    }
    // std::cout << fibb(5);
    // std::cout << fibbIter(5);
    std::cout << fibIterState(5);
}