#ifndef SHOVEL_HPP__
#define SHOVEL_HPP__

#include "GameObject.hpp"

class Shovel : public GameObject
{
public:
    Shovel(pGameWorld pgameworld);
    void Update() override {}
    void OnClick() override;
    Typeid GetType() override { return Typeid::Shovel; }
};

#endif // !SHOVEL_HPP__