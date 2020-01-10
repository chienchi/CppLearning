//
// Created by osboxes on 10/18/19.
//

#ifndef LIVECODING_RANGE_OMP_H
#define LIVECODING_RANGE_OMP_H

#include <iostream>
#include <vector>

class range {
public:
    range(int i)
            : count(i) {}

    struct iterator {
        iterator(int i)
                : i(i) {}

        iterator operator++() {
            ++i;
            return *this;
        }

        int operator-(iterator &right) {
            return i - right.i;
        }

        auto operator+=(int step) {
            i += step;
            return *this;
        }

        int operator*() const { return i; }

        bool operator!=(iterator &right) const { return i != right.i; }

        int i;
    };

    iterator begin() const { return iterator{0}; }

    iterator end() const { return iterator{count}; }

private:
    int count;
};

template<typename R, typename F>
class transform {
public:
    transform(R range, F fun)
            : range(range), fun(fun) {}

    template<typename Itr>
    struct iterator {
        iterator(Itr i, F fun)
                : i(i), fun(fun) {}

        iterator operator++() {
            ++i;
            return *this;
        }

        int operator-(iterator &right) {
            return i - right.i;
        }

        auto operator+=(int step) {
            i += step;
            return *this;
        }

        auto operator*() const { return fun(*i); }

        bool operator!=(iterator &right) const { return i != right.i; }

        Itr i;
        F fun;
    };
    // For some reason, CLANG needs this deduction guide while
    // GCC is not happy about it.
    //  template<class Iter>
    //  iterator(Iter iter, F)->iterator<Iter>;

    auto begin() const { return iterator{range.begin(), fun}; }

    auto end() const { return iterator{range.end(), fun}; }

private:
    R range;
    F fun;
};

template<typename F1, typename F2>
class CompFun {
public:
    CompFun(F1 f1, F2 f2)
            : fun1(f1), fun2(f2) {}

    auto operator()(int x) const { return fun2(fun1(x)); }

private:
    F1 fun1;
    F2 fun2;
};

// Exercise 10: How can decide if R is a range by the
// existence of R::begin()?
template<typename R>
struct is_range : std::false_type {
};

template<>
struct is_range<range> : std::true_type {
};

template<typename R, typename F>
struct is_range<transform<R, F>> : std::true_type {
};

template <typename T, typename = void>
struct is_iterable : std::false_type {};
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())>>
        : std::true_type {};

template<typename L, typename R>
auto
operator|(L lhs, R rhs) {
    // is_range<L>::value
    // is_range<L>();
    // is_same<is_range<L>, std::true_type>::value
    //if constexpr (is_range<L>::value) {
    if constexpr(is_iterable<L>::value) {
        return transform(lhs, rhs);
    } else {
        return CompFun(lhs, rhs);
    }
}
template<typename F>
struct for_each {
public:
    for_each(F fun)
            : fun(fun) {}

    template<typename R>
    auto operator()(R range) {
        for (auto i : range) {
            //#pragma omp critical
            fun(i);
        }
    }

private:
    F fun;
};

template<typename L, typename F>
auto
operator|(L lhs, for_each<F> fun) {
    fun(lhs);
}

auto rectangle(const std::pair<int,int> &begin, const std::pair<int,int> &end){
    int width = end.first - begin.first;
    int height = end.second - begin.second;

    return range(height*width) | [=](int x){
        //std::vector<std::pair<int,int>> vec;
        //for (int i:range(width)) {vec.push_back({x,i});}
        //return vec;
        return std::pair<int,int> {x/width, x%width};
    };
}

#endif //LIVECODING_RANGE_OMP_H
