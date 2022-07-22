//
// Created by shenk on 27.04.19.
//

#include "InterfeiceLayer.h"

bool InterfeiceLayer::init() {

    auto windowSize = Director::getInstance()->getVisibleSize();

    Label *text0 = Label::createWithSystemFont("Lifes:", "Arial", 14);
    text0->setPosition(20, windowSize.height-10);
    this->addChild(text0);

    lifeBar = ui::LoadingBar::create("bloodcolba2.png", 100);
    lifeBar->setPosition(Vec2(text0->getPosition().x+text0->getContentSize().width*1.5, text0->getPosition().y));
    lifeBar->setDirection(ui::LoadingBar::Direction::LEFT);
    lifeBar->setPercent(100);
    this->addChild(lifeBar);

    Label *text1 = Label::createWithSystemFont("Thing:", "Arial", 14);
    text1->setPosition(20, windowSize.height-10-lifeBar->getContentSize().height-15);
    this->addChild(text1);

    thingSprite = Sprite::create();
    thingSprite->setContentSize(Size(30, 30));
    thingSprite->setPosition(Vec2(text1->getPosition().x+text1->getContentSize().width*1.5, text1->getPosition().y
                                                                                       +lifeBar->getContentSize().height-thingSprite->getContentSize().height/2));
    this->addChild(thingSprite);

    Label *text2 = Label::createWithSystemFont("Garlic:", "Arial", 14);
    text2->setPosition(20, text1->getPositionY()
                           -thingSprite->getContentSize().height);
    this->addChild(text2);

    garlicCountText = Label::createWithSystemFont(std::to_string(0), "Arial", 14);
    garlicCountText->setPosition(20+text2->getContentSize().width, text1->getPositionY()
                                                         -thingSprite->getContentSize().height);
    this->addChild(garlicCountText);

    Label *text3 = Label::createWithSystemFont("Items:", "Arial", 14);
    text3->setPosition(25, text2->getPositionY()
                           -thingSprite->getContentSize().height);
    this->addChild(text3);

    thingsCountText = Label::createWithSystemFont(std::to_string(0), "Arial", 14);
    thingsCountText->setPosition(20+text3->getContentSize().width, text2->getPositionY()
                                                                   -thingSprite->getContentSize().height);
    this->addChild(thingsCountText);

    return true;


}

void InterfeiceLayer::setLife(float lifePoints){

    lifeBar->setPercent(lifePoints);


}

void InterfeiceLayer::setGarlicCount(int garlicCount) {

    garlicCountText->setString(std::to_string(garlicCount));

}

void InterfeiceLayer::setThingImage(const std::string &filename) {

    thingSprite->setTexture(filename);
    thingSprite->setContentSize(Size(30, 30));

}

void InterfeiceLayer::setThingsCount(int thingsCount){

    thingsCountText->setString(std::to_string(thingsCount));

}
