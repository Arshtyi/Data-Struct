#include <iostream>
using namespace std;
template <class T>
struct BinaryTreeNode
{
    T element;
    BinaryTreeNode<T> *leftChild, *rightChild;
    int leftSize;
    BinaryTreeNode(const T &theElement) : element(theElement), leftChild(NULL), rightChild(NULL), leftSize(0) {}
    BinaryTreeNode(const T &theElement, BinaryTreeNode<T> *theLeft, BinaryTreeNode<T> *theRight, int LeftSize) : element(theElement), leftChild(theLeft), rightChild(theRight), leftSize(LeftSize) {}
};
template <class T>
class indexedBST
{
private:
    int size;
    BinaryTreeNode<T> *root;

public:
    indexedBST() : size(0), root(NULL) {}
    int insert(const T &theElement)
    {
        BinaryTreeNode<T> *p = root, *pp = NULL;
        int sum = 0;
        while (p != NULL)
        {
            if (p->element < theElement)
                sum ^= p->element, pp = p, p = p->rightChild;
            else if (p->element > theElement)
                sum ^= p->element, pp = p, p = p->leftChild;
            else
                return 0;
        }
        BinaryTreeNode<T> *newNode = new BinaryTreeNode<T>(theElement);
        if (pp == NULL)
            root = newNode;
        else
        {
            if (theElement > pp->element)
                pp->rightChild = newNode;
            else if (theElement < pp->element)
                pp->leftChild = newNode;
        }
        ++size, p = root;
        while (p->element != theElement)
            if (p->element < theElement)
                p = p->rightChild;
            else if (p->element > theElement)
                p->leftSize++, p = p->leftChild;
        return sum;
    }
    int find(const T &theElement)
    {
        BinaryTreeNode<T> *p = root;
        int sum = 0;
        while (p != NULL && p->element != theElement)
        {
            sum ^= p->element;
            if (p->element > theElement)
                p = p->leftChild;
            else if (p->element < theElement)
                p = p->rightChild;
        }
        if (p == NULL)
            return 0;
        sum ^= p->element;
        return sum;
    }
    int erase(const T &theElement)
    {
        BinaryTreeNode<T> *p = root, *pp = NULL;
        int sum = 0;
        while (p != NULL && p->element != theElement)
        {
            sum ^= p->element, pp = p;
            if (p->element > theElement)
                p = p->leftChild;
            else if (p->element < theElement)
                p = p->rightChild;
        }
        if (p == NULL)
            return 0;
        sum ^= p->element, p = root;
        while (p != NULL && p->element != theElement)
            if (p->element < theElement)
                p = p->rightChild;
            else if (p->element > theElement)
                p->leftSize--, p = p->leftChild;
        if (p->leftChild != NULL && p->rightChild != NULL)
        {
            BinaryTreeNode<T> *min_right = p->rightChild, *delete_r = p;
            while (min_right->leftChild != NULL)
                min_right->leftSize--, delete_r = min_right, min_right = min_right->leftChild;
            BinaryTreeNode<T> *newNode = new BinaryTreeNode<T>(min_right->element, p->leftChild, p->rightChild, p->leftSize);
            if (pp == NULL)
                root = newNode;
            else if (p == pp->leftChild)
                pp->leftChild = newNode;
            else
                pp->rightChild = newNode;
            if (delete_r == p)
                pp = newNode;
            else
                pp = delete_r;
            delete p;
            p = min_right;
        }
        BinaryTreeNode<T> *c;
        if (p->leftChild != NULL)
            c = p->leftChild;
        else
            c = p->rightChild;
        if (p == root)
            root = c;
        else
        {
            if (p == pp->leftChild)
                pp->leftChild = c;
            else
                pp->rightChild = c;
        }
        size--;
        delete p;
        return sum;
    }
    int findByIndex(int a)
    {
        BinaryTreeNode<T> *p = root;
        int sum = 0;
        while (p != NULL && p->leftSize != a)
        {
            sum ^= p->element;
            if (p->leftSize > a)
                p = p->leftChild;
            else
                a = a - p->leftSize - 1, p = p->rightChild;
        }
        if (p == NULL)
            return 0;
        sum ^= p->element;
        return sum;
    }
    int deleteByIndex(int a)
    {
        BinaryTreeNode<T> *p = root;
        int sum = 0;
        while (p != NULL && p->leftSize != a)
        {
            sum ^= p->element;
            if (p->leftSize > a)
                p = p->leftChild;
            else if (p->leftSize < a)
                a = a - p->leftSize - 1, p = p->rightChild;
        }
        if (p == NULL)
            return 0;
        sum ^= p->element;
        int theElement = p->element;
        this->erase(theElement);
        return sum;
    }
};
int m, op, param;
indexedBST<int> bsTree;
int main()
{
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> op >> param;
        if (op == 0)
            cout << bsTree.insert(param) << endl;
        else if (op == 1)
            cout << bsTree.find(param) << endl;
        else if (op == 2)
            cout << bsTree.erase(param) << endl;
        else if (op == 3)
            cout << bsTree.findByIndex(--param) << endl;
        else if (op == 4)
            cout << bsTree.deleteByIndex(--param) << endl;
    }
    return 0;
}
