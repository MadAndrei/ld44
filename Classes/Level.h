//
// Created by shenk on 05.01.19.
//

#ifndef TEMPLATECPP_LEVEL_H
#define TEMPLATECPP_LEVEL_H


#include <string>
#include <vector>
#include <algorithm>
#include <climits>

#include "cocos2d.h"

using namespace cocos2d;

class Level {

public:
    static Level* create(const std::string& filename);
    TMXTiledMap* getMap();
    bool initWithFile(const std::string& filename);
    bool initWallColision();
    bool initExit();
    Size getMapSize();
    void initBars();
    Sprite* choseBar();
    Vector<Sprite*>& getBarsVector();
    Sprite* getExitArea();




private:
    TMXTiledMap* map;
    bool initObjectsCollision();
    bool isValid();
    Vector<Sprite*> vbars;
    Sprite* exitArea;


};


#endif //TEMPLATECPP_LEVEL_H
