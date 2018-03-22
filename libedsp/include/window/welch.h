//
// Created by mohabouje on 22/03/18.
//

#ifndef EDSP_WINDOW_WELCH_H
#define EDSP_WINDOW_WELCH_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Welch %window implementation.
     *
     * The Welch window is given by:
     * \f[
     *    w(n)=1-\left( \frac{n}{N-1} \right)
     * \f]
     *
     * This class implement two different approaches:
     *    - Symmetric: the %window has zero at each end and maximum in the middle. In this case: N = (m-1)/2
     *    - Periodic: the %window wraps around the cyclic interval. In this case: N = m/2
     *
     */
    class Welch : Window {
    public:


        /**
         * @brief Creates and computes a Welch %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Welch(size_type size);

        /**
         * @brief Creates and computes a Welch %window with the given size and type.
         * @param size The number of elements to initially create.
         * @param type Window type.
         */
        Welch(size_type size, WindowType type_);

        ~Welch() override;


        void compute() override;

    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_WELCH_H
