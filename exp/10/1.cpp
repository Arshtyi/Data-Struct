#include <iostream>
using namespace std;
template <class T>
class minHeap
{
private:
    T *heap;
    int arrayLength, heapSize;

public:
    minHeap(int initialCapacity = 10) : arrayLength(initialCapacity + 1), heapSize(0), heap(new T[arrayLength]) {}
    ~minHeap() { delete[] heap; }
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
    void heapSort(T *a, int n)
    {
        T *tempHeap = new T[n + 1];
        for (int i = 1; i <= n; ++i)
            tempHeap[i] = a[i];
        tempHeap[0] = T();
        initialize(tempHeap, n);
        for (int i = n; i >= 1; --i)
        {
            cout << heap[1] << " ";
            pop();
        }
        cout << endl;
        delete[] tempHeap;
    }
};
int n, m, op;
minHeap<int> min_heap;
int main()
{
    cin >> n;
    int *arr = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    min_heap.initialize(arr, n);
    cout << min_heap.top() << endl;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> op;
        if (op == 1)
        {
            int num;
            cin >> num;
            min_heap.push(num);
            cout << min_heap.top() << endl;
        }
        else if (op == 2)
            min_heap.pop(), cout << min_heap.top() << endl;
        else
        {
            int nn;
            cin >> nn;
            int *arr2 = new int[nn + 1];
            for (int j = 1; j <= nn; ++j)
                cin >> arr2[j];
            min_heap.heapSort(arr2, nn);
            delete[] arr2;
        }
    }
    delete[] arr;
    return 0;
}
