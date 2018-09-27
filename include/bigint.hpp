#ifndef BIG_INT_H
#define BIG_INT_H

#include <vector>

namespace io2357911 {

/**
 * @brief BigInt class is simple big int implementation
 *
 * currently supported operations are "+" and "*"
 *
 * TODO:
 * - fix memory usage
 * - implement "-" and "/"
 */
class BigInt {
public:
    BigInt(const int &value = 0) {
        add(value, 0); 
    }
    
    BigInt &operator=(const int &other) {
        _digits.resize(0);
        add(other, 0);
        return *this;
    }

    BigInt operator+(const int &other) const {
        BigInt res = *this;
        res.add(other, 0);
        return res;
    }
        
    BigInt operator+(const BigInt &other) const {
        BigInt res = other;
        for (size_t offset = 0; offset < _digits.size(); offset++) {
            res.add(_digits[offset], offset);
        }
        return res;
    } 

    BigInt operator*(const int &other) const {
        return *this * BigInt(other);
    }

    BigInt operator*(const BigInt &other) const {
        BigInt res;
    
        if (is_zero()) return res;
        if (other.is_zero()) return res;

        for (size_t o1 = 0; o1 < _digits.size(); o1++) {
            for (size_t o2 = 0; o2 < other._digits.size(); o2++) {
                short prod = _digits[o1] * other._digits[o2];
                size_t offset = o1+o2;
                res.add(prod, offset);
            }
        }
        return res;
    }

    bool operator==(const int &other) const {
        return *this == BigInt(other);
    }

    bool operator==(const BigInt &other) const {
        return std::equal(_digits.begin(), _digits.end(),
            other._digits.begin());
    }

    bool is_zero() const {
        return _digits.empty() || (_digits.size() == 1 && _digits[0] == 0);
    }

    operator std::string() const {
        std::stringstream res;
        for (auto i = _digits.rbegin(); i != _digits.rend(); i++) {
            res << (int)*i;
        }
        return res.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const BigInt &bigInt) {
        os << (std::string)bigInt;
        return os;
    }

protected:
    void add(int value, size_t offset) {
        while (value) {
            if (offset + 1 > _digits.size()) {
                _digits.resize(offset + 1, 0);
            }

            value += _digits[offset];
            _digits[offset] = value % 10;
            value /= 10;

            offset++;
        };
    }

private:
    std::vector<uint8_t> _digits;
};

} // namespace io2357911

#endif // BIG_INT_H
