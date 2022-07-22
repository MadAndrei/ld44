#include <Vampire.h>
#include "Vampire.h"


Vampire* Vampire::create(const std::string &filename) {
    Vampire *vampire = new(std::nothrow) Vampire();
    if (vampire && vampire->initWithFile(filename)) {
        vampire->autorelease();

        vampire->setPhysicsBody(PhysicsBody::createBox(vampire->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT));

        vampire->getPhysicsBody()->setRotationEnable(false);
        vampire->getPhysicsBody()->setVelocityLimit(SPEED);

        vampire->getPhysicsBody()->setGroup(VAMPIRE);

        vampire->getPhysicsBody()->setContactTestBitmask(true);
        vampire->getPhysicsBody()->setCollisionBitmask(2);


        return vampire;
    }
    CC_SAFE_DELETE(vampire);
    return nullptr;
}

Vampire* Vampire::create(const std::string &filename, Vec2 spawn) {

    auto vampire_ = Vampire::create(filename);
    vampire_->initPurauitArea(spawn);
    vampire_->setPosition(spawn);
    return vampire_;


}

void Vampire::setPlayer(Player* player) {
    this->newPlayer = player;
}

void Vampire::update(float delta) {

        Vec2 vector;
        if (staned <= 0) {

            if (purauitArea.containsPoint(newPlayer->getPosition())) {
                vector = (newPlayer->getPosition() - this->getPosition()).getNormalized() * 100;
            } else {
                vector = (spawnCoords - this->getPosition()).getNormalized() * 100;
            }

            this->getPhysicsBody()->setVelocity(vector);
            this->setRotation(CC_RADIANS_TO_DEGREES(vector.getAngle(Vec2(1, 0))));
        } else{
            this->getPhysicsBody()->setVelocity(Vec2::ZERO);
            staned -= delta;
        }

}

bool Vampire::initPurauitArea(Vec2 spawn) {

    int width = random(200, MAX_PURAUIT_AREA_WIDTH);
    int height = random(200, MAX_PURAUIT_AREA_HEIGHT);
    log("%d %d", width, height);
    purauitArea.setRect(spawn.x-width/2, spawn.y-height/2, width, height);

    this->spawnCoords = spawn;

    return true;
}

void Vampire::setStaned(int stanTime){

    staned = stanTime;

}

bool Vampire::isStaned() {
    return staned>0;
}




