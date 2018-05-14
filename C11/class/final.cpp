struct Object
{
    virtual void fun() = 0;
};

struct Rase:public Object
{
    void fun() final;
};

struct Derived:public Rase
{
    //不可以继续重载　fun();
   // void fun();
};


int main()
{
    return 0;
}