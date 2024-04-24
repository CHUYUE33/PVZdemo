#ifndef PLANTINGSPOT_HPP__
#define PLANTINGSPOT_HPP__

#include "GameObject.hpp"

class PlantingSpot : public GameObject
{
public:
    PlantingSpot(int x, int y, pGameWorld pgameworld);

    void Update() override {}
    void OnClick() override;
    Typeid GetType() override { return Typeid::PlantingSpot; }

private:
    void PlantingPlant(HoldingSeedType);
};

#endif // !PLANTINGSPOT_HPP__