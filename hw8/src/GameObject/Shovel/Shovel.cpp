#include "Shovel.hpp"
#include "GameWorld.hpp"

Shovel::Shovel(pGameWorld pgameworld)
    : GameObject(IMGID_SHOVEL, 600, WINDOW_HEIGHT - 40, LAYER_UI, 50, 50, ANIMID_NO_ANIMATION, 1, pgameworld) {}

void Shovel::OnClick() {
    if (GetGameWorld()->GetInHand() != HoldingInHand::Seed) {
        if (GetGameWorld()->GetInHand() == HoldingInHand::Shovel)
            GetGameWorld()->SetInHand(HoldingInHand::none);
        else
            GetGameWorld()->SetInHand(HoldingInHand::Shovel);
    }
}