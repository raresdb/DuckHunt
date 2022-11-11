#include "Tema1.h"

using namespace std;
using namespace t1;

Tema1::Tema1()
{
    
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    lives = 3;
    bullets = 3;
    score = 0;

    bird = new bird::Birdy(resolution);

    Mesh* body = bird->body;
    AddMeshToList(body);
    Mesh* leftWing = bird->leftWing;
    AddMeshToList(leftWing);
    Mesh* rightWing = bird->rightWing;
    AddMeshToList(rightWing);
    bird->InitialGeneration();

    pair<vector<VertexFormat>, unsigned int> grass_info =
        obj::Object2D::Rectangle(glm::vec3(0, 0, 0), resolution.x, GRASS_HEIGHT, GRASS_COLOR);
    Mesh* grass = obj::Object2D::CreateMesh("grass", grass_info.first, grass_info.second);
    AddMeshToList(grass);

    pair<vector<VertexFormat>, unsigned int> life =
        obj::Object2D::Circle(glm::vec3(40, resolution.y - 50, 0), 30, HEART_COLOR);
    Mesh* heart = obj::Object2D::CreateMesh("heart", life.first, life.second);
    AddMeshToList(heart);

    pair<vector<VertexFormat>, unsigned int> bullet_info =
        obj::Object2D::Rectangle(glm::vec3(30, resolution.y - 150, 0), 20, 50, BULLET_COLOR);
    Mesh* bullet = obj::Object2D::CreateMesh("bullet", bullet_info.first, bullet_info.second);
    AddMeshToList(bullet);

    pair<vector<VertexFormat>, unsigned int> sky_info =
        obj::Object2D::Rectangle(glm::vec3(0, GRASS_HEIGHT, 0), resolution.x,
            resolution.y - GRASS_HEIGHT, SKY_COLOR);
    Mesh* sky = obj::Object2D::CreateMesh("sky", sky_info.first, sky_info.second);
    AddMeshToList(sky);

    Mesh* maxScoreBar = new Mesh("maxScoreBar");
    vector<unsigned> indices = { 0, 1, 2, 3 };
    vector<VertexFormat> vertices = { glm::vec3(resolution.x - 30, resolution.y - 30, 0),
        glm::vec3(resolution.x - 200, resolution.y - 30, 0) , glm::vec3(resolution.x - 200,
            resolution.y - 50, 0), glm::vec3(resolution.x - 30, resolution.y - 50, 0) };

    maxScoreBar->InitFromData(vertices, indices);
    maxScoreBar->SetDrawMode(GL_LINE_LOOP);
    AddMeshToList(maxScoreBar);

    pair<vector<VertexFormat>, unsigned int> score_bar_info =
        obj::Object2D::Rectangle(glm::vec3(resolution.x - 200, resolution.y - 50, 0),
            170.0 / MAX_SCORE, 20, SCORE_COLOR);
    Mesh* score_bar = obj::Object2D::CreateMesh("score_bar", score_bar_info.first, score_bar_info.second);
    AddMeshToList(score_bar);
}


void Tema1::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (lives && score < MAX_SCORE) {
        lives -= bird->ManageEscapedDucks();

        if (bird->ManageRespawn()) {
            bullets = 3;
        }
    }

    bird->MatrixUpdate(deltaTimeSeconds);

    auto modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1) * tr2D::Translate(-75, 0);

    for (int i = 0; i < lives; i++) {
        modelMatrix *= tr2D::Translate(75, 0);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1) * tr2D::Translate(-75, 0);

    for (int i = 0; i < bullets; i++) {
        modelMatrix *= tr2D::Translate(75, 0);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["maxScoreBar"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < score; i++) {
        RenderMesh2D(meshes["score_bar"], shaders["VertexColor"], modelMatrix);
        modelMatrix *= tr2D::Translate(170.0 / MAX_SCORE, 0);
    }

    modelMatrix = bird->bodyMatrix;
    RenderMesh2D(meshes["birdy"], shaders["VertexColor"], modelMatrix);

    modelMatrix = bird->leftWingMatrix;
    RenderMesh2D(meshes["birdyLeftWing"], shaders["VertexColor"], modelMatrix);

    modelMatrix = bird->rightWingMatrix;
    RenderMesh2D(meshes["birdyRightWing"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["sky"], shaders["VertexColor"], modelMatrix);      
}


void Tema1::FrameEnd()
{
}



void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (!lives) {
        printf("No more lives!\n");
        return;
    }

    if (score == MAX_SCORE) {
        printf("Already won!-> %d p\n", score);
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_2 && bullets && !bird->isDead() && !bird->isEscaped()) {
        if (resolution.y - mouseY < GRASS_HEIGHT) {
            return;
        }
        else {
            bird->try_shoot(glm::vec2(mouseX, mouseY));
            bullets--;
            if (bird->isDead()) {
                score += 1 + bird->getIndex() / 5;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
