/*
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
* You should have received a copy of the GNU General Public License along withº
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: biquad_design.cpp
* Author: Mohammed Boujemaoui
* Date: 19/10/18
*/

#include <edsp/filter.hpp>
#include <edsp/chart/freqz.hpp>
#include <edsp/thirdparty/CLI/CLI.hpp>

using namespace edsp;
using namespace edsp::filter;
int main(int argc, char** argv) {
    std::uint32_t order;
    std::string ftype, author;
    double ripple, cutoff, lower_edge, upper_edge, sample_rate;

    CLI::App app{"Filter designer"};
    app.add_set("--author", author, {"butterworth", "chebyshevI", "chevyshevII"}, "Filter category")->required(true);
    app.add_set("--type", ftype, {"low", "high", "bandstop", "bandpass"}, "Filter type")->required(true);
    app.add_option("--order", order, "Filter order")->required(true);
    app.add_option("--sample-rate", sample_rate, "Sampling frequency in Hz")->required(true);

    auto* rpo = app.add_option("--ripple", ripple, "Peak-to-peak pass band ripple");
    auto* leo = app.add_option("--lower", lower_edge, "Lower edge frequency in Hz")->needs(rpo);
    app.add_option("--upper", upper_edge, "Upper edge frequency in Hz")->needs(leo);
    app.add_option("--cut-off", cutoff, "Cut-off frequency in Hz");

    try {
        app.parse(argc, argv);
    } catch (const std::exception& ref) {
        std::cerr << ref.what() << std::endl;
        std::cout << app.help();
        return -1;
    }

    const auto diff = upper_edge - lower_edge;
    if (ftype == "low") {
        auto designer = ButterworthDesigner<double, FilterType::LowPass, 100>();
        auto cascade = designer(order, sample_rate, cutoff);
        chart::freqz(cascade, 42000,  sample_rate);
    } else if (ftype == "high") {
        auto designer = ButterworthDesigner<double, FilterType::HighPass, 100>();
        auto cascade = designer(order, sample_rate, cutoff);
        chart::freqz(cascade, 42000,  sample_rate);
    } else if (ftype == "bandstop") {
        auto designer = ButterworthDesigner<double, FilterType::BandStop, 100>();
        auto cascade = designer(order, sample_rate, lower_edge + diff / 2, diff);
        chart::freqz(cascade, 42000,  sample_rate);
    } else if (ftype == "bandpass") {
        auto designer = ButterworthDesigner<double, FilterType::BandPass, 100>();
        auto cascade = designer(order, sample_rate, lower_edge + diff / 2, diff);
        chart::freqz(cascade, 42000,  sample_rate);
    }



    return 0;
}