//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_GAIN_H
#define EDSP_GAIN_H

#include "config.h"

EDSP_BEGIN_NAMESPACE
    namespace blocks {
        class Gain {
        public:
            explicit Gain(double gain) : m_gain(gain) {}

            template <class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    compute(*first, *out);
                };
            }

            template <typename T>
            void compute(const T input, T& output) {
                output = static_cast<T>(input * m_gain);
                if (output > 1) output = 1;
                else if(output < -1) output = -1;
            }

            void set_gain(const double gain) { m_gain = gain; }
            double gain() const { return m_gain; }
        private:
            double m_gain{1.0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_GAIN_H
