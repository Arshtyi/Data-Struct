#include <bits/stdc++.h>
template <class T>
struct chainNode
{
    T element;
    chainNode<T> *next;
    chainNode() {}
    chainNode(const T &e, chainNode<T> *p = nullptr) : element(e), next(p) {}
};
template <class T>
class linkedStack
{
private:
    chainNode<T> *stackTop;
    int stackSize;

public:
    linkedStack(int initialCapacity = 10)
    {
        stackTop = NULL;
        stackSize = 0;
    }
    ~linkedStack()
    {
        while (stackTop != NULL)
        {
            chainNode<T> *nextNode = stackTop->next;
            delete stackTop;
            stackTop = nextNode;
        }
    }
    bool empty() const { return stackSize == 0; }
    int size() const { return stackSize; }
    T &top() const
    {
        if (stackSize == 0)
            exit(0);
        return stackTop->element;
    }
    void push(const T &theElement)
    {
        stackTop = new chainNode<T>(theElement, stackTop);
        stackSize++;
    }
    void pushNode(chainNode<T> *theNode)
    {
        theNode->next = stackTop;
        stackTop = theNode;
        stackSize++;
    }
    void pop()
    {
        if (stackSize == 0)
            exit(0);
        chainNode<T> *nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
        stackSize--;
    }
    chainNode<T> *popNode()
    {
        if (stackSize == 0)
            return nullptr;
        chainNode<T> *returnNode = stackTop;
        stackTop = stackTop->next;
        stackSize--;
        return returnNode;
    }
};
// signed main()
// {
//     linkedStack<int> int_stack;
//     int_stack.push(1);
//     int_stack.push(2);
//     chainNode<int> *e = new chainNode<int>(16874321);
//     int_stack.pushNode(e);
//     std::cout << int_stack.popNode()->element << std::endl;
//     std::cout << int_stack.top() << std::endl;
//     return 0;
// }
signed main()
{
    using namespace std::chrono;
    const int N = 1e7 + 10;
    {
        linkedStack<int> s;
        auto t0 = high_resolution_clock::now();
        for (size_t i = 0; i < N; ++i)
            s.push((int)i);
        for (size_t i = 0; i < N; ++i)
            s.pop();
        auto t1 = high_resolution_clock::now();
        std::cout << "push/pop elapsed: " << duration_cast<milliseconds>(t1 - t0).count() << " ms" << std::endl;
    }
    {
        linkedStack<int> s;
        auto t0 = high_resolution_clock::now();
        for (size_t i = 0; i < N; ++i)
        {
            chainNode<int> *n = new chainNode<int>((int)i);
            s.pushNode(n);
        }
        for (size_t i = 0; i < N; ++i)
        {
            chainNode<int> *n = s.popNode();
            delete n;
        }
        auto t1 = high_resolution_clock::now();
        std::cout << "pushNode/popNode elapsed: " << duration_cast<milliseconds>(t1 - t0).count() << " ms" << std::endl;
    }
    return 0;
}
