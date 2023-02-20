#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h>


using namespace std;
using namespace m1;

Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}

void Tema3::Init()
{
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "textures");
    GetSceneCamera()->SetPosition(glm::vec3(0, 0, 0));


    // Load textures

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "ground.jpg").c_str(), GL_REPEAT);
        mapTextures["ground"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "white.png").c_str(), GL_REPEAT);
        mapTextures["white"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "sweater.jpg").c_str(), GL_REPEAT);
        mapTextures["sweater"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "snowboard.jpg").c_str(), GL_REPEAT);
        mapTextures["snowboard"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "present.jpg").c_str(), GL_REPEAT);
        mapTextures["present"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "rock.jpg").c_str(), GL_REPEAT);
        mapTextures["rock"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "steel.jpg").c_str(), GL_REPEAT);
        mapTextures["steel"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "trunk.jpg").c_str(), GL_REPEAT);
        mapTextures["trunk"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "tree.jpg").c_str(), GL_REPEAT);
        mapTextures["tree"] = texture;
    }

    // Load meshes
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cone");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cone.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }



    // Create a simple quad
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(30.f, 0.f, 30.f),    // top right
            glm::vec3(30.f,  0.f, -30.f),    // bottom right
            glm::vec3(-30.f, 0.f, -30.f),    // bottom left
            glm::vec3(-30.f,  0.f, 30.f),    // top left
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };

        vector<glm::vec2> textureCoords
        {
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.f, 1.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(1.f, 0.f)
        };

        vector<unsigned int> indices =
        {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* mesh = new Mesh("square");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("MyShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }


    // Light & material properties
    {
        dirLightPos = glm::vec3(0, 0, 0);
        dirLightColor = glm::vec3(1, 1, 1);

        materialShininess = 30;
        materialKd = 0.25f;
        materialKs = 0.25f;
    }

    mixT = false;
    isGround = false;
    
    tx = 0.f;
    ty = 0.f;
    tz = 0.f;
    orientation = 0.f;

    addObstacle = true;
    wait = false;
    collision = false;
    running = 1;
    score = 0;
    lastCollision = glm::vec3(0, 0, 0);

    cameraRotation = GetSceneCamera()->m_transform->GetWorldRotation();
}

void Tema3::RenderPlayer()
{
    // Camera
    {
        // Camera va urmari jucatorul
        GetSceneCamera()->SetPosition(glm::vec3(tx, ty, tz));
    }

    // Terenul
    {
        glm::mat4 modelMatrix = glm::mat4(1);

        // Translatez terenul sub jucator
        modelMatrix *= translateMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.35f, -0.35f));

        modelMatrix *= movementMatrix;

        modelMatrix *= rotationMatrix;

        isGround = true;
        mixT = true;
        RenderSimpleMesh(meshes["square"], shaders["MyShader"], modelMatrix, mapTextures["ground"], mapTextures["white"]);
        isGround = false;
        mixT = false;
    }

    // Jucatorul
    {
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix *= translateMatrix;

        modelMatrix *= movementMatrix;

        modelMatrix *= rotationMatrix;
        modelMatrix *= playerOrientationMatrix;

        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f, 1.f, 0.75f));

        RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, mapTextures["sweater"]);
    }

    // Schiurile
    {
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix *= translateMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.3, -0.3, 0));

        modelMatrix *= movementMatrix;

        modelMatrix *= rotationMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.3, 0.3, 0));
        modelMatrix *= playerOrientationMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.3, -0.3, 0));


        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.1f, 2.5f));

        RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, mapTextures["snowboard"]);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix *= translateMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.3, -0.3, 0));

        modelMatrix *= movementMatrix;

        modelMatrix *= rotationMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.3, 0.3, 0));
        modelMatrix *= playerOrientationMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.3, -0.3, 0));

        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.1f, 2.5f));

        RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, mapTextures["snowboard"]);
    }
}

