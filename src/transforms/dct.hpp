//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_DCT_H
#define EDSP_DCT_H

#include "base/algoritmtemplate.h"
#include "math/container.hpp"

#include <fftw3.h>
#include <assert.h>

EDSP_BEGING_NAMESPACE
    namespace transforms {
        enum DCT_Type { Type_I = 0, Type_II, Type_III, Type_IV};

        CLASS_TEMPLATE_CONTAINER(Container)
        class DCT {
            EDSP_DISABLE_COPY(DCT)
            explicit DCT(size_t size, DCT_Type t = DCT_Type::Type_I) : t(t) { setSize(size); }
            virtual ~DCT() { fftw_destroy_plan(fftwPlan); }
            DCT_Type type() const { return t; }
            size_t size() const { return input.size(); }
            void setType(DCT_Type t) {
                DCT::t = t;
                const fftw_r2r_kind_do_not_use_me format = [&]() {
                    switch(DCT::t) {
                        case Type_I: return FFTW_REDFT00;
                        case Type_II: return FFTW_REDFT10;
                        case Type_III: return FFTW_REDFT01;
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
                setType(t);
                math::set(input, Container::value_type());
                math::set(output, Container::value_type());
            }

            const Container &compute(const Container &data) {
                assert(data.size() <= input.size());
                std::copy(data.begin(), data.end(), input.begin());
                fftw_execute(fftwPlan);
                return output;
            }

        private:
            DCT_Type t{DCT_Type::Type_I};
            fftw_plan fftwPlan{nullptr};
            Container input;
            Container output;
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_DCT_H
