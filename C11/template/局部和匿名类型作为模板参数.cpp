template<typename T>class X {};
template<typename T>void TempFun(T t){};
struct {int i; }b;
typedef struct {int i; }B;

int main()
{
    struct C{} c;
    X<B> x2;
    X<C> x3;
    TempFun(b);
    TempFun(c);
}
  