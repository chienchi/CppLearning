//
// Created by osboxes on 1/3/19.
//

#include <iostream>
#include <catch.hpp>
#include "polynomial.h"
#include "rational.h"


int power(int x , int n){
    int i = 1;
    for (int j=1; j <=n; j++){
        i *= x;
    }
    return i;
}

template <typename T>
int polynomial<T>::evaluate(int x){
    int Total = 0;
    for (int i = 0; i < this->get_deg(); i++)
    {
        Total += (this->get_coff(i) * power(x, i));
    }
    return Total;
}

polynomial<int> operator+(const polynomial<int> & a, const polynomial<int> & b){
    std::vector <int> sum;

    for(int i=0; i< max(a.get_deg(),b.get_deg()); ++i){
        sum.push_back(a.get_coff(i) + b.get_coff(i));
    }
    return sum;
    /*int max = (a.get_deg() > b.get_deg()) ? a.get_deg() : b.get_deg();
    std::vector<int> sum(max);
    std::vector<int> c1=a.get_coff(), c2=b.get_coff();
    */

    /*
    for (int i = 0; i < a.get_deg(); ++i){
        // n^2 memory access
       // sum[i] = a.get_coff()[i];
        sum[i] = c1[i];
    }
    // extra loop?
    for (int i = 0; i < b.get_deg(); ++i){
        sum[i] += c2[i];
    }*/
    //return sum;
}
polynomial operator-(const polynomial & a, const polynomial & b){
    std::vector<int> sub;

    for (int i = 0; i < max(a.get_deg(),b.get_deg()); ++i) {
        sub.push_back(a.get_coff(i) - b.get_coff(i));
    }
        //while( sub[sub.size()-1] == 0 ){
        //    sub.pop_back();
        //}
    return sub;
}
polynomial operator*(const polynomial & a, const polynomial & b){
    std::vector<int> mul(a.get_deg() + b.get_deg());

    for (int i = 0; i < a.get_deg(); ++i){
        for (int j = 0; j < b.get_deg(); ++j){
            mul[i + j] += a.get_coff(i) * b.get_coff(j);
        }
    }
    return mul;
}
polynomial operator/(const polynomial & a, const polynomial & b){
    int max = a.get_deg() + b.get_deg();
    std::vector<int> div(max);
    // No Idea???
    return div;

}
bool operator==(const polynomial & a, const polynomial &b){
    if (a.get_deg() != b.get_deg()){
        return false;
    }
    for (int i = 0; i < a.get_deg(); ++i){
        if (a.get_coff(i) != b.get_coff(i)){
            return false;
        }
    }
    return true;
}

bool operator!=(const polynomial & a, const polynomial &b){
   /* for (int i = 0; i < a.get_deg(); ++i){
        if (a.get_coff()[i] != b.get_coff()[i]){
            return true;
        }
    }*/
    return ! (a==b);
}

// Can we compare two polynomial?
// Doesn't apply to polynomial
// throw out error or prevent it in programming. enforce the rule
bool operator>(const polynomial & a, const polynomial &b){

}

bool operator<(const polynomial & a, const polynomial &b){

}

ostream& operator<<( ostream& os, const polynomial &a ){
    for (int i = 0; i < a.get_deg(); ++i){
        os << a.get_coff(i);
        if ( i!=0 ){
            os << "x^" << i ;
        }
        if (i != (a.get_deg() - 1)){
            os << " + " ;
        }
    }
    return os;
}