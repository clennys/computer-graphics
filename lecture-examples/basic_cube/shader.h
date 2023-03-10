//
//  shader.h
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#ifndef SHADER_H
#define SHADER_H

GLuint getShader(const char *filename, bool type);
char* readShaderText(const char *filename);

#endif /* defined(SHADER_H) */
