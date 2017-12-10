//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_DELAY_H
#define EDSP_DELAY_H

#include "config.h"
#include "utility/vector.h"
#include <vector>
#include <assert.h>

EDSP_BEGIN_NAMESPACE
    namespace algorithm {

        template <typename T>
        class Delay {
        public:
            Delay(std::size_t delay, std::size_t maximum_delay) :
                    m_delay(delay),
                    m_max_delay(maximum_delay),
                    m_buffer{maximum_delay, 0}
            {
            }
            virtual ~Delay() = default;


            template <class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    m_buffer[input_point++] = *first * m_gain;
                    *out = m_buffer[output_point++];
                    if (input_point == m_max_delay) input_point = 0;
                    if (output_point == m_max_delay) output_point = 0;
                };
            }

            void compute(const T in, T& out) {
                m_buffer[input_point++] = in * m_gain;
                out = m_buffer[output_point++];
                if (input_point == m_max_delay) input_point = 0;
                if (output_point == m_max_delay) output_point = 0;
            }

            std::size_t delay() const { return m_delay; }
            std::size_t maximum_delay() const { return m_max_delay; }
            T gain() const { return m_gain; }

            void set_gain(const T value) { m_gain = value; }
            void set_delay(const std::size_t value) {
                assert(value <= m_max_delay && "Greater than the maximum");
                m_delay = value;
            }
            void set_maximum_delay(const std::size_t value) {
                if (m_max_delay != value) {
                    m_max_delay = value;
                    m_buffer.resize(value);
                    reset();
                }
            }


            void reset() {
                utility::set(std::begin(m_buffer), std::end(m_buffer), 0);
                input_point = 0;
                output_point = 0;
            }

        private:
            T           m_gain;
            std::size_t m_delay{0};
            std::size_t m_max_delay{1};
            std::vector<T> m_buffer;
            std::size_t input_point{0};
            std::size_t output_point{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_DELAY_H
