#include <iostream>
#include <memory>
using namespace std;

class Prototype
{
public:
    virtual ~Prototype()=default;
    virtual Prototype* Clone() const = 0;
protected:
    Prototype() = default;
};

class ConcretePrototype:public Prototype
{
public:
    ConcretePrototype() = default;
    ~ConcretePrototype() = default;
    ConcretePrototype(const ConcretePrototype& cp);
    Prototype* Clone() const;
};

ConcretePrototype::ConcretePrototype(const ConcretePrototype& cp)
{
    cout<< "ConcretePrototype copy." << endl;
}
Prototype* ConcretePrototype::Clone() const
{
    cout << "clone." <<endl;
    return new ConcretePrototype(*this);
}

int main(int argc,char* argv[])
{
    shared_ptr<Prototype> p { new ConcretePrototype()};
    shared_ptr<Prototype> p1 { p->Clone() };
    return 0;
}