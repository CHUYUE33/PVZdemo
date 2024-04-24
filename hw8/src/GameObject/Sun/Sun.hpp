#ifndef SUN_HPP__
#define SUN_HPP__

#include "GameObject.hpp"

class Sun : public GameObject {
	SunType m_suntype;
	int m_suntick;
	int m_falltime;
public:
	Sun(int x, int y, SunType suntype, pGameWorld pgameworld);
	void Update() override;
	void OnClick() override;
	Typeid GetType() override { return Typeid::Sun; }

};


#endif // !SUN_HPP__
