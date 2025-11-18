#include <iostream>
#include <string>
using namespace std;
struct Node
{
    char ch;
    int freq;
    Node() : ch('\0'), freq(0) {}
    Node(char c, int f) : ch(c), freq(f) {}
    bool operator>(const Node &rhs) const { return freq > rhs.freq; }
    bool operator<=(const Node &rhs) const { return !(*this > rhs); }
};
template <class T>
class minHeap
{
private:
    T *heap;
    int arrayLength, heapSize;

public:
    minHeap(int initialCapacity = 10) : arrayLength(initialCapacity + 1), heapSize(0), heap(new T[arrayLength]) {}
    ~minHeap() { delete[] heap; }
    int size() { return heapSize; }
    void initialize(T *theHeap, int n)
    {
        delete[] heap;
        heap = new T[n + 1];
        for (int i = 1; i <= n; ++i)
            heap[i] = theHeap[i];
        heap[0] = T();
        arrayLength = n + 1, heapSize = n;
        for (int root = heapSize / 2; root >= 1; --root)
        {
            T rootElement = heap[root];
            int child = 2 * root;
            while (child <= heapSize)
            {
                if (child < heapSize && heap[child] > heap[child + 1])
                    child++;
                if (rootElement <= heap[child])
                    break;
                heap[child / 2] = heap[child], child *= 2;
            }
            heap[child / 2] = rootElement;
        }
    }
    void push(const T &theElement)
    {
        if (heapSize == arrayLength - 1)
        {
            arrayLength *= 2;
            T *newHeap = new T[arrayLength];
            for (int i = 1; i <= heapSize; ++i)
                newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }
        int currentNode = ++heapSize;
        while (currentNode != 1 && heap[currentNode / 2] > theElement)
            heap[currentNode] = heap[currentNode / 2], currentNode /= 2;
        heap[currentNode] = theElement;
    }
    const T &top()
    {
        if (heapSize == 0)
            throw runtime_error("Heap is empty!");
        return heap[1];
    }
    T pop()
    {
        if (heapSize == 0)
            throw runtime_error("Heap is empty!");
        T minElement = heap[1], lastElement = heap[heapSize--];
        int currentNode = 1,
            child = 2;
        while (child <= heapSize)
        {
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            if (lastElement <= heap[child])
                break;
            heap[currentNode] = heap[child], currentNode = child, child *= 2;
        }
        heap[currentNode] = lastElement;
        return minElement;
    }
};
int huffmanLength(const string &str)
{
    int freq[26] = {0}, uniqueCount = 0;
    for (char c : str)
    {
        if (!freq[c - 'a'])
            uniqueCount++;
        freq[c - 'a']++;
    }
    minHeap<Node> pq;
    Node *nodes = new Node[uniqueCount + 1];
    int nodeCount = 0;
    for (int i = 0; i < 26; ++i)
        if (freq[i] > 0)
            nodes[++nodeCount] = Node('a' + i, freq[i]);
    pq.initialize(nodes, nodeCount);
    int length = 0;
    while (pq.top().freq != 0 && pq.size() > 1)
    {
        Node left = pq.pop(), right = pq.pop(), combined('\0', left.freq + right.freq);
        pq.push(combined);
        length += left.freq + right.freq;
    }
    return length;
}
string input;
int main()
{
    cin >> input;
    cout << huffmanLength(input) << endl;
    return 0;
}
