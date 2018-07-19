#pragma once
#include "glm/glm.hpp"
class Kamera
{
public:
	Kamera(glm::fvec3 kameraPozycja, glm::fvec3 gora);
	~Kamera();
	
	glm::mat4 przesun(glm::fvec3 przesuniecie, glm::fvec3 KameraKierunek);
	
private:
	glm::fvec3 gora;
	//baza kamery
	glm::fvec3 kameraKierunek;
	glm::fvec3 kameraGora;
	glm::fvec3 kameraBok;
	
	glm::fvec3 kameraPozycja;
};

