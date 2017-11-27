//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include <catch.hpp>
#include "transforms/fft.hpp"
#include "transforms/ifft.hpp"
#include "math/complex.hpp"
#include "../test_db.h"
#include "../test_config.h"

using namespace eDSP::transforms;
SCENARIO("Testing FFT") {
    auto original = test::db::ref_vector;
    auto tmp = eDSP::math::complex::real_to_complex(original);
    FFT<std::vector<std::complex<double>>> fft(original.size());
    IFFT<std::vector<std::complex<double>>> ifft(original.size());

    GIVEN("A signal ") {
        WHEN("We apply the FFT") {
            const std::vector<std::complex<double>> data = fft.compute(tmp);
            THEN("It should be the same as the estimated fft") {
                for (size_t i = 0, size = data.size(); i < size; i++) {
                    const Approx abs = Approx( std::abs(data[i])).epsilon(TEST_TOLERANCE);
                    REQUIRE( abs == std::abs(test::db::fft_ref_vector[i]));
                }
            }
        }

        AND_WHEN("We apply the inverse operation") {
            const std::vector<std::complex<double>> data = fft.compute(tmp);
            const std::vector<std::complex<double>> inverse = ifft.compute(data);
            THEN("We should get the same output") {
                for (size_t i = 0, size = inverse.size(); i < size; i++) {
                    const Approx target = Approx(inverse[i].real() / static_cast<double>(size)).epsilon(TEST_TOLERANCE);
                    REQUIRE( target == original[i]);
                }
            }
        }


    }






    fft.setSize(45);


}