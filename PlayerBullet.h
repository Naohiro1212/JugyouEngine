#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>

class SphereCollider;

class PlayerBullet : public GameObject
{
public:
    PlayerBullet(GameObject* parent);
    ~PlayerBullet() override;

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;

private:
    int bulletModel_;
    SphereCollider* pCollider_;

    float speed_;        // ‰‘¬‚Ì‘å‚«‚³
    float angle_;        // ãŒü‚«Šp“x [rad]
    float elapsedTime_;  // ”­Ë‚©‚ç‚ÌŒo‰ßŠÔ
    float gravity_;      // 4.9f ‚ğg‚¤ê‡‚Í y = y0 + vy*t - gravity*t^2 ‚Æ‚·‚é
    float y0_;           // ”­Ë‚Ì y
    float z0_;           // ”­Ë‚Ì z
    bool posInitialized_;
};