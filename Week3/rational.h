//
// Created by osboxes on 12/16/18.
//

#ifndef LIVECODING2_RATIONAL_H
#define LIVECODING2_RATIONAL_H

using namespace std;

template <typename T>
class rational {
public:
    rational(T num, T den ): num(num), den(den) {
        if(den==T{}){
            throw std::invalid_argument("denominator should not be zero");
        }
    }
    rational(T num): num(num), den(1){
    }
    rational(): num(0), den(1){   // initalization of zero
    }

    T get_num() const;
    T get_den() const {
        return den;
    };
    T GCD(T a, T b){
        if(a == T{0}) {
            return b;
        }else if (b == T{0}) {
            return a;
        }
        return a < b ? GCD(a, b % a) : GCD(b, a % b);
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
    return a.get_num()*b.get_den()<=a.get_den()*b.get_num();
}

template <typename T>
bool operator>=(const rational<T> & a, const rational<T> & b ){
    return a.get_num()*b.get_den()>=a.get_den()*b.get_num();
}

template <typename T>
bool operator!=(const rational<T> & a, const rational<T> & b ){
    return a.get_num()*b.get_den()!=a.get_den()*b.get_num();
}

template <typename T>
rational<T> operator+(rational<T> & a, rational<T> & b){
    return {b.get_num() * a.get_den() + a.get_num() * b.get_den(),b.get_den() * a.get_den()};
}

rational operator-(rational & a, rational & b);
rational operator*(rational & a, rational & b);
rational operator/(rational & a, rational & b);
ostream& operator<<( ostream& os, const rational& a );
#endif //LIVECODING2_RATIONAL_H
