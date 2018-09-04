#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace io2357911 {

/**
 * @brief class _matrix is just alias to vector of vectors
 */
template<
    class T,
    class Allocator = std::allocator<T>
>
using _matrix = std::vector<std::vector<T, Allocator>, Allocator>;

/**
 * @brief class matrix is alias to vector plus additional usefull methods
 *
 * TODO: matrix is not safe, because can contain rows with different size
 */
template<
    class T,
    class Allocator = std::allocator<T>
>
class matrix : public _matrix<T, Allocator> {
public:
    using _matrix<T, Allocator>::vector;
    using _matrix<T, Allocator>::operator=;

    size_t rows() const {
        return this->size();
    }
    size_t columns() const {
        return this->size() ? this[0].size() : 0;
    }
};

} // namespace io2357911

#endif // MATRIX_H
