//
// Created by chienchi on 12/14/18.
//

#include <iostream>
#include <catch.hpp>
#include "rational.h"

int rational::get_num() const {
    return num;
};

bool operator==(const rational & a, const rational & b ) {
    return a.get_num()*b.get_den()==a.get_den()*b.get_num();
}
bool operator<(const rational & a, const rational & b ){
    return a.get_num()*b.get_den()<a.get_den()*b.get_num();
}
bool operator>(const rational & a, const rational & b ){
    return a.get_num()*b.get_den()>a.get_den()*b.get_num();
}
bool operator<=(const rational & a, const rational & b ){
    return a.get_num()*b.get_den()<=a.get_den()*b.get_num();
}
bool operator>=(const rational & a, const rational & b ){
    return a.get_num()*b.get_den()>=a.get_den()*b.get_num();
}
bool operator!=(const rational & a, const rational & b ){
    return a.get_num()*b.get_den()!=a.get_den()*b.get_num();
}
rational operator+(rational & a, rational & b){
    return {b.get_num() * a.get_den() + a.get_num() * b.get_den(),b.get_den() * a.get_den()};
}
rational operator-(rational & a, rational & b){
    return {a.get_num() * b.get_den() - b.get_num() * a.get_den(),b.get_den() * a.get_den()};
}
rational operator*(rational & a, rational & b){
    return {b.get_num() * a.get_num(), b.get_den() * a.get_den()};
}
rational operator/(rational & a, rational & b){
    return {a.get_num() * b.get_den(), a.get_den()*b.get_num()};
}
ostream& operator<<( ostream& os, const rational& a ){
    os << a.get_num() << "/" << a.get_den();
}