//
// Created by mohabouje on 21/03/18.
//

#ifndef EDSP_WINDOW_PARZEN_H
#define EDSP_WINDOW_PARZEN_H

#include "window.hpp"

EDSP_BEGIN_NAMESPACE

/**
 * @brief Parzen %window implementation.
 *
 * Parzen windows a piecewise-cubic approximation of Gaussian windows. It is also known as de la Vallée Poussin window.
 * The following equation defines the N–point Parzen window over the interval \f$ -\frac{N-1}{2} \leqslant  n \leqslant  \frac{N-1}{2}  \f$:
 *
 * \f[
        {\displaystyle w(n)=\left\{{\begin{array}{ll}1-6\left({\frac {n}{N/2}}\right)^{2}\left(1-{\frac {|n|}{N/2}}\right),&0 \leqslant |n|\leqslant {\frac {N-1}{4}}
        \\2\left(1-{\frac {|n|}{N/2}}\right)^{3},&{\frac {N-1}{4}}<|n|\leqslant {\frac {N-1}{2}}\\\end{array}}\right.}
 * \f]
 *
 */
class Parzen : Window {
    EDSP_DECLARE_ALL_IMPLICITS(Parzen)
public:
    /**
     * @brief Creates and computes a Parzen %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Parzen(_In_ size_type size);
    ~Parzen() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

Parzen::Parzen(_In_ Window::size_type size) : Window(size) {

}

Parzen::~Parzen() = default;

void Parzen::initialize() {
    if (!empty()) {
        const value_type half = (size() - 1) / 2.;
        const value_type quarter = half / 2.;
        value_type initial = -half;
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            auto abs_initial = std::abs(initial);
            auto factor = abs_initial / half;
            if (abs_initial <= quarter) {
                auto tmp = factor * factor;
                data_[i] = 6. * (tmp + tmp * factor);
            } else if ((abs_initial > quarter) && (abs_initial <= half)) {
                auto tmp = 1 - factor;
                data_[i] = 2 * tmp * tmp * tmp;
            }
            ++initial;
        }
    }
}
EDSP_END_NAMESPACE

#endif //EDSP_PARZEN_H
