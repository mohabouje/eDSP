//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#ifndef EDSP_REALFFT_H
#define EDSP_REALFFT_H


#include "base/algoritmtemplate.h"
#include <fftw3.h>
EDSP_BEGING_NAMESPACE
    namespace transforms {
        template<typename T>
        class FFT : public AlgorithmTemplate {
        public:
            explicit FFT(size_t size);
            ~FFT() override;
            EDSP_DISABLE_COPY(FFT)

            inline size_t size() const { return input.size(); }
            void setSize(size_t size);
            const std::vector<std::complex<T>> &compute(const std::vector<T> &data);
            const std::vector<std::complex<T>> &compute(const std::vector<std::complex<T>> & data);
        private:
            fftw_plan fftwPlan{nullptr};
            std::vector<std::complex<T>> input;
            std::vector<std::complex<T>> output;
        };
    }
EDSP_END_NAMESPACE



#endif //EDSP_REALFFT_H
