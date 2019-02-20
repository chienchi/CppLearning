//
// Created by osboxes on 1/3/19.
//
#include <cassert>
#ifndef LIVECODING2_POLYNOMIAL_H
#define LIVECODING2_POLYNOMIAL_H
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
    int get_deg() const{
        return Pcoeffs.size();
    }
    int get_coff(int i) const{
        assert( i >= 0 );
        if (i >= Pcoeffs.size()){
            return 0;
        }else{
            return Pcoeffs[i];
        }
    }

    void simplify() {
        while( Pcoeffs[get_deg()-1] == 0 ){
            Pcoeffs.pop_back();
        }
    }
    int evaluate(int x);

private:
    std::vector<T> Pcoeffs;
};


template <typename T>
polynomial<T> operator+(const polynomial<T> & a, const polynomial<T> & b);

template <typename T>
polynomial<T> operator-(const polynomial<T> & a, const polynomial<T> & b);

template <typename T>
polynomial<T> operator*(const polynomial<T> & a, const polynomial<T> & b);

template <typename T>
polynomial<T> operator/(const polynomial<T> & a, const polynomial<T> & b);

template <typename T>
bool operator>(const polynomial<T> & a, const polynomial<T> & b);

template <typename T>
bool operator<(const polynomial<T> & a, const polynomial<T> & b);

template <typename T>
bool operator==(const polynomial<T> & a, const polynomial<T> &b);

template <typename T>
bool operator!=(const polynomial<T> & a, const polynomial<T> &b);

template <typename T>
ostream& operator<<(ostream& os, const polynomial<T> & p);


#endif //LIVECODING2_POLYNOMIAL_H
