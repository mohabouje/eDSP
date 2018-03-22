//
// Created by mohabouje on 22/03/18.
//

#ifndef EDSP_WINDOW_TRIANGULAR_H
#define EDSP_WINDOW_TRIANGULAR_H

#include "window.h"

EDSP_BEGIN_NAMESPACE

/**
 * @brief Triangular %window implementation.
 *
 * Unlike the Bartlett %window, this %window does not go to zero at the edge of the %window.
 *
 * See also: Bartlett
 *
 */
class Triangular : Window {
public:

    /**
     * @brief Creates and computes a Triangular %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Triangular(size_type size);
    ~Triangular() override;

    void compute() override;
};
EDSP_END_NAMESPACE


#endif //EDSP_TRIANGULAR_H
