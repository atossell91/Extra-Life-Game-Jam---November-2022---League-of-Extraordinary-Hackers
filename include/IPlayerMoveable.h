#ifndef INCLUDE_IPLAYERMOVEABLE_H_
#define INCLUDE_IPLAYERMOVEABLE_H_

class IPlayerMoveable {
 public:
  virtual void moveX(const int amt) = 0;
  virtual void moveY(const int amt) = 0;
};

#endif  // INCLUDE_IPLAYERMOVEABLE_H_
