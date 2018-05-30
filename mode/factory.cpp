#include <iostream>
#include <memory>
using namespace std;

class Product
{
public:
    virtual ~Product() =  default;
protected:
    Product() = default;
};

class ConcreteProduce: public Product
{
public:
    ~ConcreteProduce()= default;
    ConcreteProduce();
};

ConcreteProduce::ConcreteProduce()
{
    cout << "ConcreteProduce" << endl;
}

class ConcreteProduce1: public Product
{
public:
    ~ConcreteProduce1()= default;
    ConcreteProduce1();
};

ConcreteProduce1::ConcreteProduce1()
{
    cout << "ConcreteProduce1" << endl;
}


class Factory
{
public:
    virtual ~Factory() = default;
    virtual Product* CreateProduct() = 0;
protected:
    Factory() = default;
private:
};


class ConcreteFactory : public Factory
{
public:
    ~ConcreteFactory() = default;
    Product* CreateProduct();
    ConcreteFactory();   
};

ConcreteFactory:: ConcreteFactory()
{
    cout << "ConcreteFactory" << endl;    
}

Product* ConcreteFactory::CreateProduct()
{
    return new ConcreteProduce;
}

class ConcreteFactory1 : public Factory
{
public:
    ~ConcreteFactory1 () = default;
    Product* CreateProduct();
    ConcreteFactory1();   
};

ConcreteFactory1:: ConcreteFactory1()
{
    cout << "ConcreteFactory1" << endl;    
}

Product* ConcreteFactory1::CreateProduct()
{
    return new ConcreteProduce1;
}

int main()
{
    Factory *fac = new ConcreteFactory();
    Product *p  = fac->CreateProduct();
    Factory *fac1 = new ConcreteFactory1();
    Product *p1 = fac->CreateProduct();
}