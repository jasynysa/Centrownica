#include "Kamera.h"



Kamera::Kamera(glm::fvec3 kameraPozycja, glm::fvec3 gora) :
	kameraPozycja(kameraPozycja),
	gora(gora),
	kameraKierunek(0),
	kameraGora(0),
	kameraBok(0)
{
}


glm::mat4 Kamera::przesun(glm::fvec3 przesuniecie, glm::fvec3 kameraKierunek)
{
	kameraPozycja += kameraBok * przesuniecie.x + kameraGora * przesuniecie.y + kameraKierunek * przesuniecie.z;
	
	kameraGora = glm::normalize(gora - glm::dot(gora, kameraKierunek)*kameraKierunek);
	kameraBok = glm::normalize(glm::cross(kameraGora, kameraKierunek));

	//wypelnianie macierzy widoku
	glm::mat4 macierzWidoku(1);
	macierzWidoku[0] = glm::fvec4(kameraBok, 0);
	macierzWidoku[1] = glm::fvec4(kameraGora, 0);
	macierzWidoku[2] = glm::fvec4(kameraKierunek, 0);
	//obliczanie odwrotnosci macierzy
	macierzWidoku = glm::transpose(macierzWidoku);//odwrotnosc macierzy jest trasformacja z przstrzeni swiata do przestrzeni kamery
												  //tanslacja
	macierzWidoku[3] = macierzWidoku * glm::fvec4(kameraPozycja, 1);

	return macierzWidoku;
}

Kamera::~Kamera()
{
}
