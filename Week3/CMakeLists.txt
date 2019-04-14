#add_executable(rational Rational.cpp test_main.cpp)
add_executable(polynomial polynomial.cpp polynomial_test.cpp Rational.cpp Rational_test.cpp test_main2.cpp)

# Test-Driven development
# Catch2 github.com/catchorg/Catch2
# find_package(catch)

