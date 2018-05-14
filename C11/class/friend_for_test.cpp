template<typename T>
class DefenderT
{
public:
    friend T;
    void Defence(int x, int y){}
    void Tackle(int x, int y){}

private:
    int pos_x = 15;
    int pos_y = 0;
    int speed = 2;
    int stamina = 120;
};

template<typename T>
class AttackerT
{
public:
    friend T;
    void Move(int x, int y){}
    void SpeedUp(int x, int y){}

private:
    int pos_x = 15;
    int pos_y = 0;
    int speed = 2;
    int stamina = 120;
};

using Defender = DefenderT<int>;
using Attacker = AttackerT<int>;

#define  UNIT_TEST
#ifdef UNIT_TEST
class Validator;
using DefenderTest = DefenderT<Validator>;
using AttackerTest = AttackerT<Validator>;
class Validator
{
public:

    void Validata(int x, int y, DefenderTest &d){};
    void Validata(int x, int y, AttackerTest &d){};
};


int main()
{
    DefenderTest d;
    AttackerTest a;
    Validator v;
    v.Validata(1,2,d);
    v.Validata(1,2,a);
}
#endif