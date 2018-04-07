//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_WINDOW_BASE_H
#define EDSP_WINDOW_BASE_H

#include "config.h"
#include <vector>
#include <iterator>
#include <type_traits>

EDSP_BEGIN_NAMESPACE

/**
 * @brief An abstract container class that stores the computation of a generic %window function.
 *
 * In DSP, a %window function is a mathematical function that is zero-valued outside of some chosen interval. A %window
 * function is generally used for taking a small subset of a larger dataset, for processing and analysis.
 *
 * The reason there are so many types is that each one generates a slightly different frequency response and time domain
 * response.
 */

class Window {
public:
    using value_type = double;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type&;
    using const_reference = const value_type&;

    using iterator = value_type*;
    using const_iterator = value_type*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using size_type = std::vector<double>::size_type;
    using difference_type = std::ptrdiff_t;

    enum class WindowType {
        Symmetric,
        Periodic
    };


    /**
     * @brief Creates a %window with no elements.
     */
    Window();

    /**
     * @brief Creates and computes a %window with the default constructed elements.
     * @param size The number of elements to initially create.
     */
    explicit Window(_In_ size_type size);

    /**
     * @brief Creates and computes a %window with the default constructed elements and the given type
     * @param size The number of elements to initially create.
     * @param type Type of the window: Symmetric or Periodic
     */
    Window(_In_ size_type size, _In_ WindowType type);


    /**
     * @brief Default destructor that erase the different elements in the %window.
     */
    virtual ~Window();

    /**
     * @brief Applies the window to a buffer defined by both iterators and stores the result in the output buffer.
     *
     * Both buffer should be of the same size.
     *
     * @tparam InputIterator Read-Only arithmetic iterator
     * @tparam OutputIterator Read/Write arithmetic iterator
     * @param first First element of the input buffer
     * @param last Last element of the input buffer
     */
    template <class InputIterator, class OutputIterator,
            typename = typename std::enable_if<std::is_arithmetic<typename std::iterator_traits<InputIterator>::value_type >::value ||
                                      std::is_arithmetic<typename std::iterator_traits<OutputIterator>::value_type >::value>::type>
    void compute(_In_ InputIterator first, _In_ InputIterator last, _Out_ OutputIterator);


    /**
     * @brief Applies the window to a buffer defined by both iterators.
     * @throw Throw a runtime error if the size of the input array is less than the window one.
     * @tparam OutputIterator Read/Write arithmetic iterator
     * @param first First element of the input buffer
     * @param last Last element of the input buffer
     */
    template <class OutputIterator,
            typename = typename std::enable_if<std::is_arithmetic<typename std::iterator_traits<OutputIterator>::value_type >::value>::type>
    void compute(_InOut_ OutputIterator first, _InOut_ OutputIterator last);


    /**
     * @brief Applies the window in the %input buffer.
     *
     * @throw Throw a runtime error if the size of the input array is less than the window one.
     * @tparam T An arithmetic type
     * @param input Input buffer
     * @param sz Size of the buffers
     */
    template <class T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    void compute(_InOut_ T* input, _In_ size_type sz);

    /**
     * @brief Applies the window to an %input buffer and stores the result in the %output buffer.
     *
     * Both buffer should be of the same size.
     *
     * @throw Throw a runtime error if the size of the input array is less than the window one.
     * @tparam T An arithmetic type
     * @param input Input buffer
     * @param output Output buffer
     * @param sz Size of the buffers
     */
    template <class T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    void compute(_In_ const T* input, _Out_ T* output, _In_ size_type sz);

    /**
     * @brief Initialize the %window and stores the computed values in the local data.
     *
     * This function computes the data of the %window. It can be called when the size of the window has been changed
     * or when the local data has been modified and should be restored.
     */
    virtual void initialize() = 0;

    /**
     * @brief Returns the number of elements in the %window
     * @return Number of elements in the %window
     */
    EDSP_INLINE size_type size() const EDSP_NOEXCEPT;

    /**
     * @brief Returns true if the %window is empty.
     * @return True/False if the %window is empty.
     */
    EDSP_INLINE bool empty() const EDSP_NOEXCEPT;

    /**
     * @brief Attempt to preallocate enough memory for specified number of elements
     * @param size Number of elements required.
     *
     * This function atempts to reserve enough memory for the %window. It allows the reservation
     * of memory in %advance to prevent a possible reallocation of memory.
     *
     * Note: This function does not compute the %window, so %compute should be called after.
     */
    EDSP_INLINE void reserve(_In_ size_type size);

    /**
     * @brief Resizes the %window to the specified number of elements.
     * @param size Number of elements the %window should contain.
     *
     * This function will resize & compute the window to the specified number of elements.
     */
    EDSP_INLINE void resize(_In_ size_type size);

    /**
     * @brief Returns a constant pointer such that [data(), data() + size()) is a valid range.
     * @return Constant pointer to the data of the window.
     */
    EDSP_INLINE const_pointer data() const EDSP_NOEXCEPT;

    /**
     * @brief Returns a const pointer such that [data(), data() + size()) is a valid range.
     * @return Pointer to the data of the window.
     */
    EDSP_INLINE pointer data() EDSP_NOEXCEPT;

