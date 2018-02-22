//
// Created by Mohammed Boujemaoui on 09/10/2017.
//

#ifndef EDSP_CONSTANTS_H
#define EDSP_CONSTANTS_H

#include "config.h"
#include <limits>

EDSP_BEGIN_NAMESPACE
    template <typename T>
    struct constants {
        constexpr static T pi           = static_cast<T>(3.141592653589793);
        constexpr static T e            = static_cast<T>(2.718281828459045);

        constexpr static T square_pi    = static_cast<T>(9.869604401089358);
        constexpr static T square_e     = static_cast<T>(7.389056098930652);

        constexpr static T inv_pi       = static_cast<T>(0.318309886183790);
        constexpr static T inv_e        = static_cast<T>(0.367879441171442);

        constexpr static T sqrt_2       = static_cast<T>(1.414213562373095);
        constexpr static T sqrt_pi      = static_cast<T>(1.772453850905516);
        constexpr static T sqrt_e       = static_cast<T>(1.648721270700128);


        constexpr static T epsilon     = std::numeric_limits<T>::epsilon();
        constexpr static T infinity    = std::numeric_limits<T>::infinity();
        constexpr static T neg_infinity = -std::numeric_limits<T>::infinity();
        constexpr static T qnan        = std::numeric_limits<T>::quiet_NaN();
    };

EDSP_END_NAMESPACE


#endif //EDSP_CONSTANTS_H
