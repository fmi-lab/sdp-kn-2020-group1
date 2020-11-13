#ifndef __BSTREE__
#define __BSTREE__
#include<iostream>

class BSTree {
    struct BTreeNode {
        int data;
        BTreeNode* left;
        BTreeNode* right;
        BTreeNode(const int& _data, BTreeNode* _left=nullptr, BTreeNode* _right=nullptr):data{_data}, left{_left}, right{_right} {}
    };

    void addHelper(const int&, BSTree::BTreeNode*&);
    bool memberHelper(const int&, const BSTree::BTreeNode*) const;
    void removeHelper(const int&, BSTree::BTreeNode*&);
    BTreeNode* findMinInRightSubtree(BTreeNode*);
    BTreeNode* root;

    public:
    BSTree(): root{nullptr} {}
    void add(const int&);
    bool member(const int&) const;
    bool empty() const;
    void remove(const int&);
};

#endif