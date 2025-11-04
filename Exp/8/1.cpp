#include <iostream>
using namespace std;
template <class E, class K>
class HashTable
{
private:
    int D;
    E *hash_table;
    bool *empty;
    int hSearch(const K &k) const
    {
        int index = k % D, real_index = index;
        do
        {
            if (empty[real_index] || hash_table[real_index] == k)
                return real_index;
            real_index = (real_index + 1) % D;
        } while (real_index != index);
        return real_index;
    }

public:
    HashTable(int divisor = 11) : D(divisor), hash_table(new E[D]), empty(new bool[D])
    {
        for (int i = 0; i < D; i++)
            empty[i] = true;
    }
    ~HashTable()
    {
        delete[] hash_table;
        delete[] empty;
    }
    void Search(const K &k, E &e)
    {
        int place = hSearch(k);
        if (empty[place] || hash_table[place] != k)
            cout << -1 << endl;
        else
            cout << place << endl;
    }
    HashTable<E, K> &Insert(const E &e)
    {
        K k = e;
        int place = hSearch(k);
        if (empty[place])
        {
            empty[place] = false;
            hash_table[place] = e;
            cout << place << endl;
        }
        else
            cout << "Existed" << endl;
        return *this;
    }
    int Delete(const E &e)
    {
        K k = e;
        int place = hSearch(k), cnt = 0;
        if (empty[place])
        {
            cout << "Not Found" << endl;
            return -1;
        }
        else if (hash_table[place] == k)
        {
            empty[place] = true;
            int index_1 = place, index_2 = place, hash_index;
            do
            {
                index_1 = (index_1 + 1) % D;
                if (empty[index_1])
                    break;
                hash_index = hash_table[index_1] % D;
                if ((index_1 != hash_index && index_1 > index_2 && hash_index <= index_2) || (index_1 < hash_index && (index_2 < index_1 || index_2 >= hash_index)))
                {
                    empty[index_2] = false;
                    hash_table[index_2] = hash_table[index_1];
                    empty[index_1] = true;
                    cnt++;
                    index_2 = index_1;
                }
            } while (!empty[index_1 + 1] && (index_1 + 1) != index_2);
        }
        cout << cnt << endl;
        return cnt;
    }
};
int D, m;
int main()
{
    cin >> D >> m;
    HashTable<int, int> table(D);
    for (int i = 1; i <= m; ++i)
    {
        int opt, x;
        cin >> opt >> x;
        if (opt == 0)
            table.Insert(x);
        else if (opt == 1)
            table.Search(x, x);
        else
            table.Delete(x);
    }
    return 0;
}
