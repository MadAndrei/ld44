//
// Created by shenk on 05.01.19.
//

#include "Level.h"
#include "globals.h"

Level* Level::create(const std::string& filename){
    Level *obj = new(std::nothrow) Level();
    if (obj && obj->initWithFile(filename)) {

        return obj;
    }
    CC_SAFE_DELETE(obj);
    return nullptr;
}

bool Level::initWithFile(const std::string &filename) {

    this->map = TMXTiledMap::create(filename);

    if (map->getLayer("walls"))
        initWallColision();
    if (map->getLayer("bars")){
        initBars();
    }
    if (map->getLayer("decor")){
        log("decor exist");
    }

    initExit();

    return true;

}

bool Level::initWallColision() {
    auto walls = map->getLayer("walls");
    int width = map->getMapSize().width;
    int height = map->getMapSize().height;

    Sprite* now;
    Size newSize;

    for (int x=0; x<width; x++) {
        for (int y = 0; y < height; y++) {

            now = walls->getTileAt(Vec2(x, y));
            if (now) {

                newSize = now->getContentSize();

                now->setPhysicsBody(PhysicsBody::createBox(newSize));
                now->getPhysicsBody()->setGroup(WALLS);
                now->getPhysicsBody()->setDynamic(false);
                now->getPhysicsBody()->setCollisionBitmask(2);
                //now->getPhysicsBody()->setContactTestBitmask(true);

            }
        }
    }

    return true;
}

bool Level::initExit(){

    auto objLayer = map->getObjectGroup("objects");
    auto objects = objLayer->getObjects();

    int x, y, h, w;
    for (auto temp_obj : objects){
        auto object = temp_obj.asValueMap();
        if  (!object["name"].asString().compare("exit")){
            x = object["x"].asInt()*MAP_SCALE;
            y = object["y"].asInt()*MAP_SCALE;
            w = object["width"].asInt()*MAP_SCALE;
            h = object["height"].asInt()*MAP_SCALE;
        }
    }

    exitArea = Sprite::create();
    exitArea->setPosition(x+w/2, y+h/2);
    exitArea->setContentSize(Size(w, h));
    exitArea->setPhysicsBody(PhysicsBody::createBox(exitArea->getContentSize()));
    exitArea->getPhysicsBody()->setGroup(EXIT);
    exitArea->getPhysicsBody()->setContactTestBitmask(true);
    exitArea->getPhysicsBody()->setDynamic(false);

    return true;

}

Sprite* Level::getExitArea() {

    return exitArea;

}

bool Level::isValid() {

        return true;
}

TMXTiledMap* Level::getMap(){
    return map;
}

Size Level::getMapSize() {

    return map->getMapSize()*map->getTileSize().width*MAP_SCALE;

}

void Level::initBars() {

    auto bars = map->getLayer("bars");
    int width = map->getMapSize().width;
    int height = map->getMapSize().height;

    Sprite* now;

    for (int x=0; x<width; x++) {
        for (int y = 0; y < height; y++) {

            now = bars->getTileAt(Vec2(x, y));
            if (now) {
                now->setPhysicsBody(PhysicsBody::createBox(now->getContentSize()));
                now->getPhysicsBody()->setGroup(BARS);
                now->getPhysicsBody()->setDynamic(false);
                now->getPhysicsBody()->setCollisionBitmask(2);
                now->getPhysicsBody()->setContactTestBitmask(true);
                vbars.pushBack(now);
            }
        }
    }

}
//hi

Sprite* Level::choseBar() {
    return vbars.getRandomObject();
//    return vbars.back();

}

Vector<Sprite*>& Level::getBarsVector(){

    return vbars;

}