void Tema3::RenderObstacles()
{
    // Render obstacol random, adaug cate unul la un interval de timp de 0.5 secunde
    if (running) {
        int decimal = static_cast<int>(Engine::GetElapsedTime() * 10) % 10;

        // decimal reprezinta prima cifra de dupa virgula a lui ElapsedTime.
        // Folosesc variabila 'wait' pentru a astepta pana cand decimal este iar 5.
        // Am nevoie de aceasta deoarece 'decimal' o sa aiba valoare 5 de mai multe
        // ori la rand, dar eu doresc sa adaug un obstacol nou doar odata.
        if (decimal == 6) {
            wait = false;
        }

        if (!wait) {
            if (decimal == 5) {
                addObstacle = true;
                wait = true;
            }
        }

        if (addObstacle) {

            addObstacle = false;
            srand(time(NULL));
            // Aleg un obiect random din cele 4 obstacole posibile
            int object = rand() % 4 + 1;

            // Pentru pozitia random a obiectului, acesta se va genera pe
            // latura de jos a quad-ului folosit pentru teren la un x random intre -20 si 20
            int objX = -20 + rand() % (20 - (-20) + 1);
           
            objMatrix = glm::mat4(1);
            // Translatez obiectul pe marginea de jos a terenului
            objMatrix *= translateMatrix;
            objMatrix = glm::translate(objMatrix, glm::vec3(0, -0.35f, -0.35f));
            objMatrix = glm::translate(objMatrix, glm::vec3(objX, 0, 30));
            objMatrix *= movementMatrix;

            // Rotesc obiectul fata de centrul terenului
            objMatrix = glm::translate(objMatrix, glm::vec3(-objX, 0, -30));
            objMatrix *= rotationMatrix;
            objMatrix = glm::translate(objMatrix, glm::vec3(objX, 0, 30));

            // Il translatez mai sus fata de teren
            objMatrix = glm::translate(objMatrix, glm::vec3(0, 0.35f, 0.35f));

            // Vector folosit pentru coliziuni
            glm::vec3 objPos = glm::vec3(objX + tx, ty - 3 - 16.5, 30 - 11 + tz);

            switch (object) {
            case 1:
                // Copac
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = objMatrix;

                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 1.f, 0.5f));

                Obstacle obs = Obstacle(meshes["box"], shaders["MyShader"], modelMatrix, mapTextures["trunk"], objPos, false);
                obsQueue.push_back(obs);

                modelMatrix = glm::mat4(1);
                modelMatrix = objMatrix;

                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 1.f, 0.5f));

                objPos.y += 1.f;
                Obstacle obs1 = Obstacle(meshes["cone"], shaders["MyShader"], modelMatrix, mapTextures["tree"], objPos, false);
                obsQueue.push_back(obs1);
            }
            break;
            case 2:
                // Piatra
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = objMatrix;

                Obstacle obs = Obstacle(meshes["sphere"], shaders["MyShader"], modelMatrix, mapTextures["rock"], objPos, false);
                obsQueue.push_back(obs);

                modelMatrix = glm::mat4(1);
                modelMatrix = objMatrix;

                modelMatrix = glm::translate(modelMatrix, glm::vec3(0.75f, 0, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f, 1.f, 1.2f));

                objPos.x += 0.75f;
                Obstacle obs1 = Obstacle(meshes["sphere"], shaders["MyShader"], modelMatrix, mapTextures["rock"], objPos, false);
                obsQueue.push_back(obs1);

                modelMatrix = glm::mat4(1);
                modelMatrix = objMatrix;

                modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 0, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

                objPos.x += 1.5f;
                Obstacle obs2 = Obstacle(meshes["sphere"], shaders["MyShader"], modelMatrix, mapTextures["rock"], objPos, false);
                obsQueue.push_back(obs2);
            }
            break;
            case 3:
                // Stalp
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = objMatrix;

                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 3.f, 0.1f));

                objPos.y += 1;
                Obstacle obs = Obstacle(meshes["box"], shaders["MyShader"], modelMatrix, mapTextures["steel"], objPos, false);
                obsQueue.push_back(obs);

                modelMatrix = glm::mat4(1);
                modelMatrix = objMatrix;

                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 2.5, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(2.f, 0.1f, 0.1f));

                objPos.y += 2.5f;
                Obstacle obs1 = Obstacle(meshes["box"], shaders["MyShader"], modelMatrix, mapTextures["steel"], objPos, false);
                obsQueue.push_back(obs1);
            }
            break;
            case 4:
                // Cadou
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = objMatrix;

                Obstacle obs = Obstacle(meshes["box"], shaders["MyShader"], modelMatrix, mapTextures["present"], objPos, true);
                obsQueue.push_back(obs);
            }
            break;
            }
        }
    }

    // Render all obstacles in queue
    {
        for (int i = 0; i < obsQueue.size(); i++) {
            Obstacle obs = obsQueue[i];
            RenderSimpleMesh(obs.mesh, obs.shader, obs.modelMatrix, obs.texture);
        }
    }
}

