#ifndef INCLUDE_VISIBLE_H_
#define INCLUDE_VISIBLE_H_

#include <vector>
#include <SDL.h>
#include "IDrawable.h"
#include "IOverlappable.h"
#include "IPlayerMoveable.h"

class GameRectangle : public IDrawable, public IOverlappable, public IPlayerMoveable {
 public:
   const int OVERLAP_AMT = 3;
    void draw(SDL_Surface* surface) const;
    
    //  Move to collider/intersector
    bool isIntersect(const int x, const int y) const;
    bool isOverlap(const IOverlappable& other, bool reverseCheck) const;

    bool isValidMove() const;
    void moveX(const int amt);
    void moveY(const int amt);
    void setX(const int val);
    void setY(const int val);
    
    void setColour(const int r, const int g, const int b);
    
    void setPhysicalsList(std::vector<IOverlappable*>* list);
    void setNonPhysicalsList(std::vector<IOverlappable*>* list);
 private:
    int width = 50;
    int height = 50;
    int xPos = 0;
    int yPos = 0;

   std::vector<IOverlappable*>* physicals = NULL;
   std::vector<IOverlappable*>* nonPhysicals = NULL;

    int red = 255;
    int green = 0;
    int blue = 0;


};

#endif //  INCLUDE_VISIBLE_H_