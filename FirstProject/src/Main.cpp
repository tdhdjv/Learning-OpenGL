#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

#include "vendor/std_image/std_image.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "GameObjects/Constructs.h"
#include "GameObjects/Mesh.h"
#include "GameObjects/MeshFactory.h"
#include "GameObjects/Camera.h"

#include "GLObjects/FrameBuffer.h"
#include "GLObjects/Texture.h"
#include "GLObjects/Renderer.h"
#include "GLObjects/ErrorCheck.h"

unsigned int loadCubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    return textureID;
}

GLFWwindow* configGLFW() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(1000, 800, "My Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }
    return window;
}

void configOpenGLSettings() {
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
}

void processInput(GLFWwindow *window, float deltaTime, Camera &camera) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera.setYaw(camera.getYaw() + deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera.setYaw(camera.getYaw() - deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera.setPitch(camera.getPitch() + deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera.setPitch(camera.getPitch() - deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.setPosition(camera.getPosition() + camera.getFront() * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.setPosition(camera.getPosition() - camera.getFront() * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.setPosition(camera.getPosition() + camera.getRight() * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.setPosition(camera.getPosition() - camera.getRight() * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.setPosition(camera.getPosition() + glm::vec3(0.0, 1.0, 0.0) * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.setPosition(camera.getPosition() - glm::vec3(0.0, 1.0, 0.0) * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        std::cout << camera.getPosition().x << ", " << camera.getPosition().y << ", " << camera.getPosition().z << std::endl;
    }

}

int main() {
    GLFWwindow* window = configGLFW();
    if (window == NULL) {
        return -1;
    }

    configOpenGLSettings();

    Texture wood = Texture("FirstProject/res/image/shiny wood/albedo.png", GL_RGB);
    Texture metallicMap = Texture("FirstProject/res/image/shiny wood/metallic.png", GL_RED);
    Texture smoothnessMap = Texture("FirstProject/res/image/shiny wood/roughness.jpg", GL_RED);
    Texture normalMap = Texture("FirstProject/res/image/toy_box/toy_box_normal.png", GL_RGB);
    Texture depthMap = Texture("FirstProject/res/image/toy_box/toy_box_disp.png", GL_RGBA);
    Texture trans = Texture("FirstProject/res/image/trans.png", GL_RGBA);
    wood.bind(0);
    metallicMap.bind(1);
    smoothnessMap.bind(2);
    normalMap.bind(3);
    depthMap.bind(4);

    Shader shader("FirstProject/res/shaders/Vertex.vert", "FirstProject/res/shaders/Fragment.frag");
    shader.bind();
    Shader lightShader("FirstProject/res/shaders/LightVert.vert", "FirstProject/res/shaders/LightFrag.frag");
    lightShader.bind();
    Shader outLineShader("FirstProject/res/shaders/Stencil.vert", "FirstProject/res/shaders/Stencil.frag");
    outLineShader.bind();

    std::shared_ptr<Mesh> mesh1 = std::make_unique<Mesh>(createCubeMesh());
    std::shared_ptr<Mesh> mesh2 = std::make_unique<Mesh>(createCubesphereMesh(16));
    std::shared_ptr<Mesh> mesh3 = std::make_unique<Mesh>(createQuad(0, {0,0,-1}, {1,0,0}));

    mesh1->setPosition({ 0,0,5 });
    mesh2->setPosition({ 0,0,3 });
    mesh3->setPosition({ 0,0,1 });

    Renderer renderer;

    //camera
    Camera camera;

    //matrix

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shader.bind(); // don't forget to activate/use the shader before setting uniforms!
    
    std::vector<DirectionalLight> dirLightSources = {
        //{glm::vec3(0.0, 1.0, 1.0), glm::vec3(5.5, 5.5, 5.5)},
        //{glm::vec3(1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0)},
        //{glm::vec3(-1.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0)},
        //{glm::vec3(1.0, -1.0, -1.0), glm::vec3(1.0, 1.0, 1.0)}
    };

    std::vector<PointLight> pointLightSources {
        {glm::vec3(0.0, 5.0,2.0), glm::vec3(100.0, 100.0, 100.0)},
        {glm::vec3(0.0, -14.0, 4.0), glm::vec3(100.0, 100.0, 100.0)},
        {glm::vec3(1.0, 2.0, 10.0), glm::vec3(100.0, 100.0, 100.0)},
    };

    shader.setUniformDirectionalLights(dirLightSources);
    shader.setUniformPointLights(pointLightSources);
    shader.setUniform3f("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
    shader.setUniform1i("albedoMap", 0);
    shader.setUniform1i("metallicMap", 1);
    shader.setUniform1i("roughnessMap", 2);
    shader.setUniform1i("normalMap", 3);
    shader.setUniform1i("depthMap", 4);

    bool moveCam = false;

    double lastTime = glfwGetTime();
    float deltaTime = 0;

    FrameBuffer frameBuffer = FrameBuffer();
    frameBuffer.bindColorBufferTexture(10);
    
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    unsigned int quadIndex[] = {
        2, 1, 0,
        3, 2, 0,
    };

    Shader geo = Shader("FirstProject/res/shaders/Normal.vert", "FirstProject/res/shaders/Normal.frag", "FirstProject/res/shaders/NormalGeo.glsl");

    VertexBuffer vbo = VertexBuffer(quadVertices, sizeof(quadVertices));
    IndexBuffer ebo = IndexBuffer(quadIndex, sizeof(quadIndex));
    VertexArray vao;
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    vao.setBuffer(vbo, ebo, layout);


    Shader frameBufferShader("FirstProject/res/shaders/FrameBuffer.vert", "FirstProject/res/shaders/FrameBuffer.frag");

    frameBufferShader.bind();
    frameBufferShader.setUniform1i("screenTexture", 10);
    frameBufferShader.setUniform2f("resolution", 1000.0f, 800.0f);
    //sky box
    std:: vector<std::string> faces
    {
        "FirstProject/res/image/skybox/right.jpg",
        "FirstProject/res/image/skybox/left.jpg",
        "FirstProject/res/image/skybox/top.jpg",
        "FirstProject/res/image/skybox/bottom.jpg",
        "FirstProject/res/image/skybox/front.jpg",
        "FirstProject/res/image/skybox/back.jpg",
    };

    unsigned int cubemapTexture = loadCubemap(faces);

    Shader skyBoxShader("FirstProject/res/shaders/SkyBox.vert", "FirstProject/res/shaders/SkyBox.frag");
    skyBoxShader.bind();
    skyBoxShader.setUniform1i("skybox", 9);
    std::shared_ptr<Mesh> skyBoxMesh = mesh1;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        deltaTime = (float)(glfwGetTime() - lastTime);
        lastTime = glfwGetTime();
        //compute
        processInput(window, deltaTime, camera);

        //uniforms
        shader.bind();
        shader.setUniform3f("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        shader.setUniformMat4f("view", camera.getViewMat());
        shader.setUniformMat4f("projection", projection);

        // render onto the frameBuffer 
        frameBuffer.bind();
        GLCall(glClearColor(0.4f, 0.6f, 0.7f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

        //first pass
        renderer.render(shader, *mesh1);
        renderer.render(shader, *mesh2);

        //light objects
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        lightShader.bind();
        lightShader.setUniformMat4f("view", camera.getViewMat());
        lightShader.setUniformMat4f("projection", projection);
        
        renderer.renderPointLight(lightShader, pointLightSources[0]);
        renderer.renderPointLight(lightShader, pointLightSources[1]);
        renderer.renderPointLight(lightShader, pointLightSources[2]);

        //skybox
        glDepthFunc(GL_LEQUAL);
        glCullFace(GL_BACK);

        skyBoxShader.bind();
        //removes the 4th row, column of the matrix to remove the translation
        glm::mat4 noTransView = glm::mat4(glm::mat3(camera.getViewMat()));
        skyBoxShader.setUniformMat4f("view", noTransView);
        skyBoxShader.setUniformMat4f("projection", projection);

        skyBoxMesh->bind();

        unsigned int count = skyBoxMesh->getIndexCount();
        GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));

        glDepthFunc(GL_LESS);
        glCullFace(GL_FRONT);


        //draw Normals
        geo.bind();
        geo.setUniformMat4f("view", camera.getViewMat());
        geo.setUniformMat4f("projection", projection);

        mesh1->bind();
        geo.setUniformMat4f("model", mesh1->getModelMat());
        count = mesh1->getIndexCount();
        GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));


        mesh2->bind();
        geo.setUniformMat4f("model", mesh2->getModelMat());
        count = mesh2->getIndexCount();
        GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));


        mesh3->bind();
        geo.setUniformMat4f("model", mesh3->getModelMat());
        count = mesh3->getIndexCount();
        GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));


        //transparent objects
        trans.bind(0);
        GLCall(glActiveTexture(GL_TEXTURE1));
        glBindTexture(GL_TEXTURE_2D, 0);
        GLCall(glActiveTexture(GL_TEXTURE2));
        glBindTexture(GL_TEXTURE_2D, 0);
        GLCall(glActiveTexture(GL_TEXTURE3));
        glBindTexture(GL_TEXTURE_2D, 0);
        GLCall(glActiveTexture(GL_TEXTURE4));
        glBindTexture(GL_TEXTURE_2D, 0);
        renderer.render(shader, *mesh3);
        wood.bind(0);
        metallicMap.bind(1);
        smoothnessMap.bind(2);
        normalMap.bind(3);
        depthMap.bind(4);

        //post processing
        frameBufferShader.bind();
        vao.bind();
        GLCall(glDisable(GL_DEPTH_TEST));

        frameBuffer.unBind();
        GLCall(glClearColor(0.4f, 0.6f, 0.7f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

        glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, NULL);
        GLCall(glEnable(GL_DEPTH_TEST));

        GLCall(glClearColor(0.4f, 0.6f, 0.7f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

        GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glBindBuffer(GL_FRAMEBUFFER, 0);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

