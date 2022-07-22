//
// Created by shenk on 29.12.18.
//

#include "Player.h"

int gameover = 0;
Player *Player::create(const std::string &filename) {
    Player *player = new(std::nothrow) Player();
    if (player && player->initWithFile(filename)) {
        player->autorelease();

        player->setPhysicsBody(PhysicsBody::createBox(player->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT));

        player->getPhysicsBody()->setRotationEnable(false);
        player->getPhysicsBody()->setVelocityLimit(SPEED);
        player->getPhysicsBody()->setLinearDamping(1);

        player->getPhysicsBody()->setGroup(PLAYER);
        player->getPhysicsBody()->setCollisionBitmask(7);

        player->getPhysicsBody()->setContactTestBitmask(true);


        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void Player::heal(int count) {
    this->health += count;
    if (this->health > 100) {
        this->health = 100;
    }
    interfeiceLayer->setLife(health);
}

void Player::damage(int count) {
    this->health -= count;
    /*if (this->health < 0){

        Director::getInstance()->popScene();


    }*/
    interfeiceLayer->setLife(health);
}

void Player::update(float delta) {
    if (!projInited) {
        Projectile::init(this->getParent(),this);
        projInited = true;
    }

    Sequence *spawn = nullptr;
    if (up && right) {
        spawn = Sequence::create(RotateTo::create(ANIM_TIME, -45), nullptr);
    } else if (up && left) {
        spawn = Sequence::create(RotateTo::create(ANIM_TIME, -135), nullptr);
    } else if (down && right) {
        spawn = Sequence::create(RotateTo::create(ANIM_TIME, 45), nullptr);
    } else if (down && left) {
        spawn = Sequence::create(RotateTo::create(ANIM_TIME, 135), nullptr);
    } else if (up) {
        spawn = Sequence::create(RotateTo::create(ANIM_TIME, -90), nullptr);
    } else if (down) {
        spawn = Sequence::create(RotateTo::create(ANIM_TIME, 90), nullptr);
    } else if (right) {
        spawn = Sequence::create(RotateTo::create(ANIM_TIME, 0), nullptr);
    } else if (left) {
        spawn = Sequence::create(RotateTo::create(ANIM_TIME, 180), nullptr);
    }
    if (spawn) {
        this->runAction(spawn);
        this->getPhysicsBody()->applyImpulse(Vec2(FORCE*delta, 0));
    }

}

EventListenerKeyboard* Player::getMoveEvent() {
    auto event = EventListenerKeyboard::create();
    event->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        switch (keyCode) {

            case EventKeyboard::KeyCode::KEY_W:
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                up = true;
                break;
            case EventKeyboard::KeyCode::KEY_S:
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                down = true;
                break;
            case EventKeyboard::KeyCode::KEY_D:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                right = true;
                break;
            case EventKeyboard::KeyCode::KEY_A:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                left = true;
                break;
            case EventKeyboard::KeyCode::KEY_CTRL:
                if (garlicCount > 0) {
                    Projectile::Shoot();
                    garlicCount--;
                    interfeiceLayer->setGarlicCount(garlicCount);
                }
                break;
            default:
                log("Another button dispetcher");
                break;
        }
    };

    event->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        switch (keyCode) {

            case EventKeyboard::KeyCode::KEY_W:
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                up = false;
                break;
            case EventKeyboard::KeyCode::KEY_S:
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                down = false;
                break;
            case EventKeyboard::KeyCode::KEY_D:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                right = false;
                break;
            case EventKeyboard::KeyCode::KEY_A:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                left = false;
                break;

        }
    };
    return event;
}

void Player::addGarlic(){

    garlicCount++;
    interfeiceLayer->setGarlicCount(garlicCount);

}

void Player::addThing() {

    thingsCount++;
    interfeiceLayer->setThingsCount(thingsCount);


}

int Player::getThingsCount(){
    return thingsCount;
}

void Player::stopMoving(){
    up = false;
    down = false;
    right = false;
    left = false;
    this->getPhysicsBody()->setVelocity(Vec2::ZERO);
}

int Player::getHealth() {
    return health;
}

void Player::setInterfeice(InterfeiceLayer *interfeice) {

    interfeiceLayer = interfeice;

}

