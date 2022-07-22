//
// Created by shenk on 28.04.19.
//

#ifndef TEMPLATECPP_STARTSCENE_H
#define TEMPLATECPP_STARTSCENE_H

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class StartScene: public Scene {
public:

    static cocos2d::Scene* createStartScene();
    virtual bool init();
    CREATE_FUNC(StartScene);

};


#endif //TEMPLATECPP_STARTSCENE_H
