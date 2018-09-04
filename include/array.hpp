#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

namespace io2357911 {

/**
 * @brief array abstraction
 **/
template<
    class T,
    class Allocator = std::allocator<T>
>
using array = std::vector<T, Allocator>;
//using array = std::deque<T, Allocator>;

} // namespace io2357911

#endif // ARRAY_H
