#include "sphere.h"
#define PI 3.14159265358979323846f

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const float Sphere::test_vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 0.0f, 1.0f,    // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 0.0f, 1.0f,     // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.0f, 0.0f, 1.0f,  // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.0f, 0.0f, 1.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.0f, 0.0f, 1.0f,  // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 0.0f, 1.0f,     // Inner down
};

const uint Sphere::test_indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Upper triangle
    5, 4, 1  // Lower right triangle
};

void Sphere::clearVectors()
{
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<uint>().swap(indices);
}

void Sphere::buildVertices()
{
    clearVectors();

    float x, y, z, xz;                  // vertex position
    float nx, ny, nz, lengthInv = 1.0f; // normal

    float sectorStep = 2 * PI / SECTOR_COUNT;
    float stackStep = PI / STACK_COUNT;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= STACK_COUNT; ++i)
    {
        stackAngle = PI / 2 - i * stackStep; // starting from pi/2 to -pi/2
        xz = cosf(stackAngle) / 2;               // r * cos(u)
        y = sinf(stackAngle) / 2;                // r * sin(u)

        // add (SECTOR_COUNT+1) vertices per stack
        for (int j = 0; j <= SECTOR_COUNT; ++j)
        {
            sectorAngle = j * sectorStep; // starting from 0 to 2pi

            // vertex position
            x = xz * cosf(sectorAngle); // r * cos(u) * cos(v)
            z = xz * sinf(sectorAngle); // r * cos(u) * sin(v)
            addVertex(x, y, z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            addNormal(nx, ny, nz);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for (int i = 0; i < STACK_COUNT; ++i)
    {
        k1 = i * (SECTOR_COUNT + 1); // beginning of current stack
        k2 = k1 + SECTOR_COUNT + 1;  // beginning of next stack

        for (int j = 0; j < SECTOR_COUNT; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                // addIndices(k1, k2, k1 + 1); // k1---k2---k1+1
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (STACK_COUNT - 1))
            {
                // addIndices(k1 + 1, k2, k2 + 1); // k1+1---k2---k2+1
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();
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
    }
}