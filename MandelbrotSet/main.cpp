//
// Created by osboxes on 8/30/19.
//

#include <iostream>
//#include "./mandelbrot.h"
#include "./xrange.h"
#include <complex>

using namespace std;

int main (int argc, char* argv[]) {
    const int max_iter = 30;
    int xdim = 75, ydim = 50;

    if (argc >= 3)
        xdim = atoi(argv[1]), ydim = atoi(argv[2]);

    //auto z_plane = range() | xform() | xform()
    //auto mendelbrot = z_plane |xform( [](){ return z*z + c; })
    //auto Juliaset = z_plane | xform([](){ return z*z + k; })

   // auto newRange = Xrange(xdim) | Xrange(ydim);
     auto println = for_each([xdim](auto i) {  i.first == (xdim - 1)? std::cout<<"\n": std::cout << i.second ; });
     auto ij = rectangle({0,0},{xdim,ydim});
     auto z_plane = [&](auto i){
         complex<float> c (i.second,i.first);
         c*= 2.4f / static_cast<float>(ydim);
         c-= complex<float>(1.2 * xdim / ydim + 0.5, 1.2);
         //store x axis and complex number in pair
        // cout << c << " ";
         return std::pair<int,complex<float>> {i.second, c};;
     };

     auto mendelbrot = [&](auto c){
         complex<float> oc = c.second;
         complex<float> z = c.second;
         int iter;
         #pragma omp parallel for default(none) shared(z)
         for ( iter = 0 ; iter < max_iter && norm(z) <= 4.0f; iter++) {
             z = z * z + oc;
         }
         return iter==max_iter? std::pair<int,char> {c.first, '#'}:std::pair<int,char> {c.first,' '};
     };

    cout << "Mendelbrot" << endl;
    ij | z_plane | mendelbrot | println;

    auto Juliaset = [&](auto c){
        complex<float> z = c.second;
        //complex<float> k(0.353,0.288);
        complex<float> k (-0.6,0.6);
        int iter;
        #pragma omp parallel for default(none) shared(z)
        for ( iter = 0 ; iter < max_iter && norm(z) <= 4.0f; iter++) {
            z = z * z + k;
        }
        return iter==max_iter? std::pair<int,char> {c.first, '#'}:std::pair<int,char> {c.first,' '};
    };

    cout << "Juliaset" << endl;
    //ij| z_plane | Juliaset | println;

     auto z = for_each([=](auto i) {
        // for (auto j:i){
          // mandel_pixel m(i.second, i.first, xdim, ydim, max_iter);
        // m.print();
        // }
             if (i.second == xdim - 1){
               //  std::cout << "\n";
             }
     });

     // ij | z;
     //ij | println;
     for (auto h:ij){
        // std::cout << h.first << " " << h.second << std::endl;
        // for (auto w:h){
             //mandel_pixel m(w.second,w.first,xdim,ydim,max_iter);
             //m.print();
             //std::cout << w.first << "," << w.second << " ";
        // }
        // std::cout << std::endl;
     }
     // auto xy = ij
     //      z=xy
     //              iters=z;


 //   Xrange(xdim) | Xrange(ydim) | print_mandel(max_iter);

}