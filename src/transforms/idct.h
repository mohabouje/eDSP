//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_IDCT_H
#define EDSP_IDCT_H

#include "base/algoritmtemplate.h"
#include "dct.h"
#include <fftw3.h>
EDSP_BEGING_NAMESPACE
    namespace transforms {
        template<typename T>
        class IDCT : public AlgorithmTemplate {
        public:
            IDCT(size_t size, DCT_Type t);
            ~IDCT() override;
            EDSP_DISABLE_COPY(IDCT)

            inline size_t size() const { return input.size(); }
            void setSize(size_t size);
            void setType(DCT_Type t);
            const std::vector<T> &compute(const std::vector<T> &data);
        private:
            DCT_Type t{DCT_Type::Type_I};
            fftw_plan fftwPlan{nullptr};
            std::vector<T> input;
            std::vector<T> output;
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_IDCT_H
