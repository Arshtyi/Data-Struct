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
    T &operator[](int i)
    {
        if (i < 0 || i >= listSize)
            throw "Index out of bounds";
        return arr[i];
    }
    const T &operator[](int i) const
    {
        if (i < 0 || i >= listSize)
            throw "Index out of bounds";
        return arr[i];
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
template <class T>
class matrixTerm
{
public:
    int row, col;
    T value;
    matrixTerm(int r = 0, int c = 0, T v = 0) : row(r), col(c), value(v) {}
};
template <class T>
class sparseMatrix
{
private:
    int rows, cols;
    arrayList<matrixTerm<T>> terms;

public:
    sparseMatrix(int r, int c) : rows(r), cols(c), terms(10) {}
    T get(const int &r, const int &c) const
    {
        for (int i = 0; i < terms.size(); i++)
            if (terms[i].row == r && terms[i].col == c)
                return terms[i].value;
        return T();
    }
    void set(const int &r, const int &c, const T &v)
    {
        for (int i = 0; i < terms.size(); i++)
        {
            if (terms[i].row == r && terms[i].col == c)
            {
                if (v == 0)
                    terms.pop_back();
                else
                    terms[i].value = v;
                return;
            }
        }
        if (v != 0)
            terms.push_back(matrixTerm<T>(r, c, v));
    }
};
signed main()
{
    sparseMatrix<int> sm(5, 5);
    sm.set(1, 2, 10);
    sm.set(3, 4, 20);
    std::cout << "Value at (1, 2): " << sm.get(1, 2) << std::endl;
    std::cout << "Value at (3, 4): " << sm.get(3, 4) << std::endl;
    return 0;
}
