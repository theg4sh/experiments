#include <iostream>
//#include <type_traits>
#include <typeinfo>

struct Container {
    int int_field;
    float float_field;
};

template<typename T, class = typename std::enable_if< std::is_floating_point<T>::value >::type>
float& struct_field_using_tmpl_arg(Container& c)
{
    return c.float_field;
}

template<typename T, class = typename std::enable_if< std::is_integral<T>::value >::type>
int& struct_field_using_tmpl_arg(Container& c)
{
    return c.int_field;
}

template<typename T>
void do_something_using_tmpl_arg(Container& c, T value)
{
    struct_field_using_tmpl_arg<T>(c) = value;
}

template<typename T>
float& struct_field_using_parameter(Container& c, typename std::enable_if< std::is_floating_point<T>::value >::type* = 0)
{
    return c.float_field;
}

template<typename T>
int& struct_field_using_parameter(Container& c, typename std::enable_if< std::is_integral<T>::value >::type* = 0)
{
    return c.int_field;
}

template<typename T>
void do_something_using_parameter(Container& c, T value)
{
    struct_field_using_parameter<T>(c) = value;
}

int main()
{
    int v1 = 1;
    float v2 = 2.0f;
    {
        Container c;
        do_something_using_parameter(c, v1);
        do_something_using_parameter(c, v2);
        std::cout << c.int_field << std::endl;
        std::cout << c.float_field << std::endl;
    }

    v1+=2;
    v2+=2.0f;
    {
        Container c;
        do_something_using_tmpl_arg(c, v1);
        do_something_using_tmpl_arg(c, v2);
        std::cout << c.int_field << std::endl;
        std::cout << c.float_field << std::endl;
    }
    return 0;
}
