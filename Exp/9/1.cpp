#include <iostream>
using namespace std;
template <class T>
class arrayStack
{
private:
    int stackTop, arrayLength;
    T *stack;

public:
    arrayStack(int initialCapacity = 10)
    {
        if (initialCapacity < 1)
            throw invalid_argument("Initial capacity must be > 0");
        arrayLength = initialCapacity;
        stack = new T[arrayLength];
        stackTop = -1;
    }
    ~arrayStack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    T &top()
    {
        if (stackTop == -1)
            throw underflow_error("Stack is empty");
        return stack[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
            throw underflow_error("Stack is empty");
        stack[stackTop--].~T();
    }
    void push(const T &theElement)
    {
        if (stackTop == arrayLength - 1)
        {
            arrayLength *= 2;
            T *newStack = new T[arrayLength];
            for (int i = 0; i <= stackTop; i++)
                newStack[i] = stack[i];
            delete[] stack;
            stack = newStack;
        }
        stack[++stackTop] = theElement;
    }
};
template <class T>
class arrayQueue
{
public:
    arrayQueue(int initialCapacity = 10)
    {
        if (initialCapacity < 1)
            throw invalid_argument("Initial capacity must be > 0");
        arrayLength = initialCapacity;
        queue = new T[arrayLength];
        theFront = 0, theBack = 0;
    }
    ~arrayQueue() { delete[] queue; }
    bool empty() const { return theFront == theBack; }
    int size() const { return (theBack - theFront + arrayLength) % arrayLength; }
    T &front()
    {
        if (theFront == theBack)
            throw underflow_error("Queue is empty");
        return queue[(theFront + 1) % arrayLength];
    }
    T &back()
    {
        if (theFront == theBack)
            throw underflow_error("Queue is empty");
        return queue[theBack];
    }
    void pop()
    {
        if (theFront == theBack)
            throw underflow_error("Queue is empty");
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();
    }
    void push(const T &theElement)
    {
        if ((theBack + 1) % arrayLength == theFront)
        {
            int oldLength = arrayLength, newLength = 2 * oldLength;
            T *newQueue = new T[newLength];
            int start = (theFront + 1) % oldLength, sz = size();
            for (int i = 0; i < sz; ++i)
                newQueue[i] = queue[(start + i) % oldLength];
            delete[] queue;
            queue = newQueue, arrayLength = newLength;
            theFront = arrayLength - 1, theBack = sz - 1;
        }
        theBack = (theBack + 1) % arrayLength;
        queue[theBack] = theElement;
    }
    void output()
    {
        int index = (theFront + 1) % arrayLength, end = (theBack + 1) % arrayLength;
        while (index != end)
        {
            std::cout << queue[index] << std::endl;
            index = (index + 1) % arrayLength;
        }
    }

private:
    int theFront, theBack, arrayLength;
    T *queue;
};
template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;
    binaryTreeNode() { leftChild = rightChild = NULL; }
    binaryTreeNode(const T &theElement) : element(theElement), leftChild(NULL), rightChild(NULL) {}
    binaryTreeNode(const T &theElement, binaryTreeNode<T> *theLeftChild, binaryTreeNode<T> *theRightNode) : element(theElement), leftChild(theLeftChild), rightChild(theRightNode) {}
};
template <class T>
class linkedBinaryTree
{
private:
    binaryTreeNode<T> *root;
    int treeSize;

public:
    linkedBinaryTree() : treeSize(0), root(NULL) {}
    bool empty() const { return treeSize == 0; }
    int size() const { return treeSize; }
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
        arrayStack<binaryTreeNode<T> *> stack;
        binaryTreeNode<T> *p = t;
        while (p != NULL || !stack.empty())
        {
            if (p != NULL)
            {
                stack.push(p);
                p = p->leftChild;
            }
            else
            {
                p = stack.top();
                stack.pop();
                cout << p->element << " ";
                p = p->rightChild;
            }
        }
    }
    void postOrder(binaryTreeNode<T> *t)
    {
        arrayStack<binaryTreeNode<T> *> stack;
        binaryTreeNode<T> *p = t, *pp;
        while (p != NULL || !stack.empty())
        {
            if (p != NULL)
            {
                stack.push(p);
                p = p->leftChild;
            }
            else
            {
                p = stack.top();
                if (p->rightChild != NULL && p->rightChild != pp)
                {
                    p = p->rightChild;
                    stack.push(p);
                    p = p->leftChild;
                }
                else
                {
                    stack.pop();
                    cout << p->element << " ";
                    pp = p;
                    p = NULL;
                }
            }
        }
    }
    void levelOrder(binaryTreeNode<T> *t)
    {
        arrayQueue<binaryTreeNode<T> *> queue;
        binaryTreeNode<T> *p = t;
        while (p != NULL)
        {
            cout << p->element << " ";
            if (p->leftChild != NULL)
                queue.push(p->leftChild);
            if (p->rightChild != NULL)
                queue.push(p->rightChild);
            if (queue.empty())
                break;
            p = queue.front();
            queue.pop();
        }
    }
    int height(binaryTreeNode<T> *t) { return (t == NULL) ? 0 : max(height(t->leftChild), height(t->rightChild)) + 1; }
    int num(binaryTreeNode<T> *t) { return (t == NULL) ? 0 : num(t->leftChild) + num(t->rightChild) + 1; }
};
int n;
int main()
{
    cin >> n;
    binaryTreeNode<int> **NodeList = new binaryTreeNode<int> *[n + 1];
    for (int i = 1; i <= n; ++i)
        NodeList[i] = new binaryTreeNode<int>(i);
    for (int i = 1; i <= n; ++i)
    {
        int l, r;
        cin >> l >> r;
        if (l != -1)
            NodeList[i]->leftChild = NodeList[l];
        else
            NodeList[i]->leftChild = NULL;
        if (r != -1)
            NodeList[i]->rightChild = NodeList[r];
        else
            NodeList[i]->rightChild = NULL;
    }
    linkedBinaryTree<int> tree;
    tree.preOrder(NodeList[1]);
    cout << endl;
    tree.inOrder(NodeList[1]);
    cout << endl;
    tree.postOrder(NodeList[1]);
    cout << endl;
    tree.levelOrder(NodeList[1]);
    cout << endl;
    for (int i = 1; i <= n; ++i)
        cout << tree.num(NodeList[i]) << " ";
    cout << endl;
    for (int i = 1; i <= n; ++i)
        cout << tree.height(NodeList[i]) << " ";
    cout << endl;
    for (int i = 1; i <= n; ++i)
        delete NodeList[i];
    delete[] NodeList;
    return 0;
}
