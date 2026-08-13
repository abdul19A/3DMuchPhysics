#pragma once
#include <raylib.h>
#include "CameraController.h"
#include "Wall.h"

struct Config {
    FollowCam basicCamera{
        { 0.0f, 2.0f, -5.0f }, // startPos
        2.0f,                  // turnSpeed
        1.4f,                  // pitchLimit
        5.0f,                  // moveSpeed
        90.0f,                 // fovy
        8.0f                   // followRadius
    };

    Wall basicFloor{
        { 0.0f, 0.0f, 0.0f },      // position
        { 0.0f, 1.0f, 0.0f },      // normal
        { 1000.0f, 1000.0f },      // size (width, height)
        0.8f,                      // friction
        0.5f                       // bounce
    };

    struct Background {
        Color color = { 0, 0, 0, 255 };
    } background;

    struct Physics {
        float gravity = 200.0f;
        float springK = 10000.0f;
        float springDamping = 1.0f;
        int physicsSubsteps = 8;
    } physics;

    struct Screen {
        int width = 1000;
        int height = 800;
        int targetFPS = 60;
    } screen;
};

extern Config config;