#pragma once

#include "components/simple_scene.h"
using namespace std;

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

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        int hp;
        glm::mat3 modelMatrixEnemyOuter;
        glm::mat3 modelMatrixEnemyInner;
        float enemyPosX;
        float dreptunghiX, dreptunghiY;
        float enemyOuterY;
        float enemyInnerY;
        int randomcoords;
        float spawnTimer;
        int randomenemy;
        int selectedGun;
        int noOfEnemies;
        int mouseCoordsX, mouseCoordsY;
        bool selected;
        int drawpos[9];
        int gun;
        float starTimer;
        int starNo;
        glm::vec3 resourceRows;
        int occupied[9];
        int timer;
        // TODO(student): If you need any other class variables, define them here.
        
    };

   
}   // namespace m1
