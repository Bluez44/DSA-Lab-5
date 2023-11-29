#include <iostream>
#include <queue>
using namespace std;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}

    void printInorder(){
        //TODO
    }

    bool search(const T &value){
        //TODO
    }
    void inOrderRec(Node* root);
    void inOrderRecBool(Node* root, T value, bool &found);
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

template<class T> void AVLTree<T>::inOrderRec(AVLTree<T>::Node *root)
{
    if (!root) return;
    
    inOrderRec(root->pLeft);
    cout << root->data << " ";
    inOrderRec(root->pRight);
}
template<class T> inline void AVLTree<T>::printInorder(){
        //TODO
        inOrderRec(this->root);
    }
template<class T> void AVLTree<T>::inOrderRecBool(AVLTree<T>::Node *root, T value, bool &found)
    {
    if (root)
    {
        if (root->data == value)
        {
            found = true;
            return;
        }
        inOrderRecBool(root->pLeft, value, found);
        inOrderRecBool(root->pRight, value, found);
    }
    return;
    }
template<class T> inline bool AVLTree<T>::search(const T &value){
        //TODO
        bool found = false;
        inOrderRecBool(this->root, value, found);
        return found;
    }
