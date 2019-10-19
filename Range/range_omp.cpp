//
// Created by osboxes on 10/18/19.
//


#include <cmath>
#include <iostream>
#include <omp.h>
#include "range_omp.h"

auto
odd_range(int i) {
    return range(i) | [](int x) { return 2 * x + 1; };
}

// Print even No.
auto
even_range(int i) {
    return range(i) | [](int x) { return 2 * x; };
}

// Print even No.
auto
square_range(int i) {
    return range(i) | [](int x) { return x * x; };
}

// a normal function
auto
cube(int i) {
    return i * i * i;
}

auto
cubic_range(int i) {
    return range(i) | cube;
}

template<typename F>
struct for_each {
public:
    for_each(F fun)
            : fun(fun) {}

    template<typename R>
    auto operator()(R range) {
        for (auto i : range) {
            fun(i);
        }
    }

private:
    F fun;
};

template<typename L, typename F>
auto
operator|(L lhs, for_each<F> fun) {
    fun(lhs);
}

void
test(int);

int
main() {
    auto println = for_each([](auto i) { std::cout << i << " "; });
    // Our 'range' is lazy, it does not compute anything unless
    // it is absolutely necessary. This line does not generate
    // any elements in the range. It does not even generate any
    // code when optimization is on.
    auto r = range(5);

    // elements of r are computed on demand as it is iterated
    // in the for loop.
    r | println;
    std::cout << std::endl;

    // Exercise 1: create an even range such that
    // even_range(5) => {0, 2, 4, 6, 8}
    auto even = even_range(5);
    even | println;
    std::cout << std::endl;

    // Exercise 2: create an odd range such that
    // odd_range(5)  => {1, 3, 5, 7, 9}
    auto odd = odd_range(5);
    odd | println;
    std::cout << std::endl;

    // Exercise 3: create a squared range such that
    // squard_range(5) => {0, 1, 4, 9, 16}
    auto square = square_range(5);
    square | println;
    std::cout << std::endl;

    // Exercise 4: create a cubic range such that
    // cubic_range(5) => {0, 1, 8, 27, 64}
    auto cubic = cubic_range(5);
    cubic | println;
    std::cout << std::endl;

    // Question: what's wrong with the picture?
    // Answer 1: we repeated the print a lot. can we make it go away?
    // Answer 2: we copy&paste "auto some_range = some_range(n)" a lot.
    // Answer 3: what does it take to have a cubic of even_range?
    // i,e, auto even_cubes = ???????;

    // auto even_cubes = range(5) | (even_fun | cube_fun);
    // auto even_cubic = cubic(even),
    // Q: how can we define a function h = f(g(.)), such that we can
    // call h like h(5)
    // Q: how to make it looks and acts like a function?
    // Real question: What is the type of even_cubes?
    auto even_cubes =
            transform(transform(range(5), [](int x) { return 2 * x; }), cube);
    even_cubes | println;
    std::cout << std::endl;

    // auto even_cubes2 = range(5) | even_fun | cube_fun;
    // Hint 1: Do you want to sovle the problem of
    //    range(5) | even_fun
    // or
    //    even_fun | cube_fun
    auto even2 = range(5) | [](int x) { return 2 * x; };
    even2 | println;
    std::cout << std::endl;

    // auto even_cube = ? | ? | ?;
    auto even_cube =
            range(5) | [](int x) { return 2 * x; } | [](int x) { return x * x * x; };
    even_cube | println;
    std::cout << std::endl;

    auto even_cube2 = range(5) | [](int x) { return 2 * x; } | [](int x) {
        return x * x * x;
    } | [](int x) { return 2 * x; };
    even_cube2 | println;
    std::cout << std::endl;

    // Exercise 1. Refactor previous implementation of
    // even_range, odd_range, square_range etc. to use
    // operartor|

    // Exercise 2. Function composition, implement
    // something like:
    //   auto twice = ???
    //   auto plus_one = ???
    //   auto even_range = range | twice
    //   auto odd_range = range | twice | plus_one
    //   auto twice_plus_one = twice | plus_one
    //   auto odd_range2 = range | twice_plus_one
    // where twice_plus_one is the composition of twice
    // and plus_one.
    auto twice = [](int x) { return 2 * x; };
    auto plus_one = [](int x) { return x + 1; };

    range(10) | twice | println;
    std::cout << std::endl;

    range(10) | twice | plus_one | println;
    std::cout << std::endl;

    auto cf = CompFun(twice, plus_one);
    range(10) | cf | println;
    std::cout << std::endl;

    auto cf2 = twice | plus_one;
    range(20) | cf2 | println;
    std::cout << std::endl;

    range(10) | for_each([](auto i) { std::cout << i << " "; });
    std::cout << std::endl;

    // Exercise 3. Implement an "action" called println
    // that prints the elements of the range such that
    //   auto println = ???
    //   range | println
    // has the same effect of:
    //   for (auto i : range) {
    //     std::cout << i << " ";
    //   }
    //   std::cout << std::endl;

    // Exercise 4. Clean up all the test code with the
    // println action.

    // Exercise 5. Generalize println to another action for_each
    // i.e.
    //    range | for_each([](auto i) {
    //          std::cout << i << " ";
    //    });
    // has similiar effect of
    //    range | println

    // Exercise 6. Parallelize actions with OpenMP.
    // Note 1. The Compiler Explorer engine does not allow
    // multiple-threaded execution, you will need a real
    // computer for this exercise.
    // Note 2. Run your test cases in some larger computer in
    // addition to your laptop. What do you see?

    std::cout << omp_get_max_threads() << std::endl;
#pragma omp parallel for default(none) shared(std::cout)
    for (auto i : range(15)) {
        std::cout << i << " " << std::endl;
    }

#pragma omp parallel for default(none) shared(std::cout)
    for (auto i : even_range(15)) {
        std::cout << i << " " << std::endl;
    }

    //6.3 even_range(13) | for_each

    // Exercise 7. Implement the reduce() action that reduce/sum
    // the elements in the range.

    // Exercise 8 (Advanced/optional). Parallelize the reduce()
    // action with OpenMP.

    // Exercise 9 (Pretty advanced, not required). Parallelized actions using CUDA
}