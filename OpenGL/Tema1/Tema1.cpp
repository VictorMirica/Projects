#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();

    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 center = glm::vec3(0, 0, 0);
    headSize = 25;
    hitboxSize = 150;

    float bodySize = 100;
    float wingSize = 35;
    float beakSize = 10; 

    float lifeSize = 15;
    float bulletSize = 25;
    float scoreSize = 50;
    float weapon1Size = 50;
    float weapon2Size = 15;
    float fireSize = 80;
    float crosshairSize = 10;
    
    // Centrul tringhiului folosit ca corp
    cx = center.x + bodySize / 2;
    cy = center.y + bodySize / 2;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1.5f;

    // Initialize angularStep
    angularStep = 0;
    weaponAngle = 0;

    flag = 1; // flag used for wing flaps
    killed = 0; // 1 if duck was killed
    evaded = 0; // 1 if duck has evaded
    falling = 1; // 0 when duck is falling, to stop wings from flapping

    resX = resolution.x;
    resY = resolution.y;

    // Coordonate random de spawn (random intre ~0 si ~resolutie)
    spawnX = (std::rand() % ((resX - 10) - 10 + 1)) + 10;
    spawnY = 10;

    duckNumber = 1;
    score = 0;
    livesNumber = 3;
    bulletsNumber = 3;

    initialSpeed = 400;
    currentSpeed = 400;
    speedStep = 0;

    time = 0;
    renderFire = 0;
    canHit = 0;

    crosshairX = 0;
    crosshairY = 0;

    // Initialize orientation (valoare random intre dintre unghiurile care merg in sus (0 - 45 si 315 - 360)) (Daca orientation = 0, rata se va misca in sus, daca este PI ea se va misca in jos)
    //                  0
    //           315         45
    //      270         X         90
    //           225         135
    //                 180
    if (rand() % 2) {
        orientation = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (PI / 4)));
    }
    else {
        orientation = (7 * PI / 4) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((2 * PI) - (7 * PI / 4))));
    }

        // Rata
    Mesh* head = transform::CreateCircle("head", center, headSize, glm::vec3(0, 0.5f, 0));
    AddMeshToList(head);

    Mesh* body = transform::CreateTriangle("body", center, bodySize, glm::vec3(0.5f, 0.35f, 0.05f));
    AddMeshToList(body);

    Mesh* wing = transform::CreateTriangle("wing", center, wingSize, glm::vec3(1, 1, 1));
    AddMeshToList(wing);

    Mesh* beak = transform::CreateTriangle("beak", center, beakSize, glm::vec3(1, 0.64f, 0));
    AddMeshToList(beak);

        // HUD
    Mesh* bullet = transform::CreateSquare("bullet", center, bulletSize, glm::vec3(0, 1, 0));
    AddMeshToList(bullet);

    Mesh* life = transform::CreateCircle("life", center, lifeSize, glm::vec3(1, 0, 0));
    AddMeshToList(life);

    Mesh* maxScore = transform::CreateSquare("maxScore", center, scoreSize, glm::vec3(0, 0, 1), false);
    AddMeshToList(maxScore);

    Mesh* currentScore = transform::CreateSquare("currentScore", center, scoreSize, glm::vec3(0, 0, 1));
    AddMeshToList(currentScore);

    Mesh* hitbox = transform::CreateSquare("hitbox", center, hitboxSize, glm::vec3(0, 0, 0), false);
    AddMeshToList(hitbox);

    Mesh* grass = transform::CreateSquare("grass", center, resolution.x, glm::vec3(0.66f, 1, 0));
    AddMeshToList(grass);

    Mesh* weapon = transform::CreateSquare("weapon", center, weapon1Size, glm::vec3(0.82f, 0.7f, 0.55f));
    AddMeshToList(weapon);

    Mesh* weapon2 = transform::CreateSquare("weapon2", center, weapon2Size, glm::vec3(0.5f, 0.5f, 0.5f));
    AddMeshToList(weapon2);

    Mesh* fire = transform::CreateTriangle("fire", center, fireSize, glm::vec3(1, 0, 0));
    AddMeshToList(fire);

    Mesh* crosshair = transform::CreateCircle("crosshair", center, crosshairSize, glm::vec3(1, 0, 0), false);
    AddMeshToList(crosshair);
}

