#pragma once

#include <vector>
#include <iostream>
#include "components/simple_scene.h"
#include "2DObject.h"
#include "Birdy.h"

#define GRASS_HEIGHT 150
#define HEART_COLOR glm::vec3(0.53, 0.03, 0.03)
#define BULLET_COLOR glm::vec3(1, 0.99, 0)
#define GRASS_COLOR glm::vec3(0.22, 1, 0.08)
#define SKY_COLOR glm::vec3(0.53, 0.81, 0.92)
#define SCORE_COLOR glm::vec3(0.17, 0.4, 0.93)
#define MAX_SCORE 50

namespace t1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

        glm::ivec2 resolution;

     private:
        bird::Birdy* bird;

        int lives;
        int bullets;
        int score;

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
    };

    

}   // namespace t1