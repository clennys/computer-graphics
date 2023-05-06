#include "Texture.h"

#include <cstring>
#include <iostream>

#define cimg_display 0
#include <CImg.h>

using namespace cimg_library;

namespace cgCourse {
void Texture::loadFromFile(const std::string &_filename) {
  CImg<unsigned char> img(_filename.c_str());

  int channels = img.spectrum();
  size.x = img.width();
  size.y = img.height();

  img.permute_axes("cxyz");

  /*
   *  TODO Task 2 generate the texture here:
   *        - generate the texture handle and set the variable texhandle
   *        - bind the texture handle
   *        - set the min/mag filter parameter and if it works test if you
   *          see a difference between GL_LINEAR, MIPMAP_LINEAR, NEAREST etc..
   *        - set the texture wrap parameters
   *        - set the texture data with glTexImage2D
   *        - generate mipmaps
   *        - unbind the texture handle (we do this to have a clean state when
   * the function is ending and no textures are bound after this call.) Note
   * that depending on the channels the a different kind of texture might be
   * created, for 4 channels GL_RGBA, for 3 GL_RGB and for one GL_RED. Some
   * operating systems might use GL_BGRA
   */

  // generate the texture handle and set the variable texhandle
  glGenTextures(1, &texhandle);

  // bind the texture handle
  glBindTexture(GL_TEXTURE_2D, texhandle);

  // for 4 channels GL_RGBA, for 3 GL_RGB and for one GL_RED.
  GLenum format;
  switch (channels) {
  case 1:
    format = GL_RED;
    break;
  case 3:
    format = GL_RG8;
    break;
  case 4:
    format = GL_RGBA;
  default:
    break;
  }
  // set the min/mag filter parameter
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // set the texture wrap parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  // set the texture data with glTexImage2D
  glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format,
               GL_UNSIGNED_BYTE, img.data());

  // generate mipmaps
  glGenerateMipmap(GL_TEXTURE_2D);

  // Unbind the texture handle (we do this to have a clean state when
  glBindTexture(GL_TEXTURE_2D, 0);

  // TODO END
}

const GLuint &Texture::getTexHandle() const { return texhandle; }
} // namespace cgCourse
