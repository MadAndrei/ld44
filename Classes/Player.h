//
// Created by shenk on 29.12.18.
//

#ifndef TEMPLATECPP_PLAYER_H
#define TEMPLATECPP_PLAYER_H

#include "cocos2d.h"

#include "globals.h"
#include "InterfeiceLayer.h"
#include "Projectile.h"
//#include "DeathScene.h"

using namespace cocos2d;


class Player: public Sprite {

public:

    static Player* create(const std::string& filename);
    void damage(int count);
    void heal(int count);
    void update(float delta);
    EventListenerKeyboard* getMoveEvent();
    EventListenerPhysicsContactWithGroup* getEnemyEvent();
    void stopMoving();
    int getHealth();
    void setInterfeice(InterfeiceLayer *interfeice);
    void addGarlic();
    void addThing();
    int getThingsCount();
    int health = 100;
    int thingsCount = 0;

private:
    int garlicCount = 0;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    bool projInited = false;

    InterfeiceLayer *interfeiceLayer;




};


#endif //TEMPLATECPP_PLAYER_H
