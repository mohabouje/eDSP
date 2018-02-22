//
// Created by mboujemaoui on 22/02/18.
//

#ifndef EDSP_FEATURE_H
#define EDSP_FEATURE_H

#include "config.h"
#include <type_traits>
#include <iterator>

EDSP_BEGIN_NAMESPACE

class Feature {
    using value_type = double;
    using size_type = std::size_t;

    /**
     * @brief Default constructor
     */
    Feature();

    /**
     * @brief Default destructor
     */
    ~Feature();

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
    EDSP_INLINE void compute(_In_ InputIterator first, _In_ InputIterator last, _Out_ OutputIterator);

    /**
     * @brief Extracts the feature and stores it in an output buffer
     *
     * @throw Throw a runtime error if the size of the input array is less than the window one.
     * @tparam T An arithmetic type
     * @param input Input buffer
     * @param sz Size of the buffers
     */
    template <class T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    EDSP_INLINE value_type compute(_In_ T* input, _In_ size_type sz);

    /**
     * @brief Extracts the feature and stores it in an output buffer
     * @tparam T An arithmetic type
     * @param input Input buffer
     * @param sz Size of the input buffer
     * @param output Output buffer containing the extracted features
     */
    template <class T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    EDSP_INLINE void compute(_In_ T* input, _In_ size_type sz, _Out_ T* output);

protected:
    virtual void extract(_In_ const value_type* input, _In_ size_type size, _Out_  value_type* output) = 0;
};

    template<class InputIterator, class OutputIterator, typename>
    void Feature::compute(_In_ InputIterator first, _In_ InputIterator last, _Out_ OutputIterator out) {
        const auto size = static_cast<size_type>(std::distance(first, last));
        extract(first, size, out);
    }

    template<class T, typename>
    Feature::value_type Feature::compute(_In_ T *input, _In_ Feature::size_type sz) {
        value_type tmp;
        extract(input, sz, &tmp);
        return tmp;
    }

    template<class T, typename>
    void Feature::compute(_In_ T *input, _In_ Feature::size_type sz, _Out_ T *output) {
        extract(input, sz, output);
    }

    Feature::Feature() = default;

    Feature::~Feature() = default;


EDSP_END_NAMESPACE



#endif //EDSP_FEATURE_H
