#include<iostream>
#include<typeinfo>
using namespace std;
int i;
int arr[5];
int *ptr = arr;
struct S {double d; } s;

void overload(int) {}
void overload(char) {}

int && RvalRef();

const bool Func(int);

decltype(arr) val1;          //int[5] 标记符表达式
decltype(ptr) val2;          //int * 标记符表达式
decltype(s.d) val3;          //double 成员表达式
//decltype(overload) val4;     //重载函数 无法通过编译


decltype(RvalRef()) val5 = 1;    //int&&  将亡值推导

decltype(1?i : i) val6 = i;   // int&& 三元运算符，在这里返回一个i的左值
decltype((i)) val7 = i;              // int& 带圆括号的左值
decltype(++i) val8 = i ;        // int& ++i的左值
decltype(arr[3]) val9 = i;        // int& [] 操作返回左值
decltype(*ptr) val10 = i ;        // int& *ptr 返回左值
decltype("lval") val11 = "lval";        // const char(&) [9]


decltype(i++)  value12;     //int i++返回右值

int main()
{
    cout << typeid(val1).name() << endl;
    cout << typeid(val11).name() << endl;
}