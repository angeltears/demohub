
class Observer{};
class Observable
{
public:
    void register_(Observer * s)
    {}
};
class Foo: public Observer
{
public:
    Foo();
    virtual void update();
    void observer(Observable* s)
    {
        s->register_(this);
    }
};

int main()
{
    Foo *pFoo = new Foo;
    Observable* s = new Observable;
    pFoo->observer(s);
}