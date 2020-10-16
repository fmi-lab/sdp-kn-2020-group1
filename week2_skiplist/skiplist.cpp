#include<iostream>

struct SkipListNode {
    int data;
    SkipListNode* next;
    SkipListNode* previous;
    SkipListNode* skip;
};

void push(int element);
void member(int element);
void locate(int element);
void optimize();

// sqrt(n);
