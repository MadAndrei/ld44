//
// Created by shenk on 28.04.19.
//

#ifndef TEMPLATECPP_DEATHSCENE_H
#define TEMPLATECPP_DEATHSCENE_H

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class DeathScene: public Scene {
public:

    static cocos2d::Scene* createDeathScene();
    virtual bool init();
    CREATE_FUNC(DeathScene);

};


#endif //TEMPLATECPP_DEATHSCENE_H
