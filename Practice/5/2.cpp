#include <bits/stdc++.h>
template <class T>
class queue
{
public:
    virtual ~queue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &front() const = 0;
    virtual T &back() const = 0;
    virtual void pop() = 0;
    virtual void push(const T &theElement) = 0;
};
template <class T>
class extendedQueue : public queue<T>
{
public:
    virtual void input() = 0;
    virtual void output() const = 0;
    virtual void split(extendedQueue<T> &q1, extendedQueue<T> &q2) = 0;
    virtual void combine(extendedQueue<T> &q1, extendedQueue<T> &q2) = 0;
};
template <class T>
class arrayQueue : public extendedQueue<T>
{
public:
    arrayQueue(int initialCap = 10)
    {
        capacity = (initialCap < 1) ? 10 : initialCap;
        elements = new T[capacity];
        frontIndex = 0;
        count = 0;
    }
    ~arrayQueue() { delete[] elements; }
    bool empty() const { return count == 0; }
    int size() const { return count; }
    T &front() const { return elements[frontIndex]; }
    T &back() const
    {
        int idx = (frontIndex + count - 1 + capacity) % capacity;
        return elements[idx];
    }
    void pop()
    {
        if (!count)
            return;
        frontIndex = (frontIndex + 1) % capacity;
        --count;
    }
    void push(const T &theElement)
    {
        checkCapacity();
        int avail = (frontIndex + count) % capacity;
        elements[avail] = theElement;
        ++count;
    }
    void input()
    {
        int n;
        if (!(std::cin >> n))
            return;
        for (int i = 0; i < n; ++i)
        {
            T x;
            std::cin >> x;
            push(x);
        }
    }
    void output() const
    {
        std::cout << size();
        if (size() > 0)
        {
            std::cout << ' ';
            for (int i = 0; i < count; ++i)
            {
                if (i)
                    std::cout << ' ';
                std::cout << elements[(frontIndex + i) % capacity];
            }
        }
        std::cout << std::endl;
    }
    void split(extendedQueue<T> &q1, extendedQueue<T> &q2)
    {
        int idx = 0;
        for (int i = 0; i < count; ++i)
        {
            T &val = elements[(frontIndex + i) % capacity];
            if (i % 2 == 0)
                q1.push(val);
            else
                q2.push(val);
        }
    }
    void combine(extendedQueue<T> &q1, extendedQueue<T> &q2)
    {
        while (!empty())
            pop();
        arrayQueue<T> *aq1 = dynamic_cast<arrayQueue<T> *>(&q1), *aq2 = dynamic_cast<arrayQueue<T> *>(&q2);
        if (!aq1 || !aq2)
            return;
        int i1 = 0, i2 = 0;
        while (i1 < aq1->count || i2 < aq2->count)
        {
            if (i1 < aq1->count)
            {
                T &v = aq1->elements[(aq1->frontIndex + i1) % aq1->capacity];
                push(v);
                ++i1;
            }
            if (i2 < aq2->count)
            {
                T &v = aq2->elements[(aq2->frontIndex + i2) % aq2->capacity];
                push(v);
                ++i2;
            }
        }
    }

private:
    void checkCapacity()
    {
        if (count < capacity)
            return;
        int newCap = capacity * 2;
        T *newArray = new T[newCap];
        for (int i = 0; i < count; ++i)
            newArray[i] = elements[(frontIndex + i) % capacity];
        delete[] elements;
        elements = newArray;
        capacity = newCap;
        frontIndex = 0;
    }
    T *elements;
    int capacity;
    int frontIndex;
    int count;
};
template <class T>
class extendedarrayQueue : public arrayQueue<T>
{
public:
    extendedarrayQueue(int cap = 10) : arrayQueue<T>(cap) {}
};
signed main()
{
    extendedarrayQueue<int> a;
    a.input();
    a.output();
    extendedarrayQueue<int> q1, q2;
    a.split(q1, q2);
    q1.output();
    q2.output();
    extendedarrayQueue<int> b, c;
    b.input();
    c.input();
    extendedarrayQueue<int> newq;
    newq.combine(b, c);
    newq.output();
    return 0;
}
