#ifndef FIND_H
#define FIND_H

#include "matrix.hpp"

namespace io2357911 {

/**
 * @brief check if matrix contains an item 
 * @param matrix to search in
 * @param item to search
 * @return true if matrix contains item
 *
 * matrix must be sorted in rows and columns
 * TODO: add sort check
 *
 * https://tproger.ru/problems/algorithm-to-search-an-element-in-a-sorted-array/
 */
template <typename T>
bool sorted_find(const matrix<T> &matrix, T item) {
    
    int rows = matrix.rows(); 
    int cols = matrix.columns(); 

    int row = 0; 
    int col = cols - 1; 

    while (row < rows && col >= 0) {
        auto value = matrix[row][col];
        if (value == item) {
            return true;
        } else if (value < item) {
            row++;
        } else {
            col--;
        }
    } 

    return false;
}

} // namespace io2357911

#endif // FIND_H
