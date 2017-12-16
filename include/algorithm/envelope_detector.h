//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_ENVELOPE_DETECTOR_H
#define EDSP_ENVELOPE_DETECTOR_H

#include <cmath>
#include "config.h"

EDSP_BEGIN_NAMESPACE
    namespace algorithm {

        template <typename T>
        class EnvelopeDetector {
        public:
            EnvelopeDetector(const T attack, const T release, const T sample_rate) :
                    m_attack(attack),
                    m_release(release),
                    m_samplerate(sample_rate),
                    m_gain_attack(std::exp(-1.f / (sample_rate * attack))),
                    m_gain_release(std::exp(-1.f / (sample_rate * release)))
            {

            }

            template <class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    compute(*first, *out);
                }
            };


            void compute(const T input, T& out) {
                const auto actual = std::abs(input);
                if (m_envelope > actual) {
                    m_envelope *= m_gain_attack;
                    m_envelope += (1 - m_gain_attack) * actual;
                } else {
                    m_envelope *= m_gain_release;
                    m_envelope += (1 - m_gain_release) * actual;
                }
                out = m_envelope;
            }

            T samplerate() const { return m_samplerate; }
            T attack_time() const { return m_attack; }
            T release_time() const { return m_release; }

            void set_attack_time(const T value) {
                m_attack = value;
                m_gain_attack = std::exp(-1.f / (m_samplerate * m_attack));
            }
            void set_release_time(const T value) {
                m_release = value;
                m_gain_release = std::exp(-1.f / (m_samplerate * m_release));
            }
            void set_samplerate(const T value) {
                m_samplerate = value;
                set_attack_time(m_attack);
                set_release_time(m_release);
            }

            void reset() {
                m_envelope = 0;
            }
        private:
            T m_samplerate{0};
            T m_attack{0};
            T m_release{0};
            T m_gain_attack{0};
            T m_gain_release{0};
            T m_envelope{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_ENVELOPE_DETECTOR_H
