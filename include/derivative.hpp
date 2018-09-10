#ifndef DERIVATIVE_H
#define DERIVATIVE_H

/**
 * solution for polynomial derivative task
 * https://stepik.org/lesson/11831/step/10?unit=2979 
 */

#include <string>
#include <list>
#include <regex>
#include <set>

namespace io2357911 {

/**
 * @brief term class which is a member of polynomial
 */
class term {
public:
    int factor = 0;
    int power = 0;

    static term parse(const std::string &string) {
        term term;

        std::smatch match;
        std::regex re;

        bool hasX = string.find("x") != std::string::npos;

        // parse factor

        re = std::regex("^([0-9\\+\\-]+).*");
        if(std::regex_search(string, match, re) && match.size() > 1) {
            std::string value = match[1];
            if (value == "+") {
                term.factor = 1;
            } else if (value == "-") {
                term.factor = -1;
            } else {
                term.factor = std::stoi(match[1]); 
            }

        } else if (hasX) {
            term.factor = 1; 
        }

        // parse power

        re = std::regex(".*\\^([0-9]+)");
        if(std::regex_search(string, match, re) && match.size() > 1) {
            term.power = std::stoi(match[1]); 

        } else if (hasX) {
            term.power = 1; 
        }

        return term;
    }

    bool isValid() const {
        return factor;
    }
    
    term operator+(const term &other) const {
        term newTerm;
        if (power != other.power) return newTerm;

        newTerm.factor = factor + other.factor;
        newTerm.power = power;

        return newTerm;
    }

    bool operator<(const term &other) const {
        if (power > other.power) return false;
        if (power == other.power && factor > other.factor) return false;
        return true;
    }

    bool operator>(const term &other) const {
        if (other.power > power) return false;
        if (other.power == power && other.factor > factor) return false;
        return true;
    }

    operator std::string() const {
        std::stringstream res;

        bool needSign = true; // +-
        bool needFactor = true; // [0-9]+
        bool needMul = true; // *
        bool needX = true; // x
        bool needP = true; // ^
        bool needPower = true; // [0-9]+

        if (!factor) {
            needMul = false;
            needX = false;
            needP = false;
            needP = false;

        } else if (std::abs(factor) == 1) {
            needFactor = false;
            needMul = false;

        } else if (factor < 0) {
            needSign = false; 
        }

        if (!power) {
            needMul = false;
            needX = false;
            needP = false;
            needPower = false;

        } else if (power == 1) {
            needP = false;
            needPower = false;
        }

        if (!needX) {
            needFactor = true;
        }
    
        if (needSign) res << (factor < 0 ? "-" : "+");
        if (needFactor) res << factor;
        if (needMul) res << "*";
        if (needX) res << "x";
        if (needP) res << "^";
        if (needPower) res << power;

        return res.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const term &term) {
        os << (std::string)term;
        return os;
    }
};

/**
 * @brief term iterator class
 *
 * iterate through string in poly terms
 */
class term_iterator {
public:
    term_iterator(const std::string &polynomial) :
        _polynomial(polynomial), _pos(polynomial.begin()) {
    }

    bool next() {
        if (_pos == _polynomial.end()) return false;

        auto pos = _pos + 1;

        while (pos < _polynomial.end()) {
            if (*pos == '+' || *pos == '-') {
                _term = term::parse(std::string(_pos, pos));
                _pos = pos;
                return true;
            }
            pos++;
        }

        if (pos != _pos) {
            _term = term::parse(std::string(_pos, pos));
            _pos = pos;
            return true;
        }

        return false;
    }

    term operator*() const {
        return _term;
    }

private: 
    const std::string &_polynomial;
    std::string::const_iterator _pos;
    term _term;
};

/**
 * @brief polynomial class
 */
class polynomial : public std::set<term, std::greater<term>> {
public:

    static polynomial parse(const std::string &string) {
        polynomial poly;

        term_iterator term(string);
        while (term.next()) {
            poly.insert(*term);
        }

        return poly;     
    }

    operator std::string() const {

        // create output

        std::stringstream stream;
        for (auto term : *this) {
            stream << term;
        }
        auto string = stream.str();

        // remove first char if it is sign

        bool signIsFirst = string.size() && 
            (string[0] == '+');
        if (signIsFirst) string.erase(0, 1);

        return string;
    }

    friend std::ostream &operator<<(std::ostream &os, const polynomial &polynomial) {
        os << (std::string)polynomial;
        return os;
    }

};

/**
 * @brief term derivative
 * @param term is input term
 * @return term derivatirve
 */
term derivative(const term &term) {
    auto newTerm = term;

    if (newTerm.power > 0) {
        newTerm.factor = newTerm.factor * newTerm.power;
        newTerm.power--;

    } else {
        newTerm.factor = 0;    
    }

    return newTerm;
}

/**
 * @brief polynomial normalization
 * @param poly is input polynomial
 * @return normalized polynomial
 */
polynomial normalize(const polynomial &poly) {
    polynomial newPoly;
    if (poly.empty()) return poly;

    auto term = poly.begin();
    auto newTerm = *term;
    term++;
   
    while (term != poly.end()) {
        auto sumTerm = newTerm + *term;    

        if (sumTerm.isValid()) {
            newTerm = sumTerm;

        } else if (newTerm.isValid()) {
            newPoly.insert(newTerm); 
            newTerm = *term;
        }
        
        term++;
    }

    if (newTerm.isValid()) {
        newPoly.insert(newTerm); 
    }
    
    return newPoly;
}

/**
 * @brief polynomial derivative
 * @param poly is input polynomial
 * @return polynomial derivative
 */
polynomial derivative(const polynomial &poly) {
    polynomial newPoly;
    for (auto term : poly) {
        newPoly.insert(derivative(term));
    }
    return normalize(newPoly);
}

/**
 * @brief polynomial derivative
 * @param poly is input polynomial string
 * @return polynomial derivative string
 */
std::string derivative(std::string poly) {
    return derivative(polynomial::parse(poly));
}

} // namespace io2357911

#endif // DERIVATIVE_H
