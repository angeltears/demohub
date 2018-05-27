#include <iostream>
using namespace std;

int main()
{
    int j = 12;
    auto by_val_lambda = [=] {return j + 1; };
    auto by_ref_lambda = [&] {return j + 1; };

    cout << "by_val_lambda : " << by_val_lambda() << endl;
    cout << "by_ref_lambda : " << by_ref_lambda() << endl;
    j = j + 1;
    cout << "by_val_lambda : " << by_val_lambda() << endl;
    cout << "by_ref_lambda : " << by_ref_lambda() << endl;
}




//某种程度上 可以认为lambda函数的实现方式是仿函数的语法糖
//所以在捕捉值的时候，如果按值传递的话，捕捉的值将会成为lambda函数的常量
//如果按引用传递的话，捕捉的值将会成为lambda函数运行时的变量