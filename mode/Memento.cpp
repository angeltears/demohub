#include <iostream>
#include <memory>
#include <string>
using namespace std;
typedef string State;
class Memento;
class Originator
{
public:
    Originator() = default;
    ~Originator() = default;
    Originator(const State& std);
    Memento* CreateMemento();
    void RestoreToMemento(Memento* mt);
    State GetState();
    void SetState(const State& std);
    void PrintState();
    void SetMemento(Memento* men);
private: 
    State _sdt = "/0";
    Memento* mt = nullptr;
};
class Memento
{
public:
    ~Memento() = default;
private:
    friend class Originator;
    Memento() = default;
    Memento(const State& sdt);
    void SetState(const State& sdt);
    State GetState();
private:
    State _sdt;    
};
Originator::Originator(const State& std)
{
    _sdt = std;
}
Memento* Originator::CreateMemento()
{
    return new Memento(_sdt);
}
State Originator::GetState()
{
    return _sdt;
}
void Originator::SetState(const State& sdt)
{
    _sdt = sdt;
}
void Originator::PrintState()
{
    cout<<this->_sdt<<"....."<<endl;
}

void Originator::SetMemento(Memento* men)
{
    mt = men;
}
void Originator::RestoreToMemento(Memento* mt)
{
    this->_sdt = mt->GetState();
}

Memento::Memento(const State& sdt)
{
    _sdt = sdt;
}
State Memento::GetState()
{
    return _sdt;
}
void Memento::SetState(const State& sdt)
{
    _sdt = sdt;
}

int main(int argc,char* argv[])
{
    shared_ptr<Originator> o {new Originator()};
    o->SetState("old"); //备忘前状态
    o->PrintState();
    shared_ptr<Memento> m {o->CreateMemento()}; //将状态备忘
    o->SetState("new"); //修改状态
    o->PrintState();
    o->RestoreToMemento(m.get());
    //恢复修改前状态
    o->PrintState();
    return 0;
}