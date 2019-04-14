//
// Created by osboxes on 2/18/19.
//

#ifndef LIVECODING2_POLYNOMIAL_H
#define LIVECODING2_POLYNOMIAL_H
#include <cassert>
#include "rational.h"

using namespace std;

template <typename T>
class polynomial {
// constructor giving the degree of the polynomial
// A dynamic array/vectro/list of double to store the coefficiengs
// a Destructor
// a output function of ostreqm
public:
    polynomial(const vector<T> &coeffs){
        if (coeffs.empty()){
            throw std::invalid_argument("coefficient need at least one ono zero int");
        }
        Pcoeffs = coeffs;
        simplify();
    }

    // delegate constructor
    // (1)  initialized with one element of default value
    // {1}  initialized with one element and the value is 1
    polynomial(): polynomial(std::vector<T>(1)){}   // initalization of zero

    polynomial(std::initializer_list<T> l): Pcoeffs{l}{};

    int get_deg() const{
        return Pcoeffs.size();
    }
    const T get_coeff(int i) const{
        assert( i >= 0 );
        if (i >= Pcoeffs.size()){
            return 0;
        }else{
            return Pcoeffs[i];
        }
    }

    void simplify() {
        while( Pcoeffs.back() == T() ){
            Pcoeffs.pop_back();
        }
    }

    int power(int x , int n){
        if (n != 0)
            return (x*power(x, n-1));
        else
            return 1;;
    }

    // change to operator ()
    template<typename T2>
    T2 evaluate(T2 x){
        T2 Total= 0 ;
        for (int i = this->get_deg(); i >= 0  ; --i)
        {
           // Total += (this->get_coeff(i) * power(x, i));
            // Horner's method
            //ex: 1 + 2x + 3x^2 = 1 + x(2+3x)
           Total = Total*x + this->get_coeff(i);
        }
        return Total;
    }

private:
    std::vector<T> Pcoeffs;
};


template <typename T>
polynomial<T> operator+(const polynomial<T> & a, const polynomial<T> & b){
    std::vector <T> sum;

    for(int i=0; i< max(a.get_deg(),b.get_deg()); ++i){
        sum.push_back(a.get_coeff(i) + b.get_coeff(i));
    }
    return sum;
}

template <typename T>
polynomial<T> operator-(const polynomial<T> & a, const polynomial<T> & b){
    std::vector<T> sub;

    for (int i = 0; i < max(a.get_deg(),b.get_deg()); ++i) {
        sub.push_back(a.get_coeff(i) - b.get_coeff(i));
    }
    return sub;
}

template <typename T>
polynomial<T> operator*(const polynomial<T> & a, const polynomial<T> & b){
    std::vector<T> mul(a.get_deg() + b.get_deg());

    for (int i = 0; i < a.get_deg(); ++i){
        for (int j = 0; j < b.get_deg(); ++j){
            mul[i + j] = mul[i + j] + (a.get_coeff(i) * b.get_coeff(j));
        }
    }
    return mul;
}

template <typename T>
//polynomial<T> operator/(const polynomial<T> & a, const polynomial<T> & b){
// cannot convert rational<polynomial<rational<int>>>  to polynomial<rational<int>>
rational<polynomial<T>> operator/(const polynomial<T> & a, const polynomial<T> & b){
    //rational<polynomial<rational<int>>> rational;
    return  rational{a,b};
}

template <typename T>
bool operator>(const polynomial<T> & a, const polynomial<T> & b);

template <typename T>
bool operator<(const polynomial<T> & a, const polynomial<T> & b);

template <typename T>
bool operator==(const polynomial<T> & a, const polynomial<T> &b){
    if (a.get_deg() != b.get_deg()){
        return false;
    }
    for (int i = 0; i < a.get_deg(); ++i){
        if (a.get_coeff(i) != b.get_coeff(i)){
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const polynomial<T> & a, const polynomial<T> &b){
    return ! (a==b);
}

template <typename T>
ostream& operator<<(ostream& os, const polynomial<T> & a){
    for (int i = 0; i < a.get_deg(); ++i){
        os << a.get_coeff(i);
        if ( i!=0 ){
            os << "x^" << i ;
        }
        if (i != (a.get_deg() - 1)){
            os << " + " ;
        }
    }
    return os;
}




#endif //LIVECODING2_POLYNOMIAL_H