    /**
     *  @brief Returns a Read-Only iterator that points to the first
     *  element in the %window.
     *  @return Constant iterator of the first element.
     */
    EDSP_INLINE const_iterator cbegin() const EDSP_NOEXCEPT;

    /**
     *  @brief Returns a Read-Only iterator that points to the last element in the %window (cbegin() + size()).
     *  @return Contant iterator of the last element.
     */
    EDSP_INLINE const_iterator cend() const EDSP_NOEXCEPT;

    /**
     *  @brief Returns a Read/Write iterator that points to the first element in the %window.
     *  @return Iterator of the first element.
     */
    EDSP_INLINE iterator begin() const EDSP_NOEXCEPT;

    /**
     *  @brief Returns a Read/Write iterator that points to the last
     *  element in the %window (begin() + size()).
     *  @return Iterator of the last element.
     */
    EDSP_INLINE iterator end() const EDSP_NOEXCEPT;

    /**
     *  @brief Subscript access to the data contained in the %window.
     *  @param pos The index of the element for which the data should be accessed.
     *  @return Read/Write reference to data.
     *
     *  Note that data access with this operator is unchecked.
     */
    EDSP_INLINE reference operator[](_In_ size_type pos) EDSP_NOEXCEPT;

    /**
     *  @brief Subscript access to the data contained in the %window.
     *  @param pos The index of the element for which the data should be accessed.
     *  @return Read-only reference to data.
     *
     *  Note that data access with this operator is unchecked.
     */
    EDSP_INLINE const_reference operator[](_In_ size_type pos) const EDSP_NOEXCEPT;

    /**
     *  @brief Returns the type of the window
     *  @return
     */
    EDSP_INLINE WindowType type() const EDSP_NOEXCEPT;

    /**
     * @brief Set the type of the window,
     *
     * Note: In some windows updating this parameter has no effect,
     * @param type Type of the window: Symmetric or Periodic
     * @return
     */
    EDSP_INLINE WindowType set_type(_In_ WindowType type) EDSP_NOEXCEPT;
protected:
    std::vector<value_type> data_;
    WindowType type_ = WindowType::Symmetric;
};

Window::Window() {

}

Window::~Window() {

}

Window::Window(_In_ Window::size_type sz) : data_(std::vector<double>(sz)) {

}

Window::Window(_In_ size_type size, _In_ Window::WindowType type_) : data_(std::vector<double>(size)), type_(type_) {

}

Window::size_type Window::size() const EDSP_NOEXCEPT {
    return data_.size();
}

void Window::reserve(_In_ Window::size_type size) {
    data_.reserve(size);
}

void Window::resize(_In_ Window::size_type size) {
    data_.resize(size);
    initialize();
}

Window::const_pointer Window::data() const EDSP_NOEXCEPT {
    return data_.data();
}

Window::pointer Window::data() EDSP_NOEXCEPT {
    return data_.data();
}

Window::const_iterator Window::cbegin() const EDSP_NOEXCEPT {
    return const_iterator(&data_[0]);
}

Window::const_iterator Window::cend() const EDSP_NOEXCEPT {
    return cbegin() + size();
}

Window::iterator Window::begin() const EDSP_NOEXCEPT {
    return iterator(&data_[0]);
}

Window::iterator Window::end() const EDSP_NOEXCEPT {
    return begin() + size();
}

const Window::value_type &Window::operator[](_In_ Window::size_type pos) const EDSP_NOEXCEPT {
    return data_[pos];
}

Window::value_type &Window::operator[](_In_ Window::size_type pos) EDSP_NOEXCEPT {
    return data_[pos];
}

bool Window::empty() const EDSP_NOEXCEPT {
    return data_.empty();
}

Window::WindowType Window::type() const EDSP_NOEXCEPT {
    return type_;
}

Window::WindowType Window::set_type(_In_ Window::WindowType type) EDSP_NOEXCEPT {
    return type_ = type;
}

template<class InputIterator, class OutputIterator, typename>
void Window::compute(_In_ InputIterator first, _In_ InputIterator last, _Out_ OutputIterator out) {
    const auto input_size = std::distance(first, last);
    compute(first, out, input_size);
}

template<class OutputIterator, typename>
void Window::compute(_InOut_ OutputIterator first, _InOut_ OutputIterator last) {
    const auto input_size = std::distance(first, last);
    compute(first, input_size);
}

template<class T, typename>
void Window::compute(_InOut_ T *input, _In_ Window::size_type input_size) {
    if (input_size < size()) {
        throw std::runtime_error("Expected input size bigger than " + std::to_string(size()));
    }

    for (size_type i = 0, sz = size(); i < sz; ++i, ++input) {
        (*input) = (*input) * data_[i];
    }
}

template<class T, typename>
void Window::compute(_In_ const T *input, _Out_ T *out, _In_ Window::size_type input_size) {
    if (input_size < size()) {
        throw std::runtime_error("Expected input size bigger than " + std::to_string(size()));
    }

    for (size_type i = 0, sz = size(); i < sz; ++i, ++input, ++out) {
        (*out) = (*input) * data_[i];
    }
}

EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_BASE_H
