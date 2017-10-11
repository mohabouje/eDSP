//
// Created by Mohammed Boujemaoui on 10/10/2017.
//

#ifndef EDSP_TEST_DB_H
#define EDSP_TEST_DB_H

#include <vector>
namespace test {
    namespace db {
        static const std::vector<double> ref_vector = {
            0.080000000000000,
            0.090754544373360,
            0.122515306951360,
            0.173797189775404,
            0.242202309000359,
            0.324532117278097,
            0.416936964276558,
            0.515096102050708,
            0.614419718414272,
            0.710263551456361,
            0.798146050066696,
            0.873957926284640,
            0.934154301037091,
            0.975920458744089,
            0.997303460291005,
            0.997303460291005,
            0.975920458744089,
            0.934154301037091,
            0.873957926284640,
            0.798146050066696,
            0.710263551456361,
            0.614419718414272,
            0.515096102050708,
            0.416936964276558,
            0.324532117278097,
            0.242202309000359,
            0.173797189775404,
            0.122515306951360,
            0.090754544373360,
            0.080000000000000
        };


        static constexpr double max_ref_vector = 0.997303460291005;
        static constexpr double min_ref_vector = 0.080000000000000;
        static constexpr double sum_ref_vector = 15.740000000000000;
        static constexpr double mean_ref_vector = 0.524666666666667;
        static constexpr double var_ref_vector = 0.112853333333333;
        static constexpr double std_desv_ref_vector = 0.335936501936502;
        static constexpr double mode_ref_vector = 0.080000000000000;
        static constexpr double sum_square_ref_vector = 11.530999999999997;


    }
}

#endif //EDSP_TEST_DB_H
