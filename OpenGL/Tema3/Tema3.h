#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"
#include <deque>

namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
    public:
        // Struct care reprezinta un obstacol
        struct Obstacle
        {
            Obstacle() : mesh(NULL), shader(NULL), modelMatrix(glm::mat4(1)), texture(NULL), pos(glm::vec3(0, 0, 0)), isPresent(false) {}
            Obstacle(Mesh* mesh, Shader* shader, glm::mat4 modelMatrix, Texture2D* texture, glm::vec3 pos, bool isPresent) : mesh(mesh), shader(shader), modelMatrix(modelMatrix), texture(texture), pos(pos), isPresent(isPresent){}

            Mesh* mesh;
            Shader* shader;
            glm::mat4 modelMatrix;
            Texture2D* texture;
            glm::vec3 pos;
            bool isPresent;
        };

        Tema3();
        ~Tema3();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);
        void RenderPlayer();
        void RenderObstacles();
        void checkCollisions();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        std::unordered_map<std::string, Texture2D*> mapTextures;
        glm::mat4 translateMatrix;
        glm::mat4 movementMatrix;
        glm::mat4 rotationMatrix;
        glm::mat4 objMatrix;
        glm::mat4 playerOrientationMatrix;
        glm::vec3 playerPos;
        
        float tx;
        float ty;
        float tz;
        float orientation;

        bool mixT;
        float isGround;
        bool addObstacle;
        bool wait;
        bool collision;
        int running;
        int score;

        std::deque<Obstacle> obsQueue;
        glm::vec3 lastCollision;

        glm::vec3 dirLightPos;
        glm::vec3 dirLightColor;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        glm::quat cameraRotation;
    };
}   // namespace m1
