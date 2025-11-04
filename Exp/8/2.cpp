#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class illegalParameterValue
{
public:
    illegalParameterValue(string theMessage = "Illegal parameter value") { message = theMessage; }
    void outputMessage() { cout << message << endl; }

private:
    string message;
};
class illegalIndex
{
public:
    illegalIndex(string theMessage = "Illegal index") { message = theMessage; }
    void outputMessage() { cout << message << endl; }

private:
    string message;
};
template <class T>
struct chainNode
{
    T element;
    chainNode<T> *next;
    chainNode() {}
    chainNode(const T &e) : element(e) {}
    chainNode(const T &e, chainNode<T> *p) : element(e), next(p) {}
};
template <class T>
class chain
{
protected:
    void checkIndex(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
        {
            ostringstream s;
            s << "index = " << theIndex << " size = " << listSize;
            throw illegalIndex(s.str());
        }
    }
    chainNode<T> *firstNode, *lastNode;
    int listSize;

public:
    chain(int initialCapacity = 10)
    {
        if (initialCapacity < 1)
        {
            ostringstream s;
            s << "Initial capacity = " << initialCapacity << " Must be > 0";
            throw illegalParameterValue(s.str());
        }
        firstNode = lastNode = NULL;
        listSize = 0;
    }
    ~chain()
    {
        while (firstNode != NULL)
        {
            chainNode<T> *nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }
    chain(const chain<T> &theList)
    {
        listSize = theList.size();
        if (!listSize)
        {
            firstNode = lastNode = NULL;
            return;
        }
        chainNode<T> *sourceNode = theList.firstNode;
        firstNode = new chainNode<T>(sourceNode->element);
        sourceNode = sourceNode->next;
        chainNode<T> *targetNode = firstNode;
        while (sourceNode != NULL)
            targetNode->next = new chainNode<T>(sourceNode->element), targetNode = targetNode->next, sourceNode = sourceNode->next;
        targetNode->next = NULL;
        lastNode = targetNode;
    }
    chain<T> &operator=(const chain<T> &theList)
    {
        if (this != &theList)
        {
            chainNode<T> *current = firstNode;
            while (current != nullptr)
            {
                chainNode<T> *nextNode = current->next;
                delete current;
                current = nextNode;
            }
            listSize = theList.listSize;
            if (theList.firstNode == nullptr)
                firstNode = lastNode = nullptr;
            else
            {
                firstNode = new chainNode<T>(theList.firstNode->element);
                chainNode<T> *current = firstNode, *sourceNode = theList.firstNode->next;
                while (sourceNode != nullptr)
                    current->next = new chainNode<T>(sourceNode->element), current = current->next, sourceNode = sourceNode->next;
                lastNode = current;
            }
        }
        return *this;
    }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const
    {
        checkIndex(theIndex);
        chainNode<T> *currentNode = firstNode;
        for (int i = 0; i < theIndex; ++i)
            currentNode = currentNode->next;
        return currentNode->element;
    }
    int indexOf(const T &theElement) const
    {
        chainNode<T> *currentNode = firstNode;
        int index = 0;
        for (; currentNode != NULL && currentNode->element != theElement; index++)
            currentNode = currentNode->next;
        if (currentNode == NULL)
            return -1;
        else
            return index;
    }
    void erase(int theIndex)
    {
        checkIndex(theIndex);
        chainNode<T> *deleteNode;
        if (theIndex == 0)
        {
            deleteNode = firstNode, firstNode = firstNode->next;
            if (firstNode == NULL)
                lastNode = NULL;
        }
        else
        {
            chainNode<T> *frontNode = firstNode;
            for (int i = 0; i < theIndex - 1; i++)
                frontNode = frontNode->next;
            deleteNode = frontNode->next, frontNode->next = deleteNode->next;
            if (frontNode->next == NULL)
                lastNode = frontNode;
        }
        listSize--;
        delete deleteNode;
    }
    void insert(int theIndex, const T &theElement)
    {
        if (theIndex < 0 || theIndex > listSize)
            throw illegalIndex("Invalid index for insert");
        if (theIndex == 0)
            firstNode = new chainNode<T>(theElement, firstNode);
        else
        {
            chainNode<T> *frontNode = firstNode;
            for (int i = 0; i < theIndex - 1; i++)
                frontNode = frontNode->next;
            frontNode->next = new chainNode<T>(theElement, frontNode->next);
            if (frontNode->next->next == NULL)
                lastNode = frontNode->next;
        }
        listSize++;
    }
    void reverse()
    {
        if (firstNode == NULL || firstNode->next == NULL)
            return;
        else
        {
            chainNode<T> *p = NULL, *m = firstNode, *q = firstNode->next;
            while (m != NULL)
            {
                m->next = p, p = m, m = q;
                if (q != NULL)
                    q = q->next;
            }
            lastNode = firstNode, firstNode = p;
        }
    }
    void push_back(const T &theElement)
    {
        chainNode<T> *newNode = new chainNode<T>(theElement, NULL);
        if (firstNode == NULL)
            firstNode = lastNode = newNode;
        else
            lastNode->next = newNode, lastNode = newNode;
        listSize++;
    }
    void output(ostream &out) const
    {
        for (chainNode<T> *currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
            out << currentNode->element << " ";
    }
    class iterator;
    iterator begin() { return iterator(firstNode); }
    iterator end() { return iterator(NULL); }
    class iterator
    {
    public:
        iterator(chainNode<T> *theNode = NULL) : node(theNode) {}
        T &operator*() const { return node->element; }
        T &operator->() const { return &node->element; }
        iterator &operator++()
        {
            node = node->next;
            return *this;
        }
        iterator &operator++(int)
        {
            iterator old = *this;
            node = node->next;
            return old;
        }
        bool operator!=(const iterator right) const { return node != right.node; }
        bool operator==(const iterator right) const { return node == right.node; }

    protected:
        chainNode<T> *node;
    };
};
class hashChain
{
private:
    chain<int> *table;
    int D;

public:
    hashChain(int d) : D(d), table(new chain<int>[d]) {}
    ~hashChain() { delete[] table; }
    void hashInsert(int x)
    {
        int hash_value = x % D;
        if (table[hash_value].indexOf(x) != -1)
            cout << "Existed" << endl;
        else
            table[hash_value].push_back(x);
    }
    void hashSearch(int x)
    {
        int hash_value = x % D;
        if (table[hash_value].indexOf(x) == -1)
            cout << "Not Found" << endl;
        else
            cout << table[hash_value].size() << endl;
    }
    void hashDelete(int x)
    {
        int hash_value = x % D;
        if (table[hash_value].indexOf(x) == -1)
            cout << "Delete Failed" << endl;
        else
        {
            int index = table[hash_value].indexOf(x);
            table[hash_value].erase(index);
            cout << table[hash_value].size() << endl;
        }
    }
};
template <class T>
ostream &operator<<(ostream &out, const chain<T> &x)
{
    x.output(out);
    return out;
}
int D, m;
int main()
{
    cin >> D >> m;
    hashChain table(D);
    for (int i = 0; i < m; i++)
    {
        int opt, x;
        cin >> opt >> x;
        if (opt == 0)
            table.hashInsert(x);
        else if (opt == 1)
            table.hashSearch(x);
        else
            table.hashDelete(x);
    }
    return 0;
}