void Tema1::respawnDuck()
{   
    // Verificam din ce cauza dam respawn la rata
    if (evaded == 1) {
        evaded = 0;
        livesNumber--;
    } else if (killed == 1) {
        killed = 0;
        falling = 1;
        score++;
    }

    // Respawn rata la o locatie noua, random
    if (rand() % 2) {
        orientation = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (PI / 4)));
    }
    else {
        orientation = (7 * PI / 4) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((2 * PI) - (7 * PI / 4))));
    }

    spawnX = (std::rand() % ((resX - 10) - 10 + 1)) + 10;

    translateX = 0;
    translateY = -100; // Vrem ca rata sa inceapa "de mai jos"
    angularStep = 0;
    flag = 1;

    bulletsNumber = 3; // Resetam numarul de gloante
    time = 0; // Resetam timpul

    // Incrementeaza viteza
    duckNumber++;
    if (duckNumber == 6) {
        speedStep++;
        duckNumber = 1;
    }

    currentSpeed = initialSpeed + speedStep * initialSpeed / 5;
}

void Tema1::checkState()
{
    // Incrementam timpul, daca a trecut destul timp (~5 secunde), rata va evada
    time++;

    if (time >= 800 && killed == 0) {
        evaded = 1;
    }

    // Am ramas fara vieti sau am castigat (15 rate ucise)
    if (livesNumber == 0 || score == 15) {
        exit(0);
    }

    // Rata a fost ucisa.
    if (killed == 1) {
        orientation = PI;
        bulletsNumber = 3;
    }

    // Am ramas fara gloante
    if (bulletsNumber == 0) {
        evaded = 1;
    }

    // Rata a evadat.
    if (evaded == 1) {
        orientation = 0;
        killed = 0;
    }

}

void Tema1::checkCollision()
{
        // Ciocniri
    // Ciocnirile se fac cand rata ajunge intr-o margine a ecranului cu centrul corpului

    // Marginea de sus   
    if (spawnY + cy + translateY >= resY) {
        // Verificam daca rata a ajuns aici deoarece a evadat
        if (evaded == 1) {
            respawnDuck();
        }
        
        if (evaded == 0) {
            // cadran 1
            if (orientation < 90 * PI / 180) {
                orientation = (180 - orientation * 180 / PI) * PI / 180;
            }
            else {
                // cadran 4
                orientation = (270 - (orientation * 180 / PI - 270)) * PI / 180;
            }
            translateY -= 5;
        }
    }

    // Marginea de jos
    if (spawnY + cy + translateY <= 0) {
        // Verificam daca rata a ajuns aici deoarece a fost ucisa
        if (killed == 1) {
            respawnDuck();
        }

        if (killed == 0) {
            //cadran 2
            if (orientation <= 180 * PI / 180) {
                orientation = (90 - (orientation * 180 / PI - 90)) * PI / 180;
            }
            else {
                // cadran 3
                orientation = (270 + (270 - orientation * 180 / PI)) * PI / 180;
            }
            translateY += 5;
        }
    }

    // Marginea din dreapta
    if (spawnX + cx + translateX >= resX) {
        //cadran 1
        if (orientation <= 90 * PI / 180) {
            orientation = (270 + (90 - orientation * 180 / PI)) * PI / 180;
        }
        else {
            // cadran 2
            orientation = (270 - (orientation * 180 / PI - 90)) * PI / 180;
        }
        translateX -= 5;
    }

    // Marginea din stanga
    if (spawnX + cx + translateX <= 0) {
        //cadran 3
        if (orientation <= 270 * PI / 180) {
            orientation = (90 + (270 - orientation * 180 / PI)) * PI / 180;
        }
        else {
            // cadran 4
            orientation = (360 - orientation * 180 / PI) * PI / 180;
        }
        translateX += 5;
    }
}

