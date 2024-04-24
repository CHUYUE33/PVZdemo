#include "PlantingSpot.hpp"
#include "GameWorld.hpp"
#include "Plant.hpp"

PlantingSpot::PlantingSpot(int x, int y, pGameWorld pgameworld)
    : GameObject(IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION, 1, pgameworld) {}

void PlantingSpot::OnClick()
{
    if (GetGameWorld()->GetInHand() == HoldingInHand::Seed) {
        PlantingPlant(GetGameWorld()->GetSeedInHand());
        GetGameWorld()->SetInHand(HoldingInHand::none);
        GetGameWorld()->SetSeedInHand(HoldingSeedType::none);
    }
    
}

void PlantingSpot::PlantingPlant(HoldingSeedType seedtype)
{
    switch (seedtype)
    {
    case HoldingSeedType::SunflowerSeed
    : GetGameWorld()->AddRelativeObject(std::make_shared<Sunflower>(GetX(), GetY(), GetGameWorld())); break;
    case HoldingSeedType::PeashooterSeed
        : GetGameWorld()->AddRelativeObject(std::make_shared<Peashooter>(GetX(), GetY(), GetGameWorld())); break;
    case HoldingSeedType::WallnutSeed
        :GetGameWorld()->AddRelativeObject(std::make_shared<Wallnut>(GetX(), GetY(), GetGameWorld())); break;
    case HoldingSeedType::CherryBombSeed
        :GetGameWorld()->AddRelativeObject(std::make_shared<CherryBomb>(GetX(), GetY(), GetGameWorld())); break;
    case HoldingSeedType::RepeaterSeed
        :GetGameWorld()->AddRelativeObject(std::make_shared<Repeater>(GetX(), GetY(), GetGameWorld())); break;
    default: break;
    }
}