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

struct parameter {
    double ripple;
    double cutoff;
    double lower_edge;
    double upper_edge;
    double sample_rate;
    int order;
    bool display = true;
};


void compute_butterworth(const parameter& param, const std::string& type) {
    const auto diff = param.upper_edge - param.lower_edge;
    if (type == "low") {
        auto designer = ButterworthDesigner<double, FilterType::LowPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.cutoff);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "high") {
        auto designer = ButterworthDesigner<double, FilterType::HighPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.cutoff);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "bandstop") {
        auto designer = ButterworthDesigner<double, FilterType::BandStop, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.lower_edge + diff / 2, diff);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "bandpass") {
        auto designer = ButterworthDesigner<double, FilterType::BandPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.lower_edge + diff / 2, diff);
        chart::freqz(cascade, 42000,  param.sample_rate);
    }
}

void compute_chebyshevI(const parameter& param, const std::string& type) {
    const auto diff = param.upper_edge - param.lower_edge;
    if (type == "low") {
        auto designer = ChebyshevIDesigner<double, FilterType::LowPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.cutoff, param.ripple);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "high") {
        auto designer = ChebyshevIDesigner<double, FilterType::HighPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.cutoff, param.ripple);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "bandstop") {
        auto designer = ChebyshevIDesigner<double, FilterType::BandStop, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.lower_edge + diff / 2, diff, param.ripple);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "bandpass") {
        auto designer = ChebyshevIDesigner<double, FilterType::BandPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.lower_edge + diff / 2, diff, param.ripple);
        chart::freqz(cascade, 42000,  param.sample_rate);
    }
}

void compute_chebyshevII(const parameter& param, const std::string& type) {
    const auto diff = param.upper_edge - param.lower_edge;
    if (type == "low") {
        auto designer = ChebyshevIIDesigner<double, FilterType::LowPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.cutoff, param.ripple);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "high") {
        auto designer = ChebyshevIIDesigner<double, FilterType::HighPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.cutoff, param.ripple);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "bandstop") {
        auto designer = ChebyshevIIDesigner<double, FilterType::BandStop, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.lower_edge + diff / 2, diff, param.ripple);
        chart::freqz(cascade, 42000,  param.sample_rate);
    } else if (type == "bandpass") {
        auto designer = ChebyshevIIDesigner<double, FilterType::BandPass, 100>();
        const auto cascade = designer(param.order, param.sample_rate, param.lower_edge + diff / 2, diff, param.ripple);
        chart::freqz(cascade, 42000,  param.sample_rate);
    }
}



int main(int argc, char** argv) {
    std::string type, author;
    parameter param{};


    CLI::App app{"Filter designer"};
    app.add_set("--author", author, {"butterworth", "chebyshevI", "chebyshevII"}, "Filter category")->required(true);
    app.add_set("--type", type, {"low", "high", "bandstop", "bandpass"}, "Filter type")->required(true);
    app.add_option("--order", param.order, "Filter order")->required(true);
    app.add_option("--sample-rate", param.sample_rate, "Sampling frequency in Hz")->required(true);
    app.add_option("--display", param.display, "Display the magnitude/phase of the computed filter-", true);


    auto* leo = app.add_option("--lower", param.lower_edge, "Lower edge frequency in Hz");
    app.add_option("--upper", param.upper_edge, "Upper edge frequency in Hz")->needs(leo);
    app.add_option("--ripple", param.ripple, "Peak-to-peak pass band ripple");
    app.add_option("--cut-off", param.cutoff, "Cut-off frequency in Hz");

    try {
        app.parse(argc, argv);
    } catch (const std::exception& ref) {
        std::cerr << ref.what() << std::endl;
        return -1;
    }

    if (author == "butterworth") {
        compute_butterworth(param, type);
    } else if (author == "chebyshevI") {
        compute_chebyshevI(param, type);
    } else if (author == "chebyshevII") {
        compute_chebyshevII(param, type);
    }
    return 0;
}