void Tema1::drawHUD()
{   
    // Crosshair
    modelMatrix = glm::mat3(1);

    modelMatrix *= transform::Translate(crosshairX, crosshairY);

    RenderMesh2D(meshes["crosshair"], shaders["VertexColor"], modelMatrix);

    // Arma
        // Focul de arma
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(resX / 2 - 15, 185);

    modelMatrix *= transform::Translate(10, -200);
    modelMatrix *= transform::Rotate(weaponAngle);
    modelMatrix *= transform::Translate(-10, 200);

    if (renderFire == 1)
        RenderMesh2D(meshes["fire"], shaders["VertexColor"], modelMatrix);

        // Prima parte a armei
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(resX / 2 + 15, 175);

    modelMatrix *= transform::Translate(10, -200);
    modelMatrix *= transform::Rotate(weaponAngle);
    modelMatrix *= transform::Translate(-10, 200);

    RenderMesh2D(meshes["weapon2"], shaders["VertexColor"], modelMatrix);

        // A doua parte a armei
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(resX / 2, -25);

    modelMatrix *= transform::Translate(25, 0);
    modelMatrix *= transform::Rotate(weaponAngle);
    modelMatrix *= transform::Translate(-25, 0);

    modelMatrix *= transform::Scale(1, 4);

    RenderMesh2D(meshes["weapon"], shaders["VertexColor"], modelMatrix);

    // Iarba
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Scale(1, 0.1f);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    // Vietile
    if (livesNumber >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform::Translate(50, resY - 50);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }
    if (livesNumber >= 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform::Translate(100, resY - 50);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }
    if (livesNumber == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform::Translate(150, resY - 50);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }

    // Gloantele
    if (bulletsNumber >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform::Translate(37.5, resY - 110);
        modelMatrix *= transform::Scale(scaleX, scaleY);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }
    if (bulletsNumber >= 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform::Translate(87.5, resY - 110);
        modelMatrix *= transform::Scale(scaleX, scaleY);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }
    if (bulletsNumber == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform::Translate(137.5, resY - 110);
        modelMatrix *= transform::Scale(scaleX, scaleY);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    // Scorul
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(resX - 300, resY - 100);
    modelMatrix *= transform::Scale(5, 1);
    RenderMesh2D(meshes["maxScore"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(resX - 300, resY - 100);
    modelMatrix *= transform::Scale(score * 0.33f, 1);
    RenderMesh2D(meshes["currentScore"], shaders["VertexColor"], modelMatrix);


}

void Tema1::drawDuck(float deltaTimeSeconds)
{
    // Matricea corespunzatoare intregii rate, folosita la miscarea acesteia
    parentMatrix = glm::mat3(1);

    translateX += deltaTimeSeconds * sin(orientation) * currentSpeed;
    translateY += deltaTimeSeconds * cos(orientation) * currentSpeed;
    parentMatrix *= transform::Translate(translateX, translateY);


    // Capul
        // Translatia initiala
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(spawnX + cx, spawnY + cy * 2);
    // Inmultirea cu matricea parinte
    modelMatrix *= parentMatrix;
    // Orientarea initiala (rotatia fata de centrul triunghiului Corp)
    modelMatrix *= transform::Translate(0, -cy);
    modelMatrix *= transform::Rotate(-orientation);
    modelMatrix *= transform::Translate(0, cy);

    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

    // Corpul
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(spawnX, spawnY);

    modelMatrix *= parentMatrix;

    modelMatrix *= transform::Translate(cx, cy);
    modelMatrix *= transform::Rotate(-orientation);
    modelMatrix *= transform::Translate(-cx, -cy);

    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    // Aripa dreapta
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(spawnX + cx + cx / 2, spawnY + cy);

    modelMatrix *= parentMatrix;

    modelMatrix *= transform::Translate(-cx / 2, 0);
    modelMatrix *= transform::Rotate(-orientation);
    modelMatrix *= transform::Translate(cx / 2, 0);

    // Miscarea continua a aripii drepte
    if (angularStep >= 1.5f) {
        flag = -1;
    }
    if (angularStep <= -1.5f) {
        flag = 1;
    }
    angularStep += deltaTimeSeconds * 4 * flag * falling;
    modelMatrix *= transform::Rotate(angularStep);

    RenderMesh2D(meshes["wing"], shaders["VertexColor"], modelMatrix);

    // Aripa stanga
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(spawnX + cx - cx / 2, spawnY + cy);

    modelMatrix *= parentMatrix;

    modelMatrix *= transform::Translate(cx / 2, 0);
    modelMatrix *= transform::Rotate(-orientation);
    modelMatrix *= transform::Translate(-cx / 2, 0);

    // Miscarea continua a aripii  stangi
    modelMatrix *= transform::Rotate(110 * PI / 180); // Inainte de rotatie, dam flip la aripa
    modelMatrix *= transform::Rotate(-angularStep);

    RenderMesh2D(meshes["wing"], shaders["VertexColor"], modelMatrix);

    // Ciocul 
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Translate(spawnX + cx, spawnY + cy * 2 + headSize);

    modelMatrix *= parentMatrix;

    modelMatrix *= transform::Translate(0, -cy - headSize);
    modelMatrix *= transform::Rotate(-orientation);
    modelMatrix *= transform::Translate(0, cy + headSize);

    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

   // Hitbox 
   // Uncomment if you want to see it
   //modelMatrix = glm::mat3(1);
   //modelMatrix *= transform::Translate(spawnX + cx - hitboxSize / 2, spawnY + cy - hitboxSize / 2);

   //modelMatrix *= parentMatrix;

   //RenderMesh2D(meshes["hitbox"], shaders["VertexColor"], modelMatrix);

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.53f, 0.81f, 0.94f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);


}


void Tema1::Update(float deltaTimeSeconds)
{
    
    // Verificam starea ratei (evaded/killed)
    checkState();

    // Verificam daca s-a lovit de o margine
    checkCollision();

    // Deseneaza HUD-ul;
    drawHUD();

    // Deseneaza rata
    drawDuck(deltaTimeSeconds);
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
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{   
    glm::ivec2 resolution = window->GetResolution();

    // Scalam coordonatele mouse-ului la orice resolutie ar avea fereastra
    mouseX = mouseX * resX / resolution.x;
    mouseY = mouseY * resY / resolution.y;

    // Deoarece in functia OnMouseMove, pozitia (0,0) este in coltul stanga sus al ecranului
    // Dar rata are pozitia (0,0) in coltul din stanga jos, x-ul celor doua este identic, dar y-ul 
    // trebuie modificat pentru a putea fi comparate.
    float currentHitboxCenterX = spawnX + cx + translateX;
    float currentHitboxCenterY = spawnY + cy + translateY;
    currentHitboxCenterY = resY - currentHitboxCenterY;

    // Verificam daca putem sa lovim rata
    if (mouseX >= currentHitboxCenterX - hitboxSize / 2 && mouseX <= currentHitboxCenterX + hitboxSize / 2 &&
        mouseY >= currentHitboxCenterY - hitboxSize / 2 && mouseY <= currentHitboxCenterY + hitboxSize / 2) {
         canHit = 1;
    } else {
        canHit = 0;
    }

    // Calculam unghiul armei, aceasta trebuie sa urmareasca cursorul
    weaponAngle = cos(mouseX/300);

    // Coordonatele crosshair-ului, care urmareste cursorul
    crosshairX = mouseX;
    crosshairY = resY - mouseY;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    // Click stanga a fost apasat, daca cursorul se afla in
    // hitbox, rata va fi omorata
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (canHit == 1) {
            killed = 1;
            falling = 0;
        }
        bulletsNumber--;
        renderFire = 1;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    // Odata ce lasam click-ul stang, nu mai trebuie
    // rendat focul care iese din teava armei.
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        renderFire = 0;
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
