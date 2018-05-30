#include <iostream>
#include <memory>
using namespace std;

class Singleton
{
public:
    static Singleton*   Instance();

protected:
    Singleton();
private:
    static Singleton* _instance;
};
Singleton* Singleton:: _instance = nullptr;

Singleton::Singleton()
{
    cout<<"Singleton...."<<endl;
}
Singleton* Singleton::Instance()
{
    if (_instance == 0)
    {
      _instance = new Singleton();
    }
    return _instance;
}


int main()
{
    shared_ptr<Singleton> sgn { Singleton::Instance() };
    shared_ptr<Singleton> sgn2 { Singleton::Instance() };
    return 0;
}