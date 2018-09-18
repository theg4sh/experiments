#ifndef TMDEF_INTERNAL_DEFINITION_HPP 
#define TMDEF_INTERNAL_DEFINITION_HPP 

#include <foo.hpp>

class InternalDef
{
public:
    InternalDef(Foo foo): foo(foo) {}

    void callThat();

private:
    Foo foo;
};

#endif

