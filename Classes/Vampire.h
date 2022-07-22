//
// Created by shenk on 29.12.18.
//

#ifndef TEMPLATECPP_VAMPIRE_H
#define TEMPLATECPP_VAMPIRE_H

#include "cocos2d.h"

#include "globals.h"

#include "Player.h"

using namespace cocos2d;


class Vampire: public Sprite {

public:
    static Vampire* create(const std::string& filename);
    static Vampire* create(const std::string& filename, Vec2 spawnCoords);
    void update(float delta);
    void setPlayer(Player*);
    void setStaned(int stanTime);
    bool isStaned();
    int staned = 0;

private:
    Player* newPlayer;
    Vec2 vector;
    Rect purauitArea;
    bool initPurauitArea(Vec2 spawnCoords);
    Vec2 spawnCoords;

};


#endif //TEMPLATECPP_VAMPIRE_H