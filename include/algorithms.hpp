#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iterator>
#include <algorithm>

/**
 * @brief contains algorithms
 **/
namespace io2357911::algorithms {

/**
 * @brief array abstraction
 **/
template <typename T>
using array = std::vector<T>;

/**
 * @brief prints array of T items
 * @param array to be printed
 */
template <typename T>
void print(const array<T> &array) {
    std::ostream_iterator<int> osi(std::cout, ", ");
    std::cout << std::endl;
    std::copy(array.begin(), array.end(), osi);
}

/**
 * @brief bubble sort algorithm implementation
 * @param array to be sorted
 */
template <typename T>
void bubble_sort(array<T> &array) {
    size_t size = array.size();
    if (!size) return;

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j+1]) {
                std::swap(array[j], array[j+1]);
            }            
        }
    }    
}

/**
 * @brief counting sort algorithm implementation
 * @param array to be sorted
 */
template <typename T>
void count_sort(array<T> &array) {
    size_t size = array.size();
    if (!size) return;

    auto counters = std::vector<size_t>(array.size(), 0);

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (array[i] < array[j]) {
                counters[j]++;
            } else {
                counters[i]++;
            }
        }
    }

    auto arrayCopy = array;
    for (size_t i = 0; i < size; i++) {
        arrayCopy[counters[i]] = array[i]; 
    }

    array = arrayCopy;
}

} // namespace io2357911::algorithms

#endif // ALGORITHMS_H
