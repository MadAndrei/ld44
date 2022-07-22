//
// Created by shenk on 29.12.18.
//

#include "Item.h"

Item *Item::create(Sprite* owner, THINGS contentType) {
    Item *item = new(std::nothrow) Item();
    item->thingIndex = -1;
    if (item) {
        switch (contentType){

            case THING:
                item->thingIndex = random(0, THINGS_COUNT);
                item->initWithFile("thing"+std::to_string(item->thingIndex)+".png");
                break;
            case HEMATOHEN:
                item->initWithFile("hematogen.png");
                break;
            case GARLIC:
                item->initWithFile("garlic.png");
                break;

        }
        item->autorelease();

        item->setPhysicsBody(PhysicsBody::createBox(item->getContentSize()));

        item->getPhysicsBody()->setRotationEnable(false);
        item->getPhysicsBody()->setVelocityLimit(SPEED);
        item->getPhysicsBody()->setGroup(ITEM);

        item->getPhysicsBody()->setCollisionBitmask(7);
        item->getPhysicsBody()->setContactTestBitmask(true);

        item->setContentSize(owner->getContentSize()*MAP_SCALE);
        item->setPosition((owner->getPosition()+Vec2(owner->getContentSize().width/2, owner->getContentSize().width/2))*MAP_SCALE);

        if (contentType == THING){
            log("%f %f", owner->getPosition().x, owner->getPosition().y);
            log("%f %f", item->getPosition().x, item->getPosition().y);
        }
        item->setPhysicsBody(PhysicsBody::createBox(item->getContentSize()));
        item->getPhysicsBody()->setContactTestBitmask(true);
        item->getPhysicsBody()->setCollisionBitmask(2);
        item->getPhysicsBody()->setGroup(ITEM);

        item->setContentType(contentType);

        return item;
    } else {
        CC_SAFE_DELETE(item);
        return nullptr;
    }
}

void Item::update(float delta) {
}

void Item::remove() {
    this->getParent()->removeChild(this);
}

void Item::setContentType(THINGS contentType) {

    content = contentType;

}

THINGS Item::getContentType() {
    return content;
}

