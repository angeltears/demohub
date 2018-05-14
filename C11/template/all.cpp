//c98标准和c11共有的模板类
template<typename T1, typename T2 = int> class Defclass1;
//template<typename T1 = int; typename T2> class Defclass2; 此项编译不通过 没有遵循从右到左的规则指定默认值
template<typename T1, int a = 0>class Defclass3;
//template<int a = 0, typename T1>class Defclass4;   同上

//c11特有的函数模板
template<typename T1 = int, typename T2>
void DefFunc1(T1 a, T2  b);
template<int i = 0, typename T>
void DefFunc2(T a);
//如果可以从函数的形参推导出实参的话就不需要默认参数
template<class T, class U = double>
void f(T t = 0, U u = 0)
{

}
int main()
{
    f(1, 'c');          //f<int, char>
    f(1);               //f<int, double>
   // f();                //T无法被推导出来 可以看出默认参数不能作为推导依据
    f<int>();           //f<int, double>
    f<int, char>();     //f<int, char>
    return 0;
}