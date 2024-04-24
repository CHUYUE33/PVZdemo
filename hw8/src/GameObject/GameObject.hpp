#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

enum class SunType
{
	sky,
	sunflower
};

enum class HoldingInHand
{
	none,
	Seed,
	Shovel,
};

enum class HoldingSeedType
{
	none,
	SunflowerSeed,
	PeashooterSeed,
	WallnutSeed,
	CherryBombSeed,
	RepeaterSeed,
};

enum class Typeid {
	Background,
	CDMask,
	Plant,
	PlantingSpot,
	Projectile,
	Seed,
	Shovel,
	Sun,
	Zombie,
};

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
	using std::enable_shared_from_this<GameObject>::shared_from_this; // Use shared_from_this() instead of "this".
	GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int HP, pGameWorld pgameworld);
	int GetHP();
	void SetHP(int);
	pGameWorld GetGameWorld();
	inline virtual void AddCollision() {}
	virtual int GetBruise() { return 0; }
	virtual Typeid GetType() = 0;
	virtual int GetRow() { return -1; }
	int GetlX() { return GetX() - GetWidth()/2; }
	int GetrX() { return GetX() + GetWidth()/2; }
	virtual void SetEating(bool) {};

private:
	int m_HP;
	pGameWorld m_pgameworld;
};

using pGameObject = std::shared_ptr<GameObject>;

#endif // !GAMEOBJECT_HPP__
