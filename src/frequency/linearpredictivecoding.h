//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_LINEARPREDICTIVECODING_H
#define EDSP_LINEARPREDICTIVECODING_H


#include "config.h"
#include "transforms/fft.h"
#include "autocorrelation.h"

EDSP_BEGING_NAMESPACE
    namespace Frequency {
        template<typename T>
        class LinearPredictiveCode : AlgorithmTemplate {
        public:
            explicit LinearPredictiveCode(int16 order, size_t size = 1024);
            ~LinearPredictiveCode() override;
            inline const std::vector<T>& reflection() { return m_reflection; }
            inline int16 order() const { return m_order; }
            inline T lpc_error() const { return m_error; }
            const std::vector<T>& compute(const std::vector<T>&);

        private:
            AutoCorrelation<T> xcorr;
            std::vector<T> lpc;
            std::vector<T> m_reflection;
            int16          m_order{0};
            T              m_error{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_LINEARPREDICTIVECODING_H