void Tema3::checkCollisions() 
{
    // Verificam daca playerul s-a lovit de vreun obstacol
    // Pentru verificare putem sa folosim doar coordonatele x si z,
    // deoarece coordonata z a jucatorului este in continua crestere
    // nu putem avea doua instante in care x si z ale jucatorului sa fie
    // egale cu cele ale vreunui obstacol.
    if (running) {
        for (int i = 0; i < obsQueue.size(); i++) {

            collision = false;
            Obstacle obs = obsQueue[i];
            glm::vec3 obsPos = obs.pos;

            if (playerPos.x - 0.5f <= obsPos.x + 0.1f &&
                playerPos.x + 0.5f >= obsPos.x - 0.1f &&
                playerPos.z + 2.5f <= obsPos.z + 0.1f &&
                playerPos.z + 3.5f >= obsPos.z - 0.1f) {
                collision = true;
            }

            if (collision && (obsPos != lastCollision)) {

                // lastCollision este folosit ca sa nu avem mai multe "triggers"
                // cand coliziunea este cu acelasi obiect
                lastCollision = obsPos;
                if (obs.isPresent) {
                    // Cadoul va disparea (il mut la coordonatele default, pana cand acesta o sa fie
                    // automat unrendered)
                    obsQueue[i].modelMatrix = glm::mat4(1);
                    score++;
                } else {
                    // Jucatorul se opreste din miscare
                    running = 0;
                    cout << score << "\n";
                }
            }
        }
    }
}

void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    GetSceneCamera()->SetRotation(cameraRotation);
}

void Tema3::Update(float deltaTimeSeconds)
{
    // Maximul de obstacole. Daca trecem de limita, atunci pop.
    if (obsQueue.size() >= 30) {
        obsQueue.pop_front();
    }

    translateMatrix = glm::mat4(1);
    translateMatrix = glm::translate(translateMatrix, glm::vec3(0, -3, -11));

    // Translatiile sunt sin/cos de 30 deoarece planul este inclinat la 30 de grade
    tx += sin(orientation * M_PI / 180.0f) * deltaTimeSeconds * 7 * running;
    ty -= sin(30.f * M_PI / 180.0f) * deltaTimeSeconds * 7 * running;
    tz += cos(30.f * M_PI / 180.0f) * deltaTimeSeconds * 7 * running;

    movementMatrix = glm::mat4(1);
    movementMatrix = glm::translate(movementMatrix, glm::vec3(tx, ty, tz));

    rotationMatrix = glm::mat4(1);
    rotationMatrix = glm::rotate(rotationMatrix, RADIANS(30.f), glm::vec3(1, 0, 0));

    // Matricea pentru orientarea jucatorului (in urma cursorului)
    playerOrientationMatrix = glm::mat4(1);
    playerOrientationMatrix = glm::rotate(playerOrientationMatrix, RADIANS(orientation), glm::vec3(0, 1, 0));

    RenderPlayer();

    // Vector folosit pentru coliziuni
    playerPos = glm::vec3(tx, ty - 3, tz - 11);

    RenderObstacles();

    // Sursa de lumina directionala
    {
        dirLightPos = glm::vec3(tx, ty + 6, tz - 10);
    }

    checkCollisions();
}


