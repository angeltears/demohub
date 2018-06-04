#include <iostream>
using namespace std;

class Target
{
public:
    virtual ~Target() = default;
    virtual void Request() = 0;
protected:
    Target() = default;
};
void Target::Request()
{
    std::cout<<"Target::Request"<<std::endl;
}
class Adaptee
{
public:
    Adaptee() = default;
    ~Adaptee() = default;
    void SpecificRequest();
};

void Adaptee::SpecificRequest()
{
    std::cout<<"Adaptee::SpecificRequest"<<std::endl;
}

class Adapter:public Target, private Adaptee
{
public:
    Adapter() = default;
    ~Adapter() = default;
    void Request();
};

void Adapter::Request()
{
    this->SpecificRequest();
}
int main(int argc,char* argv[])
{
    Target* adt = new Adapter();
    adt->Request();
    delete adt;
    return 0;
}
