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
  int main_radius = 8.0, tube_radius = 2.0;
  float angle_main_segment = 2.0 * M_PI / nr_main_segment;
  float angle_tube_segment = 2.0 * M_PI / nr_tube_segment;

  for (size_t i = 0; i < nr_main_segment + 1; i++) {

    float phi = i * angle_main_segment;

    for (size_t j = 0; j < nr_tube_segment + 1; j++) {

      float theta = j * angle_tube_segment;

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

      colors.push_back({0.5f * cos(phi), 0.5f * sin(phi), 0.5f * sin(theta)});

      if (i != nr_main_segment && j != nr_tube_segment) {
        int face_index = i * (nr_tube_segment + 1) + j;
        int face_index_tube = face_index + nr_tube_segment;
        faces.push_back(
            {face_index_tube + 1, face_index_tube + 2, face_index + 1});
        faces.push_back({
            face_index,
            face_index_tube + 1,
            face_index + 1,
        });
      }
    }
  }

  for (size_t i = 0; i < faces.size(); i++) {
    glm::vec3 u = positions[faces[i].y] - positions[faces[i].x];
    glm::vec3 v = positions[faces[i].z] - positions[faces[i].x];
    faceNormals.push_back(glm::normalize(glm::cross(u, v)));
  }

  for (size_t i = 0; i < positions.size(); i++) {
    positions[i] += glm::vec3(offset) * normals[i];
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
