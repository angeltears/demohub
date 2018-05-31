#include <memory>
#include <iostream>
using namespace std;

class AbstratProductA
{
public:
    virtual ~AbstratProductA() = default;
protected:
    AbstratProductA() = default;
};


class AbstratProductB
{
public:
    virtual ~AbstratProductB() = default;
protected:
    AbstratProductB() = default;
};


class AbstratFactory
{
public:
    virtual ~AbstratFactory() = default;
    virtual AbstratProductA* CreateProduceA() = 0; 
    virtual AbstratProductB* CreateProduceB() = 0;
};

class ProductA1:public AbstratProductA
{
public:
     ProductA1();
     ~ProductA1() = default;
};

ProductA1::ProductA1()
{
    cout << "ProductA1" <<endl;
}

class ProductA2:public AbstratProductA
{
public:
     ProductA2();
     ~ProductA2() = default;
};

ProductA2::ProductA2()
{
    cout << "ProductA2" <<endl;
}

class ProductB1:public AbstratProductB
{
public:
     ProductB1();
     ~ProductB1() = default;
};

ProductB1::ProductB1()
{
    cout << "ProductB1" <<endl;
}

class ProductB2:public AbstratProductB
{
public:
     ProductB2();
     ~ProductB2() = default;
};

ProductB2::ProductB2()
{
    cout << "ProductB2" <<endl;
}


class ConcreteFactory1:public AbstratFactory
{
public:
    ConcreteFactory1();
    AbstratProductA* CreateProduceA() override;  
    AbstratProductB* CreateProduceB() override;
};

ConcreteFactory1::ConcreteFactory1()
{
    cout << "ConcreteFactory1" <<endl;
}

AbstratProductA* ConcreteFactory1::CreateProduceA()
{
    return new ProductA1();
}
AbstratProductB* ConcreteFactory1::CreateProduceB()
{
    return new ProductB1();
}

class ConcreteFactory2:public AbstratFactory
{
public:
    ConcreteFactory2();
    AbstratProductA* CreateProduceA() override;  
    AbstratProductB* CreateProduceB() override;
};

ConcreteFactory2::ConcreteFactory2()
{
    cout << "ConcreteFactory2" <<endl;
}

AbstratProductA* ConcreteFactory2::CreateProduceA()
{
    return new ProductA2();
}
AbstratProductB* ConcreteFactory2::CreateProduceB()
{
    return new ProductB2();
}

int main(int argc,char* argv[])
{
    AbstratFactory* cf1 = new ConcreteFactory1();
    cf1->CreateProduceA();
    cf1->CreateProduceB();
    AbstratFactory* cf2 = new ConcreteFactory2();
    cf2->CreateProduceA();
    cf2->CreateProduceB();
return 0;
}