#include <iostream>
#include <math.h>
#include <queue>
using namespace std;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    void remove(const T &value)
    {
        //TODO
    }

    Node* deleteRightBalance(Node* &root, bool &shorter);
    Node* deleteLeftBalance(Node* &root, bool &shorter);
    Node* AVLDelete(Node* &root, T value, bool &shorter, bool &success);

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};


//Helping functions
template<class T> AVLTree<T>::Node *AVLTree<T>::deleteRightBalance(AVLTree<T>::Node *&root, bool &shorter)
{
    if (root->balance == LH)
    {
        root -> balance = EH;
    }
    else if (root->balance == EH)
    {
        root->balance = RH;
        shorter = false;
    }
    else 
    {
        Node* rightTree = root->pRight;
        if (rightTree->balance == LH)
        {
            Node* leftTree = rightTree->pLeft;
            if (leftTree -> balance == LH)
            {
                rightTree->balance = RH;
                root->balance = EH;
            }
            else if (leftTree->balance == EH)
            {
                root->balance = LH;
                rightTree -> balance = EH;
            }
            else 
            {
                root->balance = LH;
                rightTree -> balance = EH;
            }
            leftTree -> balance = EH;
            root -> pRight = rotateRight(rightTree);
            root = rotateLeft(root);
        }
        else 
        {
            if (rightTree->balance != EH)
            {
                root->balance = EH;
                rightTree->balance = EH;
            }
            else 
            {
                root -> balance = RH;
                rightTree->balance = LH;
                shorter = false;
            }
            root = rotateLeft(root);
        }
    }
    return root;
}
template<class T> AVLTree<T>::Node *AVLTree<T>::deleteLeftBalance(AVLTree<T>::Node *&root, bool &shorter)
{
    if (root->balance == RH) root->balance = EH;
    else if (root->balance == EH)
    {
        root -> balance = LH;
        shorter = false;
    }
    else 
    {
        Node* leftTree = root->pLeft;
        if (leftTree -> balance == RH)
        {
            Node* rightTree = leftTree -> pRight;
            if (rightTree -> balance == RH)
            {
                leftTree->balance = LH;
                root->balance = EH;
            }
            else if (rightTree -> balance == EH)
            {
                root->balance = RH;
                leftTree->balance = EH;
            }
            else 
            {
                root->balance = RH;
                leftTree->balance = EH;
            }
            rightTree -> balance = EH;
            root->pLeft = rotateLeft(leftTree);
            root = rotateRight(root);
        }
        else 
        {
            if (leftTree -> balance != EH)
            {
                root->balance = EH;
                leftTree -> balance = EH;
            }
            else 
            {
                root->balance = LH;
                leftTree -> balance = RH;
                shorter = false;
            }
            root = rotateRight(root);
        }
    }
    return root;
}
template<class T> AVLTree<T>::Node *AVLTree<T>::AVLDelete(AVLTree<T>::Node *&root, T value, bool &shorter, bool &success)
{
    if (!root)
    {
        shorter = false;
        success = false;
        return nullptr;
    }
    if (value < root -> data)
    {
        root -> pLeft = AVLDelete(root->pLeft, value, shorter, success);
        if (shorter) root = deleteRightBalance(root, shorter);
    }
    else if (value > root->data)
    {
        root->pRight = AVLDelete(root->pRight, value, shorter, success);
        if (shorter) root = deleteLeftBalance(root, shorter);
    }
    else 
    {
        Node* deleteNode = root;
        if (!root -> pRight)
        {
            Node* newRoot = root->pLeft;
            success = true;
            shorter = true;
            delete deleteNode;
            return newRoot;
        }
        else if (!root->pLeft)
        {
            Node* newRoot = root->pRight;
            success = true;
            shorter = true;
            delete deleteNode;
            return newRoot;
        }
        else 
        {
            Node* exchPtr = root->pLeft;
            while(exchPtr->pRight)
            {
                exchPtr = exchPtr -> pRight;
            }
            root -> data = exchPtr->data;
            root->pLeft = AVLDelete(root->pLeft, exchPtr->data, shorter, success);
            if (shorter) root = deleteRightBalance(root,shorter);
        }
    }
    return root;
}
template<class T> inline void AVLTree<T>::remove(const T &value){
    //TODO
    T val = value;
    bool shorter = false;
    bool success = false;
    this->root = AVLDelete(this->root, val, shorter, success);
    
}

