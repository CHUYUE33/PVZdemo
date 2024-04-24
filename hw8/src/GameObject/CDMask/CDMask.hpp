#ifndef CDMASK_HPP__
#define CDMASK_HPP__

#include "GameObject.hpp"

class CDMask : public GameObject
{
    int m_CoolTime;
    int cdtick;

public:
    CDMask(int x, int y, int cooltime, pGameWorld pgameworld);

    void Update() override;
    void OnClick() override {}
    Typeid GetType() override { return Typeid::CDMask; }
};

#endif // !CDMASK_HPP__