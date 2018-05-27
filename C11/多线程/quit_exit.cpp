#include <iostream>
#include <cstdlib>
using namespace std;

struct A{
    ~A ()
    {
        cout << "Destruct A." << endl;
    }
};


void closedevice()
{
    cout <<" device is close " << endl;
}


int main()
{
    A a;
    at_quick_exit(closedevice);
    quick_exit(0);
}