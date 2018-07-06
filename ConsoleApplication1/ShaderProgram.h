#pragma once
#include "glew.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include "glm\glm.hpp"
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:

	GLuint programID;

	ShaderProgram(const char* sciezkaVS, const char* sciezkaFS);

	void uzyj();

	void setUniform(const char * nazwa,  glm::mat4 macierzTransformacji);




	~ShaderProgram();
};

