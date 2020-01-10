//
// Created by osboxes on 8/30/19.
//

#ifndef LIVECODING_MANDELBROT_H
#define LIVECODING_MANDELBROT_H

#endif //LIVECODING_MANDELBROT_H

#include <complex>
using namespace std;

complex<float> c;
complex<float> k;

class mandel_pixel
{
public:
    mandel_pixel(int x, int y, int xdim, int ydim, int max_iter)
            : max_iter(max_iter), iter(0), c(x, y)
    {
        // scale y to [-1.2,1.2] and shift -0.5+0i to the center
        c*= 2.4f / static_cast<float>(ydim);
        c-= complex<float>(1.2 * xdim / ydim + 0.5, 1.2);
        //k = complex<float>(-0.6,0.6);
        k = complex<float>(0.353,0.288);
        //std::cout << c << " " ;
        iterate();
    }
    int iterations() const { return iter; }
    void print(){
        if ( this->iterations() == max_iter){
            std::cout << "#";
        }else{
            std::cout << " ";
        }
    }

private:
    void iterate()
    {
        complex<float> z= c;
        #pragma omp parallel for default(none) shared(z)
        for (; iter < max_iter && norm(z) <= 4.0f; iter++)
            z= z * z + c;
            //z= z * z + k;
    };
    const int max_iter;
    int iter;
    complex<float> c;
    complex<float> k;
};
