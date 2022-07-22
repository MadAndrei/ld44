//
// Created by shenk on 27.04.19.
//

#ifndef TEMPLATECPP_INTERFEICELAYER_H
#define TEMPLATECPP_INTERFEICELAYER_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class InterfeiceLayer: public Layer {

public:
    CREATE_FUNC(InterfeiceLayer);
    virtual bool init();
    void setLife(float);
    void setGarlicCount(int);
    void setThingsCount(int);
    void setThingImage(const std::string& filename);

private:
    ui::LoadingBar *lifeBar;
    Sprite* thingSprite;
    Label *garlicCountText;
    Label *thingsCountText;

};


#endif //TEMPLATECPP_INTERFEICELAYER_H
