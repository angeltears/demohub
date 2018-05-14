struct Base
{
    virtual void Turing() = 0;
    virtual void Dijkstra() = 0;
};

struct DerivedMid: public Base
{
    void Turing();
};

struct DerivedTop:public DerivedMid
{
    void Turing() override;
    //跨代重载
    void Dijkstra() override;
    //上层没有虚函数，不可以重载
    //void asdasd() override;

    //常量和参数的不一致都会被检测来
    //没有声明为虚函数的函数也会被检测出来
    
};

int main ()
{
    return 0;
}