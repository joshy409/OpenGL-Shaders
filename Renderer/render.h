#pragma once

#include "glew/GL/glew.h"
#include "glm/glm.hpp"


struct vertex {
	glm::vec4 pos;
	glm::vec4 color;
	glm::vec2 uv;
};

struct color {
};

struct geometry {
	GLuint vao, vbo, ibo; //buffers
	GLuint size; //index count
};

struct shader {
	GLuint program;
};

struct texture {
	GLuint handle;
	unsigned width, height, channels;
};

geometry makeGeometry(vertex * verts, size_t vertCount, unsigned * indices, size_t indexCount);

void freeGeometry(geometry &geo);

shader makeShader(const char * vertSoucre, const char * fragSource);

void freeShader(shader & shad);

void draw(const shader& shad, const geometry &geo);

void setUniform(const shader &shad, GLuint location, const glm::mat4 & value);
void setUniform(const shader &shad, GLuint location, const texture &value, int textureSlot);

texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char *pixels);
void freeTexture(texture & tex);
texture loadTexture(const char * imagePath);

void GLAPIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *message,
	const void *userParam);