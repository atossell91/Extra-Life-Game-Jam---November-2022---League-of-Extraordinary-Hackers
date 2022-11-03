#ifndef INCLUDE_IOVERLAPPABLE_H_
#define INCLUDE_IOVERLAPPABLE_H_

class IOverlappable {
 public:
    virtual bool isOverlap(const IOverlappable& other, bool) const = 0;
    virtual bool isIntersect(const int x, const int y) const = 0 ;
};

#endif  // INCLUDE_IOVERLAPPABLE_H_