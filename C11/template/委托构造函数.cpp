#include <iostream>
using namespace std;
class Info
{
public:
    Info(int i)
    {
        initRest(i);
    }
    Info(char b):Info(2)    //委托构造节省大量代码　但是不能同时委托和冒号语法成员初始化
    {
        name = b;
    }
    void initRest(int i)
    { 
        type = i;
        name = 'd';
    }
    int type {1};
    char name{'a'};

};

int main()
{
    Info b('c');
    cout << b.type << " " <<b.name<<endl;
    return 0;
}

