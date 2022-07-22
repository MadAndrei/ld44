//
// Created by shenk on 28.04.19.
//

#ifndef TEMPLATECPP_WINSCENE_H
#define TEMPLATECPP_WINSCENE_H

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class WinScene: public Scene {
private:
    Label* text;
public:

    static cocos2d::Scene* createWinScene(int);
    virtual bool init();
    void setThingsCount(int);
    CREATE_FUNC(WinScene);

};


#endif //TEMPLATECPP_WINSCENE_H
