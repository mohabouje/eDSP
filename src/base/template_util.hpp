#ifndef EDSP_TEMPLATE_UTIL_H
#define EDSP_TEMPLATE_UTIL_H

#include "config.h"
EDSP_BEGING_NAMESPACE

    template<typename T>
    struct has_const_iterator
    {
    private:
        template<typename C> static char test(typename C::const_iterator*);
        template<typename C> static int  test(...);
    public:
        enum { value = sizeof(test<T>(0)) == sizeof(char) };
    };

EDSP_END_NAMESPACE


#define TEMPLATE_CONTAINER(Name, Return) template <typename Name> \
    constexpr typename std::enable_if<has_const_iterator<Name>::value, Return>::type

#endif