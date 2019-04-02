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
 * You should have received a copy of the GNU General Public License along width
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * File: random_generator.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EDSP_FISHER_DISTRIBUTION_HPP
#define EDSP_FISHER_DISTRIBUTION_HPP

#include <random>
#include <chrono>

namespace edsp { namespace random {

    /**
     * @brief The DistributionType enum represents all the available distributions in the pseudo-random number
     * generation library.
     */
    enum class DistributionType {
        Uniform,           /*<! Produces real values evenly distributed across a range */
        Bernoulli,         /*<! Produces random values on a Bernoulli distribution */
        Binomial,          /*<! Produces random values on a binomial distribution */
        Geometric,         /*<! Produces random values on a geometric distribution */
        Poisson,           /*<! Produces random values on a Poisson distribution */
        Exponential,       /*<! Produces random values on a exponential distribution */
        Gamma,             /*<! Produces random values on a Gamma distribution */
        Weibull,           /*<! Produces random values on a Weibull distribution */
        ExtremeValue,      /*<! Produces random values on a extreme value distribution */
        Normal,            /*<! Produces random values on a normal distribution */
        LogNormal,         /*<! Produces random values on a logarithmic normal distribution */
        ChiSquared,        /*<! Produces random values on a chi-squared distribution */
        Cauchy,            /*<! Produces random values on a Cauchy distribution */
        Fisher,            /*<! Produces random values on a Fisher distribution */
        Student,           /*<! Produces random values on a Student distribution */
        Discrete,          /*<! Produces random values on a discrete distribution */
        PieceWiseConstant, /*<! Produces real values distributed on constant subintervals.  */
        PieceWiseLinear    /*<! Produces real values distributed on defined subintervals.  */
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

        template <DistributionType Type, typename T>
        struct _RandomGenerator;

        template <typename T>
        struct _RandomGenerator<DistributionType::Uniform, T>
            : public RandomGeneratorImpl<std::uniform_real_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Bernoulli, T>
            : public RandomGeneratorImpl<std::bernoulli_distribution, T> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Binomial, T>
            : public RandomGeneratorImpl<std::binomial_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Geometric, T>
            : public RandomGeneratorImpl<std::geometric_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Poisson, T>
            : public RandomGeneratorImpl<std::poisson_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Exponential, T>
            : public RandomGeneratorImpl<std::exponential_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Gamma, T> : public RandomGeneratorImpl<std::gamma_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Weibull, T>
            : public RandomGeneratorImpl<std::weibull_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::ExtremeValue, T>
            : public RandomGeneratorImpl<std::extreme_value_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Normal, T> : public RandomGeneratorImpl<std::normal_distribution<T>> {
        };

        template <typename T>
        struct _RandomGenerator<DistributionType::LogNormal, T>
            : public RandomGeneratorImpl<std::lognormal_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::ChiSquared, T>
            : public RandomGeneratorImpl<std::chi_squared_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Fisher, T>
            : public RandomGeneratorImpl<std::fisher_f_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Student, T>
            : public RandomGeneratorImpl<std::student_t_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Discrete, T>
            : public RandomGeneratorImpl<std::discrete_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::PieceWiseConstant, T>
            : public RandomGeneratorImpl<std::piecewise_constant_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::PieceWiseLinear, T>
            : public RandomGeneratorImpl<std::piecewise_linear_distribution<T>> {};

        template <typename T>
        struct _RandomGenerator<DistributionType::Cauchy, T> : public RandomGeneratorImpl<std::cauchy_distribution<T>> {
        };

    } // namespace internal

    /**
     * @class random_generator
     * @brief This class implements a random generator according to one of the discrete probability function availables
     * in the c++ standard.
     *
     * @see Distribution
     */
    template <DistributionType dist, typename T>
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

}} // namespace edsp::random

#endif // EDSP_RANDOM_GENERATORDISTRIBUTION_HPP
