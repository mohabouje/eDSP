//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#ifndef EDSP_STRONGPEAK_H
#define EDSP_STRONGPEAK_H

#include "base/algoritmtemplate.h"

EDSP_BEGING_NAMESPACE
    namespace levels {
        template<typename T>
        class StrongPeak : public AlgorithmTemplate {
        public:
            StrongPeak() : AlgorithmTemplate(true, Error()) { }
            ~StrongPeak() override = default;
            inline std::pair<int, T> compute(const std::vector<T>& data) const;
        };


    }
EDSP_END_NAMESPACE
#endif //EDSP_STRONGPEAK_H
