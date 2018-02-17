//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_ECHO_H_H
#define EDSP_ECHO_H_H

#include "delay.h"
EDSP_BEGIN_NAMESPACE
    namespace blocks {
        class Echo {
            explicit Echo(std::size_t maximum_delay) : m_delay(maximum_delay/3, maximum_delay) {
                set_maximum_delay(maximum_delay);
                reset();
            }

            template <class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    compute(*first, *out);
                };
            }

            template <typename T>
            void compute(const T input, T& out) {
                delay_.compute(input, out);
                out = gain_ * (out - input) + input;
            }

            void reset() { delay_.reset(); }
            double delay() const noexcept { return delay_.delay(); }
            double maximum_delay() const noexcept { return delay_.maximum_delay(); }
            double gain() const noexcept { return gain_; }

            void set_delay(const std::size_t value) noexcept { delay_.set_delay(value); }
            void set_maximum_delay(const std::size_t value) noexcept { delay_.set_maximum_delay(value); }
            void set_gain(const double value) noexcept { gain_ = value; }

        private:
            Delay       delay_;
            double      gain;
        };
    }

EDSP_END_NAMESPACE


#endif //EDSP_ECHO_H_H
