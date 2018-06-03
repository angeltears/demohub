#include<iostream>
#include<memory>
using namespace std;

class Produce
{
public:
    Produce();
    ~Produce() = default;
    void ProducePart();
};
Produce::Produce()
{
    ProducePart();
    cout << "Return a product" << endl;
}
void Produce::ProducePart()
{
    cout << "build part of product." << endl;
}


class ProductPart
{
public:
    ProductPart();
    ~ProductPart() = default;
    ProductPart* BuildPart();
};

ProductPart::ProductPart()
{
    cout <<"bulid productpart." << endl;
}

ProductPart* ProductPart::BuildPart()
{
    return new ProductPart;
}

class Builder
{
public:
    virtual ~Builder() = default;
    virtual void BuildPartA(const string& buildPara) = 0;
    virtual void BuildPartB(const string& buildPara) = 0;
    virtual void BuildPartC(const string& buildPara) = 0;
    virtual Produce* GetProduct() = 0;
protected:
    Builder() = default;
};

class ConcreteBuilder:public Builder
{
public:
    ConcreteBuilder() = default;
    ~ConcreteBuilder() = default;
    void BuildPartA(const string& buildPara);
    void BuildPartB(const string& buildPara);
    void BuildPartC(const string& buildPara);
    Produce* GetProduct();
};

void ConcreteBuilder::BuildPartA(const string& buildPara)
{
    cout<<"Step1:Build PartA..."<<buildPara<<endl;
}
void ConcreteBuilder::BuildPartB(const string& buildPara)
{
    cout<<"Step1:Build PartB..."<<buildPara<<endl;
}
void ConcreteBuilder::BuildPartC(const string& buildPara)
{
    cout<<"Step1:Build PartC..."<<buildPara<<endl;
}
Produce* ConcreteBuilder::GetProduct()
{
    BuildPartA("pre-defined");
    BuildPartB("pre-defined");
    BuildPartC("pre-defined");
    return new Produce();
}


class Director
{
public:
    Director(Builder* bld);
    ~Director() = default;
    void Construct();
private:
    Builder* _bld;
};

Director::Director(Builder* bld)
{
_bld = bld;
}

void Director::Construct()
{
    _bld->BuildPartA("1");
    _bld->BuildPartB("12");
    _bld->BuildPartC("123");
}

int main(int argc,char* argv[])
{
    shared_ptr<Director> d {new Director(new ConcreteBuilder())};
    d->Construct();
    return 0;
}