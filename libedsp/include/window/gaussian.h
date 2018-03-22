//
// Created by mohabouje on 21/03/18.
//

#ifndef EDSP_WINDOW_GAUSSIAN_H
#define EDSP_WINDOW_GAUSSIAN_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Gaussian %window implementation.
     *
     * The Fourier transform of a Gaussian is also a Gaussian (it is an eigenfunction of the Fourier Transform).
     * Since the Gaussian function extends to infinity, it must either be truncated at the ends of the window, or
     * itself windowed with another zero-ended window
     *
     * \f[
        {\displaystyle w(n)=e^{-{\frac {1}{2}}\left({\frac {n-(N-1)/2}{\sigma (N-1)/2}}\right)^{2}}}
     * \f]
     */
    class Gaussian : Window {
    public:

        /**
         * @brief Creates and computes a Gaussian %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Gaussian(size_type size);

        /**
         * @brief Creates a Gaussian %window with the given size and a factor alpha
         * @param size The number of elements to initially create
         * @param alpha The proportional factor to the standard deviation.
         */
        Gaussian(size_type size, value_type alpha);
        ~Gaussian() override;

        void compute() override;

        /**
         * @brief Set the proportional factor to the standard deviation
         * @param alpha proportional to the reciprocal of the standard deviation
         */
        void set_alpha(value_type alpha) EDSP_NOEXCEPT;

        /**
         * @brief Returns the proportional factor to the standard deviation
         * @return the proportional factor to the reciprocal of the standard deviation
         */
        value_type alpha() const EDSP_NOEXCEPT;
    private:
        value_type alpha_;
    };
EDSP_END_NAMESPACE
#endif //EDSP_WINDOW_GAUSSIAN_H
