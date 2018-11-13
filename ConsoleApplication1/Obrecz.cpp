#include "Obrecz.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>



Obrecz::Obrecz(int iloscSegmentow, float groboscObreczy):
	groboscObreczy(groboscObreczy),
	iloscSegmentow(iloscSegmentow)
{

	///nadawanie wartosci zmiennym
	iloscWierzcholkow = iloscSegmentow * 4;
	iloscElementow = 24 * iloscSegmentow; //8 trojkatow na segment * 3 elemnty na trojkat
	rozmiarTablicyWierzcholkow = iloscWierzcholkow * 8 * sizeof(float);
	rozmiarTablicyElementow = iloscElementow * sizeof(int);
	iloscElementowSzprych = iloscSegmentow * 2;


	///alokacja pamieci
	//grafika
	tablicaWierzcholkow = new float[iloscWierzcholkow * 8];
	tablicaElementow = new int[iloscElementow];
	tablicaElementowSzprychy = new int[iloscElementowSzprych];

	//fizyka
	tablicaPredkosci = new glm::fvec3[iloscWierzcholkow];
	tablicaSil = new glm::fvec3[iloscWierzcholkow];
	tablicaOddzialywan = new Oddzialywanie*[iloscWierzcholkow];
	for (int i = 0; i < iloscWierzcholkow; i++)
	{
		tablicaOddzialywan[i] = new Oddzialywanie[9];//bo kazdy wierzcholek oddzialowuje na 9 innych wierzcholkow
	}
	tablicaDlugosciSzprych = new float[iloscSegmentow];


	///zerowanie tablicy predkosci
	for (int i = 0; i < iloscWierzcholkow; i++)
		tablicaPredkosci[i]=glm::fvec3(0);


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
			tablicaElementow[i * 24 + (j + 4) * 3] =		tablicaElementow[i * 24 + j * 3] = (4 * i + j);//i przesuwa o 24 elementy bo w segmecie jest 8 trojkotow po 3 wierzcholki kazdy
			tablicaElementow[i * 24 + (j + 4) * 3 + 1] =	tablicaElementow[i * 24 + j * 3 + 1] = (4 * i + (1 + j) % 4);
															tablicaElementow[i * 24 + j * 3 + 2] = (4 * i + 4 + j)%iloscWierzcholkow;
			tablicaElementow[i * 24 + (j + 4) * 3 + 2] = ((4 * i + iloscWierzcholkow - 4) % iloscWierzcholkow) + ((1 + j) % 4);
		}
	}


	///wypelnianie tablicy elementow szprych


	///wypelnianie tablicy oddzialywan
	for (int i = 0; i < iloscWierzcholkow; i++)
	{
		//zmienna pomocnicza
		int pierwszyWierzSegmentu = ((int)(i / 4)) * 4;
		//wyznaczanie wierzcholkow z aktualnego segmentu
		for (int j = 0; j <3 ; j++)
		{
			tablicaOddzialywan[i][j].idWierzcholka = pierwszyWierzSegmentu + (i + 1 + j) % 4; //dziwaczny sposob na uzyskanie wierzcholka z aktualnego segmentu
			tablicaOddzialywan[i][j].dlugoscSprezyny =
				//wyznaczanie doleglocsi miedzy wierzcholkami: oddzialywojacym i na ktory dziala sila
				glm::distance
				(
					glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2]),//pozycaj wierzcholka oddzialujacego
					glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
				);
		}
		//wyznaczanie wierzcholkow z kolejnego segmentu
		tablicaOddzialywan[i][3].idWierzcholka = (i + 4) % iloscWierzcholkow;
		tablicaOddzialywan[i][3].dlugoscSprezyny =
			glm::distance
			(
				glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2]),//pozycaj wierzcholka oddzialujacego
				glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][3].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][3].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][3].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
			);
		tablicaOddzialywan[i][4].idWierzcholka = (pierwszyWierzSegmentu + 4 + ((i + 1) % 4)) % iloscWierzcholkow;
		tablicaOddzialywan[i][4].dlugoscSprezyny =
			glm::distance
			(
				glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2]),//pozycaj wierzcholka oddzialujacego
				glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][4].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][4].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][4].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
			);
		tablicaOddzialywan[i][5].idWierzcholka = (pierwszyWierzSegmentu + 4 + ((i + 3) % 4)) % iloscWierzcholkow;
		tablicaOddzialywan[i][5].dlugoscSprezyny =
			glm::distance
			(
				glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2]),//pozycaj wierzcholka oddzialujacego
				glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][5].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][5].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][5].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
			);
		//wyznaczanie wierzcholkow z poprzedniego segmenu
		tablicaOddzialywan[i][6].idWierzcholka = (i + iloscWierzcholkow-4) % iloscWierzcholkow;
		tablicaOddzialywan[i][6].dlugoscSprezyny =
			glm::distance
			(
				glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2]),//pozycaj wierzcholka oddzialujacego
				glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][6].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][6].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][6].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
			);
		tablicaOddzialywan[i][7].idWierzcholka = (pierwszyWierzSegmentu + iloscWierzcholkow - 4 + ((i + 1) % 4)) % iloscWierzcholkow;
		tablicaOddzialywan[i][7].dlugoscSprezyny =
			glm::distance
			(
				glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2]),//pozycaj wierzcholka oddzialujacego
				glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][7].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][7].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][7].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
			);
		tablicaOddzialywan[i][8].idWierzcholka = (pierwszyWierzSegmentu + iloscWierzcholkow - 4 + ((i + 3) % 4)) % iloscWierzcholkow;
		tablicaOddzialywan[i][8].dlugoscSprezyny =
			glm::distance
			(
				glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2]),//pozycaj wierzcholka oddzialujacego
				glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][8].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][8].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][8].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
			);
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
	///ustawianie glugosci szprychy
	tablicaDlugosciSzprych[ktora] += dlugosc;
}


