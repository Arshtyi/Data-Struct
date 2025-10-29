#include <iostream>
using namespace std;
template <class T>
class arrayQueue
{
private:
    int theFront, theBack, arrayLength;
    T *queue;

public:
    arrayQueue(int initialCapacity = 10)
    {
        if (initialCapacity < 1)
            throw "Initial capacity must be > 0";
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
            throw "The queue is empty.";
        return queue[(theFront + 1) % arrayLength];
    }
    T &back()
    {
        if (theFront == theBack)
            throw "The queue is empty.";
        return queue[theBack];
    }
    void pop()
    {
        if (theFront == theBack)
            throw "The queue is empty.";
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();
    }
    void push(const T &theElement)
    {
        if ((theBack + 1) % arrayLength == theFront)
        {
            T *newQueue = new T[2 * arrayLength];
            int start = (theFront + 1) % arrayLength;
            if (start < 2)
                std::copy(queue + start, queue + start + arrayLength - 1, newQueue);
            else
            {
                std::copy(queue + start, queue + arrayLength, newQueue);
                std::copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
            }
            theFront = 2 * arrayLength - 1;
            theBack = arrayLength - 2;
            arrayLength *= 2;
            queue = newQueue;
        }
        theBack = (theBack + 1) % arrayLength;
        queue[theBack] = theElement;
    }
    void output()
    {
        int index = (theFront + 1) % arrayLength;
        while (index % arrayLength != (theBack + 1) % arrayLength)
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
