//
// Created by shenk on 29.12.18.
//

#ifndef TEMPLATECPP_ITEM_H
#define TEMPLATECPP_ITEM_H

#include "cocos2d.h"

#include "globals.h"

using namespace cocos2d;


class Item: public Sprite {

public:

    static Item* create(Sprite* owner, THINGS contentType);
    void update(float delta);
    void remove();
    void setContentType(THINGS contentType);
    THINGS getContentType();

    int thingIndex = -1;

private:

    THINGS content;


};


#endif //TEMPLATECPP_ITEM_H
