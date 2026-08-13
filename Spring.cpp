#include "Spring.h"
#include <cmath>

Spring::Spring(Ball* topBall, Ball* botBall, float baseLength, float k, float c)
    : topBall(topBall), 
      botBall(botBall), 
      color(GREEN), 
      baseLength(baseLength), 
      k(k), 
      c(c) 
{}

Spring::Spring(Ball* topBall, Ball* botBall, float k, float c)
    : topBall(topBall), 
      botBall(botBall), 
      color(GREEN), 
      k(k), 
      c(c) 
{
    if (topBall == nullptr || botBall == nullptr) {
        baseLength = 0.0f;
    } else {
        baseLength = Vector3Distance(topBall->GetPosition(), botBall->GetPosition());
    }
}

void Spring::ApplyForce() {
    if (!topBall || !botBall) return;

    Vector3 topPos = topBall->GetPosition();
    Vector3 botPos = botBall->GetPosition();

    float dx = topPos.x - botPos.x;
    float dy = topPos.y - botPos.y;
    float dz = topPos.z - botPos.z;
    
    float currentLength = std::sqrt(dx * dx + dy * dy + dz * dz);

    if (currentLength < 1e-6f) return;

    // 3D Unit vector pointing from botBall to topBall
    float ux = dx / currentLength;
    float uy = dy / currentLength;
    float uz = dz / currentLength;

    // Hooke's Law: F_spring = -k * dx
    float stretch = currentLength - baseLength;
    float springForceMag = -k * stretch;

    // Damping Force: F_damping = -c * (relative velocity dot unit vector)
    Vector3 topVel = topBall->GetVelocity();
    Vector3 botVel = botBall->GetVelocity();

    float relVelX = topVel.x - botVel.x;
    float relVelY = topVel.y - botVel.y;
    float relVelZ = topVel.z - botVel.z;

    float velAlongAxis = relVelX * ux + relVelY * uy + relVelZ * uz;
    float dampingForceMag = -c * velAlongAxis;

    float totalForceMag = springForceMag + dampingForceMag;

    Vector3 netForce = {
        totalForceMag * ux,
        totalForceMag * uy,
        totalForceMag * uz
    };

    // Apply equal and opposite 3D forces using Ball's ApplyForce helper
    topBall->ApplyForce(netForce);
    botBall->ApplyForce({ -netForce.x, -netForce.y, -netForce.z });

    // --- Update spring color based on strain ---
    float t = std::abs(currentLength) / baseLength;

    if (t > 1.0f) t = 1.0f;
    else if (t < 0.0f) t = 0.0f;

    auto r = static_cast<unsigned char>( t * 255);
    auto g = static_cast<unsigned char>((1.0f - t) * 255);

    color = Color{ r, g, 0, 255 };
}

float Spring::CalculateElasticEnergy() const {
    if (!topBall || !botBall) return 0.0f;

    Vector3 topPos = topBall->GetPosition();
    Vector3 botPos = botBall->GetPosition();

    float dx = topPos.x - botPos.x;
    float dy = topPos.y - botPos.y;
    float dz = topPos.z - botPos.z;

    float currentLength = std::sqrt(dx * dx + dy * dy + dz * dz);
    float deltaL = currentLength - baseLength;

    return 0.5f * k * deltaL * deltaL;
}

void Spring::Draw() const {
    if (!topBall || !botBall) return;

    DrawLine3D(topBall->GetPosition(), botBall->GetPosition(), color);
}