//
// Created by shenk on 28.04.19.
//

#include "WinScene.h"

cocos2d::Scene *WinScene::createWinScene(int thingsCount) {
    auto winScene = WinScene::create();
    winScene->setThingsCount(thingsCount);
    return winScene;
}

bool WinScene::init() {

    text = Label::createWithSystemFont("", "Arial", 24);
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

void WinScene::setThingsCount(int thingsCount){

    text->setString("You won!!!\nYou collect "+std::to_string(thingsCount)+" items\nPress Enter to start over");

}