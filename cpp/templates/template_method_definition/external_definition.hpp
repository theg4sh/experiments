#ifndef TMDEF_EXTERNAL_DEFINITION_HPP 
#define TMDEF_EXTERNAL_DEFINITION_HPP 

#include <foo.hpp>

class ExternalDef
{
public:
    ExternalDef(Foo foo): foo(foo) {}

    void callThat();

private:
    Foo foo;
};

#endif

