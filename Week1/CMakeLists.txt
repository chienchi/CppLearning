#set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer ")
add_executable(Exp2 Exercise2.cpp ../MandelbrotSet/main.cpp ../MandelbrotSet/mandelbrot.h)