//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_DHT_H
#define EDSP_DHT_H

#include "base/algoritmtemplate.h"
#include "math/container.hpp"
#include <fftw3.h>
#include <assert.h>

EDSP_BEGING_NAMESPACE
namespace transforms {
    CLASS_TEMPLATE_CONTAINER(Container)
    class DHT  {
    public:
        EDSP_DISABLE_COPY(DHT)
        explicit DHT(size_t size) { setSize(size); }
        virtual ~DHT() { fftw_destroy_plan(fftwPlan); }
        void setSize(size_t size) {
            input.resize(size);
            output.resize(size);
            fftwPlan = fftw_plan_r2r_1d(static_cast<int>(size),
                                        &input[0],
                                        &output[0],
                                        FFTW_DHT,
                                        FFTW_MEASURE);
            math::set(input, static_cast<typename Container::value_type>(0));
            math::set(output, static_cast<typename Container::value_type>(0));
        }

        const Container &compute(const Container&data) {
            assert(data.size() <= input.size());
            std::copy(data.begin(), data.end(), input.begin());
            fftw_execute(fftwPlan);
            return output;
        }
    private:
        fftw_plan fftwPlan{nullptr};
        Container  input;
        Container  output;
    };
}
EDSP_END_NAMESPACE
#endif //EDSP_DHT_H
