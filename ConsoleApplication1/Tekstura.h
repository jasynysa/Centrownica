#pragma once
#include "glew.h"
#include "SOIL\SOIL.h"



class Tekstura
{
public:
	GLuint tekstura;

	Tekstura(const char* sciezkaTek);
	~Tekstura();

private:
	static int idTekstury ;
	

};

