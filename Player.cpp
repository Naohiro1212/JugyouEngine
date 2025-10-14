#include "Player.h"
#include "Engine/Fbx.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("oden.fbx");
	transform_.scale_ = { 0.7f, 0.7f, 0.7f };
}

void Player::Update()
{
	transform_.rotate_.y += 0.5f;
}

void Player::Draw()
{
	if (pFbx_)
	{
		pFbx_->Draw(transform_);
	}
}

void Player::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}
