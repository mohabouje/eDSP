//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#ifndef EDSP_LOUDNESS_H
#define EDSP_LOUDNESS_H

#include "base/algoritmtemplate.h"

EDSP_BEGING_NAMESPACE
    namespace levels {
        template<typename T>
        class Loudness : public AlgorithmTemplate {
        public:
            Loudness() : AlgorithmTemplate(true, Error()) { }
            ~Loudness() override = default;
            inline T compute(const std::vector<T>& data) const;
        };


    }
EDSP_END_NAMESPCE
#endif //EDSP_LOUDNESS_H
