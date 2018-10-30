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
		
	float is=0, isc = 0, jcc = 0, js = 0, ksc = 0, kcc = 0;
		
	//sumowanie wspolrzednych prawych szprych
	for (int i=0, j = iloscSegmentow / 2 + iloscSegmentow % 2; i < j; i++)//pierwsza szprycha jest prawa
	{
		is += tablicaWierzcholkow[64 * i + 1]*tablicaDlugosciSzprych[i*2];
		isc += -tablicaWierzcholkow[64 * i + 2] * tablicaDlugosciSzprych[i * 2];

		jcc += tablicaWierzcholkow[64 * i + 2] * tablicaDlugosciSzprych[i * 2];
		js += -tablicaWierzcholkow[64 * i] * tablicaDlugosciSzprych[i * 2];

		ksc += tablicaWierzcholkow[64 * i] * tablicaDlugosciSzprych[i * 2];
		kcc += -tablicaWierzcholkow[64 * i] * tablicaDlugosciSzprych[i * 2];
	}
	
	//sumowanie wspolrzednych lewych szprych
	for (int i=1, j = iloscSegmentow / 2 + 1; i < j; i++)
	{

		is +=   tablicaWierzcholkow[32 * (i*2-1) + 1] * tablicaDlugosciSzprych[i * 2];//
		isc += tablicaWierzcholkow[32 * (i * 2 - 1) + 2] * tablicaDlugosciSzprych[i * 2];

		jcc -= tablicaWierzcholkow[32 * (i * 2 - 1) + 2] * tablicaDlugosciSzprych[i * 2];//
		js += tablicaWierzcholkow[32 * (i * 2 - 1)] * tablicaDlugosciSzprych[i * 2];//

		ksc -=tablicaWierzcholkow[32 * (i * 2 - 1)] * tablicaDlugosciSzprych[i * 2];
		kcc += tablicaWierzcholkow[32 * (i * 2 - 1) + 1] * tablicaDlugosciSzprych[i * 2];
	}
	katZ = atan(-jcc * is / js);
	katY = atan(cos(katZ)*jcc / js);
}
			