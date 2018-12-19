#pragma once
#include"glm/glm.hpp"

class Oddzialywanie
{
public:
	int idWierzcholka;
	float dlugoscSprezyny;
};

class Obrecz
{
public:
	Obrecz(int iloscSegmentow, float groboscObreczy);
	~Obrecz();


	///model grafiki
	float groboscObreczy;//jako czesc promienia obreczy
	float* tablicaWierzcholkow;
	//int* tablicaElementow;
	int tablicaElementow[1000];
	int iloscWierzcholkow;
	int iloscElementow;
	int iloscElementowSzprych;
	int iloscSegmentow;
	int rozmiarTablicyWierzcholkow;
	int rozmiarTablicyElementow;


	///model fizyki
	void regulujSzpryche(int ktora, float dlugosc);
	void fizyka(float dCzas);

	glm::fvec3* tablicaSil;//tablica sil ktore dzialaja na wierzcholki
	glm::fvec3* tablicaPredkosci;//tablica predkosci wierzcholkow
	Oddzialywanie** tablicaOddzialywan;//tablica opiosuje odzialywania miedzy wierzcholkami
	float* tablicaDlugosciSzprych;


};

