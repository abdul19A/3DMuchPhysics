#pragma once

#include <vector>
#include <array>
#include <raylib.h>
#include "Ball.h"

class Spring {
public:
    Spring() = default;
    Spring(Ball* topBall, Ball* botBall, float baseLength, float k, float c);
    Spring(Ball* topBall, Ball* botBall, float k, float c);
    Spring(const Spring& other) = default;
    Spring& operator=(const Spring& other) = default;

    void ApplyForce();
    float CalculateElasticEnergy() const;
    void Draw() const;

private:
    Ball* topBall = nullptr;
    Ball* botBall = nullptr;
    Color color = GREEN;
    float baseLength = 0.0f;
    float k = 0.0f; // Spring constant
    float c = 0.0f; // Damping constant
};
