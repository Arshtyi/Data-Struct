#include <iostream>
using namespace std;
template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;
    binaryTreeNode(const T &theElement) : element(theElement), leftChild(NULL), rightChild(NULL) {}
    binaryTreeNode(const T &theElement, binaryTreeNode<T> *theLeftChild, binaryTreeNode<T> *theRightNode) : element(theElement), leftChild(theLeftChild), rightChild(theRightNode) {}
};
template <class T>
class linkedBinaryTree
{
private:
    binaryTreeNode<T> *root;
    int treeSize;
    binaryTreeNode<T> *treeRebuild(T *pre, int pre_l, int pre_r, T *in, int in_l, int in_r)
    {
        if (pre_l > pre_r)
            return NULL;
        binaryTreeNode<T> *r = new binaryTreeNode<T>(pre[pre_l]);
        if (pre_l == pre_r)
            return r;
        int find = in_l;
        while (in[find] != pre[pre_l])
            find++;
        r->leftChild = treeRebuild(pre, pre_l + 1, pre_l + find - in_l, in, in_l, find - 1);
        r->rightChild = treeRebuild(pre, pre_l + find - in_l + 1, pre_r, in, find + 1, in_r);
        return r;
    }

public:
    linkedBinaryTree() : root(NULL), treeSize(0) {}
    bool empty() const { return treeSize == 0; }
    int size() const { return treeSize; }
    binaryTreeNode<T> *get_root() { return root; }
    void preOrder(binaryTreeNode<T> *t)
    {
        if (t == NULL)
            return;
        cout << t->element << ' ';
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
    void inOrder(binaryTreeNode<T> *t)
    {
        if (t == NULL)
            return;
        inOrder(t->leftChild);
        cout << t->element << ' ';
        inOrder(t->rightChild);
    }
    void postOrder(binaryTreeNode<T> *t)
    {
        if (t == NULL)
            return;
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        cout << t->element << ' ';
    }
    int height(binaryTreeNode<T> *t) { return (t == NULL) ? 0 : max(height(t->leftChild), height(t->rightChild)) + 1; }
    int num(binaryTreeNode<T> *t) { return (t == NULL) ? 0 : num(t->leftChild) + num(t->rightChild) + 1; }
    void Rebuild(T *pre, T *in, int length)
    {
        root = treeRebuild(pre, 0, length - 1, in, 0, length - 1);
        treeSize = num(root);
    }
};
int n;
int main()
{
    cin >> n;
    int *pre = new int[n];
    int *in = new int[n];
    for (int i = 0; i < n; i++)
        cin >> pre[i];
    for (int i = 0; i < n; i++)
        cin >> in[i];
    linkedBinaryTree<int> tree;
    tree.Rebuild(pre, in, n);
    tree.postOrder(tree.get_root());
    cout << endl;
    delete[] pre;
    delete[] in;
    return 0;
}
