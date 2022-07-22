//
// Created by shenk on 28.04.19.
//

#include "StartScene.h"

cocos2d::Scene *StartScene::createStartScene() {
    return StartScene::create();
}

bool StartScene::init() {

    Label* text = Label::createWithSystemFont("Mom: Go to shop and buy one thing\nPress Enter to start", "Arial", 24);
    text->setTextColor(Color4B::RED);
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