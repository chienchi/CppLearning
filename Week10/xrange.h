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
    Xrange(): _begin(0), _end(1), _step(1){};

    Xrange_iterator begin(){
        return {_begin, _step};
    }
    Xrange_iterator end(){
        return {_end, _step};
    }

};

template <typename F>
class pipeable
{
private:
    F f;
public:
    pipeable(F&& f) : f(std::forward<F>(f)) {}

    template<class... Xs>
    auto operator()(Xs&&... xs) -> decltype(std::bind(f, std::placeholders::_1, std::forward<Xs>(xs)...)) const {
        return std::bind(f, std::placeholders::_1, std::forward<Xs>(xs)...);
    }

};

template <typename F>
pipeable<F> piped(F&& f) { return pipeable<F>{std::forward<F>(f)}; }

template<typename T, typename F>
auto operator|(T&& x, const F& f) -> decltype(f(std::forward<T>(x)))
{
    return f(std::forward<T>(x));
}

template<typename InputIt, typename UnaryOperation>
auto transform_range(InputIt inRange,
                        UnaryOperation unary_op)
{
    std::vector<int> output;
    for (auto i : inRange){
        output.push_back(unary_op(i++));
    }
    return output;
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

