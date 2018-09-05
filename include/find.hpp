#ifndef FIND_H
#define FIND_H

#include "matrix.hpp"
#include <list>

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

class area;
using areas = std::list<area>;

class area {
public:
    enum Type {
        None,
        LeftUp,
        RightUp,
        LeftDown,
        RightDown,
    };
    enum Contains {
        Yes,
        Maybe,
        No
    };
    
    Type type = None;
    size_t width = 0;
    size_t height = 0;
    size_t row = 0;
    size_t col = 0;

    area(Type type = None, size_t width = 0, size_t height = 0, 
        size_t row = 0, size_t col = 0) :
        type(type), width(width), height(height), row(row), col(col)
    {}

    areas split() const {
        if (height < 2 || width < 2) {
            return {*this};
        } 

        size_t widthLeft = width / 2;
        size_t widthRight = width - widthLeft;
        size_t heightUp = height / 2;
        size_t heightDown = height - heightUp;

        return {
            area(LeftUp, widthLeft, heightUp,
                row, col),
            area(RightDown, widthRight, heightDown, 
                row + heightUp, col + widthLeft),
            area(LeftDown, widthLeft, heightDown,
                row + heightUp, col),
            area(RightUp, widthRight, heightUp,
                row, col + widthLeft),
        };
    }

    template <typename T>
    Contains contains(const matrix<T> &matrix, T item) const {
        bool isPrimitive = height < 2 || width < 2;
        if (isPrimitive) {
            // use simple search in one dimension array (binary for example)
            return find(matrix, item) ? Yes : No;    
        }
        
        if (item < min(matrix)) return No;
        if (item > max(matrix)) return No;
        return Maybe;
/*
 *        switch (type) {
 *        case LeftUp: {
 *            T max = this->max(matrix);
 *            if (item > max) {
 *                return No;
 *            } else if (item == max) {
 *                return Yes;
 *            } else {
 *                return Maybe;
 *            }
 *        }
 *        case RightDown: {
 *            T min = this->min(matrix);
 *            if (item < min) {
 *                return No;
 *            } else if (item == min) {
 *                return Yes;
 *            } else {
 *                return Maybe;
 *            }
 *        }      
 *        case LeftDown:
 *        case RightUp:
 *            return Maybe;
 *
 *        default:
 *            return No;
 *        }
 */

    }

    template <typename T>
    bool find(const matrix<T> &matrix, T item) const {
TODO: // replace with binary search
        for (size_t r = row; r < row + height; r++) {
            for (size_t c = col; c < col + width; c++) {
                if (matrix[r][c] == item) return true;
            }
        }
        return false;
    }

    template <typename T>
    T min(const matrix<T> &matrix) const {
        return matrix[row][col]; 
    }

    template <typename T>
    T max(const matrix<T> &matrix) const {
        return matrix[row + height - 1][col + width - 1]; 
    }
};

/**
 * @brief check if matrix contains an item 
 * @param matrix to search in
 * @param item to search
 * @return true if matrix contains item
 *
 * matrix is splited to multiple areas. Areas analyzed separatly lately.
 *
 * matrix must be sorted in rows and columns
 * TODO: add sort check
 *
 * https://tproger.ru/problems/algorithm-to-search-an-element-in-a-sorted-array/
 */
template <typename T>
bool binary_sorted_find(const matrix<T> &matrix, T item) {

    areas areas = {
        area(area::None, matrix.columns(), matrix.rows())
    };
    while (!areas.empty()) {

        auto area = areas.front();
        areas.pop_front(); 

        auto subareas = area.split();
        for (auto &subarea : subareas) {

            auto contains = subarea.contains(matrix, item);
            if (contains == io2357911::area::Yes) {
                return true;

            } else if (contains == io2357911::area::Maybe) {
                areas.push_back(subarea);
            }
        }
    }

    return false;
}

} // namespace io2357911

#endif // FIND_H
