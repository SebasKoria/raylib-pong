#include "raylib.h"
#include "raytween.h"
#include "ball.h"
#include "paddle.h"
#include "cpupaddle.h"
#include "textpro.h"
#include "collisionglow.h"

Color Green = Color{ 38, 185, 154, 255 };
Color Dark_Green = Color{ 20, 160, 133, 255 };
Color Light_Green = Color{ 129, 204, 184, 255 };

#define PLATFORM_WEB

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

const int screenWidth = 1280;
const int screenHeight = 800;
std::vector<std::shared_ptr<GameObject>> gameObjects;

void UpdateDrawFrame();

int main(void)
{

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");


    auto paddleScore = GameObject::Create<TextPro>(400, Color{ 255, 255, 255, 50 }, Vector2{ 3 * screenWidth / 4, screenHeight / 2 });
    auto cpuPaddleScore = GameObject::Create<TextPro>(400, Color{ 255, 255, 255, 50 }, Vector2{ screenWidth / 4, screenHeight / 2 });
    auto paddle = GameObject::Create<Paddle>(25, 120, 10, WHITE, paddleScore, Vector2{ screenWidth - 35, screenHeight / 2 - 60 });
    auto cpuPaddle = GameObject::Create<CpuPaddle>(25, 120, 10, WHITE, cpuPaddleScore, Vector2{ 10, screenHeight / 2 - 60 });
    auto ball = GameObject::Create<Ball>(20, 10, 22, YELLOW, paddle, cpuPaddle, Vector2{ screenWidth / 2, screenHeight / 2 });

    gameObjects.push_back(paddle);
    gameObjects.push_back(cpuPaddle);
    gameObjects.push_back(paddleScore);
    gameObjects.push_back(cpuPaddleScore);
    gameObjects.push_back(ball);

    paddleScore->SetPivot(Vector2{ 0.5,0.5 });
    cpuPaddleScore->SetPivot(Vector2{ 0.5,0.5 });
    paddleScore->SetText("0");
    cpuPaddleScore->SetText("0");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();

    return 0;
}

void UpdateDrawFrame()
{
    Raytween::DoTweens(GetFrameTime());
    for (auto object : gameObjects) object->Update();

    BeginDrawing();
    ClearBackground(Dark_Green);

    DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, Green);
    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

    for (auto object : gameObjects) object->Draw();

    EndDrawing();
}