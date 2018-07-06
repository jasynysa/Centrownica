#pragma once

///klasa generuje tablice wierzcholkow i tablice elementow dla denej dokladnosci kola
class Kolo
{
public:
	Kolo(int dokladnosc);
	~Kolo();

	float* tablicaWierzcholkow;
	int* tablicaElementow;
	/*float tablicaWierzcholkow[1000];
	int tablicaElementow[100];*/
	int iloscWierzcholkow;
	int iloscElementow;
	int rozmiarTablicyWierzcholkow;
	int rozmiarTablicyElementow;
	
};

