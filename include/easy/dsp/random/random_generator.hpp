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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: random_generator.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EASYDSP_FISHER_DISTRIBUTION_HPP
#define EASYDSP_FISHER_DISTRIBUTION_HPP

#include <random>
#include <chrono>

namespace easy { namespace dsp { namespace random {

    enum class Distribution {
        Uniform,
        Bernoulli,
        Binomial,
        Geometric,
        Poisson,
        Exponential,
        Gamma,
        Weibull,
        ExtremeValue,
        Normal,
        LogNormal,
        ChiSquared,
        Cauchy,
        Fisher,
        Student,
        Discrete,
        PieceWiseConstant,
        PieceWiseLinear
    };


    namespace internal {

        template <typename Distribution, typename Engine = std::mt19937>
        struct RandomGeneratorImpl {
            using value_type = typename Distribution::value_type;
            template <typename... Args>
            explicit RandomGeneratorImpl(Args... arg) :
                    generator_(
                            Engine(static_cast<std::size_t>(std::chrono::system_clock::now().time_since_epoch().count()))),
                    distribution_(Distribution(std::forward(arg...))) {}

            inline value_type operator()() {
                return static_cast<value_type>(distribution_(generator_));
            }

        private:
            Engine generator_;
            Distribution distribution_;
        };


        template <Distribution Type, typename T>
        struct _RandomGenerator;

        template <typename T>
        struct _RandomGenerator<Distribution::Uniform, T>
            : public RandomGeneratorImpl<std::uniform_real_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Bernoulli, T>
            : public RandomGeneratorImpl<std::bernoulli_distribution, T> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Binomial, T> : public RandomGeneratorImpl<std::binomial_distribution<T>> {
        };

        template <typename T>
        struct _RandomGenerator<Distribution::Geometric, T>
            : public RandomGeneratorImpl<std::geometric_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Poisson, T> : public RandomGeneratorImpl<std::poisson_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Exponential, T>
            : public RandomGeneratorImpl<std::exponential_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Gamma, T> : public RandomGeneratorImpl<std::gamma_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Weibull, T> : public RandomGeneratorImpl<std::weibull_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::ExtremeValue, T>
            : public RandomGeneratorImpl<std::extreme_value_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Normal, T> : public RandomGeneratorImpl<std::normal_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::LogNormal, T>
            : public RandomGeneratorImpl<std::lognormal_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::ChiSquared, T>
            : public RandomGeneratorImpl<std::chi_squared_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Fisher, T> : public RandomGeneratorImpl<std::fisher_f_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::Student, T> : public RandomGeneratorImpl<std::student_t_distribution<T>> {
        };

        template <typename T>
        struct _RandomGenerator<Distribution::Discrete, T> : public RandomGeneratorImpl<std::discrete_distribution<T>> {
        };

        template <typename T>
        struct _RandomGenerator<Distribution::PieceWiseConstant, T>
            : public RandomGeneratorImpl<std::piecewise_constant_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<Distribution::PieceWiseLinear, T>
            : public RandomGeneratorImpl<std::piecewise_linear_distribution<T>> {};

    } // namespace

    /**
     * @class random_generator
     * @brief This class implements a random generator according to one of the discrete probability function availables
     * in the c++ standard.
     *
     * @see Distribution
     */
    template <Distribution dist, typename T>
    struct random_generator {
        using value_type = T;

        /**
         * @brief Creates a random generator.
         * @param arg Arguments parameters to initialize the internal engine. It depends of the chosen distribution.
         * @see https://en.cppreference.com/w/cpp/numeric/random
         */
        template <typename... Args>
        explicit random_generator(Args... arg) : generator_(arg...) {}

        /**
         * @brief Generates a random number based in the chosen distribution.
         * @return The generated random number.
         */
        value_type operator()() {
            return generator_.operator()();
        }
    private:
        internal::_RandomGenerator<dist, T> generator_;
    };

}}} // namespace easy::dsp::random

#endif // EASYDSP_FISHER_DISTRIBUTION_HPP
