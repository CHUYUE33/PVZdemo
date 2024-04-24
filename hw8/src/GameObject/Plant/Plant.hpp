#ifndef PLANT_HPP__
#define PLANT_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"

class Plant : public GameObject {
	int m_PlantTick;
public:
	Plant(ImageID imageID, int x, int y, int HP, pGameWorld pgameworld);
	int GetPlantTick();
	void SetPlantTick(int);
	int GetRow() override;
	inline void AddCollision() override;
	void OnClick() override;
	Typeid GetType() override { return Typeid::Plant; }
};

class Sunflower : public Plant {
	int IsFirstSun;

	bool IsSunnyTime();
public:
	Sunflower(int x, int y, pGameWorld pgameworld);
	void Update() override;
};

class Peashooter : public Plant {
public:
	Peashooter(int x, int y, pGameWorld pgameworld);
	void Update() override;
};

class Wallnut : public Plant {
public:
	Wallnut(int x, int y, pGameWorld pgameworld);
	void Update() override;
};

class CherryBomb : public Plant {
public:
	CherryBomb(int x, int y, pGameWorld pgameworld);
	void Update() override;
};

class Repeater : public Plant {
public:
	Repeater(int x, int y, pGameWorld pgameworld);
	void Update() override;
};


#endif // !PLANT_HPP__
