#include "hud.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Hud::Hud() : shader("assets/hud.vs", "assets/hud.fs"), crosshair(shader, 0.1f, 1.0f, glm::vec3(1.0f))
{
}

void Hud::draw(const Camera &camera)
{
    glDisable(GL_DEPTH_TEST);

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    shader.use();
    shader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightColor", 100.0f, 100.0f, 100.0f);
    shader.setVec3("lightDir", 0.0f, 1.0f, 0.0f);
    shader.setVec3("viewPos", camera.Position);

    crosshair.draw(camera);

    glEnable(GL_DEPTH_TEST);
}