#ifndef BACKGROUND_HPP__
#define BACKGROUND_HPP__

#include "GameObject.hpp"

class Background : public GameObject
{
public:
    Background(pGameWorld pgameworld);

    void Update() override {}
    void OnClick() override {}
    Typeid GetType() override { return Typeid::Background; }
};

#endif // !BACKGROUND_HPP__