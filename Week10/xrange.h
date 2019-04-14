//
// Created by osboxes on 4/12/19.
//

#ifndef LIVECODING_XRANGE_H
#define LIVECODING_XRANGE_H

#include <cassert>
// Class Xrange ,
//Constructor
// argv: int total count
//
//Functions
// 1. begin, return Xrange_iterator
// 2. end,  return Xrange_iterator
//
//Data: save total count
//
// class  Xrange_iterator
//Constructor
// argv: ???
// operator
// 1. !=
// 2. ++
// 3. *   for return value
//
//Data: current count

class Xrange_iterator{
public:
    Xrange_iterator(int c, int s): cc(c),step(s){}

    bool operator != (Xrange_iterator right){
        return step<0 ? right.cc < cc : right.cc > cc;
        // this doesn't work if step skip over the _end
        //return cc != right.cc;
    }
    Xrange_iterator &operator++(){
        cc += step;
        return *this;
    }
    int operator*(){
        return cc;
    }

private:
    int cc;
    int step;
};

class Xrange{
private:
    int _begin;
    int _end;
    int _step;

public:
    Xrange(int b,int e, int s = 1): _begin(b), _end(e),_step(s) {
       // assert(s!=0);
    }
   // Xrange(int b,int e): _begin(b), _end(e), _step(1) {}
    Xrange(int e): _begin(0), _end(e), _step(1) {
       // assert(e>0);
    }

    Xrange_iterator begin(){
        return {_begin, _step};
    }
    Xrange_iterator end(){
        return {_end, _step};
    }

};






#endif //LIVECODING_XRANGE_H

