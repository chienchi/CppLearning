//
// Created by osboxes on 4/8/19.
//

#include <iostream>
#include <catch.hpp>
#include "xrange.h"

using namespace std;

TEST_CASE("Range") {
    SECTION("Construction") {
        for(long l : Xrange(100,10,-2)) {
            std::cout << l << ' '; // 0 1 2 3 4 5
        }
        std::cout << '\n';
    }
 //   SECTION("Test input one number") {

  //  }

    SECTION("Test square_range") {
        for (long l : square_range(5)){
            std::cout << l << ' ';
        }
        std::cout << '\n';
        // 0 1 4 9 16
    }
    SECTION("Test odd_range") {
        for (long l : odd_range(0,10)){
            std::cout << l << ' ';
        }
        std::cout << '\n';
        // 1,3,5,7,9
    }
    SECTION("Test even range") {
        for (long l : even_range(0,10)){
            std::cout << l << ' ';
        }
        std::cout << '\n';
        // 0 2 4 6 8
    }

}