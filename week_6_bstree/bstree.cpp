#include "bstree.h"

bool BSTree::empty() const {
    return !root;
}

bool BSTree::member(const int& element) const {
    return memberHelper(element, root);
}

bool BSTree::memberHelper(const int& element, const BSTree::BTreeNode* _root) const {
    if (empty()) {
        return false;
    }

    if (element > _root->data) {
        return memberHelper(element, _root->right);
    }

    if (element < _root->data) {
        return memberHelper(element, _root->left);
    }

    return true;
}

void BSTree::add(const int& element) {
    addHelper(element, root);
}

void BSTree::addHelper(const int& element, BTreeNode*& _root) {
    if (!_root) {
        _root = new BTreeNode{element}; 
        return;
    }
    if (element > _root->data) {
        addHelper(element, _root->right);
    } else if (element < _root->data) {
        addHelper(element, _root->left);
    }

}

void BSTree::remove(const int& element) {
    removeHelper(element, root);
}

void BSTree::removeHelper(const int& element, BTreeNode*& _root) {
    if (!_root) {
        return;
    }
    if (element < _root->data) {
        removeHelper(element, _root->left);
    }

    if (element > _root->data) {
        removeHelper(element, _root->right);
    }

    if (element == _root->data) {
        if (!_root->left && !_root->right) {
            BTreeNode* save = _root;
            _root = nullptr;
            delete save;
        }
        if (!_root->left && _root->right) {
            BTreeNode* save = _root;
            _root = _root->right;
            delete save;
        }
        if (_root->left && !_root->right) {
            BTreeNode* save = _root;
            _root = _root->left;
            delete save;
        } else {
            BTreeNode* minRightNode = findMinInRightSubtree(_root->right);
            std::swap(_root->data, minRightNode->data);
            removeHelper(element, _root->right);
        }
    }
}

BSTree::BTreeNode* BSTree::findMinInRightSubtree(BSTree::BTreeNode* _root) {
    while(_root->left) {
        _root = _root->left;
    }
    return _root;
}