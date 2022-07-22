//
// Created by shenk on 29.12.18.
//

#include "Projectile.h"
#define FORCE 50000

std::list<Projectile*>Projectile::launchedProjectiles;
cocos2d::Vector<Texture2D*> Projectile::projectileTextures;
cocos2d::Node* Projectile::_Parent;
cocos2d::Sprite* Projectile::_Shooter;


/*
static Projectile* create(Texture2D texture, float lifeTime, Vec2 firePoint, void(*OnDestroyCallback)(void));
void update(float delta);
*/
void Projectile::init(cocos2d::Node *Parent, cocos2d::Sprite *Shooter) {
	_Parent = Parent;
	_Shooter = Shooter;

	Image *tmp_img = new Image();
	Texture2D *tmp_texture;

	int i = 0;
	//while(tmp_img = Image->)
	std::string str = ("Projectiles/" + std::to_string(i) + ".png");
	while (tmp_img->initWithImageFile("Projectiles/" + std::to_string(i++) + ".png")) {
		tmp_texture = new Texture2D();
		tmp_texture->initWithImage(tmp_img);
		projectileTextures.pushBack(tmp_texture);
		//log("Pushed projectile texture %s", std::to_string(i - 1));
	}
}

/*
		
		}*/

Projectile* Projectile::create(Texture2D *texture, float lifeTime, Vec2 firePoint, Vec2 velocity) {
	
	Projectile *projectile = new(std::nothrow) Projectile();
	if (projectile && projectile->initWithTexture(texture)) {
		projectile->autorelease();

		projectile->setContentSize(projectile->getContentSize()*3);

		projectile->setPhysicsBody(PhysicsBody::createBox(projectile->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT));

		projectile->getPhysicsBody()->setRotationEnable(false);;
		projectile->getPhysicsBody()->setVelocityLimit(SPEED);

		projectile->getPhysicsBody()->setGroup(PROJECTILE_GROUP);

		projectile->getPhysicsBody()->setContactTestBitmask(true);
		projectile->getPhysicsBody()->setCollisionBitmask(3);

		
		projectile->_lifeTime = lifeTime;
		projectile->setPosition(firePoint);
		projectile->getPhysicsBody()->setVelocity(velocity);
		//projectile->OnBulletDestroy = OnDestroyCallback;

		std::list<int> lst;
		

		return projectile;
	}
	CC_SAFE_DELETE(projectile);
	
	return nullptr;
}

void Projectile::Shoot() {
	Projectile *proj = Projectile::create(projectileTextures.front(), PROJECTILE_LIFETIME, _Shooter->getPosition() + Vec2::forAngle(_PI *(2 - _Shooter->getRotation() / 180)) * PROJECTILE_OFFSET,
	 Vec2::forAngle(_PI *(2 - _Shooter->getRotation() / 180)) * PROJECTILE_SPEED);
	//this->getRotation
	_Parent->addChild(proj);
	proj->setScale(0.01f);
	launchedProjectiles.push_back(proj);
	//pr = Projectile::cre
	//launchedProjectiles.push
	return;
}

void Projectile::OnBulletDestroy(void) {
	Projectile *proj = launchedProjectiles.front();
	proj->removeFromParent();
	launchedProjectiles.pop_front();
}

/*void Projectile::update(float delta) {
	for (auto it = launchedProjectiles.begin(); it != launchedProjectiles.end(); it++) {
		(*it)->objUpdate(delta);
	}
	
}


void Projectile::objUpdate(float delta) {
	this->getPhysicsBody()->getOwner();
	if (_lifeTime)_lifeTime -= delta;
	else OnBulletDestroy();
}*/



