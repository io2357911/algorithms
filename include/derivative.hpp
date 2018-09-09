#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <string>
#include <list>
#include <regex>

namespace io2357911 {

class term {
public:
    int factor = 0;
    int power = 0;

    static term parse(const std::string &string) {
        term term;

        std::smatch match;
		std::regex re;
        
        // parse factor

TODO: // fix "-" parsing

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

        } else if (string.find("x") != std::string::npos) {
            term.factor = 1; 
        }
        
        // parse power

		re = std::regex(".*\\^([0-9]+)");
		if(std::regex_search(string, match, re) && match.size() > 1) {
            term.power = std::stoi(match[1]); 
        }

        return term;
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
        std::string res;

TODO: // implement correct formating

        if (!factor) return "0";
        if (factor >= 0) res += "+";
        else if (factor < 0) res += "-";
        //if (std::abs(factor) != 1) res += std::to_string(factor);
        res += std::to_string(factor);

        if (power > 1) res += "*x^" + std::to_string(power);
        else if (power == 1) res += "*x";

        return res;
    }

    friend std::ostream &operator<<(std::ostream &os, const term &term) {
        os << (std::string)term;
        return os;
    }
};

class term_iterator {
public:
    term_iterator(const std::string &polynomial) :
        _polynomial(polynomial)
    {}

    bool next() {
        if (_pos == std::string::npos) return false;

        std::list<std::string> signs = {"+", "-"};
        for (auto sign : signs) {
            size_t pos = _polynomial.find(sign, _pos+1);
            if (pos == std::string::npos) { 
                pos = _polynomial.size();
            }

            if (pos - _pos > 0) {
                _term = term::parse(_polynomial.substr(_pos, pos - _pos));
                _pos = pos;
                return true;
            }
        }

        return false;
    }

    term operator*() const {
        return _term;
    }


private: 
    const std::string &_polynomial;
    term _term;
    size_t _pos = 0;
};

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
        std::stringstream stream;
        for (auto term : *this) {
            stream << term << " ";
        }
        return stream.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const polynomial &polynomial) {
        os << (std::string)polynomial;
        return os;
    }

};

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

polynomial derivative(const polynomial &poly) {
    polynomial newPoly;
    for (auto term : poly) {
        newPoly.insert(derivative(term));
    }

TODO: // implement correct constants handling

    return newPoly;
}

std::string derivative(std::string polynomial) {
    return derivative(io2357911::polynomial::parse(polynomial));
}

} // namespace io2357911

#endif // DERIVATIVE_H
