//
// Created by osboxes on 4/12/19.
//

#ifndef LIVECODING_XRANGE_H
#define LIVECODING_XRANGE_H

#include <functional>
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
    Xrange(): _begin(0), _end(1), _step(1){};

    Xrange_iterator begin(){
        return {_begin, _step};
    }
    Xrange_iterator end(){
        return {_end, _step};
    }

};
/*
template <typename F>
struct pipeable{
private:
    F f;
public:
    pipeable(F&& f): f(std::forward<F>(f)){}

    template<typename ...Xs>
    auto operator()(Xs&& ...xs) -> decltype(std::bind(f,std::placeholders::_1,std::forward<Xs>(xs)...)) const {
        return std::bind(f,std::placeholders::_1, std::forward<Xs>(xs)...);
    }
};

template <typename F>
pipeable<F> piped(F&& f) {return pipeable<F>{std::forward<F>(f)};}

template<typename T, typename F>
auto operator|(T&& x, const F& f) -> decltype(f(std::forward<T>(x))){
    return f(std::forward<T>(x));
}
*/

#if 0
template<typename InputIt, typename UnaryOperation>
auto transform_range(InputIt inRange,
                        UnaryOperation unary_op)
{
    // 1. change return type int some kind of Range
    std::vector<int> output;

    // 2. move computation into iterator::operator*()
    for (auto i : inRange){
        output.push_back(unary_op(i));
    }

    // 1.5 instead of return from function, construct an object
    return output;
}

#else
template <typename Range, typename Fun>
class transform_range {
public:
        transform_range(Range input_range, Fun f):range(input_range),fun(f){};

        class iterator {

        public:
            iterator(int c): cc(c){};

            bool operator!=( iterator right) {
                return cc != right.cc;
                //return right.cc > cc;
            }

            auto &operator++() {
                cc += 1;
                return *this;
            }
            auto operator*() {
                return tr->fun(cc);
            }

        private:
            int cc;
            transform_range *tr;
        };

        iterator begin(){
            return (*range.begin());
        };

        iterator end(){
            return (*range.end());
        };

private:
        Range range;
        Fun fun;
        };


#endif

// operator| ???
// Q1: input, output type?
// Q2: how many of operator|?
template<typename T, typename F>
auto operator|(T x, const F f) {
    return transform_range(x, f);
}

auto square_range(int i){
    return transform_range(Xrange(i),[](int x){
        return x * x;
    });
}

auto odd_range(int i, int j){
    return transform_range(Xrange(i/2,j/2),[](int x){
        return x * 2 + 1;
    });
}

auto even_range(int i, int j){
    return transform_range(Xrange(i/2,j/2),[](int x){
        return x * 2 ;
    });
}







#endif //LIVECODING_XRANGE_H

