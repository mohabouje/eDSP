//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_DHT_H
#define EDSP_DHT_H

#include "base/algoritmtemplate.h"
#include <fftw3.h>
#include <type_traits>  //include this

EDSP_BEGING_NAMESPACE
namespace transforms {
    template<typename T>
    class DHT : public AlgorithmTemplate {
    public:
        explicit DHT(size_t size);
        ~DHT() override;
        EDSP_DISABLE_COPY(DHT)

        inline size_t size() const { return input.size(); }
        void setSize(size_t size);
        const std::vector<T> &compute(const std::vector<T> &data);
    private:
        fftw_plan fftwPlan{nullptr};
        std::vector<T> input;
        std::vector<T> output;
    };
}
EDSP_END_NAMESPACE
#endif //EDSP_DHT_H
