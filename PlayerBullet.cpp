#include "PlayerBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/GameTime.h"
#include "PlayScene.h"
#include <cassert>
#include <DirectXMath.h>

using namespace DirectX;

PlayerBullet::PlayerBullet(GameObject* parent)
    : GameObject(parent, "PlayerBullet"),
    bulletModel_(-1),
    pCollider_(nullptr),
    speed_(30.0f),
    angle_(XMConvertToRadians(30.0f)),
    elapsedTime_(0.0f),
    gravity_(9.8f),     
    y0_(0.0f),
    z0_(0.0f),
    posInitialized_(false)
{
}

PlayerBullet::~PlayerBullet() {}

void PlayerBullet::Initialize()
{
    bulletModel_ = Model::Load("foamBulletB.fbx");
    assert(bulletModel_ >= 0);
    transform_.scale_ = { 3.0f, 3.0f, 3.0f };
	transform_.rotate_ = { 90.0f, 0.0f, 0.0f };

    pCollider_ = new SphereCollider(3.3f);
    AddCollider(pCollider_);
    elapsedTime_ = 0.0f;
    posInitialized_ = false;
}

void PlayerBullet::Update()
{
    // 万一 SetPosition が未呼び出しでも暴れないよう防御
    if (!posInitialized_)
    {
        y0_ = transform_.position_.y;
        z0_ = transform_.position_.z;
        elapsedTime_ = 0.0f;
        posInitialized_ = true;
    }

    float dt = GameTime::GetDeltaTime();
    elapsedTime_ += dt;

    //// 角度から成分分解（z: 前方、y: 上方向）
    //const float vz = speed_ * cosf(angle_);
    //const float vy = speed_ * sinf(angle_);

    //// 解析解（gravity_=4.9f の場合は -gravity*t^2）
    //transform_.position_.z = z0_ + vz * elapsedTime_;
    //transform_.position_.y = y0_ + vy * elapsedTime_ - 0.5f * gravity_ * elapsedTime_ * elapsedTime_;

    // まっすぐ飛ばす
	transform_.position_.z += speed_ * dt;

    // 画面外に出たら消す
    if (transform_.position_.z > 1000.0f || transform_.position_.y < -100.0f)
    {
        KillMe();
        return;
    }

    // 衝突判定
    PlayScene* scene = static_cast<PlayScene*>(pParent_);
    const auto& children = scene->GetChildList();
    for (GameObject* child : children)
    {
        if (!child) continue;
        if (child->GetObjectName() == "Enemy")
        {
            Collision(child);
        }
    }
}

void PlayerBullet::Draw()
{
    Model::SetTransform(bulletModel_, transform_);
    Model::Draw(bulletModel_);
}

void PlayerBullet::Release() {}

void PlayerBullet::OnCollision(GameObject* pTarget)
{
    if (!pTarget) return;
    if (pTarget->GetObjectName() == "Enemy")
    {
        KillMe();
        // pTarget->KillMe(); // 必要なら有効化
    }
}