#include <iostream>
using namespace std;
template <class T>
class arrayQueue
{
private:
    int head, tail, arrayLength;
    T *queue;

public:
    arrayQueue(int initialCapacity = 10)
    {
        if (initialCapacity < 1)
            throw "Initial capacity must be > 0";
        arrayLength = initialCapacity;
        queue = new T[arrayLength];
        head = 0, tail = 0;
    }
    ~arrayQueue() { delete[] queue; }
    bool empty() const { return head == tail; }
    int size() const { return (tail - head + arrayLength) % arrayLength; }
    T &front()
    {
        if (head == tail)
            throw "The queue is empty.";
        return queue[(head + 1) % arrayLength];
    }
    T &back()
    {
        if (head == tail)
            throw "The queue is empty.";
        return queue[tail];
    }
    void pop()
    {
        if (head == tail)
            throw "The queue is empty.";
        head = (head + 1) % arrayLength;
        queue[head].~T();
    }
    void push(const T &theElement)
    {
        if ((tail + 1) % arrayLength == head)
        {
            int oldLength = arrayLength;
            int newLength = 2 * oldLength;
            T *newQueue = new T[newLength];
            int currentSize = size();
            int start = (head + 1) % oldLength;
            for (int i = 0; i < currentSize; ++i)
            {
                newQueue[i] = queue[(start + i) % oldLength];
            }
            delete[] queue;
            queue = newQueue;
            arrayLength = newLength;
            if (currentSize == 0)
            {
                head = tail = 0;
            }
            else
            {
                head = arrayLength - 1;
                tail = currentSize - 1;
            }
        }
        tail = (tail + 1) % arrayLength;
        queue[tail] = theElement;
    }
    void output()
    {
        int index = (head + 1) % arrayLength;
        while (index % arrayLength != (tail + 1) % arrayLength)
        {
            std::cout << queue[index] << std::endl;
            index++;
        }
    }
};
arrayQueue<int> poker;
int n;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        poker.push(i);
    if (n >= 2)
    {
        for (int i = 1; i < n; ++i)
        {
            poker.pop();
            int a = poker.front();
            poker.pop();
            poker.push(a);
        }
    }
    cout << poker.front() << endl;
    return 0;
}
