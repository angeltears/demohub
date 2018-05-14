class Ploy;
typedef Ploy P;

class LiLei
{
  friend class Ploy;
};

class Jim
{
  friend Ploy;
};

class HanMeiMei
{
  friend P;
};

template<typename T>class Peopel
{
  friend T;
};

int main()
{
  Peopel<P> pp;
  Peopel<int> Pi;
  return 0;
}
