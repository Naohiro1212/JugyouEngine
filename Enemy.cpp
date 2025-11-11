#include "Enemy.h"
#include "PlayScene.h"
#include "Engine/SphereCollider.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent) : GameObject(parent, "Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	enemyModel_ = Model::Load("oden.fbx");

	SphereCollider* col = new SphereCollider(2.0f);
	AddCollider(col);
}

void Enemy::Update()
{
//	Collision((PlayScene*)pParent_->FindChildObject("PlayerBullet"));
}

void Enemy::Draw()
{
	Model::SetTransform(enemyModel_, transform_);
	Model::Draw(enemyModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (!pTarget) return;
	if (pTarget->GetObjectName() == "PlayerBullet")
	{
		KillMe();
	}
}
