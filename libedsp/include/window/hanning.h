//
// Created by mohabouje on 21/03/18.
//

#ifndef EDSP_WINDOW_HANNING_H
#define EDSP_WINDOW_HANNING_H

#include "window.h"

EDSP_BEGIN_NAMESPACE

/**
 * @brief Hanning %window implementation.
 *
 * This %window was proposed by Julius Von Han. The advantage of the Hann window is very low aliasing,
 * and the tradeoff slightly is a decreased resolution (widening of the main lobe).The following
 * equation generates the coefficients:
 *
 * \f[
 *    w(n)=\alpha -\beta \;\cos \left({\frac {2\pi n}{N-1}}\right),
 * \f]
 * with \f$ {\displaystyle \alpha =0.5,\;\beta =1-\alpha =0.5} \f$
 *
 */
class Hanning : Window {
public:

    /**
     * @brief Creates and computes a Hanning %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Hanning(size_type size);
    ~Hanning() override;

    void compute() override;
};
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_HANNING_H
