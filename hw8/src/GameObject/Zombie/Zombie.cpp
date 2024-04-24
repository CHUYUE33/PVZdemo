#include "Zombie.hpp"
#include "GameWorld.hpp"

Zombie::Zombie(ImageID imageID, int x, int y, AnimID animID, int HP, pGameWorld pgameworld)
	:GameObject(imageID, x, y, LAYER_ZOMBIES, 20, 80, animID, HP, pgameworld), m_IsEating(0){}

Typeid Zombie::GetType() { return Typeid::Zombie; }

bool Zombie::IsEating() { return m_IsEating; }

void Zombie::SetEating(bool cond) {
	m_IsEating = cond;
	if (cond && GetCurrentAnimation() != ANIMID_EAT_ANIM)
		PlayAnimation(ANIMID_EAT_ANIM);
	if (!cond && GetCurrentAnimation() == ANIMID_EAT_ANIM)
		PlayAnimation(ANIMID_WALK_ANIM);
}

int Zombie::GetRow() {return (GetY() - FIRST_ROW_CENTER) / LAWN_GRID_HEIGHT; }









RegularZombie::RegularZombie(int x, int y, pGameWorld pgameworld)
	: Zombie(IMGID_REGULAR_ZOMBIE, x, y, ANIMID_WALK_ANIM, 200, pgameworld) {}
void RegularZombie::Update() {
	if (GetHP() <= 0)
		return;
	if (!IsEating())
		MoveTo(GetX() - 1, GetY());
}





BucketHeadZombie::BucketHeadZombie(int x, int y, pGameWorld pgameworld)
	: Zombie(IMGID_BUCKET_HEAD_ZOMBIE, x, y, ANIMID_WALK_ANIM, 1300, pgameworld) {}
void BucketHeadZombie::Update() {
	if (GetHP() <= 0)
		return;
	if (!IsEating())
		MoveTo(GetX() - 1, GetY());
	if (GetHP() <= 200)
		ChangeImage(IMGID_REGULAR_ZOMBIE);
}





PoleVaultingZombie::PoleVaultingZombie(int x, int y, pGameWorld pgameworld)
	: Zombie(IMGID_POLE_VAULTING_ZOMBIE, x, y, ANIMID_RUN_ANIM, 340, pgameworld), m_IsRunning(PVZombieCond::Running), m_JumpTick(0) {}
void PoleVaultingZombie::Update() {
	if (GetHP() <= 0)
		return;
	if (m_IsRunning== PVZombieCond::Running) {
		MoveTo(GetX() - 40, GetY());
		if (GetGameWorld()->PlantDetection(shared_from_this())) {
			m_IsRunning = PVZombieCond::Jumping;
			PlayAnimation(ANIMID_JUMP_ANIM);
		}
		MoveTo(GetX() + 40, GetY());
	}
	if (m_IsRunning == PVZombieCond::Jumping) {
		++m_JumpTick;
		if (m_JumpTick == 42) {
			m_IsRunning = PVZombieCond::Walking;
			PlayAnimation(ANIMID_WALK_ANIM);
			MoveTo(GetX() - 150, GetY());
		}
	}
	if (m_IsRunning == PVZombieCond::Running)
		MoveTo(GetX() - 2, GetY());
	if (m_IsRunning == PVZombieCond::Walking) {
		if (!IsEating())
			MoveTo(GetX() - 1, GetY());
	}
}


