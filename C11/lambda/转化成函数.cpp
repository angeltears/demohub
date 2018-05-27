int main()
{
    int girls = 3, boys = 4;
    auto totalChild = [] (int x, int y)-> int{return x + y;};
    typedef int (*allChild) (int x, int y);

    allChild p;
    p = totalChild;

    decltype(totalChild) allPeople = totalChild;
  //  decltype(totalChild  totalPeople = p;
    return 0;
}

//转化成函数的lambda必须要求没有捕捉任何变量，且函数指针所指向的函数原型必须跟lambda函数有着相同的调用方式
//函数指针不能转化为lambda函数