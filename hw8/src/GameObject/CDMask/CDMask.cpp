#include "CDMask.hpp"
#include "GameWorld.hpp"

CDMask::CDMask(int x, int y, int cooltime, pGameWorld pgameworld)
    : GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, ANIMID_NO_ANIMATION, 1, pgameworld), m_CoolTime(cooltime), cdtick(0) {}

void CDMask::Update()
{
    ++cdtick;
    if (cdtick == m_CoolTime)
        SetHP(0);
}