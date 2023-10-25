// #include "objectManager.h"

// ObjectManager::ObjectManager()
// {
//     this->camera = nullptr;
//     this->window = nullptr;
// }

// ObjectManager::~ObjectManager()
// {
//     for (auto shape : this->shapes)
//     {
//         delete shape;
//     }
// }

// void ObjectManager::add(Shape *shape)
// {
//     this->shapes.push_back(shape);
// }

// void ObjectManager::draw()
// {
//     glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//     glm::mat4 view = camera->GetViewMatrix();
//     for (auto shape : this->shapes)
//     {
//         shape->draw(*this->camera, this->camera->getProjection(), this->camera->getView());
//     }
// }

// void ObjectManager::update(float deltaTime);
// void ObjectManager::processInput(float deltaTime);
// void ObjectManager::setCamera(Camera *camera);
// void ObjectManager::setWindow(GLFWwindow *window);