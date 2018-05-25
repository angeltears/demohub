#include <iostream>
#include<type_traits>
using namespace std;

enum class type {General, Light};
enum class Category{General = 1, Pistol};


int main()
{
    type t = type::Light;
 //   t = General;                  //was not declared in this scope
 //   if (t == Category::General)     //no match for ‘operator==’ (operand types are ‘type’ and ‘Category’)
    {
        cout << "General weapon" << endl;
    }
    if (t > type::General)
    {
        cout << "Not weapon" << endl;
    }
//    if (t > 0)      // no match for ‘operator>’ (operand types are ‘type’ and ‘int’)
    {                    
         cout << "Not weapon" << endl;
    }
    if ((int) t > 0)
    {
          cout << "Not weapon" << endl;       
    }

    cout << is_pod<type>::value <<endl;
    return 0;
}