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

    auto counters = algorithms::array<size_t>(array.size(), 0);

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

/**
 * @brief insert sort algorithm implementation
 * @param array to be sorted
 */
template <typename T>
void insert_sort(array<T> &array) {
    size_t size = array.size();
    if (!size) return;

    for (size_t i = 1; i < size; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (array[j+1] < array[j]) {
                std::swap(array[j+1], array[j]);
            } else {
                break;
            }
        }
    }
}

/**
 * @brief merges two array parts into one array
 * @param firstPart is first part to be merged
 * @param secondPart is second part to be merged
 * @param target is array to merge in both parts
 */
template <typename T>
void merge(const array<T> &firstPart,
    const array<T> &secondPart,
    array<T> &target) {

    auto f = firstPart.begin();
    auto s = secondPart.begin();
    auto t = target.begin();

    // copy entire part (first or second)

    while (f != firstPart.end() && s != secondPart.end()) {
        if (*f < *s) {
            *t = *f;
            f++;
        } else {
            *t = *s;
            s++;
        }
        t++;
    }

    // copy remain part (first or second)

    if (f != firstPart.end()) {
        std::copy(f, firstPart.end(), t);
    } else {
        std::copy(s, secondPart.end(), t);
    }
}

/**
 * @brief merge sort algorithm implementation
 * @param array to be sorted
 */
template <typename T>
void merge_sort(array<T> &array) {
    size_t size = array.size();
    if (size < 2) return;

    size_t half = size / 2;

    auto firstPart = algorithms::array<T>(
        array.begin(), array.begin() + half);
    merge_sort(firstPart);

    auto secondPart = algorithms::array<T>(
        array.begin() + half, array.end());
    merge_sort(secondPart);

    merge(firstPart, secondPart, array);
}

} // namespace io2357911::algorithms

#endif // ALGORITHMS_H
