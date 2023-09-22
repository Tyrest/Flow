#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos; // Pass the fragment position to the fragment shader
out vec3 Normal;  // Pass the vertex normal to the fragment shader

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate the fragment position in world space
    Normal = mat3(transpose(inverse(model))) * aPos; // Calculate the normal in world space
}
