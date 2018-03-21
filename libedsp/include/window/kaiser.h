//
// Created by mohabouje on 21/03/18.
//

#ifndef EDSP_WINDOW_KAISER_H
#define EDSP_WINDOW_KAISER_H

#include "window.h"

EDSP_BEGIN_NAMESPACE

    /**
     * @brief Kaiser %window implementation.
     *
     * This %window is also called Kaiser-Bessel window was developed by James Kaiser.
     * This function approximates the  DPSS (Discrete Prolate Spheroidal Sequence) window which
     * maximizes the energy concentration in the main lobe  but which is difficult to compute
     * \f[
     * {\displaystyle w[n]={\begin{cases}{\frac {I_{0}\left[\alpha {\sqrt {1-\left({\frac {2n}{N-1}}-1\right)^{2}}}\right]}{I_{0}[\alpha ]}},&0\leq n\leq N-1,\\0,&{\mbox{otherwise}},\\\end{cases}}}
     * \f]
     *   where:

            - \f$ I_0 \f$ is the zeroth-order modified Bessel function of the first kind,
            - \f$ \tau \f$ is the window duration, and
            - \f$ \alpha \f$ is a non-negative real number that determines the shape of the window.
            In the frequency domain, it determines the trade-off between main-lobe width and side lobe level, which is a central decision in window design.
     *
     */
    class Kaiser : Window {
    public:

        /**
         * @brief Creates and computes a Kaiser %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Kaiser(size_type size);
        ~Kaiser() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_KAISER_H
