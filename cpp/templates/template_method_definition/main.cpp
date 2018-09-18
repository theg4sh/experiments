#include <foo.hpp>
#include <memory>

#ifdef INTERNAL
# include <internal_definition.hpp>
int main(int, char**)
{
    auto pub = std::make_shared<InternalDef>(InternalDef(Foo()));
    pub->callThat();
    return 0;
}
#endif

#ifdef EXTERNAL
# include <external_definition.hpp>
int main(int, char**)
{
    auto pub = std::make_shared<ExternalDef>(ExternalDef(Foo()));
    pub->callThat();
    return 0;
}
#endif

