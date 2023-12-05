#include "lab_m1/lab3/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include "lab_m1/lab3/Romb.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

    class EnemyHexagon {
    bool alive = true;
    public:int type;
    public:int hp = 3;
    public:float enemyInnerX = 0;
    public:float enemyInnerY = 0;
    public:float enemyOuterX = 0;
    public:float enemyOuterY = 0;
    public:int line;
    public:string inner = "";
    public:string outer = "";
    public:   EnemyHexagon();
    public: glm::mat3 modelMatrixEnemyOuter;
    public: glm::mat3 modelMatrixEnemyInner;
    public :EnemyHexagon(int random1, int random2) {
            alive = true;
            type = random2;
            if (random1 == 0) {
                enemyInnerX = 1280;
                enemyInnerY = 260;
                enemyOuterX = 1280;
                enemyOuterY = 250;
                line = 1;
            }
            else if (random1 == 1) {
                enemyInnerX = 1280;
                enemyInnerY = 140;
                enemyOuterX = 1280;
                enemyOuterY = 130;
                line = 2;
            }
            else if (random1 == 2) {
                enemyInnerX = 1280;
                enemyInnerY = 20;
                enemyOuterX = 1280;
                enemyOuterY = 10;
                line = 3;
            }
            else return;

            if (random2 == 0) {
                inner = "enemyInner1";
                outer = "enemyOuter1";
            }
            else if (random2 == 1) {
                inner = "enemyInner2";
                outer = "enemyOuter2";
            }
            else if (random2 == 2) {
                inner = "enemyInner3";
                outer = "enemyOuter3";
            }
            else if (random2 == 3) {
                inner = "enemyInner4";
                outer = "enemyOuter4";
            }

            type = random2;
            modelMatrixEnemyOuter = glm::mat3(1);
            modelMatrixEnemyOuter *= transform2D::Translate(enemyOuterX, enemyOuterY);
            modelMatrixEnemyOuter *= transform2D::Scale(20, 20);


            modelMatrixEnemyInner = glm::mat3(1);
            modelMatrixEnemyInner *= transform2D::Translate(enemyInnerX, enemyInnerY);
            modelMatrixEnemyInner *= transform2D::Scale(15, 15);

        }

    public: void dec() {
            enemyInnerX--;
        }

    public: void changepos() {


        modelMatrixEnemyOuter = glm::mat3(1);
        modelMatrixEnemyOuter *= transform2D::Translate(enemyOuterX--, enemyOuterY);
        modelMatrixEnemyOuter *= transform2D::Scale(20, 20);

        modelMatrixEnemyInner = glm::mat3(1);
        modelMatrixEnemyInner *= transform2D::Translate(enemyInnerX--, enemyInnerY);
        modelMatrixEnemyInner *= transform2D::Scale(15, 15);
    }

};

    class Romb
    {
    public:  float x, y;
    public: string color;
    public: glm::mat3 modelMatrix;
    public: int type;
    public: int squareNo;
    public: int hp, time;
    public: int value;
    public: int line;
    public: bool trage;
    public: Romb(int typee, float X, float Y) {
        type = typee;
        time = 15;
        trage = true;
        if (type == 1) {
            color = "romb1";
            value = 1;
        }
        else if (type == 2) {
            color = "romb2";
            value = 2;
        }
        else if (type == 3) {
            color = "romb3";
            value = 2;
        }
        else if (type == 4) {
            color = "romb4";
            value = 3;
        }
        hp = 1;
        x = X;
        y = Y;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, y);
        modelMatrix *= transform2D::Scale(15, 15);
    }

    public:void minimize(int deltaTime) {
        
        time-=1;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, y);
        modelMatrix *= transform2D::Scale(time, time);
    }

    };

    class Star
    {
    public: float x, y;
    public: glm::mat3 modelMatrix;
    public: bool alive;
    public: Star(float X, float Y) {
        x = X;
        y = Y;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, y);
        modelMatrix *= transform2D::Scale(10, 10);
        alive = true;
    }
    public: Star(){}
    };

    class Bullet {
    public: float x, y;
    public: glm::mat3 modelMatrix;
    public: bool alive;
    public: Bullet(float X, float Y) {
        x = X;
        y = Y;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, y);
        modelMatrix *= transform2D::Scale(12, 12);
        alive = 1;
    }
    public: void move() {
        modelMatrix *= glm::mat3(1);
        modelMatrix *= transform2D::Translate(x++, y);
        modelMatrix *= transform2D::Scale(12, 12);
    }
    };
