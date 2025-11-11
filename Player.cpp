#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "PlayerBullet.h"
#include "ChildOden.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

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
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
	pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pLChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);

	pRChildOden_->SetPosition(  2.0f, 1.0f, 0.0f );
	pLChildOden_->SetPosition( -2.0f, 1.0f, 0.0f );
	pCollider_ = new SphereCollider(0.5f);
	AddCollider(pCollider_);

	Camera::SetPosition({
		transform_.position_.x, 
		transform_.position_.y + 5.0f,
		transform_.position_.z - 15.0f });
}

void Player::Update()
{
	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 0.1f;
	}
	if(Input::IsMouseButtonDown(0))
	{
		XMFLOAT3 pos = transform_.position_;
		pos.y += 1.0f;
		Instantiate<PlayerBullet>(pParent_)->SetPosition(pos);
	}
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
