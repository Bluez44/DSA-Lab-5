#include <bits/stdc++.h>
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

    void insert(const T &value)
    {
        //TODO
    }
    
    Node* rotateRight(Node* &root);
    Node* rotateLeft(Node* &root);
    Node* leftBalance(Node* &root, bool &taller);
    Node* rightBalance(Node* &root, bool &taller);
    Node* AVLInsert(Node* &root, T value, bool &taller);
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
template<class T> AVLTree<T>::Node *AVLTree<T>::rotateRight(AVLTree<T>::Node *&root)
{
    Node* newRoot = root->pLeft;
    if (!newRoot->pRight)
    {
        root->pLeft = NULL;
        newRoot->pRight = root;
    }
    else 
    {
        root->pLeft = newRoot->pRight;
        newRoot->pRight = root;
    }
    root = newRoot;
    return root;
}
template<class T> AVLTree<T>::Node *AVLTree<T>::rotateLeft(AVLTree<T>::Node *&root)
{
    Node* newRoot = root->pRight;
    if (!newRoot->pLeft)
    {
        root->pRight = NULL;
        newRoot->pLeft = root;
    }
    else
    {
        root -> pRight = newRoot-> pLeft;
        newRoot -> pLeft = root;
    }
    root = newRoot;
    return root;
}
template<class T> AVLTree<T>::Node *AVLTree<T>::leftBalance(AVLTree<T>::Node *&root, bool &taller)
{

    // Case 1: left of left
    if (root->pLeft -> balance == LH)
    {
        root = rotateRight(root);
        root->balance = EH;
        root -> pRight -> balance = EH;
        taller = false;
    }
    
    // Case 2: right of left
    else if (root->pLeft->balance == RH) 
    {
        root->pLeft = rotateLeft(root->pLeft);
        root = rotateRight(root);

        if (root->balance == LH)
        {
            root->balance = EH;
            root->pLeft->balance = EH;
            root->pRight->balance = RH;
        }
        else if (root->balance == EH)
        {
            root->pLeft->balance = EH;
            root->pRight -> balance = EH;
        }
        else 
        {
            root->balance = EH;
            root->pLeft->balance = LH;
            root->pRight->balance = EH;
        }
        taller = false;
    }
    return root;
}
template<class T> AVLTree<T>::Node *AVLTree<T>::rightBalance(AVLTree<T>::Node *&root, bool &taller)
{
    // Case 1: right of right
    if (root->pRight->balance == RH)
    {
        root = rotateLeft(root);
        root->balance = EH;
        root->pLeft->balance = EH;
        taller = 0;
    }
    
    // Case 2: left of right
    else 
    {
        root->pRight = rotateRight(root->pRight);
        root = rotateLeft(root);
        if (root->balance == LH)
        {
            root->balance = EH;
            root->pLeft->balance = EH;
            root->pRight->balance = RH;
        }
        else if (root->balance == EH)
        {
            root->pLeft->balance = EH;
            root->pRight -> balance = EH;
        }
        else 
        {
            root->balance = EH;
            root->pLeft->balance = LH;
            root->pRight->balance = EH;
        }
        taller = 0;
    }
    return root;
}
template<class T> AVLTree<T>::Node *AVLTree<T>::AVLInsert(AVLTree<T>::Node *&root, T value, bool &taller)
{
    // Insert at root
    if (!root)
    {
        root = new Node(value);
        taller = true;
        return root;
    }
    
    if (value < root->data)
    {
        root->pLeft = AVLInsert(root->pLeft, value, taller);
        
        //Left is taller
        if (taller)
        {
            if (root->balance == LH)
            {
                root = leftBalance(root, taller);
            }
            else if (root->balance == EH)
            {
                root->balance = LH;
            }
            else 
            {
                root->balance = EH;
                taller = false;
            }
        }
    }
    else 
    {
        root->pRight = AVLInsert(root->pRight, value, taller);
        
        // Right is taller
        if (taller)
        {
           if (root->balance == LH)
            {
                root->balance = EH;
                taller = false;
            }
            else if (root->balance == EH)
            {
                root->balance = RH;
            }
            else 
            {
                root = rightBalance(root, taller);
            } 
        }
        
    }
    return root;
}
template<class T> inline void AVLTree<T>::insert(const T &value){
    //TODO
    static bool taller = false;
    this -> root = AVLInsert(this->root, value, taller);
}



