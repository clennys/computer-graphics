#include "Cube.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
namespace cgCourse {
Cube::Cube() : Shape() {
  // set geometry with respect to local origin
  positions = {
      {-1.0f, -1.0f, -1.0f}, // index 0
      {-1.0f, -1.0f, 1.0f},  {-1.0f, 1.0f, 1.0f},  {-1.0f, 1.0f, -1.0f},

      {1.0f, 1.0f, 1.0f}, // index 4
      {1.0f, -1.0f, 1.0f},   {1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, -1.0f},

      {-1.0f, -1.0f, -1.0f}, // index 8
      {1.0f, -1.0f, -1.0f},  {1.0f, -1.0f, 1.0f},  {-1.0f, -1.0f, 1.0f},

      {1.0f, 1.0f, 1.0f}, // index 12
      {1.0f, 1.0f, -1.0f},   {-1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, 1.0f},

      {-1.0f, -1.0f, -1.0f}, // index 16
      {-1.0f, 1.0f, -1.0f},  {1.0f, 1.0f, -1.0f},  {1.0f, -1.0f, -1.0f},

      {1.0f, 1.0f, 1.0f}, // index 20
      {-1.0f, 1.0f, 1.0f},   {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}};

  colors = {{0.8f, 0.0f, 0.0f}, {0.8f, 0.0f, 0.0f},
            {0.8f, 0.0f, 0.0f}, {0.8f, 0.0f, 0.0f},

            {0.8f, 0.8f, 0.0f}, {0.8f, 0.8f, 0.0f},
            {0.8f, 0.8f, 0.0f}, {0.8f, 0.8f, 0.0f},

            {0.0f, 0.8f, 0.0f}, {0.0f, 0.8f, 0.0f},
            {0.0f, 0.8f, 0.0f}, {0.0f, 0.8f, 0.0f},

            {0.0f, 0.0f, 0.8f}, {0.0f, 0.0f, 0.8f},
            {0.0f, 0.0f, 0.8f}, {0.0f, 0.0f, 0.8f},

            {0.0f, 0.8f, 0.8f}, {0.0f, 0.8f, 0.8f},
            {0.0f, 0.8f, 0.8f}, {0.0f, 0.8f, 0.8f},

            {0.8f, 0.0f, 0.8f}, {0.8f, 0.0f, 0.8f},
            {0.8f, 0.0f, 0.8f}, {0.8f, 0.0f, 0.8f}};

  normals = {{-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
             {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},

             {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},
             {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},

             {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
             {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},

             {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},
             {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},

             {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
             {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},

             {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},
             {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f}};

  /* TODO Task 2 set the texture coordinates for the cube similar
   *       to the positions array. After you set the texture coordinates
   *       for this object try to access them in the shader and
   *       check by color output if they are ok. You can also
   *       compare your results in the end with the final image
   *       so that the texture orientation is done right.
   *
   */
  texCoords = {
      {0.f, 0.f},                                     // 0
      {0.f, 1.f}, {1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f}, // 4
      {0.f, 1.f}, {1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f}, // 8
      {0.f, 1.f}, {1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f}, // 12
      {0.f, 1.f}, {1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f}, // 16
      {0.f, 1.f}, {1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f}, // 20
      {0.f, 1.f}, {1.f, 1.f}, {1.f, 0.f},
  };

  // TODO END

  faces = {{0, 1, 2},    {2, 3, 0},    {4, 5, 6},    {6, 7, 4},
           {8, 9, 10},   {10, 11, 8},  {12, 13, 14}, {14, 15, 12},
           {16, 17, 18}, {18, 19, 16}, {20, 21, 22}, {22, 23, 20}};

  /* TODO Task 2 add the tangent vectors for the cube here to
   *       to the tangent arrays
   */

  // TODO END
}
} // namespace cgCourse