void Tema3::FrameEnd()
{
}


void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    {
        // Set shader uniforms for light properties
        int directional_light_pos = glGetUniformLocation(shader->program, "directional_light_pos");
        glUniform3f(directional_light_pos, dirLightPos.x, dirLightPos.y, dirLightPos.z);

        int directional_light_color = glGetUniformLocation(shader->program, "directional_light_color");
        glUniform3f(directional_light_color, dirLightColor.x, dirLightColor.y, dirLightColor.z);

        // Set eye position (camera position) uniform
        glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
        int eye_position = glGetUniformLocation(shader->program, "eye_position");
        glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

        // Set material property uniforms (shininess, kd, ks) 
        int material_kd = glGetUniformLocation(shader->program, "material_kd");
        glUniform1f(material_kd, materialKd);

        int material_ks = glGetUniformLocation(shader->program, "material_ks");
        glUniform1f(material_ks, materialKs);

        int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
        glUniform1i(material_shininess, materialShininess);
    }

    {
        // Bind model matrix
        GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
        glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        // Bind view matrix
        glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
        int loc_view_matrix = glGetUniformLocation(shader->program, "View");
        glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        // Bind projection matrix
        glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
        int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
        glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // Set other shader uniforms
        int mix_t = glGetUniformLocation(shader->program, "mix_t");
        glUniform1i(mix_t, mixT);

        int move_y = glGetUniformLocation(shader->program, "move_y");
        glUniform1f(move_y, ty);

        int move_x = glGetUniformLocation(shader->program, "move_x");
        glUniform1f(move_x, tx);

        int is_ground = glGetUniformLocation(shader->program, "is_ground");
        glUniform1i(is_ground, isGround);
    }

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
    }

    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);
        
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        
        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
  
}


void Tema3::OnKeyPress(int key, int mods)
{
    // Add key press event
    // Apasarea tastei 'R' restarteaza jocul.
    if (key == GLFW_KEY_R) {
        tx = 0.f;
        ty = 0.f;
        tz = 0.f;
        orientation = 0.f;

        addObstacle = true;
        wait = false;
        collision = false;
        running = 1;
        score = 0;
        lastCollision = glm::vec3(0, 0, 0);

        obsQueue.clear();
    }
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Calculez unghiul dintre pozitia cursorului si o dreapta paralela cu OX
    // care trece prin centrul ferestrei
    glm::ivec2 resolution = window->GetResolution();
    glm::ivec2 windowCenter = glm::ivec2(resolution.x / 2, resolution.y / 2);

    // Calculam doar daca suntem cu cursorul in jumatatea de jos a ferestrei
    if (mouseY > windowCenter.y) {

        glm::ivec2 windowLeftSide = glm::ivec2(0, windowCenter.y);

        glm::vec2 a = glm::vec2(windowCenter.x - windowLeftSide.x, windowCenter.y - windowLeftSide.y);
        glm::vec2 b = glm::vec2(windowCenter.x - mouseX, windowCenter.y - mouseY);

        float newOrientation = acos((a.x * b.x + a.y * b.y) / (glm::length(a) * glm::length(b))) * (180 / M_PI);
        newOrientation -= 90;

        // Se va aplica noua orientatre numai daca este intr-un interval de +- 60 de grade
        if (newOrientation <= 60 && newOrientation >= -60)
            orientation = newOrientation;
    }
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
