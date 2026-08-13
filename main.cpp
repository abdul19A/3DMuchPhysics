#include "raylib.h"
#include "PhysicsConfig.h"
#include "CameraController.h"
#include "Ball.h"
#include "Spring.h"

int main() {
    InitWindow(config.screen.width, config.screen.height, "-- MUCH PHYSICS --");
    //SetTargetFPS(config.screen.targetFPS);

    FollowCam cc = config.basicCamera;
    Wall floor(
        Vector3{ 0.0, 5.0f, 0.0f },
        Vector3{ 1.0f, 1.0f, 0.0f },
        Vector2{ 100.0f, 100.0f },
        0.9f, 1.0f
    );
    Ball toppestBall(Vector3{ 0.0f, 15.0f, 0.0f }, 1.0f, 0.1f, DARKBLUE);
    Ball topBall(Vector3{ 0.0f, 10.0f, 0.0f }, 1.0f, 0.1f, DARKBLUE);
    Ball botBall(Vector3{ 2.0f, 6.0f, 0.0f }, 1.0f, 0.1f, RED);
    botBall.SetVelocity((Vector3){-10.0f, 0.0f, 1.0f});
    Spring spring1(&topBall, &botBall, 1.0f, 0.01f);
    Spring spring2(&toppestBall, &topBall, 1.0f, 0.01f);
    float dt1;
    float dt2;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.1f) dt = 0.1f; // Safeguard against large lag spikes

        // --- Camera Controls ---
        cc.UpdateOrbit(dt);
        cc.FollowPosition(botBall.GetPosition(), dt);
        // --- Physics Update Step ---
        toppestBall.ResetForce();
        topBall.ResetForce();
        botBall.ResetForce();

        topBall.ApplyGravity(9.81f);
        botBall.ApplyGravity(9.81f); 
        
        spring1.ApplyForce();
        spring2.ApplyForce();

        topBall.ForceToVelocity(dt);
        botBall.ForceToVelocity(dt);

        dt = floor.WallCollideBall(botBall, dt); 

        botBall.VelocityToPosition(dt);

        // --- Render ---
        BeginDrawing();
            ClearBackground(config.background.color);

            BeginMode3D(cc.GetCamera());
                // Render spring and balls
                floor.Draw();
                spring1.Draw();
                spring2.Draw();
                toppestBall.Draw();
                topBall.Draw();
                botBall.Draw();
                
            EndMode3D();

            DrawFPS(10, 10);
            DrawText("Arrows: look | WASD: move | Space/Shift: up/down", 10, 35, 10, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}