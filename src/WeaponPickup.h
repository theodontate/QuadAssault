#ifndef WeaponPickup_h__
#define WeaponPickup_h__

#include "ItemPickup.h"

#include "Light.h"

enum WeaponId
{
	WEAPON_LASER ,
	WEAPON_PLAZMA ,
	WEAPON_MINIGUN ,
};

class WeaponPickup : public ItemPickup
{
	typedef ItemPickup BaseClass;

public:

	WeaponPickup( Vec2f const& pos , int id );
	void init();

	virtual void tick();
	virtual void onPick(Player* player);
	virtual void onSpawn();
	virtual void onDestroy();

	virtual IRenderer* getRenderer();

protected:
	float      mRotation;
	Light  mLight;
	int        mId;

	friend class WeaponPickupRenderer;

};

#endif // WeaponPickup_h__