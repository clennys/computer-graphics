#include "MultiLine.h"

#include <cmath>
#include <iostream>

namespace cgCourse {
MultiLine::MultiLine(const std::vector<glm::vec3> &_vertices,
                     const std::vector<glm::vec3> &_normals)
    : Shape() {

  float normal_length = 0.5f;
  for (size_t i = 0; i < _vertices.size(); i++) {
    positions.push_back(_vertices[i]);
    colors.push_back({0.5f, 0.5f, 0.0});

    positions.push_back(_vertices[i] + _normals[i] * normal_length);
    colors.push_back({0.5f, 0.5f, 0.0});

    faces.push_back({2 * i, 2 * i + 1, 2 * i});
  }
}

void MultiLine::draw() const {
  // TODO: complete code to draw the normals as lines
  glBindVertexArray(vaoID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  glDrawElements(GL_LINES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
} // namespace cgCourse
