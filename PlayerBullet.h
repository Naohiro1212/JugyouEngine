#pragma once
#include "Engine/GameObject.h"

class SphereCollider;

class PlayerBullet : public GameObject
{
public:
	PlayerBullet(GameObject* parent);
	~PlayerBullet();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void OnCollision(GameObject* pTarget) override;
private:
	int bulletModel_;
	SphereCollider* pCollider_;
	float speed_;
};