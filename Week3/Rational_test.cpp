//
// Created by osboxes on 1/22/19.
//

#include <iostream>
#include <catch.hpp>
#include "rational.h"

TEST_CASE("PolyRational") {

    SECTION("Construction") {
        SECTION("Can rational number be constructed with two integers") {
            rational rn(1, 2);
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
    SECTION("Test Operation ==") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        REQUIRE(rn1 == rn2);
    }
    SECTION("Test operator +") {
        rational rn1(3, 4), rn2(3, 4), rn3(6, 4);
        rational rn4 = rn1 + rn2;
        REQUIRE(rn3 == rn4);
    }
    SECTION("Test Operation <") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        REQUIRE(rn3 < rn2);
    }
    SECTION("Test Operation *") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        rn1 * rn2;
        REQUIRE(rn3 < rn2);
    }
    SECTION("Test Operation /") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        rational rn4 = rn1 / rn2;
        REQUIRE(rn3 < rn4);
    }
    SECTION("Test Operation -") {
        rational rn1(3, 4), rn2(3, 4), rn3(1, 2);
        rational rn4 = rn1 - rn2;
        REQUIRE(rn3 > rn4);
    }
}