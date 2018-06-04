#include <memory>
#include <iostream>
using namespace std;
class ConcreteElementA;
class ConcreteElementB;
class Element;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void VisitConcreteElementA(Element* elm) = 0;
    virtual void VisitConcreteElementB(Element* elm) = 0;
protected:
    Visitor() = default;
};

class ConcreteVisitorA:public Visitor
{
public:
    ConcreteVisitorA() = default;
    ~ConcreteVisitorA() = default;
    void VisitConcreteElementA(Element* elm);
    void VisitConcreteElementB(Element* elm);
};

void ConcreteVisitorA::VisitConcreteElementA(Element* elm)
{
    cout << "i will visit Visit ElementA" << endl;
}
void ConcreteVisitorA::VisitConcreteElementB(Element* elm)
{
    cout << "i will visit Visit ElementB" << endl;
}


class ConcreteVisitorB:public Visitor
{
public:
    ConcreteVisitorB() = default;
    ~ConcreteVisitorB() = default;
    void VisitConcreteElementA(Element* elm);
    void VisitConcreteElementB(Element* elm);
};

void ConcreteVisitorB::VisitConcreteElementA(Element* elm)
{
    cout << "i will visit Visit ElementA" << endl;
}
void ConcreteVisitorB::VisitConcreteElementB(Element* elm)
{
    cout << "i will visit Visit ElementB" << endl;
}

class Element
{
public:
    virtual ~Element() = default;
    virtual void Accept(Visitor* vis) = 0;
protected:
    Element() = default;
};

class ConcreteElementA: public Element
{
public:
    ConcreteElementA() = default;
    ~ConcreteElementA() = default;
    void Accept(Visitor* vis);
};

void ConcreteElementA::Accept(Visitor* vis)
{
    vis->VisitConcreteElementA(this);
    cout<<"visiting ConcreteElementA..."<<endl;
}
class ConcreteElementB: public Element
{
public:
    ConcreteElementB() = default;
    ~ConcreteElementB() = default;
    void Accept(Visitor* vis);
};

void ConcreteElementB::Accept(Visitor* vis)
{
    vis->VisitConcreteElementB(this);
    cout<<"visiting ConcreteElementB..."<<endl;
}


int main()
{
    shared_ptr<Visitor> vis {new ConcreteVisitorA()};
    shared_ptr<Element> elm {new ConcreteElementA()};
    elm->Accept(vis.get());
    return 0;
}