vector<EnemyHexagon> enemies;
vector<Romb> guns;
vector<Star> stars;
vector<Bullet> bullets;
Star star;
Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    for (int i = 0; i < 9; i++)
        occupied[i] = 0;
    star = Star(rand() % 1000, rand() % 600);
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    mouseCoordsX = 0;
    mouseCoordsY = 0;
    translateX = 300;
    starNo = 0;
    angularStep = 0;
    hp = 3;
    dreptunghiX = 20;
    dreptunghiY = 0;
    enemyOuterY = 240;
    enemyInnerY = 250;
    randomcoords = rand() % 3;
    randomenemy = rand() % 4;
    spawnTimer = rand() % 8;
    starTimer = rand() % 5;
    noOfEnemies = 0;
    selectedGun = 0;
    timer = 5;
    resourceRows = glm::vec3(570, 530, 490);
    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);

    Mesh* cadran = object2D::CreateSquare("cadran", corner, squareSide, glm::vec3(0.741f, 0.741f, 0.741f));
    AddMeshToList(cadran);

    Mesh* health = object2D::CreateSquare("health", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(health);
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 6,  0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            // TODO(student): Complete the vertices data for the cube mesh
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 0,  0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 6,  0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 2,
           0, 2, 3

        };

        meshes["dreptunghi"] = new Mesh("generated dreptunghi 1");
        meshes["dreptunghi"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-2, 0,  1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 3,  1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, -3,  1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1.2f, -1,  1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1.2f, 1,  1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(4, 1,  1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(4, -1,  1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        };

        vector<unsigned int> indices =
        {
           0, 4, 1,
           0, 3, 4,
           0, 2, 3,
           3, 6, 5,
           3, 5, 4,

        };

        meshes["romb1"] = new Mesh("generated romb 1");
        meshes["romb1"]->InitFromData(vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-2, 0,  1), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 3,  1), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, -3,  1), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1.2f, -1,  1), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1.2f, 1,  1), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(4, 1,  1), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(4, -1,  1), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        };

        vector<unsigned int> indices =
        {
           0, 4, 1,
           0, 3, 4,
           0, 2, 3,
           3, 6, 5,
           3, 5, 4,

        };

        meshes["romb2"] = new Mesh("generated romb 2");
        meshes["romb2"]->InitFromData(vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-2, 0,  1), glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 3,  1), glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, -3,  1), glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1.2f, -1,  1), glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1.2f, 1,  1), glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(4, 1,  1), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(4, -1,  1), glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
        };

        vector<unsigned int> indices =
        {
           0, 4, 1,
           0, 3, 4,
           0, 2, 3,
           3, 6, 5,
           3, 5, 4,

        };

        meshes["romb3"] = new Mesh("generated romb 3");
        meshes["romb3"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {

        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-2, 0,  1), glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            // TODO(student): Complete the vertices data for the cube mesh
            VertexFormat(glm::vec3(0, 3,  1), glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, -3,  1), glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1.2f, -1,  1), glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(1.2f, 1,  1), glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(4, 1,  1), glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(4, -1,  1), glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 4, 1,
           0, 3, 4,
           0, 2, 3,
           3, 6, 5,
           3, 5, 4,

        };

        meshes["romb4"] = new Mesh("generated romb 4");
        meshes["romb4"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 3,  1),     glm::vec3(0.702f, 0.698f, 0.667f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, -3,  1),     glm::vec3(0.702f, 0.698f, 0.667f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(3, 0.6f,  1),        glm::vec3(0.702f, 0.698f, 0.667f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-3, 0.6f,  1), glm::vec3(0.702f, 0.698f, 0.667f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, -3,  1),       glm::vec3(0.702f, 0.698f, 0.667f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, -1.6f,  1),  glm::vec3(0.702f, 0.698f, 0.667f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           1, 5, 0,
           5, 4, 0,
           5, 2, 3

        };

        meshes["star1"] = new Mesh("generated star 1");
        meshes["star1"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0 + 2.8f, 4.4f,  1),     glm::vec3(0, 1, 0.62), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0 + 2.8f, 1.2f,  1),     glm::vec3(0, 1, 0.62), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2 + 2.8f, 0,  1),       glm::vec3(0, 1, 0.62), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2 + 2.8f, 0,  1),        glm::vec3(0, 1, 0.62), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2.8f + 2.8f, 2.8f,  1), glm::vec3(0, 1, 0.62), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2.8f + 2.8f, 2.8f,  1),  glm::vec3(0, 1, 0.62), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           1, 0, 2,
           1, 3, 0,
           1, 4, 5

        };

        meshes["star2"] = new Mesh("generated star 1");
        meshes["star2"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 4, 0.5f),     glm::vec3(1, 0.58f, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 3,  0.5f),     glm::vec3(1, 0.58f, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 1,  0.5f),       glm::vec3(1, 0.58f, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  0.5f),        glm::vec3(1, 0.58f, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 1,  0.5f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 3,  0.5f),  glm::vec3(1, 0.58f, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 5,
           1, 2, 5,
           2, 4, 5,
           3, 4, 2,

        };

        meshes["enemyOuter1"] = new Mesh("generated enemyOuter 1");
        meshes["enemyOuter1"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 4, 1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 3,  1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 1,  1),       glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  1),        glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 1,  1), glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 3,  1),  glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 5,
           1, 2, 5,
           2, 4, 5,
           3, 4, 2,

        };

        meshes["enemyInner1"] = new Mesh("generated enemyInner1 1");
        meshes["enemyInner1"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }
    
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 4, 0.5f),     glm::vec3(0, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 3,  0.5f),     glm::vec3(0, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 1,  0.5f),       glm::vec3(0, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  0.5f),        glm::vec3(0, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 1,  0.5f), glm::vec3(0, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 3,  0.5f),  glm::vec3(0, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 5,
           1, 2, 5,
           2, 4, 5,
           3, 4, 2,

        };

        meshes["enemyOuter2"] = new Mesh("generated enemyOuter 2");
        meshes["enemyOuter2"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 4, 1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 3,  1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 1,  1),       glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  1),        glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 1,  1), glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 3,  1),  glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 5,
           1, 2, 5,
           2, 4, 5,
           3, 4, 2,

        };

        meshes["enemyInner2"] = new Mesh("generated enemyInner2");
        meshes["enemyInner2"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 4, 0.5f),     glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 3,  0.5f),     glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 1,  0.5f),       glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  0.5f),        glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 1,  0.5f), glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 3,  0.5f),  glm::vec3(1, 1, 0), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 5,
           1, 2, 5,
           2, 4, 5,
           3, 4, 2,

        };

        meshes["enemyOuter3"] = new Mesh("generated enemyOuter 3");
        meshes["enemyOuter3"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 4, 1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 3,  1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 1,  1),       glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  1),        glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 1,  1), glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 3,  1),  glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 5,
           1, 2, 5,
           2, 4, 5,
           3, 4, 2,

        };

        meshes["enemyInner3"] = new Mesh("generated enemyInner 3");
        meshes["enemyInner3"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 4, 0.5f),     glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 3,  0.5f),     glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 1,  0.5f),       glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  0.5f),        glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 1,  0.5f), glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 3,  0.5f),  glm::vec3(0.733f, 0, 1), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 5,
           1, 2, 5,
           2, 4, 5,
           3, 4, 2,

        };

        meshes["enemyOuter4"] = new Mesh("generated enemyOuter 4");
        meshes["enemyOuter4"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 4, 1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 3,  1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-2, 1,  1),       glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  1),        glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 1,  1), glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 3,  1),  glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           0, 1, 5,
           1, 2, 5,
           2, 4, 5,
           3, 4, 2,

        };

        meshes["enemyInner4"] = new Mesh("generated enemyInner 4");
        meshes["enemyInner4"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-1, 3, 1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-1, 0,  1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-3, 0,  1),       glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-3, -1,  1),        glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-1, -5,  1),  glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, -5, 1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, -1,  1),     glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, -1,  1),       glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 0,  1),        glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0, 3,  1),  glm::vec3(0.031f, 0.969f, 0.796f), glm::vec3(1, 0.58f, 0), glm::vec3(1, 0, 0)),

        };

        vector<unsigned int> indices =
        {
           3, 1, 2,
           4, 1, 3,
           5, 6, 0,
           6, 11, 0,
           7, 8, 9,
           7, 9, 10,

        };

        meshes["Crucifix"] = new Mesh("generated crucifix");
        meshes["Crucifix"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
    }
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (hp > 0) {


       modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX++, 300);
        modelMatrix *= transform2D::Rotate(angularStep);
        angularStep += 0.001;
        modelMatrix *= transform2D::Scale(10, 10);      
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(dreptunghiX, dreptunghiY);
        modelMatrix *= transform2D::Scale(50, 57);

        RenderMesh2D(meshes["dreptunghi"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(140, 120);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(260, 120);


        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(380, 120);

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(140, 240);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(260, 240);

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(380, 240);

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(380, 120);


        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(140, 240);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(260, 240);
        

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(380, 240);

       

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(140, 0);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(260, 0);
       

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(380, 0);

       

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(60, 660);
        modelMatrix *= transform2D::Scale(15, 15);

        RenderMesh2D(meshes["romb1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(260, 660);
        modelMatrix *= transform2D::Scale(15, 15);

        RenderMesh2D(meshes["romb2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(460, 660);
        modelMatrix *= transform2D::Scale(15, 15);

        RenderMesh2D(meshes["romb3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(660, 660);
        modelMatrix *= transform2D::Scale(15, 15);

        RenderMesh2D(meshes["romb4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(20, 570);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(220, 570);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(260, 570);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(420, 570);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(460, 570);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(620, 570);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(660, 570);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(700, 570);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(20, 610);

        RenderMesh2D(meshes["cadran"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(220, 610);
        RenderMesh2D(meshes["cadran"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(420, 610);
        RenderMesh2D(meshes["cadran"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(620, 610);
        RenderMesh2D(meshes["cadran"], shaders["VertexColor"], modelMatrix);


        if (hp == 3) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(820, 610);
            RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(930, 610);
            RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1040, 610);
            RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
        }
        else if (hp == 2) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(820, 610);
            RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(930, 610);
            RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
        }
        else if (hp == 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(820, 610);
            RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
        }
            spawnTimer -= deltaTimeSeconds;
            starTimer -= deltaTimeSeconds;
            timer -= deltaTimeSeconds;
            if (spawnTimer < 0) {
                EnemyHexagon testEnemy = EnemyHexagon(rand() % 3, rand() % 4);
                RenderMesh2D(meshes[testEnemy.outer], shaders["VertexColor"], testEnemy.modelMatrixEnemyOuter);
                RenderMesh2D(meshes[testEnemy.inner], shaders["VertexColor"], testEnemy.modelMatrixEnemyInner);
                enemies.push_back(testEnemy);
                noOfEnemies++;
                spawnTimer = rand() % 10;
            }
            for (auto it = enemies.begin(); it != enemies.end(); )
            {
                it->changepos();
                RenderMesh2D(meshes[it->outer], shaders["VertexColor"], it->modelMatrixEnemyOuter);
                RenderMesh2D(meshes[it->inner], shaders["VertexColor"], it->modelMatrixEnemyInner);
                for (auto g = guns.begin(); g != guns.end(); g++)
                    if (it->enemyOuterX == g->x + 90 && it->line == g->line)
                        g->hp = 0;
                if (it->enemyOuterX < dreptunghiX + 120) {
                    hp--;
                    it = enemies.erase(it);
                }
                else {
                    ++it; 
                }
            }
            if (selectedGun != 0) {
                Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
                RenderMesh2D(meshes[romb.color], shaders["VertexColor"], romb.modelMatrix);
            }
            for (auto it = guns.begin(); it != guns.end(); ) {
               RenderMesh2D(meshes[it->color], shaders["VertexColor"], it->modelMatrix);
               if (it->hp == 0) {
                   it->minimize(deltaTimeSeconds);
                   for (int i = 0; i < 3; ++i) {
                       for (int j = 0; j < 3; ++j) {
                           int index = i * 3 + j;
                           int minX = 140 + i * 120;
                           int maxX = 240 + i * 120;
                           int minY = 380 + j * 120;
                           int maxY = 480 + j * 120;
                           if (it->x >= minX && it->x <= maxX && it->y >= minY && it->y <= maxY)
                               occupied[index] = 0;
                       }
                   }
               }
               if (it->time <= 0)
                   it = guns.erase(it);
               else {
                   ++it;
               }
                
                
                
            }
                 
           if (starTimer < 0) {
               Star star1 = Star(rand() % 1000, rand() % 600);
               stars.push_back(star1);
               starTimer = rand() % 4;        
           }
           for (auto it = stars.begin(); it != stars.end(); it++) {
               if(it->alive)
               RenderMesh2D(meshes["star2"], shaders["VertexColor"], it->modelMatrix);
           }

           for (int i = 0; i < starNo; i++) {
               modelMatrix = glm::mat3(1);
               if(i < 9)
               modelMatrix *= transform2D::Translate(820 + i * 40, resourceRows[0]);
               else if(i < 18)
                    modelMatrix *= transform2D::Translate(820 + (i - 9) * 40, resourceRows[1]);
               else modelMatrix *= transform2D::Translate(820 + (i - 18) * 40, resourceRows[2]);
               modelMatrix *= transform2D::Scale(5, 5);
               RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
           }

           for (int i = 0; i < guns.size(); i++) {
               if (guns[i].trage && timer <= 0) {
                   Bullet bullet = Bullet(guns[i].x, guns[i].y);
                   bullets.push_back(bullet);
                   timer = 5;
               }
           }

           for (int i = 0; i < bullets.size(); i++) {
               bullets[i].move();
               RenderMesh2D(meshes["star1"], shaders["VertexColor"], bullets[i].modelMatrix);
           }
    }
     else {
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(700, 400);
         modelMatrix *= transform2D::Scale(40, 40);
         RenderMesh2D(meshes["Crucifix"], shaders["VertexColor"], modelMatrix);
        }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_R)
        hp = 3;
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (selectedGun != 0) {
        mouseCoordsX = mouseX;
        mouseCoordsY = 720 - mouseY;
    }
        
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_3) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int index = i * 3 + j;
                int minX = 140 + i * 120;
                int maxX = 240 + i * 120;
                int minY = 380 + j * 120;
                int maxY = 480 + j * 120;

                if (mouseX >= minX && mouseX <= maxX && mouseY >= minY && mouseY <= maxY) {
                    occupied[index] = 0;
                    for (auto it = guns.begin(); it != guns.end(); it++) {
                        if (mouseX >= it->x - 50 && mouseX <= it->x + 50 && 720 - mouseY >= it->y - 50 && 720 - mouseY <= it->y + 50)
                            it->hp = 0;
                    }
                }
            }
        }
    }

    else {
        for (auto it = stars.begin(); it != stars.end(); ) {
            if (mouseX >= it->x && mouseX <= it->x + 50 && 720 - mouseY >= it->y && 720 - mouseY <= it->y + 50) {
                it = stars.erase(it);
                starNo++;
            }
            else {
                ++it;
            }
        }
        if (mouseX >= 20 && mouseX <= 120 && mouseY >= 10 && mouseY <= 120 && starNo >= 1) {
            selectedGun = 1;
        }
        else
            if (mouseX >= 220 && mouseX <= 320 && mouseY >= 10 && mouseY <= 120 && starNo >= 2) {
                selectedGun = 2;

            }
            else if (mouseX >= 420 && mouseX <= 520 && mouseY >= 10 && mouseY <= 120 && starNo >= 2) {
                selectedGun = 3;

            }
            else if (mouseX >= 620 && mouseX <= 720 && mouseY >= 10 && mouseY <= 120 && starNo >= 3) {
                selectedGun = 4;
            }
    }

}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (mouseX >= 140 && mouseX <= 240 && mouseY >= 380 && mouseY <= 480 && occupied[0] == 0) {
        mouseCoordsX = 175;
        mouseCoordsY = 720 - 430;
        if (selectedGun == 1) {
            //occupied[0] = 1;
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
            //occupied[0] = 1;
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
            //occupied[0] = 1;
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
            //occupied[0] = 1;
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        
    }
    else if (mouseX >= 140 && mouseX <= 240 && mouseY >= 500 && mouseY <= 600 && occupied[1] == 0) {
        mouseCoordsX = 175;
        mouseCoordsY = 720 - 550;
        if (selectedGun == 1) {
            //occupied[1] = 1;
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
            //occupied[1] = 1;
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
            //occupied[1] = 1;
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
            //occupied[1] = 1;
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
    }
    else if (mouseX >= 140 && mouseX <= 240 && mouseY >= 620 && mouseY <= 720 && occupied[2] == 0) {
        mouseCoordsX = 175;
        mouseCoordsY = 720 - 670;
        if (selectedGun == 1) {
            //occupied[2] = 1;
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
            //occupied[2] = 1;
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
            //occupied[2] = 1;
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
            //occupied[2] = 1;
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
    }
    else if (mouseX >= 260 && mouseX <= 360 && mouseY >= 380 && mouseY <= 480 && occupied[3] == 0) {
        mouseCoordsX = 295;
        mouseCoordsY = 720 - 430;
        if (selectedGun == 1) {
            //occupied[3] = 1;
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
           // occupied[3] = 1;
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
           // occupied[3] = 1;
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
           // occupied[3] = 1;
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
    }
    else if (mouseX >= 260 && mouseX <= 360 && mouseY >= 500 && mouseY <= 600 && occupied[4] == 0)
    {
        mouseCoordsX = 295;
        mouseCoordsY = 720 - 550;
        if (selectedGun == 1) {
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
    }
    else if (mouseX >= 260 && mouseX <= 360 && mouseY >= 620 && mouseY <= 720 && occupied[5] == 0)
    {
        mouseCoordsX = 295;
        mouseCoordsY = 720 - 670;
        if (selectedGun == 1) {
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
    }
    else if (mouseX >= 380 && mouseX <= 480 && mouseY >= 380 && mouseY <= 480 && occupied[6] == 0)
    {
        mouseCoordsX = 415;
        mouseCoordsY = 720 - 430;
        if (selectedGun == 1) {
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 1;
            guns.push_back(romb);
        }
    }
    else if (mouseX >= 380 && mouseX <= 480 && mouseY >= 500 && mouseY <= 600 && occupied[7] == 0)
    {
        mouseCoordsX = 415;
        mouseCoordsY = 720 - 550;
        if (selectedGun == 1) {
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 2;
            guns.push_back(romb);
        }
    }
    else if (mouseX >= 380 && mouseX <= 480 && mouseY >= 620 && mouseY <= 720 && occupied[8] == 0)
    {
        mouseCoordsX = 415;
        mouseCoordsY = 720 - 670;
        if (selectedGun == 1) {
            starNo--;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 2) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 3) {
            starNo -= 2;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
        if (selectedGun == 4) {
            starNo -= 3;
            Romb romb = Romb(selectedGun, mouseCoordsX, mouseCoordsY);
            romb.line = 3;
            guns.push_back(romb);
        }
    }
    selectedGun = 0;
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
