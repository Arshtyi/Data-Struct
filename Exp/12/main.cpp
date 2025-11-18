#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
template <class T>
class arrayList
{
private:
    int arrayLength, listSize;
    T *element;

public:
    arrayList(int initialCapacity = 10) : arrayLength(initialCapacity), listSize(0), element(new T[arrayLength])
    {
        for (int i = 0; i < arrayLength; ++i)
            element[i] = T();
    }
    arrayList(const arrayList<T> &arr) : arrayLength(arr.arrayLength), listSize(arr.listSize), element(new T[arrayLength]) { copy(arr.element, arr.element + listSize, element); }
    ~arrayList() { delete[] element; }
    bool empty() const { return listSize == 0; }
    int size() { return listSize; }
    void check_index(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
        {
            ostringstream s;
            s << "index = " << theIndex << "size = " << listSize;
            cout << s.str() << endl;
            exit(0);
        }
    }
    T &get(int theIndex)
    {
        check_index(theIndex);
        return element[theIndex];
    }
    int index_of(const T &theElement) const
    {
        for (int i = 0; i < listSize; ++i)
            if (element[i] == theElement)
                return i;
        return -1;
    }
    void insert(int theIndex, const T &theElement)
    {
        if (listSize == arrayLength)
        {
            arrayLength *= 2;
            T *newElement = new T[arrayLength];
            for (int i = 0; i < listSize; ++i)
                newElement[i] = element[i];
            delete[] element;
            element = newElement;
        }
        if (theIndex == listSize - 1)
            element[listSize++] = theElement;
        else
        {
            copy_backward(element + theIndex, element + listSize, element + listSize + 1);
            element[theIndex] = theElement;
            listSize++;
        }
    }
    void erase(int theIndex)
    {
        check_index(theIndex);
        copy(element + theIndex + 1, element + listSize, element + theIndex);
        element[--listSize].~T();
    }
    void push_back(const T &theElement)
    {
        if (listSize == arrayLength)
        {
            arrayLength *= 2;
            T *newElement = new T[arrayLength];
            for (int i = 0; i < listSize; ++i)
                newElement[i] = element[i];
            delete[] element;
            element = newElement;
        }
        element[listSize++] = theElement;
    }
    void output(ostream &out) const { copy(element, element + listSize, ostream_iterator<T>(out, " ")); }
    void sort() { std::sort(element, element + listSize); }
    void clear() { listSize = 0; }
    void reset(int length, T value)
    {
        this->clear();
        for (int i = 0; i < length; ++i)
            this->push_back(value);
    }
    T &operator[](int index)
    {
        check_index(index);
        return element[index];
    }
    const T &operator[](int index) const
    {
        check_index(index);
        return element[index];
    }
    T &operator*() { return element[0]; };
    const T &operator*() const { return element[0]; };
    operator T *() { return element; };
    operator const T *() const { return element; };
};
template <class T>
ostream &operator<<(ostream &out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}
template <class T>
struct chainNode
{
    T element;
    chainNode<T> *next;
    chainNode() : next(nullptr) {}
    chainNode(const T &e) : element(e), next(nullptr) {}
    chainNode(const T &e, chainNode<T> *p) : element(e), next(p) {}
};
template <class T>
class chain
{
protected:
    chainNode<T> *head, *tail;
    int listSize;
    void check_index(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
        {
            ostringstream s;
            s << "index = " << theIndex << " size = " << listSize;
            throw s.str();
        }
    }

public:
    chain(int initialCapacity = 10)
    {
        if (initialCapacity < 1)
        {
            ostringstream s;
            s << "Initial capacity = " << initialCapacity << " Must be > 0";
            throw s.str();
        }
        head = tail = nullptr;
        listSize = 0;
    }
    chain(const chain<T> &rhs)
    {
        listSize = rhs.size();
        if (listSize == 0)
        {
            head = tail = nullptr;
            return;
        }
        chainNode<T> *sourceNode = rhs.head;
        head = new chainNode<T>(sourceNode->element);
        sourceNode = sourceNode->next;
        chainNode<T> *targetNode = head;
        while (sourceNode != nullptr)
            targetNode->next = new chainNode<T>(sourceNode->element), targetNode = targetNode->next, sourceNode = sourceNode->next;
        targetNode->next = nullptr, tail = targetNode;
    }
    chain<T> &operator=(const chain<T> &rhs)
    {
        if (this != &rhs)
        {
            chainNode<T> *current = head;
            while (current != nullptr)
            {
                chainNode<T> *nextNode = current->next;
                delete current;
                current = nextNode;
            }
            listSize = rhs.listSize;
            if (rhs.head == nullptr)
                head = tail = nullptr;
            else
            {
                head = new chainNode<T>(rhs.head->element);
                chainNode<T> *current = head, *sourceNode = rhs.head->next;
                while (sourceNode != nullptr)
                    current->next = new chainNode<T>(sourceNode->element), current = current->next, sourceNode = sourceNode->next;
                tail = current;
            }
        }
        return *this;
    }
    ~chain()
    {
        while (head != nullptr)
        {
            chainNode<T> *nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const
    {
        check_index(theIndex);
        chainNode<T> *currentNode = head;
        for (int i = 0; i < theIndex; i++)
            currentNode = currentNode->next;
        return currentNode->element;
    }
    int index_of(const T &theElement) const
    {
        if (head == nullptr)
            return -1;
        chainNode<T> *currentNode = head;
        int index = 0;
        for (; currentNode != nullptr && currentNode->element != theElement; ++index)
            currentNode = currentNode->next;
        return (currentNode == nullptr) ? -1 : index;
    }
    void erase(int theIndex)
    {
        check_index(theIndex);
        chainNode<T> *deleteNode;
        if (theIndex == 0)
        {
            deleteNode = head, head = head->next;
            if (head == nullptr)
                tail = nullptr;
        }
        else
        {
            chainNode<T> *frontNode = head;
            for (int i = 0; i < theIndex - 1; ++i)
                frontNode = frontNode->next;
            deleteNode = frontNode->next, frontNode->next = deleteNode->next;
            if (frontNode->next == nullptr)
                tail = frontNode;
        }
        listSize--;
        delete deleteNode;
    }
    void insert(int theIndex, const T &theElement)
    {
        check_index(theIndex);
        if (theIndex == 0)
            head = new chainNode<T>(theElement, head);
        else
        {
            chainNode<T> *frontNode = head;
            for (int i = 0; i < theIndex - 1; i++)
                frontNode = frontNode->next;
            frontNode->next = new chainNode<T>(theElement, frontNode->next);
            if (frontNode->next->next == nullptr)
                tail = frontNode->next;
        }
        listSize++;
    }
    void push_back(const T &theElement)
    {
        chainNode<T> *newNode = new chainNode<T>(theElement, nullptr);
        if (head == nullptr)
            head = tail = newNode;
        else
            tail->next = newNode, tail = newNode;
        listSize++;
    }
    void output(ostream &out) const
    {
        for (chainNode<T> *currentNode = head; currentNode != nullptr; currentNode = currentNode->next)
            out << currentNode->element << " ";
    }
    class iterator
    {
    public:
        iterator(chainNode<T> *theNode = nullptr) : node(theNode) {}
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
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
};
template <class T>
ostream &operator<<(ostream &out, const chain<T> &x)
{
    x.output(out);
    return out;
}
template <class T>
class arrayQueue
{
private:
    int head, tail, arrayLength;
    T *queue;

public:
    arrayQueue(int initialCapacity = 10) : head(0), tail(0), arrayLength(initialCapacity + 1), queue(new T[arrayLength]) {}
    ~arrayQueue() { delete[] queue; }
    bool empty() const { return head == tail; }
    int size() const { return (tail - head + arrayLength) % arrayLength; }
    T &front()
    {
        if (head == tail)
            throw "Queue is empty";
        return queue[(head + 1) % arrayLength];
    }
    T &back()
    {
        if (head == tail)
            throw "Queue is empty";
        return queue[tail];
    }
    void pop()
    {
        if (head == tail)
            throw "Queue is empty";
        head = (head + 1) % arrayLength;
        queue[head].~T();
    }
    void push(const T &theElement)
    {
        if ((tail + 1) % arrayLength == head)
        {
            int oldArrayLength = arrayLength, start = (head + 1) % oldArrayLength;
            T *newQueue = new T[2 * oldArrayLength];
            for (int i = 0; i < oldArrayLength - 1; ++i)
                newQueue[i] = queue[(start + i) % oldArrayLength];
            head = 2 * oldArrayLength - 1, tail = oldArrayLength - 2, arrayLength = 2 * oldArrayLength;
            delete[] queue;
            queue = newQueue;
        }
        tail = (tail + 1) % arrayLength;
        queue[tail] = theElement;
    }
    void output()
    {
        int index = (head + 1) % arrayLength;
        while (index % arrayLength != (tail + 1) % arrayLength)
            cout << queue[index++] << endl;
    }
};
template <class T>
class graphChain : public chain<T>
{
public:
    void erase_element(int theVertex)
    {
        int index = this->index_of(theVertex);
        this->erase(index);
    }
    void sort_list()
    {
        arrayList<T> tmp;
        for (chainNode<T> *node = this->head; node != nullptr; node = node->next)
            tmp.push_back(node->element);
        tmp.sort();
        chainNode<T> *cur = this->head;
        while (cur != nullptr)
        {
            chainNode<T> *next = cur->next;
            delete cur;
            cur = next;
        }
        this->head = this->tail = nullptr, this->listSize = 0;
        for (int i = 0; i < tmp.size(); i++)
            this->push_back(tmp[i]);
    }
};

class linkedGraph
{
protected:
    graphChain<int> *aList;
    int n, e;

public:
    linkedGraph(int num = 0)
    {
        if (num < 0)
            exit(0);
        n = num, e = 0;
        aList = new graphChain<int>[n + 1];
    }
    ~linkedGraph() { delete[] aList; }
    void output()
    {
        for (int i = 1; i <= n; i++)
            cout << "节点" << i << ":" << aList[i] << endl;
        cout << endl;
    }
    bool exist_edge(int i, int j)
    {
        if (i > n || j > n || i < 1 || j < 1)
            return false;
        return ((&aList[i])->index_of(j) != -1);
    }
    void insert_edge(int i, int j)
    {
        if (!exist_edge(i, j))
            aList[i].push_back(j), aList[j].push_back(i), e++;
    }
    void erase_edge(int i, int j)
    {
        if (exist_edge(i, j))
            aList[i].erase_element(j), aList[j].erase_element(i), e--;
    }
    void sort_all_lists()
    {
        for (int i = 1; i <= n; ++i)
            aList[i].sort_list();
    }
    int bfs(int st, arrayList<int> &res, arrayList<int> &vis)
    {
        arrayQueue<int> q(10);
        vis[st] = 1;
        q.push(st);
        while (!q.empty())
        {
            int w = q.front();
            q.pop();
            res.push_back(w);
            for (chain<int>::iterator i = aList[w].begin(); i != aList[w].end(); ++i)
                if (!vis[*i])
                    q.push(*i), vis[*i] = 1;
        }
        return res.size();
    }
    void dfs(int st, arrayList<int> &res, arrayList<int> &vis)
    {
        vis[st] = 1, res.push_back(st);
        for (chain<int>::iterator i = aList[st].begin(); i != aList[st].end(); ++i)
            if (!vis[*i])
                dfs(*i, res, vis);
    }
    int count_connected_components(arrayList<int> &mi)
    {
        arrayList<int> vis(n + 1), res;
        vis.reset(n + 1, 0);
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (vis[i] == 0)
            {
                res.clear();
                dfs(i, res, vis);
                mi.push_back(i);
                cnt++;
            }
        return cnt;
    }
    int find_shortest_path(int st, int ed)
    {
        if (st == ed)
            return 0;
        arrayQueue<int> q(10);
        arrayList<int> vis(n + 1), dist(n + 1);
        vis.reset(n + 1, 0), dist.reset(n + 1, 0);
        q.push(st);
        vis[st] = 1, dist[st] = 0;
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            arrayList<int> neighbors;
            for (chain<int>::iterator i = aList[current].begin(); i != aList[current].end(); ++i)
                neighbors.push_back(*i);
            for (int i = 0; i < neighbors.size(); ++i)
            {
                int neighbor = neighbors[i];
                if (vis[neighbor] == 0)
                {
                    q.push(neighbor);
                    vis[neighbor] = 1;
                    dist[neighbor] = dist[current] + 1;
                    if (neighbor == ed)
                        return dist[neighbor];
                }
            }
        }
        return -1;
    }
};
int n, m, s, t;
int main()
{
    // freopen("data.in", "r", stdin);
    cin >> n >> m >> s >> t;
    linkedGraph graph(n);
    for (int i = 0; i < m; i++)
    {
        int op, u, v;
        cin >> op >> u >> v;
        op ? graph.erase_edge(u, v) : graph.insert_edge(u, v);
    }
    graph.sort_all_lists();
    arrayList<int> mi, vis, res;
    cout << graph.count_connected_components(mi) << endl;
    cout << mi << endl;
    vis.reset(n + 1, 0);
    graph.dfs(s, res, vis);
    cout << res.size() << endl;
    cout << res << endl;
    res.clear();
    vis.reset(n + 1, 0);
    cout << graph.bfs(t, res, vis) << endl;
    cout << res << endl;
    cout << graph.find_shortest_path(s, t) << endl;
    return 0;
}
