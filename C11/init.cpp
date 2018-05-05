#include <string>
#include <iostream>
using namespace std;

struct C
{
  C(int i):c(i){};
  int c = 3;
};

struct init
{
    int a = 1;
    string b{"hello"};
    C c{1};
};

int main(int argc, char const *argv[]) {
  C c(1);
  init in;
  cout<<in.c.c<<endl;
  return 0;
}
