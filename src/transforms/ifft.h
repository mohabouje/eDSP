//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_IFFT_H
#define EDSP_IFFT_H


#include "base/algoritmtemplate.h"
#include <fftw3.h>
EDSP_BEGING_NAMESPACE
    namespace transforms {
        template<typename T>
        class IFFT : public AlgorithmTemplate {
        public:
            explicit IFFT(size_t size);
            ~IFFT() override;
            EDSP_DISABLE_COPY(IFFT)

            inline size_t size() const { return input.size(); }
            void setSize(size_t size);
            const std::vector<std::complex<T>> &compute(const std::vector<std::complex<T>> & data);
        private:
            fftw_plan fftwPlan{nullptr};
            std::vector<std::complex<T>> input;
            std::vector<std::complex<T>> output;
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_IFFT_H
