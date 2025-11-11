#pragma once
#include "Engine/GameObject.h"

class SphereCollider;
class ChildOden;
class Fbx;

class Player :
    public GameObject
{
public:
	Player(GameObject* parent);
	~Player();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	ChildOden* pRChildOden_;
	ChildOden* pLChildOden_;
	int hModel_;
};

