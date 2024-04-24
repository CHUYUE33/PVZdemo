#include "GameWorld.hpp"
#include "Sun.hpp"
#include "Seed.hpp"
#include "Background.hpp"
#include "PlantingSpot.hpp"
#include "Shovel.hpp"
#include "Plant.hpp"
#include "Zombie.hpp"



using std::make_shared;

GameWorld::GameWorld() { 
	CollisionList.resize(5);
	ZombieList.resize(5);
}

GameWorld::~GameWorld() {}

void GameWorld::Init() {
	SetWave(0);
	SetSun(50);
	AllObjects.emplace_back(make_shared<Background>(shared_from_this()));
	for (int row = 0; row < GAME_ROWS; ++row)
	{
		for (int col = 0; col < GAME_COLS; ++col)
		{
			AllObjects.emplace_back(std::make_shared<PlantingSpot>(FIRST_COL_CENTER + col*LAWN_GRID_WIDTH, FIRST_ROW_CENTER + row*LAWN_GRID_HEIGHT, shared_from_this()));
		}
	}
	AllObjects.emplace_back(make_shared<SunflowerSeed>(shared_from_this()));
	AllObjects.emplace_back(make_shared<PeashooterSeed>(shared_from_this()));
	AllObjects.emplace_back(make_shared<WallnutSeed>(shared_from_this()));
	AllObjects.emplace_back(make_shared<CherryBombSeed>(shared_from_this()));
	AllObjects.emplace_back(make_shared<RepeaterSeed>(shared_from_this()));



	AllObjects.emplace_back(make_shared<Shovel>(shared_from_this()));
}

LevelStatus GameWorld::Update() {

	++GameTick;
	++WaveTick;
	int MaxTick;
	if (GetWave() <= 22)
		MaxTick = 600 - 20 * GetWave();
	else
		MaxTick = 150;

	// genrating sun...
	if ((GameTick - 180) % 300 == 0 && GameTick >= 180)
		AllObjects.emplace_back(make_shared<Sun>(randInt(75, WINDOW_WIDTH - 75), WINDOW_HEIGHT - 1, SunType::sky, shared_from_this()));


	// generating zombies...
	if (GetWave() == 0) {
		if (WaveTick == 1200) {
			WaveTick = 0;
			SetWave(1);
			AllObjects.emplace_back(make_shared<RegularZombie>(randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1), FIRST_ROW_CENTER + randInt(0, 4) * LAWN_GRID_HEIGHT, shared_from_this()));
		}
	}
	else {
		if (WaveTick == MaxTick) {
			WaveTick = 0;
			SetWave(GetWave() + 1);
			int tmp = (15 + GetWave()) / 10, i = 0;
			int p1 = 20, p2 = GetWave() - 8 > 0 ? 2 * (GetWave() - 8) : 0, p3 = GetWave() - 15 > 0 ? 3 * (GetWave() - 15) : 0, sum2 = p1+p2 ,sum3 = p1 + p2 + p3;

			while (i < tmp) {
				int t = randInt(1, sum3);
				if ((t >= 1) && (t <= p1)) 				
					AllObjects.emplace_back(make_shared<RegularZombie>(randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1), FIRST_ROW_CENTER + randInt(0, 4) * LAWN_GRID_HEIGHT, shared_from_this()));
				else if ((t >= p1+1) && (t <= sum2))
					AllObjects.emplace_back(make_shared<PoleVaultingZombie>(randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1), FIRST_ROW_CENTER + randInt(0, 4) * LAWN_GRID_HEIGHT, shared_from_this()));
				else
					AllObjects.emplace_back(make_shared<BucketHeadZombie>(randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1), FIRST_ROW_CENTER + randInt(0, 4) * LAWN_GRID_HEIGHT, shared_from_this()));
				++i;
			}
		}

	}

	



	//counting zombies...
	for (auto& obj : AllObjects) {
		if (obj->GetType() == Typeid::Zombie)
			AddToZombieList(obj->GetRow(), obj);
	}


	// update all GameObjects for the first time...
	
	for (auto& obj : AllObjects)
		obj->Update();

	for (int i = 0; i < 5; ++i)
		CollisionList[i].clear();


	for (auto& obj : AllObjects) 
		obj->AddCollision();
		

	// detecting collisions...
	for (int i = 0; i < 5; ++i)
	{
		for (auto& zombie : ZombieList[i]) {
			int tmp = 0;
			for (auto& collision : CollisionList[i]) {
				if ((zombie->GetrX() <= collision->GetrX() + 20) && (zombie->GetrX() >= collision->GetlX())){
					collision->SetHP(collision->GetHP() - 3);
					zombie->SetHP(zombie->GetHP() - collision->GetBruise());
					if (collision->GetType() == Typeid::Plant)
						tmp += 1;
				}
			}
			zombie->SetEating((bool)tmp);
		}
	}


	// update all GameObjects for the second time...
	for (auto it = AllObjects.begin(); it != AllObjects.end();)
	{
		if ((*it)->GetHP() <= 0)
			AllObjects.erase(it++);
		else
			++it;
	}

	for (int i = 0; i < 5; ++i)
	{
		for (auto it = ZombieList[i].begin(); it != ZombieList[i].end();)
		{
			if ((*it)->GetHP() <= 0)
				ZombieList[i].erase(it++);
			else
				++it;
		}
		for (auto it = CollisionList[i].begin(); it != CollisionList[i].end();)
		{
			if ((*it)->GetHP() <= 0)
				CollisionList[i].erase(it++);
			else
				++it;
		}
	}


	// judging failure...

	for (int i = 0; i < 5; ++i)
	{
		for (auto& zombie : ZombieList[i])
		{
			if (zombie->GetX() < 0) {
				return LevelStatus::LOSING;
			}
		}
	}


	// additional collision detecting...

	for (int i = 0; i < 5; ++i)
	{
		for (auto& zombie : ZombieList[i]) {
			zombie->SetEating(PlantDetection(zombie));
		}
	}


	// clearing ZombieList...
	for (int i = 0; i < 5; ++i) {
		ZombieList[i].clear();
	}

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
	AllObjects.clear();
	int GameTick = 0, WaveTick = 0;
	m_inhand = HoldingInHand::none;
	m_seedinhand = HoldingSeedType::none;
	for (int i = 0; i < 5; ++i) {
		ZombieList[i].clear();
		CollisionList[i].clear();
	}
}

HoldingInHand GameWorld::GetInHand() {
	return m_inhand;
}

void GameWorld::SetInHand(HoldingInHand inhand) {
	m_inhand = inhand;
}

HoldingSeedType GameWorld::GetSeedInHand() {
	return m_seedinhand;
}

void GameWorld::SetSeedInHand(HoldingSeedType seedinhand) {
	m_seedinhand = seedinhand;
}

void GameWorld::AddRelativeObject(pGameObject pgameobject) {
	AllObjects.emplace_back(pgameobject);
}

void GameWorld::AddToCollisionList(int row, pGameObject obj) {
	CollisionList[row].emplace_back(obj);
}

void GameWorld::AddToZombieList(int row, pGameObject obj) {
	ZombieList[row].emplace_back(obj);
}

bool GameWorld::ZombieExistence(int row) {
	return !(ZombieList[row].empty());
}

bool GameWorld::PlantDetection(pGameObject zombie) {
	int tmp = 0;
	for (auto& collision : CollisionList[zombie->GetRow()]) {
		if (collision->GetType() == Typeid::Plant) {
			if ((zombie->GetrX() <= collision->GetrX() + 20) && (zombie->GetrX() >= collision->GetlX()))
				tmp += 1;
		}
	}
	return (bool)tmp;
}