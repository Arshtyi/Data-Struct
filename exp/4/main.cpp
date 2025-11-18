#include <bits/stdc++.h>
template <typename T>
void quickSort(int l, int r, T a[])
{
    if (l >= r)
        return;
    int i = l, j = r;
    T x = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] < x)
            i++;
        while (a[j] > x)
            j--;
        if (i <= j)
        {
            std::swap(a[i], a[j]);
            i++, j--;
        }
    }
    quickSort(l, j, a), quickSort(i, r, a);
}
template <class T>
struct Node
{
    T cur;
    Node<T> *next;
    Node(T val, Node<T> *n = nullptr) : cur(val), next(n) {}
};
template <class T>
class chain
{
private:
    Node<T> *head, *tail;
    int listSize;
    void checkIndex(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
            throw "Index out of range";
    }

public:
    chain(const int initialCapacity = 10)
    {
        if (initialCapacity < 1)
            throw "Initial capacity must be > 0";
        head = tail = nullptr;
        listSize = 0;
    }
    chain(const chain<T> &other)
    {
        head = tail = nullptr;
        listSize = 0;
        if (other.head == nullptr)
            return;
        head = new Node<T>(other.head->cur);
        Node<T> *currentNew = head;
        Node<T> *currentOld = other.head->next;
        while (currentOld)
        {
            currentNew->next = new Node<T>(currentOld->cur);
            currentNew = currentNew->next;
            currentOld = currentOld->next;
        }
        tail = currentNew;
        listSize = other.listSize;
    }
    chain<T> &operator=(const chain<T> &other)
    {
        if (this == &other)
            return *this;
        while (head)
        {
            Node<T> *nextNode = head->next;
            delete head;
            head = nextNode;
        }
        head = tail = nullptr;
        listSize = 0;
        if (other.head == nullptr)
            return *this;
        head = new Node<T>(other.head->cur);
        Node<T> *currentNew = head;
        Node<T> *currentOld = other.head->next;
        while (currentOld)
        {
            currentNew->next = new Node<T>(currentOld->cur);
            currentNew = currentNew->next;
            currentOld = currentOld->next;
        }
        tail = currentNew;
        listSize = other.listSize;
        return *this;
    }
    chain(T a[], int l, int r)
    {
        if (l > r)
        {
            head = tail = nullptr;
            listSize = 0;
            return;
        }
        listSize = r - l + 1;
        head = new Node<T>(a[l]);
        Node<T> *currentNode = head;
        for (int i = l + 1; i <= r; ++i)
        {
            currentNode->next = new Node<T>(a[i]);
            currentNode = currentNode->next;
        }
        tail = currentNode;
    }
    ~chain()
    {
        while (head)
        {
            Node<T> *nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    int indexOf(const T &theElement) const
    {
        Node<T> *currentNode = head;
        int index = 0;
        while (currentNode)
        {
            if (currentNode->cur == theElement)
                return index;
            currentNode = currentNode->next;
            ++index;
        }
        return -1;
    }
    void insert(int theIndex, const T &theElement)
    {
        if (theIndex < 0 || theIndex > listSize)
            throw "Index out of range";
        if (theIndex == 0)
        {
            head = new Node<T>(theElement, head);
            if (listSize == 0)
                tail = head;
        }
        else
        {
            Node<T> *currentNode = head;
            for (int i = 0; i < theIndex - 1; ++i)
                currentNode = currentNode->next;
            currentNode->next = new Node<T>(theElement, currentNode->next);
            if (theIndex == listSize)
                tail = currentNode->next;
        }
        ++listSize;
    }
    void remove(const T &theElement)
    {
        Node<T> *currentNode = head, *prevNode = nullptr;
        while (currentNode)
        {
            if (currentNode->cur == theElement)
            {
                if (prevNode)
                    prevNode->next = currentNode->next;
                else
                    head = currentNode->next;
                if (currentNode == tail)
                    tail = prevNode;
                Node<T> *deleteNode = currentNode;
                currentNode = currentNode->next;
                delete deleteNode;
                --listSize;
                return;
            }
            else
            {
                prevNode = currentNode;
                currentNode = currentNode->next;
            }
        }
        std::cout << -1 << std::endl;
    }
    void push_back(const T &theElement)
    {
        Node<T> *newNode = new Node<T>(theElement);
        if (listSize == 0)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        ++listSize;
    }
    void reverse()
    {
        if (head == NULL || head->next == NULL)
            return;
        else
        {
            Node<T> *p = NULL, *m = head, *q = head->next;
            while (m != NULL)
            {
                m->next = p;
                p = m;
                m = q;
                if (q != NULL)
                    q = q->next;
            }
            tail = head;
            head = p;
        }
    }
    class iterator
    {
    private:
        Node<T> *node;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        iterator(Node<T> *theNode = NULL) : node(theNode) {}
        T &operator*() const { return node->cur; }
        T *operator->() const { return &node->cur; }
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
        int operator-(const iterator &right) const
        {
            int dist = 0;
            Node<T> *currentNode = right.node;
            while (currentNode != node)
            {
                currentNode = currentNode->next;
                ++dist;
            }
            return dist;
        }
    };
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
    void computeXorSum()
    {
        long long ans = 0;
        int idx = 0;
        for (iterator it = this->begin(); it != this->end(); ++it, ++idx)
        {
            ans += (long long)(*it) ^ idx;
        }
        std::cout << ans << std::endl;
    }
};
template <class T>
void meld(chain<T> &a, chain<T> &b, chain<T> &c)
{
    // 贪心：每次从a,b中取出较小的放入c中，然后处理剩余的，那么一定有序，复杂度也只有O(n)
    typename chain<T>::iterator ap = a.begin(), bp = b.begin();
    while (ap != a.end() && bp != b.end())
    {
        if (*ap <= *bp)
        {
            c.push_back(*ap);
            ++ap;
        }
        else
        {
            c.push_back(*bp);
            ++bp;
        }
    }
    while (ap != a.end())
    {
        c.push_back(*ap);
        ++ap;
    }
    while (bp != b.end())
    {
        c.push_back(*bp);
        ++bp;
    }
}
int main()
{
    using namespace std;
    chain<int> s;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        s.push_back(x);
    }
    for (int i = 1; i <= q; ++i)
    {
        int op;
        cin >> op;
        int idx, val;
        switch (op)
        {
        case 1:
            cin >> idx >> val;
            s.insert(idx, val);
            break;
        case 2:
            cin >> val;
            s.remove(val);
            break;
        case 3:
            s.reverse();
            break;
        case 4:
            cin >> val;
            cout << s.indexOf(val) << endl;
            break;
        case 5:
            s.computeXorSum();
            break;
        }
    }
    return 0;
}
// int main()
// {
//     using namespace std;
//     const int N = 2001;
//     int n, m, a[N], b[N];
//     cin >> n >> m;
//     chain<int> A, B, C;
//     for (int i = 1; i <= n; ++i)
//         cin >> a[i];
//     for (int i = 1; i <= m; ++i)
//         cin >> b[i];
//     quickSort(1, n, a), quickSort(1, m, b);
//     A = chain<int>(a, 1, n), B = chain<int>(b, 1, m);
//     meld(A, B, C);
//     A.computeXorSum(), B.computeXorSum(), C.computeXorSum();
//     return 0;
// }
