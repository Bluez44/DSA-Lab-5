#include<bits/stdc++.h>
using namespace std;

class SplayTree {
    struct Node {
        int val;
        Node* pLeft;
        Node* pRight;
        Node* pParent;
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr, Node* par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) { }
    };
    Node* root;

    // print the tree structure for local testing
    void printBinaryTree(string prefix, const Node* root, bool isLeft, bool hasRightSibling) {
        if (!root && isLeft && hasRightSibling) {
            cout << prefix << "├──\n";
        }
        if (!root) return;
        cout << prefix;
        if (isLeft && hasRightSibling) 
            cout << "├──";
        else 
            cout << "└──";
        cout << root->val << '\n';
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pLeft, true, root->pRight);
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pRight, false, root->pRight);
    }

    void printPreorder(Node* p) {
        if (!p) {
            return;
        }
        cout << p->val << ' ';
        printPreorder(p->pLeft);
        printPreorder(p->pRight);
    }
public:
    SplayTree() {
        root = nullptr;
    }
    ~SplayTree() {
        // Ignore deleting all nodes in the tree
    }

    void printBinaryTree() {
        printBinaryTree("", root, false, false);
    }

    void printPreorder() {
        printPreorder(root);
        cout << "\n";
    }

    void splay(Node* p) {
        // To Do
    }

    void insert(int val) {
        // To Do
    }
    void rightRotate(Node* x);
    void leftRotate(Node* x) ;
};


// write your helper functions here
void SplayTree::rightRotate(SplayTree::Node *x)
{
    Node* y = x->pLeft;
    x->pLeft = y->pRight;
   
    if (y->pRight) 
    {
        y->pRight->pParent = x;
    }
    y->pParent = x->pParent;
    
    if (!x->pParent) 
    {
        root = y;
    } 
    
    else if (x == x->pParent->pLeft) 
    {
        x->pParent->pLeft = y;
    } 
    
    else 
    {
        x->pParent->pRight = y;
    }
    y->pRight = x;
    x->pParent = y;
}

void SplayTree::leftRotate(SplayTree::Node *x)
{
    Node* y = x->pRight;
    x->pRight = y->pLeft;
    
    if (y->pLeft) 
    {
        y->pLeft->pParent = x;
    }
    y->pParent = x->pParent;
    
    if (!x->pParent) 
    {
        root = y;
    } 
    
    else if (x == x->pParent->pLeft) 
    {
        x->pParent->pLeft = y;
    } 
    
    else 
    {
        x->pParent->pRight = y;
    }
    y->pLeft = x;
    x->pParent = y;
}

void SplayTree::splay(SplayTree::Node *p)
{
    while (p->pParent) 
    {
        Node* parent = p->pParent;
        Node* grandparent = parent->pParent;

        if (!grandparent) 
        {
            //Zig step
            if (p == parent->pLeft) 
            {
                rightRotate(parent);
            } 
            
            else 
            {
                leftRotate(parent);
            }
            
        } 
        
        else 
        {
            // Zig-zig or Zig-zag step
            if (p == parent->pLeft && parent == grandparent->pLeft) 
            {
                rightRotate(grandparent);
                rightRotate(parent);
            } 
            
            else if (p == parent->pRight && parent == grandparent->pRight) 
            {
                leftRotate(grandparent);
                leftRotate(parent);
            } 
            
            else 
            {
                // Zig-zag step
                if (p == parent->pLeft) 
                {
                    rightRotate(parent);
                    leftRotate(grandparent);
                } 
                
                else 
                {
                    leftRotate(parent);
                    rightRotate(grandparent);
                }
            }
        }
    }
    root = p;
}

void SplayTree::insert(int val) 
{
    if (!root) 
    {
        root = new Node(val);
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current) 
    {
        parent = current;
        if (val < current->val) 
        {
            current = current->pLeft;
        } 
        
        else 
        {
            current = current->pRight;
        }
    }

    Node* newNode = new Node(val, nullptr, nullptr, parent);
    if (val < parent->val) 
    {
        parent->pLeft = newNode;
    } 
    
    else 
    {
        parent->pRight = newNode;
    }
    splay(newNode);
}