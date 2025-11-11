#include "PlayerBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

PlayerBullet::PlayerBullet(GameObject* parent)
	:GameObject(parent, "PlayerBullet"), bulletModel_(-1), speed_(0)
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Initialize()
{
	bulletModel_ = Model::Load("oden.fbx");
	assert(bulletModel_ >= 0);
	transform_.scale_ = { 0.3f, 0.3f, 0.3f };
	speed_ = 5.0f;
	pCollider_ = new SphereCollider(0.35f);
	AddCollider(pCollider_);
}

void PlayerBullet::Update()
{
	transform_.position_.z += speed_;
	if (transform_.position_.z > 100.0f)
	{
		KillMe();
	}

	GameObject* pEnemy = FindObject("Enemy");
	if (pEnemy == nullptr) return;
	Collision(pEnemy);
}

void PlayerBullet::Draw()
{
	Model::SetTransform(bulletModel_, transform_);
	Model::Draw(bulletModel_);
}

void PlayerBullet::Release()
{
}

void PlayerBullet::OnCollision(GameObject* pTarget)
{
	KillMe();
	pTarget->KillMe();
}
