#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../shader.h"
#include "../camera.h"
#include "crosshair.h"

class Hud
{
public:
    Hud();

    void draw(const Camera &camera);

private:
    Shader shader;
    Crosshair crosshair;
};
