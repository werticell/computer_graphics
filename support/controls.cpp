#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "controls.hpp"

namespace support {

glm::mat4 view_matrix;
glm::mat4 projection_matrix;

glm::mat4 GetViewMatrix() {
  return view_matrix;
}
glm::mat4 GetProjectionMatrix() {
  return projection_matrix;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 5);
// Initial horizontal angle : toward -Z
float horizontal_angle = 3.14f;
// Initial vertical angle : none
float vertical_angle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f;  // 3 units / second
float mouse_speed = 0.005f;

glm::vec3 GetPosition() {
  return position;
}

void ComputeMatricesFromInputs(GLFWwindow* window) {
  // glfwGetTime is called only once, the first time this function is called
  static double last_time = glfwGetTime();

  // Compute time difference between current and last frame
  double current_time = glfwGetTime();
  float delta_time = float(current_time - last_time);

  // Get mouse position
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  // Reset mouse position for next frame
  glfwSetCursorPos(window, 1024 / 2, 768 / 2);

  // Compute new orientation
  horizontal_angle += mouse_speed * float(1024 / 2 - xpos);
  vertical_angle += mouse_speed * float(768 / 2 - ypos);

  // Direction : Spherical coordinates to Cartesian coordinates conversion
  glm::vec3 direction(cos(vertical_angle) * sin(horizontal_angle),
                      sin(vertical_angle),
                      cos(vertical_angle) * cos(horizontal_angle));

  // Right vector
  glm::vec3 right = glm::vec3(sin(horizontal_angle - 3.14f / 2.0f), 0,
                              cos(horizontal_angle - 3.14f / 2.0f));

  // Up vector
  glm::vec3 up = glm::cross(right, direction);

  // Move forward
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    position += direction * delta_time * speed;
  }
  // Move backward
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    position -= direction * delta_time * speed;
  }
  // Strafe right
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    position += right * delta_time * speed;
  }
  // Strafe left
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    position -= right * delta_time * speed;
  }

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit
  // <-> 100 units
  projection_matrix = glm::perspective(initialFoV, 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  view_matrix = glm::lookAt(position, position + direction, up);

  // For the next frame, the "last time" will be "now"
  last_time = current_time;
}
}  // namespace support