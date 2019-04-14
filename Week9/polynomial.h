//
// Created by osboxes on 2/18/19.
//

#ifndef LIVECODING2_POLYNOMIAL_H
#define LIVECODING2_POLYNOMIAL_H
#include <cassert>
#include <map>
#include "rational.h"

using namespace std;

// default type int
template <typename T=int>
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
        for (int i=0; i< coeffs.size(); ++i){
            // need to skip when coeffs is zero
            if (coeffs[i] !=  T())
                pMap.insert({i,coeffs[i]});
                // pMap[i]=coeffs[i];
        }
    }

    // no need ref &pairs, no need const,  compiled time generation
    polynomial(std::initializer_list<std::pair<int,T>> pairs){
        for (auto i : pairs) {
            if (pMap.find(i.first) != pMap.end()){
                throw std::invalid_argument("duplicate degree");
            }
            pMap[i.first]=i.second;
            // or use
            //pMap.insert(i);
        }
    };

    // delegate constructor
    // (1)  initialized with one element of default value
    // {1}  initialized with one element and the value is 1
    polynomial(): polynomial(std::vector<T>(1)){}   // initalization of zero

    polynomial(std::initializer_list<T> lst){
        for (int i=0; i< lst.size(); ++i){
            // skip coeff == zero
            if (lst.begin()[i] !=  T())
                pMap.insert({i,lst.begin()[i]});
        }

    };

    polynomial(std::map<int,T> map){
            for (auto const& [key,value] : map){
                if (pMap.find(key) != pMap.end()){
                    throw std::invalid_argument("duplicate degree");
                }
                if (value != T()) {
                    pMap[key] = value;
                }
            }
    }


    int get_deg() const{
        return pMap.rbegin()->first;
    }
    const T get_coeff(int i) const{
        if (pMap.find(i) == pMap.end()){
            return 0;
        }else{
            return pMap.find(i)->second;
        }
    }

    const std::map<int,T> get_all_coeff() const{
        return pMap;
    }

// No need simplify with std::map
    void simplify() {
        while( pMap.rbegin()->second == T()){
            pMap.erase(pMap.rbegin()->first);
        }
    }

    // change to operator ()
    template<typename T2>
    T2 operator()(T2 x){
        T2 Total = 0 ;
       // for (auto const& [key,value] : this)){
        //    Total = Total*x + value;
        //}
        for (int i = this->get_deg(); i >= 0  ; --i)
        {
           // Total += (this->get_coeff(i) * power(x, i));
            // Horner's method
            //ex: 1 + 2x + 3x^2 = 1 + x(2+3x)

           Total = Total*x + this->get_coeff(i);
            //cout << Total*x << " " << i << endl;
        }
        return Total;
    }

private:
    std::map<int, T> pMap;
};


template <typename T>
polynomial<T> operator+(const polynomial<T> & a, const polynomial<T> & b){
    // hint merge sort
    std::map <int,T> sum = a.get_all_coeff();
    for (auto const& [key,value] : b.get_all_coeff()){
        // do we need find ???
      //  if (sum.find(key) == sum.end()){
       //     sum[key] = value;
       // }else{
            sum[key] = sum[key] + value;
        //}
    }
    return sum;
}

template <typename T>
polynomial<T> operator-(const polynomial<T> & a, const polynomial<T> & b){
    std::map <int,T> sub = b.get_all_coeff();
    for (auto const& [key,value] : a.get_all_coeff()){
        if (sub.find(key) == sub.end()){
            sub[key] = value;
        }else{
            if (value - sub[key] == T()){
                sub.erase(key);
            }else {
                sub[key] = value - sub[key];
            }
        }
    }
    return sub;
}

template <typename T>
polynomial<T> operator*(const polynomial<T> & a, const polynomial<T> & b){
    std::map <int,T> mul;
    // hidden insertion.
    for (auto const& [key_a,value_a] : a.get_all_coeff()){
        for (auto const& [key_b,value_b] : b.get_all_coeff()){
            mul[key_a + key_b] = mul[key_a + key_b] + (value_a * value_b);
        }
    }
    /*
    for (int i = 0; i <= a.get_deg(); ++i){
        for (int j = 0; j <= b.get_deg(); ++j){
            mul[i + j] = mul[i + j] + (a.get_coeff(i) * b.get_coeff(j));
        }
    }*/
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
    return a.get_all_coeff() == b.get_all_coeff();
}

template <typename T>
bool operator!=(const polynomial<T> & a, const polynomial<T> &b){
    return ! (a==b);
}

template <typename T>
ostream& operator<<(ostream& os, const polynomial<T> & a){
    for (auto [key,value] : a.get_all_coeff()){
        os << value;
        if ( key != 0){
            os << "x^" << key ;
        }
        if ( key != a.get_deg()){
            os << " + " ;
        }
    }
    return os;
}




#endif //LIVECODING2_POLYNOMIAL_H
