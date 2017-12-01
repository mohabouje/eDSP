//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#ifndef EDSP_REALFFT_H
#define EDSP_REALFFT_H

#include "base/template_util.hpp"
#include "utility/vector_util.hpp"
#include <fftw3.h>
#include <assert.h>

EDSP_BEGING_NAMESPACE
    namespace transforms {
        EDSP_CTEMPLATE_GENERIC_CONTAINER(Container)
        class FFT {
        public:
            EDSP_DISABLE_COPY(FFT)
            explicit FFT(size_t size) { setSize(size); }
            virtual ~FFT() { fftw_destroy_plan(fftwPlan); }
            void setSize(size_t size) {
                input.resize(size);
                output.resize(size);
                fftwPlan = fftw_plan_dft_1d(static_cast<int>(size),
                                            reinterpret_cast<fftw_complex *>(&input[0]),
                                            reinterpret_cast<fftw_complex *>(&output[0]),
                                            FFTW_FORWARD, FFTW_ESTIMATE);
                utility::vector::set(input, static_cast<typename Container::value_type>(0));
                utility::vector::set(output, static_cast<typename Container::value_type>(0));
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



#endif //EDSP_REALFFT_H
