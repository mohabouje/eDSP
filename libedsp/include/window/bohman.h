//
// Created by mohabouje on 22/03/18.
//

#ifndef EDSP_WINDOW_BOHMAN_H
#define EDSP_WINDOW_BOHMAN_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Bohman %window implementation.
     *
     * See also: Rectangular and Bartlett
     */
    class Bohman : Window {
    public:

        /**
         * @brief Creates and computes a Bohman %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Bohman(size_type size);
        ~Bohman() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_BOHMAN_H
