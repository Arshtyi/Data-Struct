#include <bits/stdc++.h>
template <class T>
class arrayList
{
private:
    T *arr;
    int capacity, listSize;

public:
    arrayList(int s)
    {
        if (s < 1)
            throw "Size must be > 0";
        capacity = s, listSize = 0;
        arr = new T[capacity];
    }
    ~arrayList() { delete[] arr; }
    int size() const { return listSize; }
    void push_back(const T &x)
    {
        if (listSize == capacity)
        {
            T *old = arr;
            capacity *= 2;
            arr = new T[capacity];
            for (int i = 0; i < listSize; i++)
                arr[i] = old[i];
            delete[] old;
        }
        arr[listSize++] = x;
    }
    void pop_back()
    {
        if (listSize == 0)
            throw "List is empty";
        listSize--;
    }
    void print() const
    {
        std::cout << "Capacity: " << capacity << ", Size: " << listSize << ", Elements: ";
        for (int i = 0; i < listSize; i++)
            std::cout << arr[i] << " ";
        std::cout << "\n";
    }
    void reserve(int s)
    {
        capacity = std::max(s, capacity);
        T *old = arr;
        arr = new T[capacity];
        for (int i = 0; i < listSize; i++)
            arr[i] = old[i];
        delete[] old;
    }
    void clear()
    {
        listSize = 0;
        delete[] arr;
        arr = new T[capacity];
    }
};
signed main()
{
    arrayList<int> arr(2);
    arr.push_back(1), arr.push_back(2);
    arr.print();
    arr.reserve(100);
    arr.print();
    arr.clear();
    arr.print();
    return 0;
}
