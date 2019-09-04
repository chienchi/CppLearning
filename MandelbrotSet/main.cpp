//
// Created by osboxes on 8/30/19.
//

#include <iostream>
//#include "./mandelbrot.h"
#include "./xrange.h"

int main (int argc, char* argv[]) {
    const int max_iter = 30;
    int xdim = 75, ydim = 50;


    if (argc >= 3)
        xdim = atoi(argv[1]), ydim = atoi(argv[2]);

    //auto z_plane = range() | xform() | xform()
    //auto mendelbrot = z_plane |xform( [](){ return z*z + c; })
    //auto Juliaset = z_plane | xform([](){ return z*z + k; })

   // auto newRange = Xrange(xdim) | Xrange(ydim);
    Xrange(xdim) | Xrange(ydim) | print_mandel(max_iter);

}