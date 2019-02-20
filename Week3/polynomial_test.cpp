//
// Created by osboxes on 1/3/19.
//

#include <iostream>
#include <catch.hpp>
#include "polynomial.h"
#include "rational.h"


TEST_CASE("Polynomial") {
    SECTION("Construction giving the degree of the polynomial") {
        std::vector<int> c1{1,2,3};
        polynomial p(c1);
        std::vector<int> c2;
        SECTION("vector should not be empty") {
            REQUIRE_THROWS_AS(polynomial(c2), std::invalid_argument);
        }
    }
    SECTION("Test simplify") {
        std::vector<int> c1{1,2,0};
        std::vector<int> c2{1,2};
        REQUIRE(polynomial(c1) == polynomial(c2));
    }
    SECTION("Test Operation ==") {
        std::vector<int> c1{1,2,3,4};
        std::vector<int> c2{1,2,3,4};
        REQUIRE(polynomial(c1) == polynomial(c2));
    }
    SECTION("Test Operation !=") {
        std::vector<int> c1{1,2,3};
        std::vector<int> c2{1,2,4};
        REQUIRE(polynomial(c1) != polynomial(c2));
    }
    SECTION("Test operator +") {
        std::vector<int> c1{1,2,3};
        polynomial p1(c1);
        std::vector<int> c2{1,2,3,4};
        polynomial p2(c2);
        std::vector<int> c3{2,4,6,4};
        polynomial p3(c3);
        REQUIRE( (p1 + p2) == p3);
        REQUIRE( (p2 + p1) == p3);
    }
    SECTION("Test operator -") {
        std::vector<int> c1{1,2,3};
        polynomial p1(c1);
        polynomial p2(c1);
        std::vector<int> c2{2,4,6};
        polynomial p3(c2);
        //polynomial p4 = p3 - p2;
        REQUIRE( (p3 - p2) == p1);
    }
    SECTION("Test operator *") {
        std::vector<int> c1{1,2,3};
        polynomial p1(c1);
        polynomial p2(c1);
        std::vector<int> c2{2,4,6};
        polynomial p3(c2);
        REQUIRE( (p1 * p2) != p1);
    }
    SECTION("Test operator /") {

    }
    SECTION("Test operator >") {

    }
    SECTION("Test evaluate"){
        std::vector<int> c1{1,2,3};
        polynomial p(c1);
        REQUIRE(p.evaluate(5) == 86);
    }
    SECTION("Test Output"){
        std::vector<int> c1{1,2,3};
        polynomial p(c1);
        cout << p << endl;
    }
}