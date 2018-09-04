#ifndef SORT_H
#define SORT_H

#include <iterator>
#include <iostream>
#include <algorithm>
#include <queue>
#include "array.hpp"
#include "matrix.hpp"

/**
 * @brief contains classes and algorithms
 **/
namespace io2357911 {

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

    auto counters = io2357911::array<size_t>(array.size(), 0);

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

    auto firstPart = io2357911::array<T>(
        array.begin(), array.begin() + half);
    merge_sort(firstPart);

    auto secondPart = io2357911::array<T>(
        array.begin() + half, array.end());
    merge_sort(secondPart);

    merge(firstPart, secondPart, array);
}

/**
 * @brief makes partiton for quick sort algorithm
 * @param first is iterator to array's first item
 * @param last is iterator to array's last item
 * @return iterator to partition item
 */
template <typename It>
It partition(It first, It last) {
    auto part = last - 1; // partition item
    auto border = first; // first item larger than the partition one
    auto cur = first;

    // push less item to the left behind the border

    while (cur != last) {
        if (*cur < *part) {
            std::iter_swap(cur, border);
            border++;
        }
        cur++;
    }

    // place the partition item at it's place

    std::iter_swap(part, border);

    return border;
}

/**
 * @brief quick sort algorithm implementation
 * @param first is iterator to array's first item
 * @param last is iterator to array's last item
 */
template <typename It>
void quick_sort(It first, It last) {
    if (last - first < 2) return;

    auto part = partition(first, last);
    quick_sort(first, part);
    quick_sort(part + 1, last);
}

/**
 * @brief quick sort algorithm implementation
 * @param array to be sorted
 */
template <typename T>
void quick_sort(array<T> &array) {
    return quick_sort(array.begin(), array.end());
}

/**
 * @brief heap sort algorithm implementation
 * @param array to be sorted
 */
template <typename T>
void heap_sort(array<T> &array) {
    std::priority_queue<T> queue;

    for (auto item : array) {
        queue.push(item);
    }

    for (auto i = array.rbegin(); i != array.rend(); i++) {
        *i = queue.top();
        queue.pop();
    }
}

} // namespace io2357911

#endif // SORT_H

