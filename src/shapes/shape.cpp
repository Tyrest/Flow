#include "shape.h"

void Shape::build()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // 1. bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 2. copy vertices array into buffer's memory
    buildVertices();
    glBufferData(GL_ARRAY_BUFFER, getVertices().size() * sizeof(float), getVertices().data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndices().size() * sizeof(uint), getIndices().data(), GL_STATIC_DRAW);
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

    built = true;
}

Shape::~Shape()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Shape::setupShader(const Camera &camera) const
{
    shader.use();
    shader.setVec3("objectColor", color);
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightDir", lightDir);
    shader.setVec3("viewPos", camera.Position);
    shader.setMat4("model", transform());
}

void Shape::draw(const Camera &camera) const
{
    if (!built)
    {
        std::cout << "Shape::draw() called before Shape::build()" << std::endl;
        exit(1);
    }
    setupShader(camera);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, getIndices().size() * sizeof(uint), GL_UNSIGNED_INT, 0);
}

glm::mat4 Shape::transform() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, rotationAxis);
    model = glm::scale(model, glm::vec3(size));
    return model;
}