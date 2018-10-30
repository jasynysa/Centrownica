#pragma once
#include"glm/glm.hpp"
class Obrecz
{
public:
	Obrecz(int iloscSegmentow, float groboscObreczy);
	~Obrecz();


	///model grafiki
	float groboscObreczy;//jako czesc promienia obreczy
	float* tablicaWierzcholkow;
	int* tablicaElementow;
	int iloscWierzcholkow;
	int iloscElementow;
	int iloscSegmentow;
	int rozmiarTablicyWierzcholkow;
	int rozmiarTablicyElementow;


	///model fizyki
	void regulujSzpryche(int ktora, float dlugosc);
	float katZ, katY;
		

	
	//glm::fvec3 tablicaSil[200];
	float* tablicaDlugosciSzprych;
	

	

};

