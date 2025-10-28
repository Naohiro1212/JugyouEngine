#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "ChildOden.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//pFbx_ = new Fbx;
	//pFbx_->Load("oden.fbx");
	hModel_ = Model::Load("oden.fbx");
	assert(hModel_ >= 0);
	transform_.scale_ = { 0.7f, 0.7f, 0.7f };
	pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pLChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);

	pRChildOden_->SetPosition(  2.0f, 1.0f, 0.0f );
	pLChildOden_->SetPosition( -2.0f, 1.0f, 0.0f );
}

void Player::Update()
{
	static float x = 0.0f;
	float tx = sin(x) * 5.0f;
	x += 0.02f;
	transform_.position_.x = tx;
	transform_.rotate_.y += 1.0f;
	/*if (transform_.rotate_.y > 720.0f)
	{
		KillMe();
	}*/
}

void Player::Draw()
{
	/*if (pFbx_)
	{
		pFbx_->Draw(transform_);
	}*/
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
