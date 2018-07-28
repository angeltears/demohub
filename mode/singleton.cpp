#include <iostream>
#include <memory>
using namespace std;
class Singleton
{
public:
    static Singleton*   Instance();
    class obstack
    {
        public:
        ~obstack()
        {
            if(_instance != nullptr)
                 delete _instance;
        }
    };
    friend class obstack;
    static obstack ob;
    ~Singleton()
    {
         cout<<"~Singleton...."<<endl;
    }
protected:
    Singleton();
private:
    
    static Singleton* _instance;
};
Singleton* Singleton:: _instance = nullptr;
Singleton::obstack Singleton::ob; 
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
    Singleton* sgn =  Singleton::Instance() ;
    Singleton* sgn2 =  Singleton::Instance() ;
    Singleton* sgn3 =  Singleton::Instance() ;
    return 0;
}