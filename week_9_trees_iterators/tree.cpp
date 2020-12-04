#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<stack>
#include<queue>

class BSTree {
    struct BTreeNode {
        int data;
        BTreeNode* left;
        BTreeNode* right;
        int height;
        BTreeNode(const int& _data, BTreeNode* _left=nullptr, BTreeNode* _right=nullptr, int _height=0): data{_data}, left{_left}, right{_right}, height{_height} {}
    };

    void addHelper(const int&, BSTree::BTreeNode*&);
    bool memberHelper(const int&, const BSTree::BTreeNode*) const;
    void removeHelper(const int&, BSTree::BTreeNode*&);
    int height_helper(const BSTree::BTreeNode*) const;
    int balance(const BSTree::BTreeNode*) const;
    void leftRotation(BSTree::BTreeNode*&);
    void rightRotation(BSTree::BTreeNode*&);
    void visualizeHelp (std::ostream& out, BTreeNode *curr) const;
    void bfsHelper(BSTree::BTreeNode*) const;
    void dfsHelper(BSTree::BTreeNode*) const;
    BTreeNode* findMinInRightSubtree(BTreeNode*);
    BTreeNode* root;

    public:
    class Iterator {
        struct IteratorWrapper{
            BTreeNode* node;
            bool shouldStop;
        };
        void unwind() {
            while(!elements.empty() && elements.top().node && !elements.top().shouldStop) {
                IteratorWrapper current = elements.top();
                elements.pop();
                if(current.node) {
                    if(current.node->right) {
                        elements.push({current.node->right, false});
                    }

                    elements.push({current.node, true});

                    if(current.node->left) {
                        elements.push({current.node->left, false});
                    }
                }
            }
        }
        std::stack<IteratorWrapper> elements;
        public:
        Iterator(BSTree::BTreeNode* _node) {
            if(_node) {
                 elements.push({nullptr, false});
            }
            elements.push({_node, false});
            unwind();
        }
        bool operator !=(const Iterator& other) {
            return elements.top().node != other.elements.top().node;
        }
        int operator*() {
            if(elements.empty()){
                throw std::runtime_error("No elements");
            }
            return elements.top().node->data;
        }

        Iterator& operator++() {
            elements.pop();
            unwind();
            return *this;
        }
    };
    BSTree(): root{nullptr} {}
    void add(const int&);
    bool member(const int&) const;
    bool empty() const;
    void remove(const int&);
    int height() const;
    void visualize(std::ostream&) const;
    void dfs() const;
    void bfs() const;
    Iterator begin() {
        return Iterator(root);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
};

void BSTree::dfs() const {
    dfsHelper(root);
}

void BSTree::bfs() const {
    bfsHelper(root);
}

void BSTree::dfsHelper(BSTree::BTreeNode* _root) const {
    struct DFSWrapper{
        BTreeNode* node;
        bool toProcess;
    };
    // left root right
    std::stack<DFSWrapper> stack;
    stack.push({_root, false});

    while (!stack.empty()){
        DFSWrapper cur = stack.top();
        stack.pop();

        if(cur.toProcess) {
            std::cout << cur.node->data;
        } else {
            if(cur.node->right) {
                stack.push({cur.node->right, false});
            }

            stack.push({cur.node, true});

            if(cur.node->left) {
                stack.push({cur.node->left, false});
            }
        }
    }
    

}

void BSTree::bfsHelper(BSTree::BTreeNode* _root) const {
    std::queue<BSTree::BTreeNode*> nodes;
	nodes.push(_root);

    while(!nodes.empty()){
        BSTree::BTreeNode* current = nodes.front();
        nodes.pop();
        std::cout << current->data << " ";

        if(current->left){
            nodes.push(current->left);
        }

        if(current->right){
            nodes.push(current->right);
        }
    }
}

int BSTree::height() const {
    return height_helper(root);
}

int BSTree::height_helper(const BSTree::BTreeNode* _root) const {
    if(!_root) {
        return -1;
    }
    return std::max(height_helper(_root->left), height_helper(_root->right)) + 1;
}

int BSTree::balance(const BSTree::BTreeNode* _root) const {
    return height_helper(_root->left) - height_helper(_root->right);
}

void BSTree::leftRotation(BSTree::BTreeNode*& _root) {
    BSTree::BTreeNode* rightChild = _root->right;
    BSTree::BTreeNode* leftGrandChild = rightChild->left;
    BSTree::BTreeNode* rootCopy = _root;
    _root = rightChild;
    _root->left = rootCopy;
    _root->left->right = leftGrandChild;
}

void BSTree::rightRotation(BSTree::BTreeNode*& _root) {
    BSTree::BTreeNode* leftChild = _root->left;
    BSTree::BTreeNode* rightGrandChild = leftChild->right;
    BSTree::BTreeNode* rootCopy = _root;
    _root = leftChild;
    _root->right = rootCopy;
    _root->right->left = rightGrandChild;
}

void BSTree::visualizeHelp (std::ostream& out, BTreeNode *curr) const{
    if (curr)
    {     
        out << (long)curr << "[label=\"" << curr->data << "\"];\n";

        if (curr->left)
        {
            out << (long)curr << "->" << (long)(curr->left) << "[color=blue];\n";
        } 
        if (curr->right)
        {
            out << (long)curr << "->" << (long)(curr->right) << "[color=red];\n";
        }
        visualizeHelp (out, curr->left);
        visualizeHelp (out, curr->right);
    }
}

void BSTree::visualize(std::ostream& out) const
{
    out << "digraph G{\n";
    visualizeHelp(out, root);
    out << "}";
}

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

void BSTree::addHelper(const int& element, BSTree::BTreeNode*& _root) {
    if (!_root) {
        _root = new BSTree::BTreeNode{element};
    } else if (element > _root->data) {
        addHelper(element, _root->right);
    } else if (element < _root->data) {
        addHelper(element, _root->left);
    }

    _root->height = std::max(height_helper(_root->left), height_helper(_root->right)) + 1;

    int rootBalance = balance(_root); // hL - hR

    if(rootBalance < -1 && element > _root->right->data) {
        //right right
        leftRotation(_root);
    }
    if(rootBalance < -1 && element < _root->right->data) {
        //right left
        rightRotation(_root->right);
        leftRotation(_root);
    }
    if(rootBalance > 1 && element < _root->left->data) {
        //left left
        rightRotation(_root);
    }
    if(rootBalance > 1 && element > _root->left->data) {
        //left right
        leftRotation(_root->left);
        rightRotation(_root);
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

namespace utils{
    std::string generateStepLogName(int stepCount) {
        std::string result = "step_";
        return (result+(char)('a'+ stepCount)+".dot");
    }
}

int main() {
    BSTree tree;
    std::vector<int> elements = {1,2,3,4,5,6,7,8,9,10};
    int step = 0;
    for( int element : elements) {
        tree.add(element);
    }
    // tree.dfs();

    // BSTree::Iterator it = tree.begin();
    // std::cout << *it << " ";
    // ++it;
    // std::cout << *it << " ";
    try{
        for(int element : tree) {
            std::cout << element << " ";
        }
    } catch() {
        
    }
}