#include "Projectile.hpp"
#include "GameWorld.hpp"

Projectile::Projectile(ImageID imageID, int x, int y, int width, int height, int HP, int bruise, pGameWorld pgameworld)
	: GameObject(imageID, x, y, LAYER_PROJECTILES, width, height, ANIMID_NO_ANIMATION, HP, pgameworld), m_bruise(bruise) {}

int Projectile::GetBruise() { return m_bruise; }





Pea::Pea(int x, int y, pGameWorld pgameworld)
: Projectile(IMGID_PEA, x, y, 28, 28, 1, 20, pgameworld) {}

void Pea::Update() {
	if (GetHP() <= 0)
		return;
	MoveTo(GetX() + 8, GetY());
	if (GetY() >= WINDOW_WIDTH)
		SetHP(0);
}

int Pea::GetRow() { return (GetY() - 20 - FIRST_ROW_CENTER) / LAWN_GRID_HEIGHT; }


inline void Pea::AddCollision() { GetGameWorld()->AddToCollisionList(GetRow(), shared_from_this()); }





Explosion::Explosion(int x, int y, pGameWorld pgameworld)
	:Projectile(IMGID_EXPLOSION, x, y, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, 4000, 1500, pgameworld), m_ExlosionTick(0) {}

void Explosion::Update() {
	m_ExlosionTick++;
	if (m_ExlosionTick == 3)
		SetHP(0);
}

int Explosion::GetRow() { return (GetY() - FIRST_ROW_CENTER) / LAWN_GRID_HEIGHT; }

inline void Explosion::AddCollision() {
	int row = GetRow();
	for (int i = -1; i <= 1; ++i) {
		if ((row + i >= 0) && (row + i <= 4)) 
			GetGameWorld()->AddToCollisionList(row + i, shared_from_this());
	}
}