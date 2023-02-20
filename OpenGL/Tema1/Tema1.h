#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        
        void checkState();
        void checkCollision();
        void drawHUD();
        void drawDuck(float deltaTimeSeconds);
        void respawnDuck();

    protected:
        float const PI = 3.1415926f;
        float cx, cy;
        glm::mat3 modelMatrix;
        glm::mat3 parentMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep, orientation, weaponAngle;
        int flag, killed, evaded, falling;
        int resX, resY;
        int spawnX, spawnY;
        float headSize, hitboxSize;
        int duckNumber, score, livesNumber, bulletsNumber;
        int initialSpeed, currentSpeed, speedStep;
        int time;
        int canHit, renderFire;
        int crosshairX, crosshairY;

    };
}   // namespace m1
