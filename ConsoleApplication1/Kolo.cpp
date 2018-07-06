#include "Kolo.h"
#define _USE_MATH_DEFINES
#include <math.h>




Kolo::Kolo(int dokladnosc)
{

	///nadawanie wartosci zmiennym
	int iloscWierzcholkowNaKole = pow(2, dokladnosc);
	iloscWierzcholkow = iloscWierzcholkowNaKole + 1;
	iloscElementow = 3 * iloscWierzcholkowNaKole;
	rozmiarTablicyWierzcholkow = sizeof(float) * 8 * iloscWierzcholkow;
	rozmiarTablicyElementow = sizeof(float)*iloscElementow;
	/*rozmiarTablicyElementow = sizeof(tablicaElementow);
	rozmiarTablicyWierzcholkow = sizeof(tablicaWierzcholkow);*/
	

	///alokacja pamieci
	tablicaWierzcholkow = new float[8*iloscWierzcholkow];//razy 8 bo wierzcholek sklada sie z 8 floatow
	tablicaElementow = new int[iloscElementow];
	
	
	///wypelnianie tablicyWierzcholkow
	//nadawanie wartosci pierwszemu wierzcholku, ktory jest w srodku kola
	for (int i = 0; i < 6; i++)
		tablicaWierzcholkow[i] = 0;//X, Y, Z, R, G, B
	tablicaWierzcholkow[6] = 0.5;//S
	tablicaWierzcholkow[7] = 0.5;//T
	
	//nadawanie wartosci wierzcholka na okregu
	for (int i = 1; i < iloscWierzcholkowNaKole + 1; i++)
	{
		//zmienne pomocnicze
		float sinus = sin((2 * M_PI) / iloscWierzcholkowNaKole * i);
		float cosinus = cos((2 * M_PI) / iloscWierzcholkowNaKole * i);
		//wproadzanie x-ow do tablicyWierzcholkow
		tablicaWierzcholkow[8 * i] = cosinus;
		//wprowadzanie y-ow do tablicyWierzcholkow
		tablicaWierzcholkow[8 * i + 1] = sinus;
		//wprowadzanie z-ow 
		tablicaWierzcholkow[8 * i + 2] = 0;
		//wprowadzanie RGB
		tablicaWierzcholkow[8 * i + 3] = 1;
		tablicaWierzcholkow[8 * i + 4] = 1;
		tablicaWierzcholkow[8 * i + 5] = 1;
		//wprowadzanie S
		tablicaWierzcholkow[8 * i + 6] = sinus / 2 + 0.5;
		//wprowadzanie T
		tablicaWierzcholkow[8 * i + 7] = cosinus / 2 + 0.5;
	}


	///wypelnianie tablicyElementow
	for (int i = 0; i < iloscWierzcholkowNaKole; i++)
	{
		tablicaElementow[3 * i] = 0;
		tablicaElementow[3 * i + 1] = i + 1;
		tablicaElementow[3 * i + 2] = i + 2;
	}
	tablicaElementow[iloscElementow - 1] = 1;
	//przykladowa tablica elementow dla 4 wierzcholkow
	//0,1,2
	//0,2,3
	//0,3,4
	//0,4,1



}

Kolo::~Kolo()
{
	delete[] tablicaWierzcholkow;
	delete[] tablicaElementow;
}