void Obrecz::fizyka(float dCzasA)
{
	for (int i = 1; i <= 10; i++)
	{
		float dCzas = dCzasA * i / 10;
		///zmiana polozenia (przesuwanie) wierzcholkow w oparciu o przedkosc i dCzas
		for (int i = 0; i < iloscWierzcholkow; i++)
		{


			{
				tablicaWierzcholkow[8 * i] += tablicaPredkosci[i].x*dCzas;
				tablicaWierzcholkow[8 * i + 1] += tablicaPredkosci[i].y*dCzas;
				tablicaWierzcholkow[8 * i + 2] += tablicaPredkosci[i].z*dCzas;
			}


		}


		///obliczanie sil dzalajach na wierzcholki przy aktualnej konfiguracji
		//zerowanie tablicySil
		for (int i = 0; i < iloscWierzcholkow; i++)
		{
			tablicaSil[i] = glm::fvec3(0);
		}

		//oddzialowanie szprych
		for (int i = 0; i < iloscSegmentow; i++)
		{//parzyste szprychy zamocowane sa po dodatniej stronie osi Z, a nieparzyste po ujemnej
			tablicaSil[i * 4] =(float)0.01*
				glm::normalize
				(
					glm::fvec3(0, 0, groboscObreczy* std::pow((-1), i))
					-
					glm::fvec3(tablicaWierzcholkow[32 * i], tablicaWierzcholkow[32 * i + 1], tablicaWierzcholkow[32 * i + 2])
				)
				*
				(
					glm::distance
					(
						glm::fvec3(tablicaWierzcholkow[32 * i], tablicaWierzcholkow[32 * i + 1], tablicaWierzcholkow[32 * i + 2]),
						glm::fvec3(0, 0, groboscObreczy* std::pow((-1), i))
					)
					-
					tablicaDlugosciSzprych[i]
						
					);

			tablicaSil[i * 4 + 3] =(float)0.01*
				glm::normalize
				(
					glm::fvec3(0, 0, groboscObreczy* std::pow((-1), i))
					-
					glm::fvec3(tablicaWierzcholkow[32 * i + 24], tablicaWierzcholkow[32 * i + 25], tablicaWierzcholkow[32 * i + 26])
				)
				*
				(
					glm::distance
					(
						glm::fvec3(tablicaWierzcholkow[32 * i + 24], tablicaWierzcholkow[32 * i + 25], tablicaWierzcholkow[32 * i + 26]),
						glm::fvec3(0, 0, groboscObreczy* std::pow((-1), i))
					)
					-
					tablicaDlugosciSzprych[i]
					);

		}

		//oddzalywanie pukntow na siebie
		for (int i = 0; i < iloscWierzcholkow; i++)
		{
			//i-ty punkt oddzialowuje na j-te punkty
			for (int j = 0; j < 9; j++)// j<9 bo kadzdy punkt oddzialowujje na 9 innych
			{
				//wyliczanie sily polega na :
				// 1) wyznaczeniu znormalizowanego wektora pomiedzy punktem na ktory dziala sila a punktem oddzalujacym
				// 2) wyznaczenie odlegloscie miedzy tymi punktami i odjecie promiena okregu zmiany kierunku sil
				// 3) pomno¿enie 1) i 2)
				tablicaSil[tablicaOddzialywan[i][j].idWierzcholka] += //tutaj sumowanie sa wszystkie sily ktore dzialaja na dany punkt
					//1)
					glm::normalize//normalizowanie dlugosci wektora
					(
						glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2])//pozycja wierzcholka odzialujacego
						- //roznica
						glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
					)
					//3)
					*

					//2)
					(
						glm::distance
						(
							glm::fvec3(tablicaWierzcholkow[8 * i], tablicaWierzcholkow[8 * i + 1], tablicaWierzcholkow[8 * i + 2]),//pozycaj wierzcholka oddzialujacego
							glm::fvec3(tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka], tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka + 1], tablicaWierzcholkow[8 * tablicaOddzialywan[i][j].idWierzcholka + 2])//pozycja wierzcholka na ktory dziala sila
						)
						- //odiecie promienia okragu zmiany kierunku sily
						tablicaOddzialywan[i][j].dlugoscSprezyny
						);
			}
		}

		//tarcie
		for (int i = 0; i < iloscWierzcholkow; i++)
		{
			//if (glm::length(tablicaSil[i]) < 0.01 && glm::length(tablicaPredkosci[i]) < 0.01)//dla male sily i predkosci sila jest rowna  0 i predkosc jest rowna 0
			//{
			//	tablicaSil[i] = glm::fvec3(0);
			//	tablicaPredkosci[i] = glm::fvec3(0);
			//}
			//else
			if(tablicaPredkosci[i]!=glm::fvec3(0))
				tablicaSil[i] -= tablicaPredkosci[i] * (float)0.00001 / glm::length(tablicaPredkosci[i]);//sila dziala przeciwnie do kierunku wektora predkosci
		}

		///zmiana predkosci na podstawie sily i dCzas (kazdy wierzcholek ma mase jednostkowa)
		for (int i = 0; i < iloscWierzcholkow; i++)
		{
			tablicaPredkosci[i] += tablicaSil[i] * dCzas;
		}
	}
}
			