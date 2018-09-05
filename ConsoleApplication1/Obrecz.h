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

	glm::fvec3* tablicaSil;//tablica w ktorej przechowywane sa coœ jakby si³y dzia³aj¹ce na poszczegolne punkty, jednak nie zmieniaja one predkosci punktow, tylko ich po³o¿enie, wiêc bardziej przypomina to prêdkoœæ
	//glm::fvec3 tablicaSil[200];
	int** tablicaOddzialywan;
	float* tablicaDlugosciSzprych;

	float silaMax;
	float przesuniecieMax;

};

