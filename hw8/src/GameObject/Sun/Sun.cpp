#include "Sun.hpp"
#include "GameWorld.hpp"

Sun::Sun(int x, int y, SunType suntype, pGameWorld pgameworld) : GameObject(IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM, 1, pgameworld), m_suntype(suntype), m_suntick(0) {
	if (suntype == SunType::sky)
		m_falltime = randInt(63, 263);
	else
		m_falltime = 12;
}

void Sun::Update()  {
	++m_suntick;
	if (m_suntick <= m_falltime) {
		if (m_suntype == SunType::sky)
			MoveTo(GetX(), GetY() - 2);
		else
			MoveTo(GetX() - 1, GetY() + 4 - (m_suntick - 1));;
	}
	else {
		if (m_suntick > 300 + m_falltime)
			SetHP(0);
	}

}
void Sun::OnClick() {
	SetHP(0);
	GetGameWorld()->SetSun(GetGameWorld()->GetSun()+25);

}