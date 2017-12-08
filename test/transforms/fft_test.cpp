//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include <catch.hpp>
#include "frequency/fft.h"
#include "frequency/ifft.h"
#include "math/complex.h"
#include "../test_db.h"
#include "../test_config.h"

using namespace eDSP::frequency;
SCENARIO("Testing FFT") {
    auto original = test::db::ref_vector;
    auto tmp = eDSP::math::complex::real_to_complex(original);
    FFT<double, 30> fft{};
    IFFT<double, 30> ifft{};

    GIVEN("A signal ") {
        WHEN("We apply the FFT") {
            auto data = fft.compute(tmp);
            THEN("It should be the same as the estimated fft") {
                for (size_t i = 0, size = data.size(); i < size; i++) {
                    const Approx abs = Approx(std::abs(data[i])).epsilon(TEST_TOLERANCE);
                    REQUIRE(abs == std::abs(test::db::fft_ref_vector[i]));
                }
            }
        }

        AND_WHEN("We apply the inverse operation") {
            auto data = fft.compute(tmp);
            auto inverse = ifft.compute(data);
            THEN("We should get the same output") {
                for (size_t i = 0, size = inverse.size(); i < size; i++) {
                    const Approx target = Approx(inverse[i].real() / static_cast<double>(size)).epsilon(TEST_TOLERANCE);
                    REQUIRE(target == original[i]);
                }
            }
        }
    }
}