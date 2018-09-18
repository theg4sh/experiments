#include <iostream>
#include <internal_definition.hpp>

using namespace std;

template<typename T>
void Foo::bar(T value)
{
    cout << "value=" << value << endl;
}

void InternalDef::callThat()
{
    int value = 11;
    this->foo.bar(value);
}

