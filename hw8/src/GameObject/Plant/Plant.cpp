#include "Plant.hpp"
#include "GameWorld.hpp"
#include "Sun.hpp"
#include "Projectile.hpp"

Plant::Plant(ImageID imageID, int x, int y, int HP, pGameWorld pgameworld)
	: GameObject(imageID, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM, HP, pgameworld), m_PlantTick(0) {}

int Plant::GetPlantTick() {return m_PlantTick;}

void Plant::SetPlantTick(int tick) { m_PlantTick = tick; }

int Plant::GetRow() { return (GetY() - FIRST_ROW_CENTER) / LAWN_GRID_HEIGHT; }

inline void Plant::AddCollision(){GetGameWorld()->AddToCollisionList(GetRow(), shared_from_this());}

void Plant::OnClick() {
	if (GetGameWorld()->GetInHand() == HoldingInHand::Shovel) {
		SetHP(0);
		GetGameWorld()->SetInHand(HoldingInHand::none);
	}
}





Sunflower::Sunflower(int x, int y, pGameWorld pgameworld)
: Plant(IMGID_SUNFLOWER, x, y, 300, pgameworld), IsFirstSun(randInt(30,600)) {}

bool Sunflower::IsSunnyTime() {
	if (IsFirstSun) {
		if (GetPlantTick() == IsFirstSun)
		{
			IsFirstSun = 0;
			SetPlantTick(0);
			return true;
		}
		
	}
	else {
		if (GetPlantTick() == 600)
		{
			SetPlantTick(0);
			return true;
		}
	}
	return false;
}

void Sunflower::Update() {
	SetPlantTick(GetPlantTick() + 1);
	if (GetHP() <= 0)
		return;
	else
	{
		if (IsSunnyTime())
			GetGameWorld()->AddRelativeObject(std::make_shared<Sun>(GetX(), GetY(), SunType::sunflower, GetGameWorld()));
	}
}







Peashooter::Peashooter(int x, int y, pGameWorld pgameworld)
	: Plant(IMGID_PEASHOOTER, x, y, 300, pgameworld) {}

void Peashooter::Update() {
	if (GetHP() <= 0)
		return;
	if (GetPlantTick() > 0) {
		SetPlantTick(GetPlantTick() - 1);
		return;
	}
	else
	{
		if (GetGameWorld()->ZombieExistence(GetRow())) {
			GetGameWorld()->AddRelativeObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, GetGameWorld()));
			SetPlantTick(30);
		}
	}

}





Wallnut::Wallnut(int x, int y, pGameWorld pgameworld)
	: Plant(IMGID_WALLNUT, x, y, 4000, pgameworld) {}

void Wallnut::Update() {
	if (GetHP() <= 0)
		return;
	if (GetHP() < 4000 / 3)
		ChangeImage(IMGID_WALLNUT_CRACKED);
}





CherryBomb::CherryBomb(int x, int y, pGameWorld pgameworld)
	: Plant(IMGID_CHERRY_BOMB, x, y, 4000, pgameworld) {}

void CherryBomb::Update() {
	SetPlantTick(GetPlantTick() + 1);
	if (GetHP() <= 0)
		return;
	if (GetPlantTick() == 15) {
		SetHP(0);
		GetGameWorld()->AddRelativeObject(std::make_shared<Explosion>(GetX(), GetY(), GetGameWorld()));
	}
	
}





Repeater::Repeater(int x, int y, pGameWorld pgameworld)
	: Plant(IMGID_REPEATER, x, y, 300, pgameworld) {}

void Repeater::Update() {
	if (GetHP() <= 0)
		return;
	if (GetPlantTick() > 0) {
		SetPlantTick(GetPlantTick() - 1);
		if (GetPlantTick() == 25)
			GetGameWorld()->AddRelativeObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, GetGameWorld()));
		return;
	}
	else
	{
		if (GetGameWorld()->ZombieExistence(GetRow())) {
			GetGameWorld()->AddRelativeObject(std::make_shared<Pea>(GetX() + 30, GetY() + 20, GetGameWorld()));
			SetPlantTick(30);
		}
	}

}