#ifndef PROJECTILE_HPP__
#define PROJECTILE_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"

class Projectile : public GameObject {
	int m_bruise;
public:
	Projectile(ImageID imageID, int x, int y, int width, int height, int HP, int bruise, pGameWorld pgameworld);

	int GetBruise() override;

	void OnClick() override {}
	Typeid GetType() override { return Typeid::Projectile; }

};

class Pea : public Projectile {
public:
	Pea(int x, int y, pGameWorld pgameworld);
	
	void Update() override;

	int GetRow() override;

	inline void AddCollision() override;
};

class Explosion : public Projectile {
	int m_ExlosionTick;
public:
	Explosion(int x, int y, pGameWorld pgameworld);

	void Update() override;

	int GetRow() override;

	inline void AddCollision() override;
};

#endif // !PROJECTILE_HPP__