/*
 * eDSP, A cross-platform DSP framework written in C++.
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
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EDSP_FEATURE_H
#define EDSP_FEATURE_H

#include "config.h"
#include <type_traits>
#include <iterator>

EDSP_BEGIN_NAMESPACE

/**
 *  @brief Abstract class to implement different feature extraction.
 */
class Feature {
public:
    using value_type = double;
    using size_type = std::size_t;

    /**
     * @brief Default constructor
     */
    Feature();

    /**
     * @brief Default destructor
     */
    virtual ~Feature();

    /**
     * @brief Extracts the feature and stores it in an output buffer
     *
     * @tparam InputIterator Read-Only arithmetic iterator
     * @tparam OutputIterator Read/Write arithmetic iterator
     * @param first First element of the input buffer
     * @param last Last element of the input buffer
     */
    template <class InputIterator, class OutputIterator,
            typename = typename std::enable_if<std::is_arithmetic<typename std::iterator_traits<InputIterator>::value_type >::value ||
                                               std::is_arithmetic<typename std::iterator_traits<OutputIterator>::value_type >::value>::type>
    EDSP_INLINE void extract(_In_ InputIterator first, _In_ InputIterator last, _Out_ OutputIterator);

    /**
     * @brief Extracts the feature and stores it in an output buffer
     * @tparam T An arithmetic type
     * @param input Input buffer
     * @param sz Size of the input buffer
     * @param output Output buffer containing the extracted features
     */
    template <class T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    EDSP_INLINE void extract(_In_ T* input, _In_ size_type sz, _Out_ T* output);

protected:
    virtual void extract_implementation(_In_ const value_type *input, _In_ size_type size, _Out_  value_type *output) = 0;
};

    template<class InputIterator, class OutputIterator, typename>
    void Feature::extract(_In_ InputIterator first, _In_ InputIterator last, _Out_ OutputIterator out) {
        const auto size = static_cast<size_type>(std::distance(first, last));
        extract_implementation(first, size, out);
    }

    template<class T, typename>
    void Feature::extract(_In_ T *input, _In_ Feature::size_type sz, _Out_ T *output) {
        extract_implementation(input, sz, output);
    }

    Feature::Feature() = default;

    Feature::~Feature() = default;


EDSP_END_NAMESPACE



#endif //EDSP_FEATURE_H
