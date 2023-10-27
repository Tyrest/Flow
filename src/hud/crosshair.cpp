#include "crosshair.h"

const float Crosshair::triforce_vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 1.0f, 0.0f,    // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 1.0f, 0.0f,     // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.0f, 1.0f, 0.0f,  // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.0f, 1.0f, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.0f, 1.0f, 0.0f,  // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 1.0f, 0.0f,     // Inner down
};

const uint Crosshair::triforce_indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Upper triangle
    5, 4, 1  // Lower right triangle
};

Crosshair::Crosshair(const Shader &shader, float size, float thickness, const glm::vec3 &color)
    : shader(shader), size(size), thickness(thickness), color(color)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // 1. bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 2. copy vertices array into buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(triforce_vertices), triforce_vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triforce_indices), triforce_indices, GL_STATIC_DRAW);
    // 3. set vertex attribute pointers
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)nullptr);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Crosshair::draw(const Camera &camera)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, camera.Position + camera.Front * 0.2f);
    model = glm::rotate(model, -glm::radians(camera.Yaw) + glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, -glm::radians(camera.Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(size * 0.2f));
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(triforce_indices), GL_UNSIGNED_INT, 0);
}