//
// Created by mohabouje on 21/03/18.
//

#ifndef EDSP_WINDOW_BLACKMAN_H
#define EDSP_WINDOW_BLACKMAN_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Blackman %window implementation.
     *
     * It was designed to have close to the minimal leakage possible. It is close to optimal, only slightly worse than a Kaiser window.
     *
     * \f[
     * w(n)=a_{0}-a_{1}\cos \left({\frac {2\pi n}{N-1}}\right)+a_{2}\cos \left({\frac {4\pi n}{N-1}}\right)
     * \f]
     * with \f$ {\displaystyle a_{0}={\frac {1-\alpha }{2}};\quad a_{1}={\frac {1}{2}};\quad a_{2}={\frac {\alpha }{2}}\,}
     * a_{0}={\frac {1-\alpha }{2}};\quad a_{1}={\frac {1}{2}};\quad a_{2}={\frac {\alpha }{2}}\
     * \f$
     *
     * By common convention, the unqualified term Blackman is \f$ \alpha = 0.16 \f$
     *
     */
    class Blackman : Window {
    public:

        /**
         * @brief Creates and computes a Blackman %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Blackman(size_type size);
        ~Blackman() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_BLACKMAN_H
