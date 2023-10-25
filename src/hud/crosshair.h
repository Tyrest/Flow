#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../shader.h"
#include "../camera.h"

class Crosshair
{
public:
    Crosshair(const Shader &shader, float size, float thickness, const glm::vec3 &color);

    void draw(const Camera &camera);

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

private:
    Shader shader;
    float size;
    float thickness;
    glm::vec3 color;

    static const float triforce_vertices[];
    static const uint triforce_indices[];
};
