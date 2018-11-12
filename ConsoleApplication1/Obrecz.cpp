#include "Obrecz.h"
#define _USE_MATH_DEFINES
#include <math.h>



Obrecz::Obrecz(int iloscSegmentow, float groboscObreczy):
	groboscObreczy(groboscObreczy),
	iloscSegmentow(iloscSegmentow)
{
	///nadawanie wartosci zmiennym
	iloscWierzcholkow = iloscSegmentow * 4;
	iloscElementow = 24 * iloscSegmentow; //8 trojkatow na segment * 3 elemnty na trojkat
	rozmiarTablicyWierzcholkow = iloscWierzcholkow * 8 * sizeof(float);
	rozmiarTablicyElementow = iloscElementow * sizeof(int);
	

	///alokacja pamieci
	tablicaWierzcholkow = new float[iloscWierzcholkow * 8];
	tablicaElementow = new int[iloscElementow];

	tablicaDlugosciSzprych = new float[iloscSegmentow];

	///wypelnianie tablicy wierzcholkow
	for (int i = 0; i < iloscSegmentow; i++)//jeden cykl to wypelnienie calego segmentu czyli czterech wierzcholkow wiec 32= 4 weirzcholki* 8 atrybutow w wierzcholku
	{
		//zmienne pomocnicze
		float kat = (float)i / (float)iloscSegmentow * 2 * M_PI;//bez rzutowania na float zawsze wychodzilo 0
		float sinus = sin(kat);
		float cosinus = cos(kat);
		
		//wierzcholek przedni wewnetrzny//////////////////////////////////////////////
		//wspolrzedne ST(tekstura)				//wzpolrzedne XYZ
		tablicaWierzcholkow[32 * i + 6] =		tablicaWierzcholkow[32 * i] = sinus;
		tablicaWierzcholkow[32 * i + 7] =		tablicaWierzcholkow[32 * i + 1] = cosinus;
												tablicaWierzcholkow[32 * i + 2] = -groboscObreczy/2;//zeby obrecz byla symetryczna wzgledem plaszczyzny XY
		//wspolrzedne RGB
		tablicaWierzcholkow[32 * i + 3] = 1;
		tablicaWierzcholkow[32 * i + 4] = 0;
		tablicaWierzcholkow[32 * i + 5] = 0;


		//wierzcholek przedni zewnetrzny///////////////////////////////////////////////////
		//wspolrzedne ST(tekstura)				//wzpolrzedne XYZ
		tablicaWierzcholkow[32 * i + 14] = 		tablicaWierzcholkow[32 * i + 8] = sinus* (groboscObreczy+1);
		tablicaWierzcholkow[32 * i + 15] = 		tablicaWierzcholkow[32 * i + 9] = cosinus* (groboscObreczy+1);
												tablicaWierzcholkow[32 * i + 10] = -groboscObreczy/2;
		//wspolrzedne RGB
		tablicaWierzcholkow[32 * i + 11] = 0;
		tablicaWierzcholkow[32 * i + 12] = 1;
		tablicaWierzcholkow[32 * i + 13] = 0;


		//wierzcholek tylny zewnetrzny/////////////////////////////////////////////////////////
		//wspolrzedne ST(tekstura)				//wzpolrzedne XYZ
		tablicaWierzcholkow[32 * i + 22] =		tablicaWierzcholkow[32 * i + 16] = sinus * (groboscObreczy + 1);
		tablicaWierzcholkow[32 * i + 23] =		tablicaWierzcholkow[32 * i + 17] = cosinus * (groboscObreczy + 1);
												tablicaWierzcholkow[32 * i + 18] = groboscObreczy/2;
		//wspolrzedne RGB
		tablicaWierzcholkow[32 * i + 19] = 0;
		tablicaWierzcholkow[32 * i + 20] = 0;
		tablicaWierzcholkow[32 * i + 21] = 1;		
		

		//wierzcholek tylny wewnetrzny///////////////////////////////////////////////////////////
		//wspolrzedne ST(tekstura)				//wzpolrzedne XYZ
		tablicaWierzcholkow[32 * i + 30] =		tablicaWierzcholkow[32 * i + 24] = sinus;
		tablicaWierzcholkow[32 * i + 31] =		tablicaWierzcholkow[32 * i + 25] = cosinus;
												tablicaWierzcholkow[32 * i + 26] = groboscObreczy / 2;
		//wspolrzedne RGB
		tablicaWierzcholkow[32 * i + 27] = 1;
		tablicaWierzcholkow[32 * i + 28] = 1;
		tablicaWierzcholkow[32 * i + 29] = 1;
		
		
		
	}


	///wypelnianie tablicy elementow
	for (int i = 0; i < iloscSegmentow; i++)//w karzdym cyklu formowane sa trojkaty dla itego segmetu
	{
		for (int j = 0; j < 4; j++)
		{
			tablicaElementow[i * 24 + (j + 4) * 3] = tablicaElementow[i * 24 + j * 3] = (4 * i + j);//i przesuwa o 24 elementy bo w segmecie jest 8 trojkotow po 3 wierzcholki kazdy
			tablicaElementow[i * 24 + (j + 4) * 3 + 1] = tablicaElementow[i * 24 + j * 3 + 1] = (4 * i + (1 + j) % 4);
			tablicaElementow[i * 24 + j * 3 + 2] = (4 * i + 4 + j) % iloscWierzcholkow;
			tablicaElementow[i * 24 + (j + 4) * 3 + 2] = ((4 * i + iloscWierzcholkow - 4) % iloscWierzcholkow) + ((1 + j) % 4);
		}
	}


	///wypelnianie tablicyDlugosciSzprych
	for (int i = 0; i < iloscSegmentow; i++)
		tablicaDlugosciSzprych[i] = 1;
}

