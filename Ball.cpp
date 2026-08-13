#include "Ball.h"

// ==========================================
// Ball Implementation
// ==========================================

Ball::Ball(Vector3 position, float weight, float radius, Color color)
    : position(position), 
      weight((weight > 0.0f) ? weight : 0.001f), 
      radius((radius > 0.0f) ? radius : 0.1f), 
      color(color) 
{}

void Ball::ApplyGravity(float gravity) {
    netForce.y -= gravity * weight;
}

void Ball::ApplyForce(Vector3 force) {
    netForce = Vector3Add(netForce, force);
}

void Ball::ResetForce() {
    netForce = { 0.0f, 0.0f, 0.0f };
}


void Ball::ForceToVelocity(float dt) {
    Vector3 accel = Vector3Scale(netForce, 1.0f / weight);
    velocity = Vector3Add(velocity, Vector3Scale(accel, dt));
}

void Ball::VelocityToPosition(float dt) {
    position = Vector3Add(position, Vector3Scale(velocity, dt));
}

float Ball::CalculateKineticEnergy() const {
    float speedSqr = Vector3LengthSqr(velocity);
    return 0.5f * weight * speedSqr;
}

float Ball::CalculatePotentialEnergy(float gravity, float floorY) const {
    float height = position.y - floorY;
    return weight * gravity * height;
}

void Ball::Draw() const {
    DrawSphere(position, radius, color);
    DrawSphereWires(position, radius * 1.02f, 10, 10, WHITE);
}

// ==========================================
// BallArray Implementation
// ==========================================

void BallArray::AddBall(const Ball& ball) {
    container.push_back(ball);
}

void BallArray::Clear() {
    container.clear();
}

Ball& BallArray::operator[](int index) {
    return container[index];
}

const Ball& BallArray::operator[](int index) const {
    return container[index];
}

void BallArray::ApplyGravity(float gravity) {
    for (auto& ball : container) {
        ball.ApplyGravity(gravity);
    }
}

void BallArray::ApplyForce(Vector3 force) {
    for (auto& ball : container) {
        ball.ApplyForce(force);
    }
}

void BallArray::ResetForce() {
    for (auto& ball : container) {
        ball.ResetForce();
    }
}

void BallArray::ForceToVelocity(float dt) {
    for (auto& ball : container) {
        ball.ForceToVelocity(dt);
    }
}

float BallArray::CalculateKineticEnergy() const {
    float totalKE = 0.0f;
    for (const auto& ball : container) {
        totalKE += ball.CalculateKineticEnergy();
    }
    return totalKE;
}

float BallArray::CalculatePotentialEnergy(float gravity, float floorY) const {
    float totalPE = 0.0f;
    for (const auto& ball : container) {
        totalPE += ball.CalculatePotentialEnergy(gravity, floorY);
    }
    return totalPE;
}

void BallArray::Draw() const {
    for (const auto& ball : container) {
        ball.Draw();
    }
}

Ball BallArray::CalculateAverage() const {
    if (container.empty()) return Ball();

    Vector3 avgPos = { 0.0f, 0.0f, 0.0f };
    Vector3 avgVel = { 0.0f, 0.0f, 0.0f };
    Vector3 avgForce = { 0.0f, 0.0f, 0.0f };
    float totalWeight = 0.0f;
    float totalRadius = 0.0f;

    for (const auto& b : container) {
        avgPos = Vector3Add(avgPos, b.GetPosition());
        avgVel = Vector3Add(avgVel, b.GetVelocity());
        avgForce = Vector3Add(avgForce, b.GetNetForce());
        totalWeight += b.GetWeight();
        totalRadius += b.GetRadius();
    }

    float count = static_cast<float>(container.size());

    Ball avg;
    avg.SetPosition(Vector3Scale(avgPos, 1.0f / count));
    avg.SetVelocity(Vector3Scale(avgVel, 1.0f / count));
    avg.SetNetForce(Vector3Scale(avgForce, 1.0f / count));
    avg.SetWeight(totalWeight / count);
    avg.SetRadius(totalRadius / count);

    return avg;
}

