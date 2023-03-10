#include "Torus.h"
#include <glm/ext/vector_uint3.hpp>
#include <glm/vec3.hpp>
#include <iostream>

// this define and include will enable M_PI from math.h.
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse {
Torus::Torus() : Torus(0.0) {}

Torus::Torus(double offset) {
  /* TODO: Add your code here
   * First create the torus mesh
   * Then offset the vertex positions along the calculated face normals by
   * offset
   *
   * formula:
   * x(theta,phi)  = (R + r*cos(theta))*cos(phi)
   * y(theta,phi)  = (R + r*cos(theta))*sin(phi)
   * z(theta,phi)  = r*sin(theta)
   * theta, phi in [0, 2*M_PI)
   *
   * R is the distance from the center of the tube to the center of the torus
   * r is the radius of the tube.
   * theta, phi are angles which make a full circle, so their values start and
   * end at the same point,
   */

  int nr_main_segment = 20, nr_tube_segment = 20;
  int main_radius = 8, tube_radius = 3;
  float angle_main_segment = 2 * M_PI / nr_main_segment;
  float angle_tube_segment = 2 * M_PI / nr_tube_segment;

  for (size_t i = 0; i < nr_main_segment; i++) {
    float tmp = i * angle_main_segment;
    for (size_t j = 0; j < nr_tube_segment; j++) {
      float theta = (j % nr_tube_segment) * angle_tube_segment;
      for (size_t k = 0; k < 2; k++) {
        float phi = tmp + k * angle_main_segment;
        float x = (main_radius + tube_radius * cos(theta)) * cos(phi);
        float y = (main_radius + tube_radius * cos(theta)) * sin(phi);
        float z = tube_radius * sin(theta);
        positions.push_back({x, y, z});

        /* Normals of points
         * Nx = cos(theta) * cos(phi)
         * Ny = cos(theta) * sin(phi)
         * Nz = sin(theta)
         */

        float nx = cos(theta) * cos(phi);
        float ny = cos(theta) * sin(phi);
        float nz = sin(theta);
        normals.push_back({nx, ny, nz});

        colors.push_back({0.0f, 0.8f, 0.8f});
      }
      theta += angle_tube_segment;
    }
  }
  for (size_t i = 0; i < positions.size(); i += 3) {
    faces.push_back({i % positions.size(), i % positions.size() + 1,
                     i % positions.size() + 2});
  }
  // 	Vec3f A = v1 - v0; // edge 0
  // Vec3f B = v2 - v0; // edge 1
  // Vec3f C = cross(A, B); // this is the triangle's normal
  //
  for (size_t i = 0; i < positions.size(); i++) {
    glm::vec3 u = {positions[i + 1][0] - positions[i][0],
                   positions[i + 1][1] - positions[i][1],
                   positions[i + 1][2] - positions[i][2]};
    glm::vec3 v = {positions[i + 2][0] - positions[i][0],
                   positions[i + 2][1] - positions[i][1],
                   positions[i + 2][2] - positions[i][2]};

    faceNormals.push_back(glm::cross(u, v));
  }
}

void Torus::draw() {
  glBindVertexArray(vaoID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
} // namespace cgCourse
