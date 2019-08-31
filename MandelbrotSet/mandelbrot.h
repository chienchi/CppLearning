//
// Created by osboxes on 8/30/19.
//

#ifndef LIVECODING_MANDELBROT_H
#define LIVECODING_MANDELBROT_H

#endif //LIVECODING_MANDELBROT_H
#include <complex>

class mandel_pixel
{
public:
    mandel_pixel(SDL_Surface* screen, int x, int y, int xdim, int ydim, int max_iter)
            : screen(screen), max_iter(max_iter), iter(0), c(x, y)
    {
        // scale y to [-1.2,1.2] and shift -0.5+0i to the center
        c*= 2.4f / static_cast<float>(ydim);
        c-= complex<float>(1.2 * xdim / ydim + 0.5, 1.2);
        iterate();
    }

    int iterations() const { return iter; }
    uint32_t color() const
    {
        if (iter == max_iter) return SDL_MapRGB(screen->format, 0, 0, 0);
        const int ci= 512 * iter / max_iter; // incremental value for color
        // return SDL_MapRGB(screen->format, 40*iter & 255, 66*iter & 255, 100*iter & 255);
        return iter < max_iter/2 ? SDL_MapRGB(screen->format, ci, 0, 0)
                                 : SDL_MapRGB(screen->format, 255, ci-255, ci-255);
    }

private:
    void iterate()
    {
        complex<float> z= c;
        for (; iter < max_iter && norm(z) <= 4.0f; iter++)
            z= z * z + c;
    };

    SDL_Surface* screen;
    const int max_iter;
    int iter;
    complex<float> c;
};
