//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_IDCT_H
#define EDSP_IDCT_H


#include "base/algoritmtemplate.h"
#include "math/container.hpp"
#include "dct.hpp"
#include <fftw3.h>
#include <assert.h>

EDSP_BEGING_NAMESPACE
    namespace transforms {
        CLASS_TEMPLATE_CONTAINER(Container)
        class IDCT {
        public:
            EDSP_DISABLE_COPY(IDCT)
            explicit IDCT(size_t size, DCT_Type t = DCT_Type::Type_I) : t(t) { setSize(size); }
            virtual ~IDCT() { fftw_destroy_plan(fftwPlan); }
            void setType(DCT_Type t) {
                IDCT::t = t;
                const fftw_r2r_kind_do_not_use_me format = [&]() {
                    switch(IDCT::t) {
                        case Type_I: return FFTW_REDFT00;
                        case Type_II: return FFTW_REDFT01;
                        case Type_III: return FFTW_REDFT10;
                        case Type_IV: return FFTW_REDFT11;
                        default: return FFTW_REDFT00;
                    }
                }();

                fftwPlan = fftw_plan_r2r_1d(static_cast<int>(input.size()),
                                            &input[0],
                                            &output[0],
                                            format,
                                            FFTW_MEASURE);
            }

            void setSize(size_t size) {
                input.resize(size);
                output.resize(size);
                fftwPlan = fftw_plan_r2r_1d(size,
                                            &input[0],
                                            &output[0],
                                            FFTW_DHT,
                                            FFTW_MEASURE);
                setType(t);
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
            DCT_Type t{DCT_Type::Type_I};
            Container  input;
            Container  output;
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_IDCT_H
