# Much Physics

<img width="500" height="400" alt="image" src="https://github.com/user-attachments/assets/35f9081d-02da-4743-b083-0691390a73c1" />

A small 3D physics sandbox written in C++ with [raylib](https://www.raylib.com/). Balls, springs, and a bouncy floor, all simulated from scratch with a hand-rolled integrator.

## Features

- **Balls** with mass, radius, color, and velocity, affected by gravity
- **Springs** connecting pairs of balls, with configurable stiffness and damping
- **Walls** (finite planes) with adjustable friction and bounciness, and collision handling against balls
- **Follow camera** that orbits and tracks a chosen object, with free movement controls
- **Central config** (`PhysicsConfig`) for tuning gravity, spring constants, substeps, window size, and camera behavior
- Frame-time clamping so lag spikes don't blow up the simulation

## Demo scene

The default scene in `main.cpp` is a chain of three balls joined by two springs. The bottom (red) ball is launched sideways and bounces off a tilted floor while the two blue balls above it get dragged along. The camera follows the red ball.

## Requirements

- A C++ compiler (g++ or clang++)
- `make`
- [raylib](https://github.com/raysan5/raylib) installed, with `raylib.h` available on your include path

### Installing raylib

**Debian / Ubuntu**
```bash
sudo apt install libraylib-dev
```

**macOS (Homebrew)**
```bash
brew install raylib
```

**Other platforms / from source**: see the [raylib installation guide](https://github.com/raysan5/raylib#build-and-installation).

## Building and running

```bash
git clone <your-repo-url> muchphysics
cd muchphysics
make
./muchphysics
```

> The executable name depends on your `makefile`. Adjust the last line if yours differs.

## Controls

| Key | Action |
| --- | --- |
| Arrow keys | Look / orbit |
| `W` `A` `S` `D` | Move |
| `Space` | Move up |
| `Shift` | Move down |

## Project structure

| File | Purpose |
| --- | --- |
| `main.cpp` | Window setup, scene creation, main loop (update + render) |
| `Ball.h` / `Ball.cpp` | Ball object: position, velocity, force accumulation, integration, drawing |
| `Spring.h` / `Spring.cpp` | Spring connecting two balls; computes and applies spring/damping forces |
| `wall.h` / `wall.cpp` | Finite wall/plane with friction and bounce; ball collision |
| `CameraController.h` / `.cpp` | `FollowCam`: orbiting, following, and free-fly camera |
| `PhysicsConfig.h` / `.cpp` | Global `config` with physics, screen, camera, and background settings |
| `idea.txt` | Notes and ideas for the project |
| `makefile` | Build script |

## How the simulation works

Each frame:

1. Clamp the frame time (`dt`) to avoid huge steps after a lag spike.
2. Update the camera.
3. Reset accumulated forces on every ball.
4. Apply gravity and spring forces.
5. Convert force to velocity (`ForceToVelocity(dt)`).
6. Resolve wall collisions.
7. Convert velocity to position (`VelocityToPosition(dt)`).
8. Draw the scene.

This is a semi-implicit Euler integrator: velocity is updated first, then position is updated from the new velocity.

## Configuration

Most tunable values live in `PhysicsConfig.h`:

```cpp
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
```

The camera defaults (start position, turn speed, pitch limit, move speed, field of view, follow radius) are set in `config.basicCamera`.

## Creating your own scene

Edit `main.cpp`. Objects are built like this:


# AI Use

This README was written by Claude Sonnet 5.5 by Anthropic

```cpp
// Ball(position, mass, radius, color)
Ball ball(Vector3{ 0.0f, 10.0f, 0.0f }, 1.0f, 0.1f, RED);
ball.SetVelocity(Vector3{ -10.0f, 0.0f, 1.0f });

// Spring(ballA, ballB, restLength, stiffness)
Spring spring(&ballA, &ballB, 1.0f, 0.01f);

// Wall(position, normal, size, friction, bounce)
Wall floor(
    Vector3{ 0.0f, 5.0f, 0.0f },
    Vector3{ 1.0f, 1.0f, 0.0f },
    Vector2{ 100.0f, 100.0f },
    0.9f, 1.0f
);
```

Then add the matching `ResetForce`, `ApplyGravity`, `ApplyForce`, `ForceToVelocity`, `WallCollideBall`, and `VelocityToPosition` calls to the update loop, and `Draw()` calls to the render section.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
