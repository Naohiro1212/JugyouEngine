#include "Enemy.h"
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

	SphereCollider* col = new SphereCollider(2.5f);
	AddCollider(col);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(enemyModel_, transform_);
	Model::Draw(enemyModel_);
}

void Enemy::Release()
{
}

