#ifndef INCLUDE_VISIBLE_H_
#define INCLUDE_VISIBLE_H_

#include <vector>
#include <SDL2/SDL.h>
#include <string>
#include <functional>

#include "IDrawable.h"
#include "IOverlappable.h"
#include "IPlayerMoveable.h"

class GameRectangle : public IDrawable, public IOverlappable,
    public IPlayerMoveable {
 public:
   const int OVERLAP_AMT = 3;
   ~GameRectangle();
    virtual void draw(SDL_Surface* surface);
    
    //  Move to collider/intersector
    bool isIntersect(const int x, const int y) const;
    bool isOverlap(const IOverlappable& other, bool reverseCheck) const;

    void setWidth(int w);
    void setHeight(int h);

    bool isValidMove() const;
    void moveX(const int amt);
    void moveY(const int amt);
    void setX(const int val);
    void setY(const int val);
    
    void setColour(const int r, const int g, const int b);
    void loadImage(const std::string& img);
    void loadSpriteFiles(const std::vector<std::string>& files);
    
    void setPhysicalsList(std::vector<IOverlappable*>* list);
    void setNonPhysicalsList(std::vector<IOverlappable*>* list);

    void addOverlapFunc(std::function<void (GameRectangle*)> foo);
    void callOverlapFuncs();
    std::vector<IOverlappable*> findOverlaps();

    public:
  std::vector<IOverlappable*> *physicals = NULL;
  std::vector<IOverlappable*> *nonPhysicals = NULL;
 private:
     
  int currentFrame = 0;
  int drawCounter = 0;

  std::vector<IOverlappable*> triggeredObjs;

   std::vector<std::function<void (GameRectangle*)>> overlapFuncs;

  SDL_Surface *img_surface = NULL;

  int red = 255;
  int green = 0;
  int blue = 0;
  protected:
    int width = 50;
    int height = 50;
    int xPos = 0;
    int yPos = 0;
  std::vector<SDL_Surface*> sprites;

};

#endif //  INCLUDE_VISIBLE_H_
