/*
 * EasyDSP, Yet another header-only library for C++ meta-programming.
 * Copyright (C) 2018 Mohammed Boujemaoui
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
 * Filename: standard_binding.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/7/2018
 */
#ifndef STANDARD_BINDING_HPP
#define STANDARD_BINDING_HPP

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/numpy.hpp>

#include <easy/dsp/standard/crosscorrelation.hpp>
#include <easy/dsp/standard/convolution.hpp>
#include <easy/dsp/standard/spectrum.hpp>
#include <easy/dsp/standard/autocorrelation.hpp>
#include <easy/dsp/standard/cepstrum.hpp>

using namespace boost::python;
using namespace boost::python::numpy;
using namespace easy::dsp;

template <class Standard>
boost::python::list compute_simple(Standard& component, const boost::python::list& data) {
    const auto size = static_cast<std::size_t>(boost::python::len(data));
    std::vector<double> stored, computed;
    stored.reserve(size);
    computed.reserve(size);
    for (std::size_t i = 0; i < size; ++i) {
        stored.push_back(boost::python::extract<double>(data[i]));
    }
    component.compute(std::cbegin(stored), std::cend(stored), std::begin(computed));
    boost::python::list output;
    for (const auto element : computed) {
        output.append(element);
    }
    return output;
}

template <class Standard>
boost::python::list compute_double(Standard& component,
                            const boost::python::list& data_X,
                            const boost::python::list& data_Y) {
    const auto size = static_cast<std::size_t>(boost::python::len(data_X));
    std::vector<double> stored_X, stored_Y, computed;
    stored_X.reserve(size);
    stored_Y.reserve(size);
    computed.reserve(size);
    for (std::size_t i = 0; i < size; ++i) {
        stored_X.push_back(boost::python::extract<double>(data_X[i]));
        stored_Y.push_back(boost::python::extract<double>(data_Y[i]));

    }
    component.compute(std::cbegin(stored_X), std::cend(stored_X),
                      std::cbegin(stored_Y), std::begin(computed));
    boost::python::list output;
    for (const auto element : computed) {
        output.append(element);
    }
    return output;
}


void declare_standard() {

    enum_<::AutoCorrelation<double>::ScaleOpt>("AutoCorrelationScale")
            .value("Biased", ::AutoCorrelation<double>::ScaleOpt::Biased)
            .value("None", ::AutoCorrelation<double>::ScaleOpt::None);

    enum_<::CrossCorrelation<double>::ScaleOpt>("CrossCorrelationScale")
            .value("Biased", ::CrossCorrelation<double>::ScaleOpt::Biased)
            .value("None", ::CrossCorrelation<double>::ScaleOpt::None);

    class_<::AutoCorrelation<double>>("AutoCorrelation", init<std::size_t, ::AutoCorrelation<double>::ScaleOpt>())
            .def("compute", &compute_simple<::AutoCorrelation<double>>);
    class_<::Spectrum<double>>("Spectrum", init<std::size_t>())
            .def("compute", &compute_simple<::Spectrum<double>>);
    class_<::Cepstrum<double>>("Cepstrum", init<std::size_t>())
            .def("compute", &compute_simple<::Cepstrum<double>>);
    class_<::CrossCorrelation<double>>("CrossCorrelation", init<std::size_t, ::CrossCorrelation<double>::ScaleOpt>())
            .def("compute", &compute_double<::CrossCorrelation<double>>);
    class_<::Convolution<double>>("Convolution", init<std::size_t>())
            .def("compute", &compute_double<::Convolution<double>>);
}

class Standard {};

#endif // STANDARD_BINDING_HPP
