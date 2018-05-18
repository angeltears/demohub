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

class Info2
{
public:
    Info2(): Info2(1){}
    Info2(int i):Info2(i, 'a'){}     //注意不要生成委托环
    Info2(char b):Info2(1, b) {}
private:
    Info2(int i, char e):type(i), name(e){}   //不允许带默认参数
    int type {1};
    char name{'a'};
};
int main()
{
    Info b('c');
    Info2 c('c');
    cout << b.type << " " <<b.name<<endl;
    return 0;
}

