//
// Created by shenk on 28.04.19.
//

#include "DeathScene.h"

cocos2d::Scene *DeathScene::createDeathScene() {
    return DeathScene::create();
}

bool DeathScene::init() {

    Label* text = Label::createWithSystemFont("You lose\nPress Enter to start over", "Arial", 24);
    text->setTextColor(Color4B::WHITE);
    text->setPosition(Director::getInstance()->getVisibleSize()/2);
    this->addChild(text);

    auto event = EventListenerKeyboard::create();
    event->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        switch (keyCode) {

            case EventKeyboard::KeyCode::KEY_ENTER:
                Director::getInstance()->replaceScene(HelloWorld::createScene());
        }
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);

    return true;

}