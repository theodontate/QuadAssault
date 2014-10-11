#include "MinigunBullet.h"

#include "GameInterface.h"
#include "Level.h"
#include "TextureManager.h"
#include "Explosion.h"
#include "LightObject.h"
#include "RenderUtility.h"

class MinigunBulletRenderer : public IRenderer
{
public:
	virtual void init()
	{
		texG = getGame()->getTextureMgr()->getTexture("minigun1Glow.tga");
	}

	virtual void render( RenderPass pass , LevelObject* object )
	{
		if( pass !=RP_GLOW )
			return;

		MinigunBullet* bullet = object->cast< MinigunBullet >();

		Vec2f size = Vec2f(16,32);
		float rot= Math::atan2( bullet->mDir.y, bullet->mDir.x ) + Math::toRad( 90 );
		drawSprite( bullet->getPos() - size / 2 , size , rot , texG );

	}
	Texture* texG;
};


DEFINE_RENDERER( MinigunBullet , MinigunBulletRenderer )

void MinigunBullet::init()
{
	BaseClass::init();

	mSpeed    = 1000;
	mLifeTime = 0.5;
	mDamage   = 0.5;
}

void MinigunBullet::onSpawn()
{
	BaseClass::onSpawn();

	light.radius = 128;
	light.host   = this;
	light.setColorParam( Vec3f(1.0, 1.0, 0.1 ) , 12 );

	getLevel()->addLight( light );
	getLevel()->playSound("minigun1.wav");		
}

void MinigunBullet::onDestroy()
{
	light.remove();

	Explosion* e = getLevel()->createExplosion( getPos() , 64 );
	e->setParam(4,100,80);
	e->setColor(Vec3f(1.0, 0.75, 0.5));	
}

void MinigunBullet::tick()
{
	Bullet::tick();
}

