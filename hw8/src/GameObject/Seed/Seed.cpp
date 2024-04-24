#include "Seed.hpp"
#include "GameWorld.hpp"
#include "CDMask.hpp"

Seed::Seed(ImageID imageID, int x, int CoolTime, int Price, pGameWorld pgameworld, HoldingSeedType seedtype)
	: GameObject(imageID, x, WINDOW_HEIGHT - 44, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION, 1, pgameworld), m_CoolTime(CoolTime), m_Price(Price), m_seedtype(seedtype) {}

int Seed::GetCoolTime() { return m_CoolTime; }

int Seed::GetPrice() { return m_Price; }

void Seed::OnClick() {
	if (GetGameWorld()->GetInHand() == HoldingInHand::Seed || GetGameWorld()->GetInHand() == HoldingInHand::Shovel)
		return;
	else
		if (GetGameWorld()->GetSun() >= GetPrice()) {
			GetGameWorld()->AddRelativeObject(std::make_shared<CDMask>(GetX(), GetY(), GetCoolTime(), GetGameWorld()));
			GetGameWorld()->SetSun(GetGameWorld()->GetSun() - GetPrice());
			GetGameWorld()->SetInHand(HoldingInHand::Seed);
			GetGameWorld()->SetSeedInHand(m_seedtype);
		}
}


SunflowerSeed::SunflowerSeed(pGameWorld pgameworld) :Seed(IMGID_SEED_SUNFLOWER, 130, 240, 50, pgameworld, HoldingSeedType::SunflowerSeed) {}

PeashooterSeed::PeashooterSeed(pGameWorld pgameworld) :Seed(IMGID_SEED_PEASHOOTER, 130 + 60, 240, 100, pgameworld, HoldingSeedType::PeashooterSeed) {}

WallnutSeed::WallnutSeed(pGameWorld pgameworld) :Seed(IMGID_SEED_WALLNUT, 130 + 60*2, 900, 50, pgameworld, HoldingSeedType::WallnutSeed) {}

CherryBombSeed::CherryBombSeed(pGameWorld pgameworld) :Seed(IMGID_SEED_CHERRY_BOMB, 130 + 60 * 3, 1200, 150, pgameworld, HoldingSeedType::CherryBombSeed) {}

RepeaterSeed::RepeaterSeed(pGameWorld pgameworld) :Seed(IMGID_SEED_REPEATER, 130 + 60 * 4, 240, 200, pgameworld, HoldingSeedType::RepeaterSeed) {}
