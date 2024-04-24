#include "GameObject.hpp"
#include "GameWorld.hpp"

GameObject::GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int HP, pGameWorld pgameworld)
	: ObjectBase(imageID, x, y, layer, width, height, animID), m_HP(HP), m_pgameworld(pgameworld) {}

int GameObject::GetHP() { return m_HP; }

void GameObject::SetHP(int a) { m_HP = a; }

pGameWorld GameObject::GetGameWorld() { return m_pgameworld; }