#version 410 core
out vec4 FragColor;

uniform vec4 ourColor; // The color of the square

void main()
{
    FragColor = ourColor;
}
