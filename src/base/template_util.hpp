#ifndef EDSP_TEMPLATE_UTIL_H
#define EDSP_TEMPLATE_UTIL_H

#include <type_traits>


template<typename T>
struct has_const_iterator
{
private:
    template<typename C> static char test(typename C::const_iterator*);
    template<typename C> static int  test(...);
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

template <typename T>
struct has_begin
{
private:
    template<typename C> static char test(typename std::enable_if<
            std::is_same<decltype(static_cast<typename C::const_iterator(C::*)() const>(&C::begin)),
                    typename C::const_iterator(C::*)() const>::value>::type *);

    template<typename C> static int & test(...);
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};


template <typename T>
struct has_end
{
private:
    template<typename C> static char test(typename std::enable_if<
            std::is_same<decltype(static_cast<typename C::const_iterator(C::*)() const>(&C::end)),
                    typename C::const_iterator(C::*)() const>::value>::type *);

    template<typename C> static int & test(...);
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};


#define EDSP_FTEMPLATE_ARITHMETIC_CONTAINER(Name, Return) template <typename Name> \
    constexpr typename std::enable_if<has_const_iterator<Name>::value \
    && has_begin<Name>::value \
    && has_end<Name>::value \
    && std::is_arithmetic<typename Container::value_type>::value, Return>::type

#define EDSP_FTEMPLATE_GENERIC_CONTAINER(Name, Return) template <typename Name> \
    constexpr typename std::enable_if<has_const_iterator<Name>::value \
    && has_begin<Name>::value \
    && has_end<Name>::value, Return>::type

#define EDSP_CTEMPLATE_GENERIC_CONTAINER(Name) template <typename Name, typename = typename std::enable_if<has_const_iterator<Name>::value \
    && has_begin<Name>::value \
    && has_end<Name>::value \
    >::type>

#define EDSP_CTEMPLATE_ARITHMETIC_CONTAINER(Name) template <typename Name, typename = typename std::enable_if<has_const_iterator<Name>::value \
    && has_begin<Name>::value \
    && has_end<Name>::value \
    && std::is_arithmetic<typename Container::value_type>::value>::type>

#endif