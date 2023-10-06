#include "shape.h"

glm::mat4 Shape::transform() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, rotationAxis);
    model = glm::scale(model, glm::vec3(size));
    return model;
}