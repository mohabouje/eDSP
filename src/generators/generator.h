//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_GENERATOR_H
#define EDSP_GENERATOR_H

#include "config.h"
#include "base/algoritmtemplate.h"

EDSP_BEGING_NAMESPACE
    namespace generators {
        template<typename T>
        class Generator : public AlgorithmTemplate {
        public:
            Generator() = default;
            explicit Generator(size_t size, T sampleRate = 0, T frequency = 0, T amplitude = 0) :
                                                                             sampleRate(sampleRate),
                                                                             frequency(frequency),
                                                                             amplitude(amplitude),
                                                                             data(std::vector<T>(size)),
                                                                             AlgorithmTemplate(true, Error())
            {

            }
            ~Generator() override = default;

            inline size_t getSize() const {  return data.size(); }
            void setSize(size_t size) {
                if (size != data.size()) {
                    data.resize(size);
                }
            }

            inline T getSampleRate() const { return sampleRate; }
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
            T sampleRate;
            T frequency;
            T amplitude;
            std::vector<T> data;
        };

}

EDSP_END_NAMESPCE


#endif //EDSP_GENERATOR_H
