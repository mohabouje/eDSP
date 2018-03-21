//
// Created by mohabouje on 21/03/18.
//

#ifndef EDSP_WINDOW_PARZEN_H
#define EDSP_WINDOW_PARZEN_H

#include "window.h"

EDSP_BEGIN_NAMESPACE

    /**
     * @brief Parzen %window implementation.
     *
     * Parzen windows a piecewise-cubic approximation of Gaussian windows. It is all known as de la Vallée Poussin window.
     * The following equation defines the N–point Parzen window over the interval \f$ -\frac{N-1}{2} \leqslant  n \leqslant  \frac{N-1}{2}  \f$:
     *
     * \f[
            {\displaystyle w(n)=\left\{{\begin{array}{ll}1-6\left({\frac {n}{N/2}}\right)^{2}\left(1-{\frac {|n|}{N/2}}\right),&0 \leqslant |n|\leqslant {\frac {N-1}{4}}
            \\2\left(1-{\frac {|n|}{N/2}}\right)^{3},&{\frac {N-1}{4}}<|n|\leqslant {\frac {N-1}{2}}\\\end{array}}\right.}
     * \f]
     *
     */
    class Parzen : Window {
    public:

        /**
         * @brief Creates and computes a Parzen %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Parzen(size_type size);
        ~Parzen() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_PARZEN_H
