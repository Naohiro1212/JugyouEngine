#include "GameTime.h"
#include <chrono>

namespace GameTime
{
    using Clock = std::chrono::steady_clock;
    static Clock::time_point previousTime_;
    static float deltaTime_ = 0.0f;

    void Initialize()
    {
        previousTime_ = Clock::now();
        deltaTime_ = 0.0f;
    }

    void Update()
    {
        auto now = Clock::now();
        std::chrono::duration<float> dt = now - previousTime_;
        deltaTime_ = dt.count(); // 秒単位のfloat

        if (deltaTime_ < 0.0f) deltaTime_ = 0.0f;

        // 大きすぎるdtを防ぐ（例: デバッグで一時停止後のジャンプ対策）
        const float maxDelta = 0.1f; // 100ms 程度に制限
        if (deltaTime_ > maxDelta) deltaTime_ = maxDelta;

        previousTime_ = now;
    }

    float GetDeltaTime()
    {
        return deltaTime_;
    }
}