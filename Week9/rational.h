//
// Created by osboxes on 12/16/18.
//


#ifndef LIVECODING2_RATIONAL_H
#define LIVECODING2_RATIONAL_H
//#include "polynomial.h"
#include <algorithm>

using namespace std;

template <typename T>
class rational {
public:
    rational(T n, T d) : num(n) , den(d) {
        if (den == T{}) {
            throw std::invalid_argument("denominator should not be zero");
        }
        reduce();
    }

    // need T(num)?
    // delegating contructor
    rational(T num) : rational(num, 1) {
    }

    rational() : rational(0, 1) {   // initalization of zero
    }

    void reduce(){
        if constexpr (std::is_integral_v<T>){
            int gcd = __gcd(num, den);
            num = num / gcd;
            den = den / gcd;
        }
    }

    T get_num() const {
        return num;
    }
    T get_den() const {
        return den;
    }

    // Type conversion out
    operator float() const{
        return float(num)/float(den);
    }

    rational inverse() const{
        if (num == T()) throw std::invalid_argument("Cannot inverse Zero");
        else{
            return {den, num};
        }
    }

private:

    T num;
    T den;
};

template <typename T>
bool operator==(const rational<T> & a, const rational<T> & b ){
    return a.get_num()*b.get_den()==a.get_den()*b.get_num();
}
template <typename T>
bool operator<(const rational<T> & a, const rational<T> & b ){
    return a.get_num()*b.get_den()<a.get_den()*b.get_num();
}

template <typename T>
bool operator>(const rational<T> & a, const rational<T> & b ){
    return a.get_num()*b.get_den()>a.get_den()*b.get_num();
}

template <typename T>
bool operator<=(const rational<T> & a, const rational<T> & b ){
    // 1/3    1/-2
    // how to enforce
    return a.get_num()*b.get_den()<=a.get_den()*b.get_num();
}

template <typename T>
bool operator>=(const rational<T> & a, const rational<T> & b ){
    return a.get_num()*b.get_den()>=a.get_den()*b.get_num();
}

template <typename T>
bool operator!=(const rational<T> & a, const rational<T> & b ){
    return !(a==b);
}

template <typename T>
rational<T> operator+(const rational<T> & a, const rational<T> & b){
    return {b.get_num() * a.get_den() + a.get_num() * b.get_den(),b.get_den() * a.get_den()};
}

template <typename T>
rational<T> operator-(const rational<T> & a, const rational<T> & b){
    return {a.get_num() * b.get_den() - b.get_num() * a.get_den(),b.get_den() * a.get_den()};
}

template <typename T>
rational<T> operator*(const rational<T> & a, const rational<T> & b){
    return {b.get_num() * a.get_num(), b.get_den() * a.get_den()};
}

template <typename T>
rational<T> operator/(const rational<T> & a, const rational<T> & b){
    return {a.get_num() * b.get_den(), a.get_den()*b.get_num()};
}

template <typename T>
ostream& operator<<( ostream& os, const rational<T> & a ){
    if (a.get_num() == a.get_den()){
        os << '1';
    }else{
        os << a.get_num() << "/" << a.get_den();
    }
}

//rational(polynomial) polynomial<rational<int>> operator/(const polynomial<rational<int>> & a, const polynomial<rational<int>> & b);

#endif //LIVECODING2_RATIONAL_H