#include <iostream>
using namespace std;
int  main()
{
    int val;

    //编译失败 在const lambda中修改常量   error: assignment of read-only variable ‘val’
  //  auto const_val_lambda = [=] () {val = 3;};

    //声明成为非const lambda
    auto mutable_val_lambda = [=] ()mutable {val = 3;};
    cout << val << "  ";
    //依然是const lambda 没有改变引用本身
    auto const_ref_lambda = [&] {val = 4; };
    cout << val << "  ";
    //依然是const lambda 通过哦参数传递val
    auto const_param_lambda = [&](int v) {v = 5; };
    const_param_lambda(val);
    cout << val << "  ";
    return 0;
}