#include <vector>
#include <string>
#include <iostream>
using namespace std;

enum Gender{boy, girl};
class Peopel
{
public:
    Peopel(initializer_list<pair<string, Gender>> l)
    {
        auto i = l.begin();
        for (; i != l.end(); ++i)
        {
            data.push_back(*i);
        }
    }
private:
    vector<pair<string, Gender>> data;
};

void Fun(initializer_list<int> iv){}


class Mydata
{
public:
    Mydata & operator[] (initializer_list<int> l)
    {
        for (auto i = l.begin(); i != l.end(); ++i)
        {
            idx.push_back(*i);
        }
        return *this;
    }
    Mydata & operator = (int v)
    {
        if (idx.empty() != true)
        {
            for (auto i = idx.begin(); i != idx.end(); ++i)
            {
                d.resize(max<int>(*i, d.size()));
                d[*i - 1] = v;
            }
            idx.clear();
        }
        return *this;
    }
    void print()
    {
        for (auto i = d.begin(); i != d.end(); ++i)
        {
            cout << *i <<" ";
        }
        cout << endl;
    }
private:
    vector<int> idx;
    vector<int> d;
};

int main()
{
    Peopel ship2012 = {{"Garfield", b0oy}, {"HelloKitty", girl}};
    Fun ({1, 2});
    Mydata d;
    d[{2, 4 ,7}] = 7;
    d[{1, 3 ,6}] = 2;
    d.print();
    return 0;
}