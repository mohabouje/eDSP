//
// Created by mohabouje on 21/03/18.
//

#ifndef EDSP_WINDOW_HAMMING_H
#define EDSP_WINDOW_HAMMING_H

#include "window.h"

EDSP_BEGIN_NAMESPACE

    /**
     * @brief Hamming %window implementation.
     *
     * This %window was proposed by Richard W. Hammming. It's optimized to minimize the maximum
     * side lobe. The following equation generates the coefficients:
     *
     * \f[
     *    w(n)=\alpha -\beta \;\cos \left({\frac {2\pi n}{N-1}}\right),
     * \f]
     * with \f[ {\displaystyle \alpha =0.54,\;\beta =1-\alpha =0.46,} \f]
     *
     */
    class Hamming : Window {
    public:

        /**
         * @brief Creates and computes a Hamming %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Hamming(size_type size);
        ~Hamming() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_HAMMING_H
