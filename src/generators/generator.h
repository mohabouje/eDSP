//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_GENERATOR_H
#define EDSP_GENERATOR_H

#include "utility/vector_util.h"

EDSP_BEGING_NAMESPACE
    namespace generators {
        template<typename T, std::size_t N>
        class EDSP_EXPORT Generator {
        public:
            explicit Generator(T sampleRate = 0, T frequency = 0, T amplitude = 1) :
                     sampleRate(sampleRate),
                     frequency(frequency),
                     amplitude(amplitude)
            {
            }
            virtual ~Generator() = default;
            std::size_t getSize() const {  return N; }
            T getSampleRate() const { return sampleRate; }
            void setSampleRate(T sampleRate) {
                Generator::sampleRate = sampleRate;
            }

            inline T getFrequency() const { return frequency; }
            void setFrequency(T frequency) {
                Generator::frequency = frequency;
            }

            inline T getAmplitude() const {  return amplitude; }
            void setAmplitude(T amplitude) {
                Generator::amplitude = amplitude;
            }

        protected:
            T sampleRate{0};
            T frequency{0};
            T amplitude{1};
            std::array<T,N> data;
        };

}

EDSP_END_NAMESPACE


#endif //EDSP_GENERATOR_H
