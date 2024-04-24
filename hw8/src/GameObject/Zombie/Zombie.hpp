#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"

class Zombie : public GameObject
{
	bool m_IsEating;
public:
	Zombie(ImageID imageID, int x, int y, AnimID animID, int HP, pGameWorld pgameworld);
	void OnClick() override {}
	Typeid GetType() override;
	bool IsEating();
	void SetEating(bool) override;
	int GetRow() override;
};

class RegularZombie : public Zombie {
public:
	RegularZombie(int x, int y, pGameWorld pgameworld);
	void Update() override;
};

class BucketHeadZombie : public Zombie {
public:
	BucketHeadZombie(int x, int y, pGameWorld pgameworld);
	void Update() override;
};

class PoleVaultingZombie : public Zombie {
	enum class PVZombieCond {
		Running,
		Jumping,
		Walking,
	};
	PVZombieCond m_IsRunning;
	int m_JumpTick;
public:
	PoleVaultingZombie(int x, int y, pGameWorld pgameworld);
	void Update() override;
};


#endif // !ZOMBIE_HPP__
