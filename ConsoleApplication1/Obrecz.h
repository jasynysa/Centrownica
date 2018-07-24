#pragma once
class Obrecz
{
public:
	Obrecz(int iloscSegmentow, float groboscObreczy);
	~Obrecz();

	float groboscObreczy;//jako czesc promienia obreczy
	float* tablicaWierzcholkow;
	int* tablicaElementow;
	int iloscWierzcholkow;
	int iloscElementow;
	int rozmiarTablicyWierzcholkow;
	int rozmiarTablicyElementow;
};

