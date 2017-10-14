//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#ifndef EDSP_REALFFT_H
#define EDSP_REALFFT_H


#include "base/algoritmtemplate.h"
#include <memory>
#include <ldap_schema.h>

EDSP_BEGING_NAMESPACE
    namespace transforms {
        template<typename T>
        class FFT : public AlgorithmTemplate {
        public:
            explicit FFT(size_t size);
            FFT();
            ~FFT() override;
            EDSP_DISABLE_COPY(FFT)

            size_t size() const;
            void setSize(size_t size);
            const std::vector<std::complex<T>> &compute(const std::vector<T> &data);
            const std::vector<std::complex<T>> &compute(const std::vector<std::complex<T>> & data);
        private:
            class Pimpl;
            std::unique_ptr<Pimpl> pimpl;

        };
    }
EDSP_END_NAMESPCE

#endif //EDSP_REALFFT_H
