#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "sphere.h"
#define PI 3.14159265358979323846f

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const float Sphere::cube_vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f};

Sphere::Sphere(const Shader &shader, const glm::vec3 &lightDir, const glm::vec3 &color, const glm::vec3 &position, float angle, const glm::vec3 &rotationAxis) : Shape(shader, lightDir, color, position, angle, rotationAxis)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    // 1. bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 2. copy vertices array into buffer's memory
    buildVertices(2, 2);
    for (int i = 0; i < toDraw.size() / 6; i++)
    {
        std::cout << "x: " << toDraw[i * 6] << "\ty: " << toDraw[i * 6 + 1] << "\tz: " << toDraw[i * 6 + 2] << "\tnx: " << toDraw[i * 6 + 3] << "\tny: " << toDraw[i * 6 + 4] << "\tnz: " << toDraw[i * 6 + 5] << "\n";
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(toDraw.data()), toDraw.data(), GL_STATIC_DRAW);
    // 3. set vertex attribute pointers
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)nullptr);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // unbind vertex array
    glBindVertexArray(0);
}

Sphere::~Sphere()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Sphere::draw(const Camera &camera, const glm::mat4 &projection, const glm::mat4 &view) const
{
    shader.use();
    shader.setVec3("objectColor", color);
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightDir", lightDir);
    shader.setVec3("viewPos", camera.Position);

    shader.setMat4("model", transform());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

unsigned int Sphere::VAO = 0;
unsigned int Sphere::VBO = 0;

void Sphere::clearVectors()
{
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(interleavedVertices);
    std::vector<float>().swap(toDraw);
}

void Sphere::buildVertices(int sectorCount, int stackCount)
{
    clearVectors();

    float x, y, z, xy;                  // vertex position
    float nx, ny, nz, lengthInv = 1.0f; // normal
    // float s, t;                         // texCoord

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep; // starting from pi/2 to -pi/2
        xy = cosf(stackAngle);               // r * cos(u)
        z = sinf(stackAngle);                // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep; // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)
            addVertex(x, y, z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            // addNormal(nx, ny, nz);
            addNormal(1.0f, 1.0f, 1.0f);

            // // vertex tex coord between [0, 1]
            // s = (float)j / sectorCount;
            // t = (float)i / stackCount;
            // addTexCoord(s, t);
        }
    }

    std::vector<unsigned int> indices;

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1); // beginning of current stack
        k2 = k1 + sectorCount + 1;  // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                // addIndices(k1, k2, k1 + 1); // k1---k2---k1+1
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1))
            {
                // addIndices(k1 + 1, k2, k2 + 1); // k1+1---k2---k2+1
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    std::cout << "Indices size: " << indices.size() << "\n";

    // generate interleaved vertex array as well
    buildInterleavedVertices();

    for (int i = 0; i < indices.size(); i++)
    {
        toDraw.push_back(vertices[indices[i] * 3]);
        toDraw.push_back(vertices[indices[i] * 3 + 1]);
        toDraw.push_back(vertices[indices[i] * 3 + 2]);
        toDraw.push_back(normals[indices[i] * 3]);
        toDraw.push_back(normals[indices[i] * 3 + 1]);
        toDraw.push_back(normals[indices[i] * 3 + 2]);
    }
}

void Sphere::buildInterleavedVertices()
{
    std::vector<float>().swap(interleavedVertices);

    std::size_t i, j;
    std::size_t count = vertices.size();
    for (i = 0, j = 0; i < count; i += 3, j += 2)
    {
        interleavedVertices.push_back(vertices[i]);
        interleavedVertices.push_back(vertices[i + 1]);
        interleavedVertices.push_back(vertices[i + 2]);

        interleavedVertices.push_back(normals[i]);
        interleavedVertices.push_back(normals[i + 1]);
        interleavedVertices.push_back(normals[i + 2]);

        // interleavedVertices.push_back(texCoords[j]);
        // interleavedVertices.push_back(texCoords[j + 1]);
    }
}