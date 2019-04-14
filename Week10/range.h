//
// Created by osboxes on 4/8/19.
//

#ifndef LIVECODING2_RANGE_H
#define LIVECODING2_RANGE_H

#endif //LIVECODING2_RANGE_H
#include <algorithm>

class Range {
public:
    Range():FROM(0),TO(0){};
    Range(long from, long to): FROM(from),TO(to){};
    Range(long to): FROM(0),TO(to){};

    // member typedefs provided through inheriting from std::iterator
    class iterator: public std::iterator<
            std::input_iterator_tag,   // iterator_category
            long,                      // value_type
            long,                      // difference_type
            const long*,               // pointer
            long                       // reference
    >{
      //  friend class Range;
    public:
        explicit iterator(long _num = 0) : num(_num) {}
        iterator& operator++() {++num; return *this;}
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
        bool operator==(iterator other) const {return num == other.num;}
        bool operator!=(iterator other) const {return !(*this == other);}
        reference operator*() const {return num;}
    private:
        long num;
    };
    iterator begin() const {
        return FROM;
    }
    iterator end() const {
        return TO;
    }
private:
    iterator FROM;
    iterator TO;
    int STEP;
};

