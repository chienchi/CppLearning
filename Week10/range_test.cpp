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
    SECTION("Test cubic range") {
        auto cubic = transform_range(Xrange(0,5), [](int i){
            return i * i * i;
        });
        for (auto i : cubic){
            std::cout << i << " ";
        }
        std::cout << std::endl;
        // 0 1 8 27 64
    }
    SECTION("Test pipe transform") {
        auto square = Xrange(0,5)|transform2( [](int i){return i * i; });


        for (auto i : square | transform2( [](int i){return i * i; })){
            std::cout << i << " ";
        }
        std::cout << std::endl;
        // 0 1 4 9 16
    }




}