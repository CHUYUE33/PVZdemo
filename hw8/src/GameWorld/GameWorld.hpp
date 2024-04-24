#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"
#include "utils.hpp"
#include "GameObject.hpp"

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
	using std::enable_shared_from_this<GameWorld>::shared_from_this;// Use shared_from_this() instead of "this".
  GameWorld();
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;





  HoldingInHand GetInHand();

  void SetInHand(HoldingInHand);





  HoldingSeedType GetSeedInHand();

  void SetSeedInHand(HoldingSeedType);




  void AddToCollisionList(int row, pGameObject);

  void AddToZombieList(int row, pGameObject);


  void AddRelativeObject(pGameObject);

  bool ZombieExistence(int row);

  bool PlantDetection(pGameObject zombie);

private: 
	std::list<pGameObject> AllObjects;
	int GameTick = 0, WaveTick = 0;
	HoldingInHand m_inhand = HoldingInHand::none;
	HoldingSeedType m_seedinhand = HoldingSeedType::none;
	std::vector <std::list<pGameObject>> CollisionList;
	std::vector <std::list<pGameObject>> ZombieList;
};


#endif // !GAMEWORLD_HPP__
