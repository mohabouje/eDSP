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
#include <edsp/thirdparty/CLI/CLI.hpp>

using namespace edsp;
using namespace edsp::filter;

struct parameter {
    double ripple{};
    double cutoff{};
    double lower_edge{};
    double upper_edge{};
    double sample_rate{};
    std::size_t order{};
    std::size_t points{42000};
    bool display{true};
};

template <typename T, std::size_t N>
void display(const biquad_cascade<T, N>& filter, const parameter& param) {
    if (param.display) {
    }
}

void compute_butterworth(const parameter& param, const std::string& type) {
    const auto diff = param.upper_edge - param.lower_edge;
    auto d = designer<double, designer_type::Butterworth, 100>();
    if (type == "low") {
        const auto cascade = d.design<filter_type::LowPass>(param.order, param.sample_rate, param.cutoff);
        display(cascade, param);
    } else if (type == "high") {
        const auto cascade = d.design<filter_type::HighPass>(param.order, param.sample_rate, param.cutoff);
        display(cascade, param);
    } else if (type == "bandstop") {
        const auto cascade = d.design<filter_type::BandStop>(param.order, param.sample_rate, param.lower_edge + diff / 2, diff);
        display(cascade, param);
    } else if (type == "bandpass") {
        const auto cascade = d.design<filter_type::BandPass>(param.order, param.sample_rate, param.lower_edge + diff / 2, diff);
        display(cascade, param);
    }
}

void compute_chebyshevI(const parameter& param, const std::string& type) {
    const auto diff = param.upper_edge - param.lower_edge;
    auto d = designer<double, designer_type::ChebyshevI, 100>();
    if (type == "low") {
        const auto cascade = d.design<filter_type::LowPass>(param.order, param.sample_rate, param.cutoff, param.ripple);
        display(cascade, param);
    } else if (type == "high") {
        const auto cascade = d.design<filter_type::HighPass>(param.order, param.sample_rate, param.cutoff, param.ripple);
        display(cascade, param);
    } else if (type == "bandstop") {
        const auto cascade = d.design<filter_type::BandStop>(param.order, param.sample_rate, param.lower_edge + diff / 2, diff, param.ripple);
        display(cascade, param);
    } else if (type == "bandpass") {
        const auto cascade = d.design<filter_type::BandPass>(param.order, param.sample_rate, param.lower_edge + diff / 2, diff, param.ripple);
        display(cascade, param);
    }
}

void compute_chebyshevII(const parameter& param, const std::string& type) {
    const auto diff = param.upper_edge - param.lower_edge;
    auto d = designer<double, designer_type::ChebyshevII, 100>();
    if (type == "low") {
        const auto cascade = d.design<filter_type::LowPass>(param.order, param.sample_rate, param.cutoff, param.ripple);
        display(cascade, param);
    } else if (type == "high") {
        const auto cascade = d.design<filter_type::HighPass>(param.order, param.sample_rate, param.cutoff, param.ripple);
        display(cascade, param);
    } else if (type == "bandstop") {
        const auto cascade = d.design<filter_type::BandStop>(param.order, param.sample_rate, param.lower_edge + diff / 2, diff, param.ripple);
        display(cascade, param);
    } else if (type == "bandpass") {
        const auto cascade = d.design<filter_type::BandPass>(param.order, param.sample_rate, param.lower_edge + diff / 2, diff, param.ripple);
        display(cascade, param);
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
    app.add_option("--display-samples", param.points, "Number of points to display", true);


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