//
// Created by mohabouje on 22/03/18.
//

#ifndef EDSP_WINDOW_BATHANNWIN_H
#define EDSP_WINDOW_BATHANNWIN_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Bartlett-Hann %window implementation.
     *
     * See also: Bartlett and Hann.
     *
     */
    class BartHann : Window {
    public:

        /**
         * @brief Creates and computes a Blackman %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit BartHann(size_type size);
        ~BartHann() override;

        void compute() override;
    };
EDSP_END_NAMESPACE



#endif //EDSP_WINDOW_BATHANNWIN_H
