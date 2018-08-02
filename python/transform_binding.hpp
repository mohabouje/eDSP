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
 * Filename: transform_binding.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-30
 */

#ifndef PYTHON_BINDING_TRANSFORM_H
#define PYTHON_BINDING_TRANSFORM_H

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/iterator.hpp>

#include <easy/dsp/transform/dct.hpp>
#include <easy/dsp/transform/dht.hpp>
#include <easy/dsp/transform/dft.hpp>

using namespace boost::python;
using namespace easy::dsp;

class Transform {
public:
    static boost::python::list dft(boost::python::list data, const std::size_t size) {
        std::vector<double> real_data(size, 0);
        std::vector<std::complex<double>> complex_data(size / 2 + 1);
        for (std::size_t i = 0; i < size; ++i) {
            real_data[i] = boost::python::extract<double>(data[i]);
        }
        ::dft(std::cbegin(real_data), std::cend(real_data), std::begin(complex_data));
        boost::python::list output;
        for (const auto& element : complex_data) {
            output.append(element);
        }
        return output;
    }

    static boost::python::list idft(boost::python::list data) {
        const auto length = static_cast<std::size_t>(boost::python::len(data));
        std::vector<std::complex<double>> complex_data(length, 0);
        std::vector<double> real_data(2 * length - 1);
        for (std::size_t i = 0; i < length; ++i) {
            complex_data[i] = boost::python::extract<std::complex<double>>(data[i]);
        }
        ::idft(std::cbegin(complex_data), std::cend(complex_data), std::begin(real_data));
        boost::python::list output;
        for (auto element : real_data) {
            output.append(element);
        }
        return output;
    }

    static boost::python::list dct(boost::python::list data, const DCT_Type type, const std::size_t size) {
        std::vector<double> real_data(size, 0), transfor_data(size);
        for (std::size_t i = 0; i < size; ++i) {
            real_data[i] = boost::python::extract<double>(data[i]);
        }
        ::dct(std::cbegin(real_data), std::cend(real_data), std::begin(transfor_data), type);
        boost::python::list output;
        for (const auto& element : transfor_data) {
            output.append(element);
        }
        return output;
    }

    static boost::python::list idct(boost::python::list data, const DCT_Type type, const std::size_t size) {
        std::vector<double> real_data(size, 0), transfor_data(size);
        for (std::size_t i = 0; i < size; ++i) {
            real_data[i] = boost::python::extract<double>(data[i]);
        }
        ::idct(std::cbegin(real_data), std::cend(real_data), std::begin(transfor_data), type);
        boost::python::list output;
        for (const auto& element : transfor_data) {
            output.append(element);
        }
        return output;
    }

    static boost::python::list dht(boost::python::list data, const std::size_t size) {
        std::vector<double> real_data(size, 0), transfor_data(size);
        for (std::size_t i = 0; i < size; ++i) {
            real_data[i] = boost::python::extract<double>(data[i]);
        }
        ::dht(std::cbegin(real_data), std::cend(real_data), std::begin(transfor_data));
        boost::python::list output;
        for (const auto& element : transfor_data) {
            output.append(element);
        }
        return output;
    }

};

#endif
