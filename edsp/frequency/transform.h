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
#ifndef EDSP_FREQUENCY_TRANSFORM_H
#define EDSP_FREQUENCY_TRANSFORM_H

#include "config.h"
#include <fftw3.h>
#include <memory>
#include <functional>

EDSP_BEGIN_NAMESPACE

template <class Input, class Output,
        class InputAllocator = std::allocator<Input>,
        class OutputAllocator = std::allocator<Output>>
class Transform {
    EDSP_DECLARE_MOVE_IMPLICITS(Transform)
public:
    Transform(_In_ std::size_t size);
    virtual ~Transform();

    EDSP_INLINE void resize(_In_ std::size_t size);
    EDSP_INLINE std::size_t size() const EDSP_NOEXCEPT;

    template <class InputIterator, class OutputIterator>
    EDSP_INLINE void compute(_In_ InputIterator first, _In_ InputIterator last,_Out_ OutputIterator out);

    EDSP_INLINE void compute(_In_ const Input* in, _In_ std::size_t sz, _Out_ Output* out);

protected:
    virtual void build_plan() = 0;
    virtual void execute_plan() = 0;
    EDSP_INLINE void make_plan(_In_ fftw_plan* plan);

    using fftw_unique_ptr = std::unique_ptr<fftw_plan, std::function<void(fftw_plan)>>;
    fftw_unique_ptr _plan = nullptr;
    std::vector<Input, InputAllocator> _input;
    std::vector<Output, OutputAllocator> _output;
};

template <class Input, class Output, class InputAllocator, class OutputAllocator>
Transform<Input, Output, InputAllocator, OutputAllocator>::Transform(_In_ std::size_t size) :
    _input(std::vector<Input, InputAllocator>(size)),
    _output(std::vector<Output, OutputAllocator>(size)) {
}

template <class Input, class Output, class InputAllocator, class OutputAllocator>
Transform<Input, Output, InputAllocator, OutputAllocator>::~Transform() = default;

template <class Input, class Output, class InputAllocator, class OutputAllocator>
void Transform<Input, Output, InputAllocator, OutputAllocator>::resize(_In_ const std::size_t size)  {
    _input.resize(size);
    _output.resize(size);
    build_plan();
}

template <class Input, class Output, class InputAllocator, class OutputAllocator>
std::size_t Transform<Input, Output, InputAllocator, OutputAllocator>::size() const EDSP_NOEXCEPT {
    return _input.size();
}

template<class Input, class Output, class InputAllocator, class OutputAllocator>
void Transform<Input, Output, InputAllocator, OutputAllocator>::make_plan(_In_ fftw_plan *plan) {
    _plan.reset(nullptr);
    _plan = fftw_unique_ptr(plan, fftw_destroy_plan);
}

template<class Input, class Output, class InputAllocator, class OutputAllocator>
template<class InputIterator, class OutputIterator>
void Transform<Input, Output, InputAllocator, OutputAllocator>::compute(_In_ InputIterator first, _In_ InputIterator last, _Out_ OutputIterator out) {
    static_assert (std::is_same<typename std::iterator_traits<InputIterator>::value_type, Input>::value &&
                   std::is_same<typename std::iterator_traits<InputIterator>::value_type, Input>::value, "Introduced iterator is not valid");

    const auto sz = std::distance(first, last);
    compute(first, sz, out);
}

template<class Input, class Output, class InputAllocator, class OutputAllocator>
void Transform<Input, Output, InputAllocator, OutputAllocator>::compute(_In_ const Input *in, _In_ std::size_t sz, _Out_ Output *out) {
    if (sz > size()) {
        throw std::runtime_error("Expected size " + size());
    }

    std::copy(in, in + sz, std::begin(_input));
    execute_plan();
    std::copy(std::begin(_output), std::end(_output), out);
}


EDSP_END_NAMESPACE
#endif //EDSP_FREQUENCY_TRANSFORM_H
