#include <bits/stdc++.h>
using namespace std;
class Contact
{
private:
    string Name, Telephone;
    int Class, Dorm;

public:
    Contact() {}
    void Input() { cin >> Name >> Telephone >> Class >> Dorm; }
    string get_Name() { return Name; }
    string get_Telephone() { return Telephone; }
    int get_Class() { return Class; }
    int get_Dorm() { return Dorm; }
    void change_Tele(string &tele) { Telephone = tele; }
    void change_Class(int cla) { Class = cla; }
    void change_Dorm(int d) { Dorm = d; }
};
template <class T>
class arrayList
{
private:
    T *element;
    int arrayLength, listSize;

public:
    arrayList(int initialCapacity = 10)
    {
        arrayLength = initialCapacity;
        element = new T[arrayLength];
        listSize = 0;
    }
    arrayList(const arrayList<T> &arr)
    {
        arrayLength = arr.arrayLength;
        listSize = arr.listSize;
        element = new T[arrayLength];
        copy(arr.element, arr.element + listSize, element);
    }
    ~arrayList() { delete[] element; }
    int get_Size() { return listSize; }
    void checkIndex(int theIndex) const
    {
        if (theIndex < 0 || theIndex >= listSize)
        {
            std::ostringstream s;
            s << "index = " << theIndex << "size = " << listSize;
            cout << s.str() << endl;
            exit(0);
        }
    }
    void push_back(const T &theElement)
    {
        if (listSize == arrayLength)
        {
            arrayLength *= 2;
            T *newElement = new T[arrayLength];
            for (int i = 0; i < listSize; ++i)
                newElement[i] = element[i];
            delete[] element;
            element = newElement;
        }
        element[listSize++] = theElement;
    }
    void erase(int theIndex)
    {
        checkIndex(theIndex);
        std::copy(element + theIndex + 1, element + listSize, element + theIndex);
        element[--listSize].~T();
    }
    T &get(int theIndex)
    {
        checkIndex(theIndex);
        return element[theIndex];
    }
};
class Contact_List
{
private:
    arrayList<Contact *> contact_list;

public:
    Contact_List() {}
    ~Contact_List() {}
    void Insert_Contact()
    {
        Contact *c = new Contact;
        c->Input();
        contact_list.push_back(c);
    }
    void Delete_Contact(const string &name)
    {
        for (int i = 0; i < contact_list.get_Size(); i++)
            if (contact_list.get(i)->get_Name() == name)
            {
                Contact *p = contact_list.get(i);
                delete p;
                contact_list.erase(i);
            }
    }
    void Edit_Contact(const string &name)
    {
        int index;
        for (int i = 0; i < contact_list.get_Size(); i++)
            if (contact_list.get(i)->get_Name() == name)
                index = i;
        int oper;
        cin >> oper;
        switch (oper)
        {
        case 1:
        {
            string tele;
            cin >> tele;
            contact_list.get(index)->change_Tele(tele);
        }
        break;
        case 2:
        {
            int cla;
            cin >> cla;
            contact_list.get(index)->change_Class(cla);
        }
        break;
        case 3:
        {
            int d;
            cin >> d;
            contact_list.get(index)->change_Dorm(d);
        }
        break;
        }
    }
    void Search_Contact(const string &name)
    {
        for (int i = 0; i < contact_list.get_Size(); i++)
            if (contact_list.get(i)->get_Name() == name)
            {
                cout << "1" << endl;
                return;
            }
        cout << "0" << endl;
    }
    void Output_Contact(int cla)
    {
        int sum = 0;
        for (int i = 0; i < contact_list.get_Size(); i++)
            if (contact_list.get(i)->get_Class() == cla)
                sum ^= contact_list.get(i)->get_Dorm();
        cout << sum << endl;
    }
};
signed main()
{
    Contact_List con_list;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int oper_1;
        cin >> oper_1;
        switch (oper_1)
        {
        case 0:
            con_list.Insert_Contact();
            break;
        case 1:
        {
            string name_1;
            cin >> name_1;
            con_list.Delete_Contact(name_1);
        }
        break;
        case 2:
        {
            string name_2;
            cin >> name_2;
            con_list.Edit_Contact(name_2);
        }
        break;
        case 3:
        {
            string name_3;
            cin >> name_3;
            con_list.Search_Contact(name_3);
        }
        break;
        case 4:
        {
            int cl;
            cin >> cl;
            con_list.Output_Contact(cl);
        }
        break;
        }
    }
    return 0;
}
