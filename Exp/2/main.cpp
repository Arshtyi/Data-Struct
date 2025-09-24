#include <bits/stdc++.h>
template <class T>
class Sort
{
private:
    int size;
    T *arr;
    long long compCount, moveCount;

public:
    Sort(int n, const T *p) : size(n), compCount(0), moveCount(0)
    {
        arr = new T[size];
        for (int i = 0; i < size; ++i)
            arr[i] = p[i];
    }
    ~Sort() { delete[] arr; }
    void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
        moveCount += 3;
    }
    void printArray()
    {
        for (int i = 0; i < size; ++i)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
    }
    void resetCounts() { compCount = 0, moveCount = 0; }
    long long getComparisons() const { return compCount; }
    long long getMoves() const { return moveCount; }
    void countSort()
    {
        int r[size] = {0};
        for (int i = 0; i < size - 1; ++i)
        {
            for (int j = i + 1; j < size; ++j)
            {
                ++compCount;
                if (arr[i] <= arr[j])
                    ++r[j];
                else
                    ++r[i];
            }
        }
        for (int i = 0; i < size; ++i)
        {
            while (r[i] != i)
            {
                int t = r[i];
                swap(arr[i], arr[t]);
                swap(r[i], r[t]);
                printArray();
            }
        }
    }
    void SelectSort()
    {
        for (int end = size - 1; end > 0; --end)
        {
            int k = 0;
            for (int j = 1; j <= end; ++j)
            {
                ++compCount;
                if (arr[j] > arr[k])
                    k = j;
            }
            if (k != end)
            {
                swap(arr[k], arr[end]);
                printArray();
            }
            else
            {
                bool ordered = true;
                for (int i = 1; i < end; ++i)
                {
                    ++compCount;
                    if (arr[i - 1] > arr[i])
                    {
                        ordered = false;
                        break;
                    }
                }
                if (ordered)
                    break;
            }
        }
    }
    void BubbleSort()
    {
        int n = size;
        while (n > 1)
        {
            int lastSwap = 0;
            for (int j = 0; j < n - 1; ++j)
            {
                ++compCount;
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                    lastSwap = j + 1;
                    printArray();
                }
            }
            if (!lastSwap)
                break;
            n = lastSwap;
        }
    }
    void InsertSort()
    {
        for (int i = 1; i < size; ++i)
        {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0)
            {
                ++compCount;
                if (arr[j] > key)
                {
                    arr[j + 1] = arr[j];
                    ++moveCount;
                    --j;
                    printArray();
                }
                else
                    break;
            }
            arr[j + 1] = key;
            ++moveCount;
            printArray();
        }
    }
};
signed main()
{
    int n;
    std::cin >> n;
    int orig[n];
    for (int i = 0; i < n; i++)
        std::cin >> orig[i];
    auto test = [&](const std::string &name, void (Sort<int>::*method)())
    {
        std::cout << "=== " << name << " ===" << std::endl;
        Sort<int> s(n, orig);
        std::cout << "初始: ";
        s.printArray();
        (s.*method)();
        std::cout << "结果: ";
        s.printArray();
        std::cout << "比较次数: " << s.getComparisons() << "  移动次数: " << s.getMoves() << std::endl;
    };
    test("CountSort", &Sort<int>::countSort);
    test("SelectSort", &Sort<int>::SelectSort);
    test("BubbleSort", &Sort<int>::BubbleSort);
    test("InsertSort", &Sort<int>::InsertSort);
    return 0;
}
