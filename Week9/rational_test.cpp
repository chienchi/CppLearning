//
// Created by osboxes on 1/22/19.
//

#include <iostream>
#include <catch.hpp>
#include "rational.h"
#include "polynomial.h"

using namespace std;

TEST_CASE("PolyRational") {

    SECTION("Construction") {
        SECTION("Can rational number be constructed with two integers") {
            rational {1.2, 2.2};

            SECTION("denominator should not be zero") {
                REQUIRE_THROWS_AS(rational(1, 0), std::invalid_argument);
            }
        }
        SECTION("Can rational number be constructed with one integer argument") {
            rational rn(-3);
        }
        SECTION("Can rational number be constructed with one float number argument") {
            float b = 0.1;
            rational rn(b);
        }
    }
    SECTION("Test PolyRational + "){
        rational rn1(1, 2), rn2(1, 3), rn3(1, 1), rn4(2,3);
        std::vector<rational<int>> c1{rn1, rn2};
        std::vector<rational<int>> c2{rn3, rn4};
        polynomial<rational<int>> p4(c1);
        polynomial<rational<int>> p5(c2);
        polynomial p6 = p4 + p4; // 1 + 2/3x^1
        REQUIRE(p6==p5);
    }
    SECTION("Test PolyRational - "){
        rational rn1(1, 2), rn2(1, 3), rn3(1, 1), rn4(2,3);
        std::vector<rational<int>> c1{rn1, rn2};
        std::vector<rational<int>> c2{rn3, rn4};
        polynomial<rational<int>> p4(c1);
        polynomial<rational<int>> p5(c2);
        polynomial p6 = p5 - p4; // 1/2 + 1/3x^1
        REQUIRE(p6==p4);
    }
    SECTION("Test PolyRational * "){
        rational rn1(1, 2), rn2(1, 3), rn3(1, 4), rn4(1,3), rn5(1,9);
        std::vector<rational<int>> c1{rn1, rn2};
        std::vector<rational<int>> c2{rn3, rn4, rn5};
        polynomial<rational<int>> p4(c1);
        polynomial<rational<int>> p5(c2);
        polynomial p6 = p4 * p4; //  1/4 + 1/3x^1 + 1/9x^2
        REQUIRE(p6==p5);
    }
    SECTION("Test PolyRational / "){
        rational rn1(1, 2), rn2(1, 3), rn3(1, 4), rn4(1,3), rn5(1,9);
        std::vector<rational<int>> c1{rn1, rn2};
        std::vector<rational<int>> c2{rn3, rn4, rn5};
        polynomial<rational<int>> p4(c1);
        polynomial<rational<int>> p5(c2);
        polynomial p6 = p4 / p5;
    }
    SECTION("Test Rational Inverse"){
        REQUIRE(rational(1.0f, 2.0f) == rational(4.0f,2.0f).inverse());
    }
    SECTION("Test Rational Operation ==") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        REQUIRE(rn1 == rn2);
    }
    SECTION("Test Polynomial operator +") {
        rational rn1(3, 4), rn2(3, 4), rn3(6, 4);
        rational rn4 = rn1 + rn2;
        REQUIRE(rn3 == rn4);
        std::vector<int> c1{1,2,3};
        polynomial p1(c1);
        std::vector<int> c2{1,2,3,4};
        polynomial p2(c2);
        std::vector<int> c3{2,4,6,4};
        polynomial p3(c3);
        REQUIRE( (p1 + p2) == p3);
        REQUIRE( (p2 + p1) == p3);
    }
    SECTION("Test Rational Operation <") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        REQUIRE(rn3 < rn2);
    }
    SECTION("Test Rational Operation *") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        rn1 * rn2;
        REQUIRE(rn3 < rn2);
    }
    SECTION("Test Rational Operation /") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        rational rn4 = rn1 / rn2;
        REQUIRE(rn3 < rn4);
    }
    SECTION("Test Rational Operation -") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        rational rn4 = rn1 - rn2;
        REQUIRE(rn3 > rn4);
    }
    SECTION("Test polynomial int evaluate"){
        std::vector<int> c1{1,2,3};
        polynomial p1(c1);
        REQUIRE(p1.evaluate(5) == 86);
    }
    SECTION("Test polyRational evaluate"){
        rational rn1(1, 2), rn2(1, 3),rn3(2,3);
        std::vector<rational<int>> c2{rn1, rn2};
        polynomial p2(c2); // 1/2+1/3x
        REQUIRE(p2.evaluate(rn1) == rn3);
    }
}