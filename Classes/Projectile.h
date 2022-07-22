#ifndef TEMPLATECPP_PROJECTILE_H
#define TEMPLATECPP_PROJECTILE_H

#include "cocos2d.h"

#include "globals.h"

#define PROJECTILE_SCALE 0.05f
#define PROJECTILE_LIFETIME 2
#define PROJECTILE_OFFSET 10
#define PROJECTILE_SPEED 300
#define PROJECTILE_GROUP PROJECTILE //Should be added to enum ObjectsType

using namespace cocos2d;


class Projectile : public Sprite {

public:
	static void init(cocos2d::Node *Parent, cocos2d::Sprite *Shooter);
	static Projectile* create(Texture2D *texture, float lifeTime, Vec2 firePoint, Vec2 velocity/*, void(*OnDestroyCallback)(void)*/);
	static void Shoot();
	//static void update(float delta);

	//void objUpdate(float delta);




	/*
	void damage(int count);
	void heal(int count);
	EventListenerKeyboard* getMoveEvent();
	EventListenerPhysicsContactWithGroup* getEnemyEvent();
	void stopMoving();
	int getHealth();
	*/

private:
	static void OnBulletDestroy(void);
	static std::list<Projectile*> launchedProjectiles;
	static cocos2d::Vector<Texture2D*> projectileTextures;
	static cocos2d::Node *_Parent;
	static cocos2d::Sprite *_Shooter;
	float _lifeTime = PROJECTILE_LIFETIME;
	Vec2 _firePoint = Vec2::ZERO;
	Vec2 _speed = Vec2::ZERO;
	//void(*OnBulletDestroy)(void);
};


#endif //TEMPLATECPP_PROJECTILE_H
