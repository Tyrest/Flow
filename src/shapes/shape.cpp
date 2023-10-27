#include "shape.h"

void Shape::setupShader(const Camera &camera) const
{
    shader.use();
    shader.setVec3("objectColor", color);
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightDir", lightDir);
    shader.setVec3("viewPos", camera.Position);
    shader.setMat4("model", transform());
}

glm::mat4 Shape::transform() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, rotationAxis);
    model = glm::scale(model, glm::vec3(size));
    return model;
}