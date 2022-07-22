/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int playerLife = 100;
int garlicCount = 0;
int alreadyCombined = 0;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    auto layer = HelloWorld::create();
    auto interfeice = InterfeiceLayer::create();
    layer->setInterfeice(interfeice);
    scene->addChild(layer);
    scene->addChild(interfeice);

    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    return scene;
}

bool HelloWorld::init() {

    player = Player::create("man.png");
    player->getPhysicsBody()->setCollisionBitmask(1);
    player->setPosition(100, 100);
    this->addChild(player);

    /*vampire = Vampire::create("man.png");
    vampire->setPlayer(player);
    this->addChild(vampire);*/

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(player->getMoveEvent(), this);
    this->runAction(Follow::create(player));

    level = Level::create("map.tmx");
    level->getMap()->setScale(MAP_SCALE);

    vampire_array = create_vampire_array();

    auto barsVector = level->getBarsVector();
    for (int i=0; i<barsVector.size(); i++){

        if (random(0, 10) == 1){

            if (random(0, 3) == 1)
                this->addChild(Item::create(*(barsVector.begin()+i), HEMATOHEN));
            else
                this->addChild(Item::create(*(barsVector.begin()+i), GARLIC));

        }

    }

    this->addChild(level->getMap(), -1);
    this->addChild(level->getExitArea());

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->scheduleUpdate();

    return true;

}

void HelloWorld::update(float delta) {
//    player->update(delta);
//    update_vampire_array(delta);

    if (needDelete){
        genNewThing();
        player->addThing();
        needDelete = false;
    }

}

void HelloWorld::setInterfeice(InterfeiceLayer *interfeiceLayer) {

    interfeice = interfeiceLayer;
    player->setInterfeice(interfeiceLayer);
    genNewThing();

}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if (a->getGroup() == PLAYER && b->getGroup() == ITEM){
        Item *item1 = (Item*)(b->getOwner());
        switch (item1->getContentType()){

            case GARLIC:
                player->addGarlic();
                player->damage(3);
                if (player->health < 0) {
                    Director::getInstance()->replaceScene(DeathScene::createDeathScene());
                } 
                break;
            case HEMATOHEN:
                player->heal(HEMATOHEN_HEAL);
                break;
            case THING:
                needDelete = true;
                break;

        }
        this->removeChild(item1);
    }

    if (a->getGroup() == ITEM && b->getGroup() == PLAYER){
        Item *item1 = (Item*)(a->getOwner());
        switch (item1->getContentType()){

            case GARLIC:
                player->addGarlic();
                player->damage(3);
                if (player->health < 0) {
                    Director::getInstance()->replaceScene(DeathScene::createDeathScene());
                } 
                break;
            case HEMATOHEN:
                player->heal(HEMATOHEN_HEAL);
                break;
            case THING:
                needDelete = true;
                break;

        }
        this->removeChild(item1);
    }

    if (a->getGroup() == PLAYER && b->getGroup() == ITEM
        || a->getGroup() == ITEM && b->getGroup() == PLAYER) {
        return false;
    }

    if (a->getGroup() == PLAYER && b->getGroup() == WALLS
        || a->getGroup() == WALLS && b->getGroup() == PLAYER) {
        return false;
    }

    if (a->getGroup() == WALLS && b->getGroup() == ITEM
        || a->getGroup() == ITEM && b->getGroup() == WALLS) {
        return false;
    }

    if (a->getGroup() == VAMPIRE && b->getGroup() == ITEM
        || a->getGroup() == ITEM && b->getGroup() == VAMPIRE) {
        return false;
    }

    if (a->getGroup() == VAMPIRE && b->getGroup() == WALLS
        || a->getGroup() == WALLS && b->getGroup() == VAMPIRE) {
        return false;
    }

    if (a->getGroup() == BARS && b->getGroup() == ITEM
        || a->getGroup() == ITEM && b->getGroup() == BARS) {
        return false;
    }

    if (a->getGroup() == PROJECTILE && b->getGroup() == ITEM
        || a->getGroup() == ITEM && b->getGroup() == PROJECTILE) {
        return false;
    }

    if (a->getGroup() == PLAYER && b->getGroup() == VAMPIRE) {
        if (!((Vampire*)(b->getOwner()))->isStaned()) {
            player->damage(10);
            if (player->health < 0) {
                Director::getInstance()->replaceScene(DeathScene::createDeathScene());
            } 
        }
        return false;
    }
    if (a->getGroup() == VAMPIRE && b->getGroup() == PLAYER) {
        if (!((Vampire*)(a->getOwner()))->isStaned()) {
            player->damage(10);
            if (player->health < 0) {
                Director::getInstance()->replaceScene(DeathScene::createDeathScene());
            } 
        }
        return false;
    }

    if (a->getGroup() == VAMPIRE && b->getGroup() == PROJECTILE) {
        this->removeChild(b->getOwner());
        ((Vampire*)(a->getOwner()))->setStaned(STAN_TIME);
    }
    if (a->getGroup() == PROJECTILE && b->getGroup() == VAMPIRE) {
        this->removeChild(a->getOwner());
        ((Vampire*)(b->getOwner()))->setStaned(STAN_TIME);

    }
    if (a->getGroup() == VAMPIRE || b->getGroup() == VAMPIRE) {
        return false;
    }

    if (a->getGroup() == EXIT && b->getGroup() == PLAYER || a->getGroup() == PLAYER && b->getGroup() == EXIT) {
        log("VICTORY");

        Director::getInstance()->replaceScene(WinScene::createWinScene(player->getThingsCount()));
        return false;
    }

    return true;
}

Vector<Vampire*> HelloWorld::create_vampire_array() {
    Vector<Vampire*> a(VAMPIRE_COUNT);

    //int N = level->getMapSize().height, M = level->getMapSize().width; // size of map
    int N = 3000, M = 3000;
    log("ONO%d %d", N, M);
    for (int i = 0; i < VAMPIRE_COUNT; i++) {
        Vec2 vector = Vec2(random(50, N-50), random(50, M-50));
        Vampire* vampire_ = Vampire::create("vampire.png", vector);
        vampire_->setPlayer(player);
        a.pushBack(vampire_);
        this->addChild(vampire_);
    }
    return a;
}

void HelloWorld::update_vampire_array(float delta){

    for (int i = 0; i < VAMPIRE_COUNT; i++) {
        (*(vampire_array.begin()+i))->update(delta);
    }

}

void HelloWorld::genNewThing() {

    log("Hi");
    auto thingBar = level->choseBar();
    auto thingItem = Item::create(thingBar, THING);
    interfeice->setThingImage("thing"+std::to_string(thingItem->thingIndex)+".png");


    this->addChild(thingItem);

}
