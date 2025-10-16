#include <bits/stdc++.h>
using namespace std;
struct matrixTerm
{
    int row, col, value;
    matrixTerm &operator=(matrixTerm &rhs)
    {
        row = rhs.row, col = rhs.col, value = rhs.value;
        return *this;
    }
};
class sparseMatrix
{
private:
    int rows, cols, listSize = 0, arrayLength = 10;
    matrixTerm *terms;

public:
    sparseMatrix(int n, int m) : rows(n), cols(m), terms(new matrixTerm[arrayLength]) {}
    ~sparseMatrix() { delete[] terms; }
    sparseMatrix &operator=(sparseMatrix &rhs)
    {
        rows = rhs.rows, cols = rhs.cols, arrayLength = rhs.arrayLength, listSize = rhs.listSize;
        delete[] terms;
        terms = new matrixTerm[arrayLength];
        copy(rhs.terms, rhs.terms + listSize, terms);
        return *this;
    }
    void inputElement(int x, int y, int value)
    {
        matrixTerm NewElement;
        NewElement.row = x, NewElement.col = y, NewElement.value = value;
        if (listSize == arrayLength)
        {
            arrayLength *= 2;
            matrixTerm *newTerms = new matrixTerm[arrayLength];
            for (int i = 0; i < listSize; ++i)
            {
                newTerms[i] = terms[i];
            }
            delete[] terms;
            terms = newTerms;
        }
        terms[listSize++] = NewElement;
    }
    void initial(int n, int m)
    {
        rows = n, cols = m, listSize = 0;
        for (int i = 1; i <= rows; ++i)
        {
            for (int j = 1; j <= cols; ++j)
            {
                int v;
                cin >> v;
                if (v)
                    inputElement(i, j, v);
            }
        }
    }
    void transpose()
    {
        sparseMatrix t(cols, rows);
        t.listSize = this->listSize;
        delete[] t.terms;
        t.terms = new matrixTerm[this->arrayLength];
        t.arrayLength = this->arrayLength;
        int *colSize = new int[cols + 1], *rowNext = new int[cols + 1];
        for (int i = 1; i <= cols; ++i)
            colSize[i] = 0;
        for (int i = 0; i < listSize; ++i)
            colSize[terms[i].col]++;
        rowNext[1] = 0;
        for (int i = 2; i <= cols; i++)
            rowNext[i] = rowNext[i - 1] + colSize[i - 1];
        for (int i = 0; i < listSize; ++i)
        {
            int j = rowNext[terms[i].col]++;
            t.terms[j].row = this->terms[i].col, t.terms[j].col = this->terms[i].row, t.terms[j].value = this->terms[i].value;
        }
        *this = t;
        delete[] colSize;
        delete[] rowNext;
    }
    int add(sparseMatrix &rhs)
    {
        if (rows != rhs.rows || cols != rhs.cols)
        {
            *this = rhs;
            return -1;
        }
        sparseMatrix result(rows, cols);
        int it = 0, ib = 0;
        while (it != listSize && ib != rhs.listSize)
        {
            int tIndex = (terms[it].row) * cols + terms[it].col, bIndex = (rhs.terms[ib].row) * cols + rhs.terms[ib].col;
            if (tIndex < bIndex)
            {
                result.inputElement(terms[it].row, terms[it].col, terms[it].value);
                it++;
            }
            else if (tIndex > bIndex)
            {
                result.inputElement(rhs.terms[ib].row, rhs.terms[ib].col, rhs.terms[ib].value);
                ib++;
            }
            else
            {
                if (terms[it].value + rhs.terms[ib].value != 0)
                {
                    result.inputElement(terms[it].row, terms[it].col, terms[it].value + rhs.terms[ib].value);
                }
                it++, ib++;
            }
        }
        for (; it != listSize; ++it)
            result.inputElement(terms[it].row, terms[it].col, terms[it].value);
        for (; ib != rhs.listSize; ++ib)
            result.inputElement(rhs.terms[ib].row, rhs.terms[ib].col, rhs.terms[ib].value);
        *this = result;
        return 0;
    }
    int multiply(sparseMatrix &rhs)
    {
        if (cols != rhs.rows)
        {
            *this = rhs;
            return -1;
        }
        sparseMatrix C(rows, rhs.cols);
        int rowSize[10000] = {0}, rowNext[10000] = {0}, Answer[10000] = {0};
        for (int i = 0; i < rhs.listSize; i++)
        {
            rowSize[rhs.terms[i].row]++;
        }
        rowNext[1] = 0;
        for (int i = 2; i <= rhs.rows; ++i)
            rowNext[i] = rowNext[i - 1] + rowSize[i - 1];
        int p = 0;
        for (int i = 1; i <= rows; ++i)
        {
            fill(Answer, Answer + rhs.cols + 1, 0);
            while (p < listSize && terms[p].row == i)
            {
                int t = terms[p].col;
                for (int q = rowNext[t]; q < rowNext[t] + rowSize[t]; ++q)
                {
                    Answer[rhs.terms[q].col] += terms[p].value * rhs.terms[q].value;
                }
                p++;
            }
            for (int k = 1; k <= rhs.cols; ++k)
            {
                if (Answer[k] != 0)
                {
                    C.inputElement(i, k, Answer[k]);
                }
            }
        }
        *this = C;
        return 0;
    }
    void output()
    {
        int k = 0;
        cout << rows << " " << cols << endl;
        for (int i = 1; i <= rows; ++i)
        {
            for (int j = 1; j <= cols; ++j)
            {
                if (k < listSize && terms[k].row == i && terms[k].col == j)
                {
                    cout << terms[k].value << " ";
                    k++;
                }
                else
                    cout << "0 ";
            }
            cout << endl;
        }
    }
};
int main()
{
    // freopen("data.out", "w", stdout);
    sparseMatrix P(0, 0);
    int n, row, col, cnt, op, f;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> op;
        switch (op)
        {
        case 1:
        {
            cin >> row >> col;
            P.initial(row, col);
            break;
        }
        case 2:
        {
            cin >> row >> col >> cnt;
            sparseMatrix Q1(row, col);
            for (int j = 1; j <= cnt; ++j)
            {
                int x, y, value;
                cin >> x >> y >> value;
                Q1.inputElement(x, y, value);
            }
            f = P.multiply(Q1);
            if (f == -1)
                cout << f << endl;
            break;
        }
        case 3:
        {
            cin >> row >> col >> cnt;
            sparseMatrix Q2(row, col);
            for (int j = 1; j <= cnt; ++j)
            {
                int x, y, value;
                cin >> x >> y >> value;
                Q2.inputElement(x, y, value);
            }
            f = P.add(Q2);
            if (f == -1)
                cout << f << endl;
            break;
        }
        case 4:
        {
            P.output();
            break;
        }
        case 5:
        {
            P.transpose();
            break;
        }
        }
    }
    return 0;
}
