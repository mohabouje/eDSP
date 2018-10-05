/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: testing_statistics.cpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */

#include <easy/dsp/statistics.hpp>
#include <gtest/gtest.h>


using namespace easy::dsp::statistics;
template class easy::dsp::statistics::histogram<float>;

// Kaiser window
static const std::array<double, 128> kaiser_reference = {
    0.940306193319157, 0.942143511816820, 0.943953418461233, 0.945735830246360, 0.947490665417824, 0.949217843477105,
    0.950917285185670, 0.952588912569041, 0.954232648920796, 0.955848418806504, 0.957436148067598, 0.958995763825185,
    0.960527194483780, 0.962030369734986, 0.963505220561105, 0.964951679238676, 0.966369679341956, 0.967759155746330,
    0.969120044631653, 0.970452283485529, 0.971755811106521, 0.973030567607293, 0.974276494417684, 0.975493534287722,
    0.976681631290555, 0.977840730825333, 0.978970779620005, 0.980071725734059, 0.981143518561190, 0.982186108831897,
    0.983199448616019, 0.984183491325191, 0.985138191715241, 0.986063505888514, 0.986959391296129, 0.987825806740159,
    0.988662712375755, 0.989470069713189, 0.990247841619833, 0.990995992322067, 0.991714487407115, 0.992403293824819,
    0.993062379889329, 0.993691715280739, 0.994291271046640, 0.994861019603611, 0.995400934738634, 0.995910991610445,
    0.996391166750805, 0.996841438065711, 0.997261784836527, 0.997652187721056, 0.998012628754524, 0.998343091350514,
    0.998643560301810, 0.998914021781183, 0.999154463342101, 0.999364873919368, 0.999545243829693, 0.999695564772186,
    0.999815829828791, 0.999906033464632, 0.999966171528306, 0.999996241252091, 0.999996241252091, 0.999966171528306,
    0.999906033464632, 0.999815829828791, 0.999695564772186, 0.999545243829693, 0.999364873919368, 0.999154463342101,
    0.998914021781183, 0.998643560301810, 0.998343091350514, 0.998012628754524, 0.997652187721056, 0.997261784836527,
    0.996841438065711, 0.996391166750805, 0.995910991610445, 0.995400934738634, 0.994861019603611, 0.994291271046640,
    0.993691715280739, 0.993062379889329, 0.992403293824819, 0.991714487407115, 0.990995992322067, 0.990247841619833,
    0.989470069713189, 0.988662712375755, 0.987825806740159, 0.986959391296129, 0.986063505888514, 0.985138191715241,
    0.984183491325191, 0.983199448616019, 0.982186108831897, 0.981143518561190, 0.980071725734059, 0.978970779620005,
    0.977840730825333, 0.976681631290555, 0.975493534287722, 0.974276494417684, 0.973030567607293, 0.971755811106521,
    0.970452283485529, 0.969120044631653, 0.967759155746330, 0.966369679341956, 0.964951679238676, 0.963505220561105,
    0.962030369734986, 0.960527194483780, 0.958995763825185, 0.957436148067598, 0.955848418806504, 0.954232648920796,
    0.952588912569041, 0.950917285185670, 0.949217843477105, 0.947490665417824, 0.945735830246360, 0.943953418461233,
    0.942143511816820, 0.940306193319157};


