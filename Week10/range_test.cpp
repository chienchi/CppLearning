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
    SECTION("Test function"){
        Xrange(5).begin();

        Xrange(5).end();
    }
}