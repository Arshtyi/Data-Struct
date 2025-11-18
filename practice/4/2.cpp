#include <bits/stdc++.h>
class LowerTriangularMatrix
{
private:
    double *data;
    int n;

public:
    LowerTriangularMatrix(int size) : n(size), data(new double[n * (n + 1) / 2]) {}
    ~LowerTriangularMatrix() { delete[] data; }
    void set(int i, int j, double value)
    {
        if (i >= j)
            data[i * (i + 1) / 2 + j] = value;
    }
    double get(int i, int j) { return (i >= j) ? data[i * (i + 1) / 2 + j] : 0; }
    int size() { return n; }
};
class UpperTriangularMatrix
{
private:
    double *data;
    int n;

public:
    UpperTriangularMatrix(int size) : n(size), data(new double[n * (n + 1) / 2]) {}
    ~UpperTriangularMatrix() { delete[] data; }
    void set(int i, int j, double value)
    {
        if (i <= j)
            data[i * n - i * (i - 1) / 2 + (j - i)] = value;
    }
    double get(int i, int j) { return (i <= j) ? data[i * n - i * (i - 1) / 2 + (j - i)] : 0; }
    int size() { return n; }
};
class Matrix
{
private:
    double **data;
    int n;

public:
    Matrix(int size)
    {
        n = size;
        data = new double *[n];
        for (int i = 0; i < n; i++)
        {
            data[i] = new double[n];
            for (int j = 0; j < n; j++)
                data[i][j] = 0;
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < n; i++)
            delete[] data[i];
        delete[] data;
    }
    void set(int i, int j, int value) { data[i][j] = value; }
    double get(int i, int j) { return data[i][j]; }
    int size() { return n; }
    void output()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }
    }
};
void multiply(LowerTriangularMatrix &low, UpperTriangularMatrix up, Matrix &m)
{
    int n = low.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int sum_result = 0;
            for (int k = 0; k <= i; k++)
                sum_result += low.get(i, k) * up.get(k, j);
            m.set(i, j, sum_result);
        }
    }
}
