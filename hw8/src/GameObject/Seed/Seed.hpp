#ifndef SEED_HPP__
#define SEED_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"

class Seed : public GameObject{
	int m_Price, m_CoolTime;
	HoldingSeedType m_seedtype;
public:
	Seed(ImageID imageID, int x, int CoolTime, int Price, pGameWorld pgameworld, HoldingSeedType seedtype);
	int GetCoolTime();
	int GetPrice();
	void OnClick() override;
	Typeid GetType() override { return Typeid::Seed; }
};

class SunflowerSeed :public Seed {
public:
	SunflowerSeed(pGameWorld pgameworld);
	void Update() override{}
};

class PeashooterSeed :public Seed {
public:
	PeashooterSeed(pGameWorld pgameworld);
	void Update() override {}
};

class WallnutSeed :public Seed {
public:
	WallnutSeed(pGameWorld pgameworld);
	void Update() override {}
};

class CherryBombSeed :public Seed {
public:
	CherryBombSeed(pGameWorld pgameworld);
	void Update() override {}
};

class RepeaterSeed :public Seed {
public:
	RepeaterSeed(pGameWorld pgameworld);
	void Update() override {}
};



#endif // !SEED_HPP__
