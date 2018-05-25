#include <iostream>
using namespace std;

constexpr int Fibonacci(int n)
{
    return (n == 1) ? 1 : (n == 2) ? 1 : Fibonacci(n - 1) + Fibonacci(n - 2);
}


int main()
{
    int fib[] = 
    {
        Fibonacci(11), Fibonacci(12),
        Fibonacci(13), Fibonacci(14),
        Fibonacci(15), Fibonacci(16)
    };
    for(int i : fib)
        cout << i <<" ";
    cout << endl;
}

//实际上 在编译期间 数值已经被计算，运行代码时并没有调用Fibonacci函数
//常量函数表达式  必须只有单一return返回语句 使用前必须定义 return 返回语句必须是一个常量表达式
//常量表达式 在编译器确定 如果没有显示使用 编译器可以选择不为其分配空间 
//常量构造函数表达式 函数体必须为空 初始化列表只能由表达式来赋值