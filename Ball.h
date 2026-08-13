#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>

class Ball {
public:
    Ball() = default;
    Ball(Vector3 position, float weight = 1.0f, float radius = 0.5f, Color color = RED);

    // Default copy semantics (Rule of Zero)
    Ball(const Ball& other) = default;
    Ball& operator=(const Ball& other) = default;

    // Getters
    Vector3 GetPosition() const { return position; }
    Vector3 GetVelocity() const { return velocity; }
    Vector3 GetNetForce() const { return netForce; }
    float GetWeight() const { return weight; }
    float GetRadius() const { return radius; }
    Color GetColor() const { return color; }

    // Setters
    void SetPosition(Vector3 pos) { position = pos; }
    void SetVelocity(Vector3 vel) { velocity = vel; }
    void SetNetForce(Vector3 force) { netForce = force; }
    void SetWeight(float w) { weight = (w > 0.0f) ? w : 0.001f; }
    void SetRadius(float r) { radius = (r > 0.0f) ? r : 0.1f; }
    void SetColor(Color c) { color = c; }

    // Physics
    void ApplyGravity(float gravity = 9.81f);
    void ApplyForce(Vector3 force);
    void ResetForce();
    void ForceToVelocity(float dt);
    void VelocityToPosition(float dt);

    // Energy
    float CalculateKineticEnergy() const;
    float CalculatePotentialEnergy(float gravity, float floorY = 0.0f) const;

    // Rendering
    void Draw() const;

private:
    Vector3 position = { 0.0f, 0.0f, 0.0f };
    Vector3 velocity = { 0.0f, 0.0f, 0.0f };
    Vector3 netForce = { 0.0f, 0.0f, 0.0f };
    float weight = 1.0f;
    float radius = 0.5f;
    Color color = RED;
};

class BallArray {
public:
    BallArray() = default;
    BallArray(const Ball& reference, int numCopies);

    // Default copy semantics
    BallArray(const BallArray& other) = default;
    BallArray& operator=(const BallArray& other) = default;

    // Container Management
    int GetSize() const { return static_cast<int>(container.size()); }
    bool IsEmpty() const { return container.empty(); }
    void AddBall(const Ball& ball);
    void Clear();

    // Subscript Operators
    Ball& operator[](int index);
    const Ball& operator[](int index) const;

    // --- Range-Based For Loop Support ---
    auto begin() { return container.begin(); }
    auto end() { return container.end(); }
    auto begin() const { return container.begin(); }
    auto end() const { return container.end(); }
    auto cbegin() const { return container.cbegin(); }
    auto cend() const { return container.cend(); }

    // Batch Physics Operations
    void ApplyGravity(float gravity = 9.81f);
    void ApplyForce(Vector3 force);
    void ResetForce();
    void ForceToVelocity(float dt);

    // Aggregate Energy Calculations
    float CalculateKineticEnergy() const;
    float CalculatePotentialEnergy(float gravity, float floorY = 0.0f) const;

    // Batch Rendering
    void Draw() const;

    // Analysis
    Ball CalculateAverage() const;

private:
    std::vector<Ball> container;
};