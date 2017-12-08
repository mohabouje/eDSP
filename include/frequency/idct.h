//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_IDCT_H
#define EDSP_IDCT_H

#include "frequency/dct.h"
EDSP_BEGING_NAMESPACE
    namespace frequency {

        template<typename T, std::size_t N>
        class EDSP_EXPORT IDCT {
        public:
            EDSP_DISABLE_COPY(IDCT)
            explicit IDCT(DCT_Type t = DCT_Type::Type_I) : t(t) {
                setType(t);
            }
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

                fftwPlan = fftw_plan_r2r_1d(static_cast<int>(N),
                                            &input[0],
                                            &output[0],
                                            format,
                                            FFTW_MEASURE);
            }

            template<typename Container>
            typename std::enable_if<std::is_same<typename Container::value_type,
                    std::complex<T>>::value, const std::array<std::complex<double>, N>&>::type
            compute(const Container& data) {
                assert(data.size() <= input.size());
                std::transform(data.begin(), data.end(), input.begin(), [](std::complex<T> tmp) {
                    return std::complex<double>(tmp.real(), tmp.imag());
                });
                fftw_execute(fftwPlan);
                return output;
            }
        private:
            DCT_Type t{DCT_Type::Type_I};
            fftw_plan fftwPlan{nullptr};
            std::array<std::complex<double>, N>  input{};
            std::array<std::complex<double>, N>  output{};
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_IDCT_H