TEST(TestingStatistics, ComputeKaiserWindowMean) {
    constexpr auto kaiser_reference_solution = 0.979665937752067;
    EXPECT_NEAR(::mean(std::cbegin(kaiser_reference), std::cend(kaiser_reference)), kaiser_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeKaiserWindowMax) {
    constexpr auto kaiser_reference_solution = 0.999996241252091;
    EXPECT_NEAR(::max(std::cbegin(kaiser_reference), std::cend(kaiser_reference)), kaiser_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeKaiserWindowMin) {
    constexpr auto kaiser_reference_solution = 0.940306193319157;
    EXPECT_NEAR(::min(std::cbegin(kaiser_reference), std::cend(kaiser_reference)), kaiser_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeKaiserWindowMedian) {
    //constexpr auto kaiser_reference_solution = 0.984660841520216;
    //EXPECT_NEAR(::median(std::cbegin(kaiser_reference), std::cend(kaiser_reference)), kaiser_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeKaiserWindowVariance) {
    constexpr auto kaiser_reference_solution = 3.30637767761220e-04;
    EXPECT_NEAR(::variance(std::cbegin(kaiser_reference), std::cend(kaiser_reference)), kaiser_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeKaiserWindowStandardDeviation) {
    constexpr auto kaiser_reference_solution = 0.0181834476313272;
    EXPECT_NEAR(::standard_deviation(std::cbegin(kaiser_reference), std::cend(kaiser_reference)), kaiser_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeKaiserWindowSkewness) {
    constexpr auto kaiser_reference_solution = -0.628013603349620;
    EXPECT_NEAR(::skewness(std::cbegin(kaiser_reference), std::cend(kaiser_reference)), kaiser_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeKaiserWindowKurtosis) {
    constexpr auto kaiser_reference_solution = 2.12461664834483;
    EXPECT_NEAR(::kurtosis(std::cbegin(kaiser_reference), std::cend(kaiser_reference)), kaiser_reference_solution, 1e-4);
}


// Hamming window
static const std::array<double, 128> hamming_reference = {
    0.0800000000000000, 0.0805628485414398, 0.0822500167810610, 0.0850573759354599, 0.0889780559263524,
    0.0940024621928066, 0.1001182991707413, 0.1073106003822318, 0.1155617650609889, 0.1248516012243839,
    0.1351573750866134, 0.1464538666920827, 0.1587134316328634, 0.1719060686991922, 0.1859994932974579,
    0.2009592164560126, 0.2167486292254646, 0.2333290922669115, 0.2506600304088785, 0.2686990319415610,
    0.2874019524053867, 0.3067230226199044, 0.3266149606886389, 0.3470290877058146, 0.3679154468817951,
    0.3892229257957187, 0.4108993814761573, 0.4328917680037049, 0.4551462663232323, 0.4776084159481322,
    0.5002232482342569, 0.5229354208974015, 0.5456893534451469, 0.5684293631916387, 0.5910998015224501,
    0.6136451900760669, 0.6360103565087342, 0.6581405695104272, 0.6799816727415385, 0.7014802173625156,
    0.7225835928321281, 0.7432401556542779, 0.7633993557582885, 0.7830118602033984, 0.8020296739047342,
    0.8204062570853257, 0.8380966391667384, 0.8550575288196161, 0.8712474199048161, 0.8866266930458899,
    0.9011577125843333, 0.9148049186803513, 0.9275349143337446, 0.9393165471119649, 0.9501209853853384,
    0.9599217888828948, 0.9686949733961399, 0.9764190694724346, 0.9830751749543423, 0.9886470012363748,
    0.9931209131259411, 0.9964859622109474, 0.9987339136523965, 0.9998592663364183, 0.9998592663364183,
    0.9987339136523965, 0.9964859622109474, 0.9931209131259412, 0.9886470012363748, 0.9830751749543423,
    0.9764190694724348, 0.9686949733961400, 0.9599217888828947, 0.9501209853853385, 0.9393165471119649,
    0.9275349143337446, 0.9148049186803513, 0.9011577125843333, 0.8866266930458900, 0.8712474199048164,
    0.8550575288196159, 0.8380966391667386, 0.8204062570853258, 0.8020296739047343, 0.7830118602033985,
    0.7633993557582885, 0.7432401556542781, 0.7225835928321284, 0.7014802173625159, 0.6799816727415388,
    0.6581405695104274, 0.6360103565087342, 0.6136451900760672, 0.5910998015224505, 0.5684293631916386,
    0.5456893534451471, 0.5229354208974017, 0.5002232482342571, 0.4776084159481323, 0.4551462663232323,
    0.4328917680037049, 0.4108993814761571, 0.3892229257957189, 0.3679154468817953, 0.3470290877058144,
    0.3266149606886390, 0.3067230226199044, 0.2874019524053867, 0.2686990319415613, 0.2506600304088787,
    0.2333290922669114, 0.2167486292254647, 0.2009592164560127, 0.1859994932974580, 0.1719060686991924,
    0.1587134316328634, 0.1464538666920826, 0.1351573750866135, 0.1248516012243840, 0.1155617650609890,
    0.1073106003822320, 0.1001182991707413, 0.0940024621928066, 0.0889780559263524, 0.0850573759354599,
    0.0822500167810610, 0.0805628485414398, 0.0800000000000000};

TEST(TestingStatistics, ComputeHammingWindowMean) {
    constexpr auto hamming_reference_solution = 0.536406250000000;
    EXPECT_NEAR(::mean(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeHammingWindowMax) {
    constexpr auto hamming_reference_solution = 0.999859266336418;
    EXPECT_NEAR(::max(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeHammingWindowMin) {
    constexpr auto hamming_reference_solution = 0.0800000000000000;
    EXPECT_NEAR(::min(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeHammingWindowMedian) {
    //constexpr auto hamming_reference_solution = 0.534312387171274;
    //EXPECT_NEAR(::median(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeHammingWindowVariance) {
    constexpr auto hamming_reference_solution = 0.107453125000000;
    EXPECT_NEAR(::variance(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-2);
}

TEST(TestingStatistics, ComputeHammingWindowStandardDeviation) {
    constexpr auto hamming_reference_solution = 0.327800434716002;
    EXPECT_NEAR(::standard_deviation(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-2);
}

TEST(TestingStatistics, ComputeHammingWindowSkewness) {
    constexpr auto hamming_reference_solution = 0.0111756306502672;
    EXPECT_NEAR(::skewness(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeHammingWindowKurtosis) {
    constexpr auto hamming_reference_solution = 1.49619158551927;
    EXPECT_NEAR(::kurtosis(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-4);
}

TEST(TestingStatistics, ComputeHammingWindowRMS) {
    constexpr auto hamming_reference_solution = 0.627969197094890;
    EXPECT_NEAR(::rms(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-1);
}

TEST(TestingStatistics, ComputeHammingWindowRSSQ) {
    constexpr auto hamming_reference_solution = 7.10466044227309;
    EXPECT_NEAR(::rssq(std::cbegin(hamming_reference), std::cend(hamming_reference)), hamming_reference_solution, 1e-1);
}

TEST(TestingStatistics, ComputeHammingWindowPeak) {
    const auto candidate = ::peak(std::cbegin(hamming_reference), std::cend(hamming_reference));
    const auto maximum = ::max(std::cbegin(hamming_reference), std::cend(hamming_reference));
    EXPECT_EQ(candidate.second, maximum);
    EXPECT_EQ(hamming_reference[candidate.first], maximum);

    const auto candidate_abs = ::peakabs(std::cbegin(hamming_reference), std::cend(hamming_reference));
    const auto maximum_abs = ::maxabs(std::cbegin(hamming_reference), std::cend(hamming_reference));
    EXPECT_EQ(candidate_abs.second, maximum_abs);
    EXPECT_EQ(hamming_reference[candidate_abs.first], maximum_abs);
}