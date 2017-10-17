//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include <catch.hpp>
#include "transforms/fft.h"
#include "transforms/ifft.h"
#include "../test_db.h"
#include "../test_config.h"

using namespace eDSP::transforms;
SCENARIO("Testing FFT") {
    const std::vector<double> original = test::db::ref_vector;
    FFT<double> fft(original.size());
    IFFT<double> ifft(original.size());

    GIVEN("A signal ") {
        WHEN("We apply the FFT") {
            const std::vector<std::complex<double>> data = fft.compute(original);
            THEN("It should be the same as the estimated fft") {
                for (size_t i = 1, size = data.size(); i < size; i++) {
                    const Approx real = Approx(data[i].real()).epsilon(TEST_TOLERANCE);
                    const Approx imag = Approx(data[i].imag()).epsilon(TEST_TOLERANCE);
                    REQUIRE( real == test::db::fft_ref_vector[i].real());
                    REQUIRE( imag == test::db::fft_ref_vector[i].imag());
                }
            }
        }

        AND_WHEN("We apply the inverse operation") {
            const std::vector<std::complex<double>> data = fft.compute(original);
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