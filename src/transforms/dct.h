//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_DCT_H
#define EDSP_DCT_H

#include "base/algoritmtemplate.h"
#include <fftw3.h>
EDSP_BEGING_NAMESPACE
    namespace transforms {
        enum DCT_Type { Type_I = 0, Type_II, Type_III, Type_IV};
        template<typename T>
        class DCT : public AlgorithmTemplate {
        public:
            DCT(size_t size, DCT_Type t);
            ~DCT() override;
            EDSP_DISABLE_COPY(DCT)

            inline DCT_Type type() const { return t; }
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

#endif //EDSP_DCT_H
