#pragma once

#include <glm/glm.hpp>


#include <objloader.hpp>

class Doggo {
 public:
  Doggo()
      : vertices_(default_vertices),
        uvs_(default_uvs),
        normals_(default_normals) {
    glm::vec3 offset = RandomDoggoPosition(kMinOffset, kMaxOffset);
    current_center += offset;

    glm::mat4 rotate =
        glm::rotate(glm::mat4(1.0f), float(glm::radians((float)(rand() % 360))),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    for (glm::vec3& vertex : vertices_) {
      vertex = glm::vec3(rotate * glm::vec4(vertex, 1));
      vertex += offset;
    }
  }

  static void LoadDoggoObj(const char* filepath) {
    support::LoadObj(filepath, default_vertices, default_uvs, default_normals);
  }

 public:
  static inline const float kDistanceToCollide = 1;

  std::vector<glm::vec3> vertices_;
  std::vector<glm::vec3> normals_;
  std::vector<glm::vec2> uvs_;
  glm::vec3 current_center{0, 0, 0};

 private:
  glm::vec3 RandomDoggoPosition(int64_t min, int64_t max) {
    double phi = 2 * M_PI * rand() / RAND_MAX;
    int64_t r = min + rand() % (max - min);
    return glm::vec3(r * sin(phi), 0, r * cos(phi));
  }

 private:
  static inline std::vector<glm::vec3> default_vertices;
  static inline std::vector<glm::vec3> default_normals;
  static inline std::vector<glm::vec2> default_uvs;

  static const inline int64_t kMinOffset = 8;
  static const inline int64_t kMaxOffset = 20;
};
