//
// Created by osboxes on 8/30/19.
//

#include <iostream>


int main (int argc, char* argv[])
{
    const int max_iter= 30;
    int xdim= 1200, ydim= 800;

    if (argc >= 3)
        xdim= atoi(argv[1]), ydim= atoi(argv[2]);

    std::cout<< "hi" << std::endl;
}