Obrecz::~Obrecz()
{
}

void Obrecz::regulujSzpryche(int ktora, float dlugosc)
{

	
		//ustawianie glugosci szprychy
		tablicaDlugosciSzprych[ktora] = dlugosc;
		
		float I = 0, II = 0, III = 0, IV = 0, V = 0, VI = 0, OPx=0, OLx=0, OPy=0, OLy=0, OPz=0, OLz=0, Ox=0, Oy=0, Oz=0;
		
	//sumowanie wspolrzednych z uwzglednieniem naciagu prawych szprych
	for (int i=0, j = iloscSegmentow / 2 + iloscSegmentow % 2; i < j; i++)//pierwsza szprycha jest prawa
	{
		OPx += tablicaWierzcholkow[64 * i] * tablicaDlugosciSzprych[i * 2];
		OPy += tablicaWierzcholkow[64 * i + 1] * tablicaDlugosciSzprych[i * 2];
		OPz += tablicaWierzcholkow[64 * i + 2] * tablicaDlugosciSzprych[i * 2];
		//I += tablicaWierzcholkow[64 * i + 1]*tablicaDlugosciSzprych[i*2];//y
		//II += -tablicaWierzcholkow[64 * i + 2] * tablicaDlugosciSzprych[i * 2];

		//III += tablicaWierzcholkow[64 * i + 2] * tablicaDlugosciSzprych[i * 2];
		//IV += -tablicaWierzcholkow[64 * i] * tablicaDlugosciSzprych[i * 2];

		//V += tablicaWierzcholkow[64 * i] * tablicaDlugosciSzprych[i * 2];
		//VI += -tablicaWierzcholkow[64 * i] * tablicaDlugosciSzprych[i * 2];
	}
	
	//sumowanie wspolrzednych z uwzglednieniem naciagu lewych szprych
	for (int i=1, j = iloscSegmentow / 2 + 1; i < j; i++)
	{
		OLx += tablicaWierzcholkow[32 * (i * 2 - 1)] * tablicaDlugosciSzprych[i * 2 - 1];
		OLy += tablicaWierzcholkow[32 * (i * 2 - 1) + 1] * tablicaDlugosciSzprych[i * 2 - 1];
		OLz += tablicaWierzcholkow[32 * (i * 2 - 1) + 2] * tablicaDlugosciSzprych[i * 2 - 1];

		//I +=   tablicaWierzcholkow[32 * (i*2-1) + 1] * tablicaDlugosciSzprych[i * 2-1];//
		//II += tablicaWierzcholkow[32 * (i * 2 - 1) + 2] * tablicaDlugosciSzprych[i * 2-1];

		//III -= tablicaWierzcholkow[32 * (i * 2 - 1) + 2] * tablicaDlugosciSzprych[i * 2-1];//
		//IV += tablicaWierzcholkow[32 * (i * 2 - 1)] * tablicaDlugosciSzprych[i * 2-1];//

		//V -=tablicaWierzcholkow[32 * (i * 2 - 1)] * tablicaDlugosciSzprych[i * 2-1];
		//VI += tablicaWierzcholkow[32 * (i * 2 - 1) + 1] * tablicaDlugosciSzprych[i * 2-1];
	}

	//wypelnianie pomocniczych zmiennych 
	Ox = OPx - OLx;
	Oy = OPy - OLy;	
	Oz = OPz - OLz;
		
	//obliczanie katow obrotow
	katY = atan((Oz*Oz)/(Oy*Ox));//alfa
	if (Oz == 0)
		katX=M_PI/2;
	else
	katX = atan(sin(katY)*(Oy/Oz));//fi
	
}
			