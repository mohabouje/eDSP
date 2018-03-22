//
// Created by mohabouje on 21/03/18.
//

#ifndef EDSP_WINDOW_RECTANGULAR_H
#define EDSP_WINDOW_RECTANGULAR_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Rectangular %window implementation.
     *     *
     * \f[
            {\displaystyle w(n)=1}
     * \f]
     *
     */
    class Rectangular : Window {
    public:

        /**
         * @brief Creates and computes a Rectangular %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Rectangular(size_type size);
        ~Rectangular() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_RECTANGULAR_H
