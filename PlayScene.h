#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Player;
class PlayerBullet;
class Enemy;
class ChildOden;

class PlayScene :
	public GameObject
{
public:
	PlayScene(GameObject* parent);
	~PlayScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	Player* pPlayer;
	std::vector<Enemy*> enemies;
	std::vector<PlayerBullet*> bullets;
	
	ChildOden* pChildOden;
};