// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "stdafx.h"
#include "SDL.h"
#include "glew.h"

#include "chrono"
#include "SOIL\SOIL.h"
#include "glm\glm.hpp"
#include "glm\gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "Kolo.h"
#include "Tekstura.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Transformacja.h"
#include "Kamera.h"


int main(int argc, char* argv[])
{
	///inicjalizacja modolow sdl'a
	SDL_Init(SDL_INIT_EVERYTHING);


	///tworzenie okna
	SDL_Window* okno = SDL_CreateWindow("Moje okno", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);//ustawienia dla kontekstu OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GLContext kontekst= SDL_GL_CreateContext(okno);//tworzenie kontekstu (cokolwiek to znaczy) OpenGL 


	///powiazanie funkcji OpenGL z moim programem
	glewExperimental = GL_TRUE;
	glewInit();


	///dane wierzcholkow
	GLfloat wierzcholki[] = {
		//X		Y		Z		R	G		B	S		T
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,//pierwsza sciana
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,//druga
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,//3
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,//4
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,//5
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,//6
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f , 1.0f, 0.0f, 1.0f,

		
		- 1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//podloga
		1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	
	///elementy czyli kolejnosc rysowania wierzcholkow 
	GLuint elementy[] = {
		0,	1,	2,
		1,	2,	5


	};

	Kolo kolo(10);

	Tekstura kot(".\\res\\obraz.png");
	Tekstura sierpIMlot(".\\res\\sierp.png");
	

	///*///ładowanie obrazu jako tekstury
	//{
	//	int szerokosc, wysokosc, borys;
	//	unsigned char* obraz = SOIL_load_image(".\\res\\obraz.png", &szerokosc, &wysokosc, &borys, SOIL_LOAD_RGB);
	//	if (obraz == 0)
	//		std::cerr << "Nie mozna zaladowac tekstury  " << SOIL_last_result();
	//	else
	//		std::cout << obraz << "  rozmiar obrazu: " << wysokosc << " X " << szerokosc;*/
	//}
	

	///tablica powiazan powina zostac stworzona przed wiazaniem GL_ARRAY_BufFEr(chyba) i wogole przed tworzeneim buforow
	GLuint vertexArrayObject1;
	glGenVertexArrays(1, &vertexArrayObject1);
	GLuint vertexArrayObject2;
	glGenVertexArrays(1, &vertexArrayObject2);
	GLuint vaoKolo;
	glGenVertexArrays(1, &vaoKolo);
	
	
	///element buffor object
	glBindVertexArray(vertexArrayObject1);
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementy), elementy, GL_STATIC_DRAW);

	glBindVertexArray(vaoKolo);
	GLuint eboKolo;
	glGenBuffers(1, &eboKolo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboKolo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, kolo.rozmiarTablicyElementow, kolo.tablicaElementow, GL_STATIC_DRAW);
	

	///bufor wierzcholkow VBO0/////////////////////////////////////////////////////////////////////////////////////////////
	glBindVertexArray(vertexArrayObject1);
	GLuint buforWierzcholkow1;
	glGenBuffers(1, &buforWierzcholkow1);//tworzenie jednego bufora wierzcholkow
	glBindBuffer(GL_ARRAY_BUFFER, buforWierzcholkow1);// zwiazanie czy cos zmiennej albo raczej wzkaznika "buforWierzcholkow" z typem bufora OpenGL "GL_ARRAY_BUFFER"
	glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki), wierzcholki, GL_STATIC_DRAW); // zaladowanie danych do bufora

	glBindVertexArray(vaoKolo);
	GLuint vboKolo;
	glGenBuffers(1, &vboKolo);
	glBindBuffer(GL_ARRAY_BUFFER, vboKolo);
	glBufferData(GL_ARRAY_BUFFER, kolo.rozmiarTablicyWierzcholkow, kolo.tablicaWierzcholkow, GL_STATIC_DRAW); 


	/////tekstura
	//GLuint tekstura;
	//glGenTextures(1, &tekstura);
	//glBindTexture(GL_TEXTURE_2D, tekstura);
	////ustawienia tekstury
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//niebardzo wiem co znaczy to S i T
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	////wczytywanie tekstury
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, szerokosc, wysokosc, 0, GL_RGB, GL_UNSIGNED_BYTE, obraz);
	////tworzenie mipmapy, czyli zbioru tekstur o roznej rozdzielczosci
	//glGenerateMipmap(GL_TEXTURE_2D);


	///tworzenie programu z dwoma shaderami
	ShaderProgram program(".\\res\\VertexShaderSource.VS", ".\\res\\FragmentShaderSource.FS");	


	///informowanie w jaki sposob odczytywac dane z VBO
	//zapisywanie do pierwszego VAO
	glBindVertexArray(vertexArrayObject1);
	glBindBuffer(GL_ARRAY_BUFFER, buforWierzcholkow1);//
	//wiazanie atrbutu "pozycja" z vertexShadera z tablica wierzcholkow
	GLint IdAtrybutuPozycja = glGetAttribLocation(program.programID, "pozycja");
	glVertexAttribPointer(IdAtrybutuPozycja, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);//ta funkcja okresla rodzaj i uklad danych w GL_ARRAY_BUFFER i zwiaze go z atrybutem  "pozycja"
	glEnableVertexAttribArray(IdAtrybutuPozycja);//ta funkcj aktyuje atrybut
	//
	GLint IdAtrybutuKolor = glGetAttribLocation(program.programID, "kolor");
	glVertexAttribPointer(IdAtrybutuKolor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(IdAtrybutuKolor);
	//ustawienia atrybutu "wzpolrzedneTekstury"
	GLint IdAtrybutuWspolrzedneTek = glGetAttribLocation(program.programID, "wspolrzedneTek");
	glVertexAttribPointer(IdAtrybutuWspolrzedneTek, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(IdAtrybutuWspolrzedneTek);
	//zapisywanine do drugiego VAO
	glBindVertexArray(vertexArrayObject2);
	//
	glVertexAttribPointer(IdAtrybutuPozycja, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(IdAtrybutuPozycja);
	//
	glVertexAttribPointer(IdAtrybutuKolor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(IdAtrybutuKolor);
	//
	glVertexAttribPointer(IdAtrybutuWspolrzedneTek, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(IdAtrybutuWspolrzedneTek);
	//zapisywanie do vaoKolo
	glBindVertexArray(vaoKolo);
	//
	glBindBuffer(GL_ARRAY_BUFFER, vboKolo);
	//
	glVertexAttribPointer(IdAtrybutuPozycja, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(IdAtrybutuPozycja);
	//
	glVertexAttribPointer(IdAtrybutuKolor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(IdAtrybutuKolor);
	//
	glVertexAttribPointer(IdAtrybutuWspolrzedneTek, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(IdAtrybutuWspolrzedneTek);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	auto t_start = std::chrono::high_resolution_clock::now();
	auto przelaczeniaProgramu = t_start;
	bool czyOtwarte = true; //zmienna na potrzeby glownej petli programu
	SDL_Event wydarzenie; //zmienna w ktorej sa zapisywane wydarzenia
	glClearColor(1, 1, 0, 0);
	float poprzedni=0;
	float time=0;
	int nrProgramu = 0;
	glm::mat4 macierzPerspektywy = tran::perspektywa(M_PI, 0.1, 1000);//macierz perspektywy
	Kamera kamera(glm::fvec3(0, 0, 0), glm::fvec3(0, 0, 1));

	glEnable(GL_DEPTH_TEST);//włączenie testu głębikosci Który powoduje rysowanie tylko najpłytszego piksela
	glClearColor(1, 0, 0, 1);
	
	int liczbaAtrybutow;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &liczbaAtrybutow);
	std::cout << std::endl << "liczba mozliwych atrybutow: " << liczbaAtrybutow;
	program.uzyj();
	glUniform1i(glGetUniformLocation(program.programID, "tekstura0"), 0);
	glUniform1i(glGetUniformLocation(program.programID, "tekstura1"), 1);

	glBindVertexArray(vertexArrayObject1);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///glowna petla programu
	while (czyOtwarte)
	{



		auto t_now = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		float dCzas = time - poprzedni;
		poprzedni = time;
		////przelacznie programow
		//		
		//		if (std::chrono::duration_cast<std::chrono::duration<float>>(t_now - przelaczeniaProgramu).count() > 1 )
		//		{
		//			
		//			if (nrProgramu == 0)
		//			{
		//				program.uzyj();
		//				nrProgramu = 1;
		//			}
		//			else if (nrProgramu==1)
		//			{
		//				glUseProgram(shaderProgram);
		//				nrProgramu = 0;
		//			}
		//			przelaczeniaProgramu = t_now;
		//		}

		int pozycjaMyszy[2];
		int rozmiarOkna[2];
		SDL_GetMouseState(&pozycjaMyszy[0], &pozycjaMyszy[1]);
		SDL_GetWindowSize(okno, &rozmiarOkna[0], &rozmiarOkna[1]);
		float sinus0 = sin((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 2 * M_PI);
		float cosinus0 = cos((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 2 * M_PI);
		float sinus1= sin((float)pozycjaMyszy[1] / (float)rozmiarOkna[1] * 0.9 * M_PI+0.1);
		float cosinus1 = cos((float)pozycjaMyszy[1] / (float)rozmiarOkna[1] * 0.9 * M_PI+0.1);
		

		///rozne macierze transformacji
		
		////obrot wokol osi Z
		//glm::mat4 macierzObrotuZ(1);
		//macierzObrotuZ[0].x = cosinus0;
		//macierzObrotuZ[0].y = sinus0;
		//macierzObrotuZ[1].x = -sinus0;
		//macierzObrotuZ[1].y = cosinus0;
		//
		////obrot wokol osi X		
		//glm::mat4 macierzObrotuX(1);
		//macierzObrotuX[1].y = cosinus1;
		//macierzObrotuX[1].z = sinus1;
		//macierzObrotuX[2].y = -sinus1;
		//macierzObrotuX[2].z = cosinus1;

		////obrot wokol osi Y
		//glm::mat4 macierzObrotuY(1);
		//macierzObrotuY[0].x = cosinus0;
		//macierzObrotuY[0].z = sinus0;
		//macierzObrotuY[2].x = sinus0;
		//macierzObrotuY[2].z = cosinus0;
		////obrot woklol wektora r(r musi byc jadnostkowy)
		//glm::mat4 macierzObrotuR(1);
		//glm::fvec3 wektorObrotu(0);
		//wektorObrotu.x = cosinus0;
		//wektorObrotu.y = sinus0;
		//float B = 1 - cosinus1;
		////wypelnianie macierzy 		
		//macierzObrotuR[0].x = wektorObrotu.x*wektorObrotu.x*B + cosinus1;
		//macierzObrotuR[0].y = wektorObrotu.x*wektorObrotu.y*B + wektorObrotu.z*sinus1;
		//macierzObrotuR[0].z = wektorObrotu.x*wektorObrotu.z*B - wektorObrotu.y*sinus1;
		//														
		//macierzObrotuR[1].x = wektorObrotu.y*wektorObrotu.x*B - wektorObrotu.z*sinus1;
		//macierzObrotuR[1].y = wektorObrotu.y*wektorObrotu.y*B + cosinus1;
		//macierzObrotuR[1].z = wektorObrotu.y*wektorObrotu.z*B + wektorObrotu.x*sinus1;
		//														
		//macierzObrotuR[2].x = wektorObrotu.z*wektorObrotu.x*B + wektorObrotu.y*sinus1;
		//macierzObrotuR[2].y = wektorObrotu.z*wektorObrotu.y*B - wektorObrotu.x*sinus1;
		//macierzObrotuR[2].z = wektorObrotu.z*wektorObrotu.z*B + cosinus1;
		//
		////odbicie wzgladem wektora normalnego plaszczyzny n
		//glm::mat4 macierzOdbicia(1);
		//glm::fvec3 wektorNormalny(0);
		//wektorNormalny.x = cosinus0;//dlugosc tego wektora musi wynosic 1
		//wektorNormalny.y = sinus0;
		////wypelnianie macierzy
		//macierzOdbicia[0].x = 1 - 2 * wektorNormalny.x*wektorNormalny.x;
		//macierzOdbicia[0].y = - 2 * wektorNormalny.x*wektorNormalny.y;
		//macierzOdbicia[0].z = - 2 * wektorNormalny.x*wektorNormalny.z;

		//macierzOdbicia[1].x = -2 * wektorNormalny.y*wektorNormalny.x;
		//macierzOdbicia[1].y = 1 - 2 * wektorNormalny.y*wektorNormalny.y;
		//macierzOdbicia[1].z = - 2 * wektorNormalny.y*wektorNormalny.z;

		//macierzOdbicia[2].x = -2 * wektorNormalny.z*wektorNormalny.x;
		//macierzOdbicia[2].y = -2 * wektorNormalny.z*wektorNormalny.y;
		//macierzOdbicia[2].z = 1 - 2 * wektorNormalny.z*wektorNormalny.z;

		////macierz widoku
		//glm::mat4 macierzWidoku(1);
		//glm::fvec4 wektorObruconegoPrzsuniecia(0);//dalo by sie bez tej zmiennej
		//glm::fvec4 wektorKierunkuMyszy(0);
		////obracanie kamery wzdledem X
		//wektorKierunkuMyszy.z = sinus1;
		//wektorKierunkuMyszy.y = cosinus1;
		//wektorKierunkuMyszy.w = 1;
		////obracenie kamery wzgledem Y
		//wektorKierunkuMyszy = macierzObrotuY * wektorKierunkuMyszy;
		////wektory wejsciowe kamery
		//static glm::fvec3 wektorPozycji(0,0,-1);
		//glm::fvec3 wektorObiektu(0);
		//glm::fvec3 wektorGorySwiata(0,1,0);
		////baza przestrzeni widoku
		//glm::fvec3 wektorKierunek = glm::fvec3(wektorKierunkuMyszy);//glm::normalize(wektorObiektu - wektorPozycji);
		//glm::fvec3 wektorGora = glm::normalize(wektorGorySwiata - glm::dot(wektorGorySwiata, wektorKierunek)*wektorKierunek);
		//glm::fvec3 wektorBok = glm::normalize(glm::cross(wektorGora, wektorKierunek));
		////wypelnianie macierzy
		//macierzWidoku[0] = glm::fvec4(wektorBok,0);//jest to macierz przejscia ze wspolzednych widoku do wspolrzednych swiat
		//macierzWidoku[1] = glm::fvec4(wektorGora, 0);
		//macierzWidoku[2] = glm::fvec4(wektorKierunek, 0);
		////obliczanie odwrotnosci macierzy
		//macierzWidoku = glm::transpose(macierzWidoku);
		////obracanie wektora przesuniecia(-wektorPozycji)
		//wektorObruconegoPrzsuniecia = macierzWidoku * glm::fvec4(-wektorPozycji,1);
		////wprowadzanie wektorObruconegoPrzsuniecia do macierzWidoku
		//macierzWidoku[3] = wektorObruconegoPrzsuniecia;

		////macierz perspektywy
		//glm::mat4 macierzPerspektywy(0);
		//float x =0;
		//float odleglosc = 1 +x;
		//float pierwszyPlan = 0.1;
		//float drugiPlan = 100000000;
		////wypelnianie macierzy
		//macierzPerspektywy[0] = glm::fvec4(odleglosc, 0, 0, 0);
		//macierzPerspektywy[1] = glm::fvec4(0, odleglosc, 0, 0);
		//macierzPerspektywy[2] = glm::fvec4(0, 0, (-pierwszyPlan - drugiPlan) / (pierwszyPlan - drugiPlan), 1);
		//macierzPerspektywy[3] = glm::fvec4(0, 0, (2 * pierwszyPlan*drugiPlan) / (pierwszyPlan - drugiPlan), 0);


		////przesylanie uniform'ow do karty graficznej
		////program.setUniform("macierz", macierzObrotuX);
		////program.setUniform("macierz", macierzObrotuZ);
		////program.setUniform("macierz", macierzObrotuR);
		////program.setUniform("macierz", macierzOdbicia);
		////program.setUniform("macierz", macierzWidoku);
		

		static glm::fvec3 wektorPredkosci(0);

		while (SDL_PollEvent(&wydarzenie))
		{
			switch (wydarzenie.type)
			{
			case SDL_KEYDOWN:			
				switch (wydarzenie.key.keysym.sym)
				{
				case SDLK_w:
					wektorPredkosci.z = 0.1;
					break;
				case SDLK_s:
					wektorPredkosci.z = -0.1;
					break;
				case SDLK_d:
					wektorPredkosci.x = 0.1;
					break;
				case SDLK_a:
					wektorPredkosci.x = -0.1;
					break;
				case SDLK_LCTRL:
					wektorPredkosci.y = -0.1;
					break;
				case SDLK_LSHIFT:
					wektorPredkosci.y = 0.1;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (wydarzenie.key.keysym.sym)
				{
				case SDLK_w:
					wektorPredkosci.z = 0;
					break;				
				case SDLK_s:			
					wektorPredkosci.z = 0;
					break;				
				case SDLK_d:			
					wektorPredkosci.x = 0;
					break;				
				case SDLK_a:			
					wektorPredkosci.x = 0;
					break;				
				case SDLK_LCTRL:		
					wektorPredkosci.y = 0;
					break;				
				case SDLK_LSHIFT:		
					wektorPredkosci.y = 0;
					break;
				}
			}
			if (wydarzenie.type == SDL_QUIT)
				czyOtwarte = false;
			
			
		}		
		//przesowanie kamery
		glm::fvec3 kameraPrzesuniecie = wektorPredkosci * dCzas;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::fvec4 kameraKierunek(0);
		//obracanie kamery wzdledem X
		kameraKierunek.z = sinus1;
		kameraKierunek.y = cosinus1;
		kameraKierunek.w = 1;
		kameraKierunek = tran::obrotY((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 2 * M_PI)*kameraKierunek;

		int n = 10;
		for (int i = 0 ; i < n; i++)
		{
			glm::mat4 macierzSwiata0(1);
			glm::mat4 macierzSwiata1(1);//przejscie z local space do world space
			macierzSwiata0[0].x = (float)cos((float)i/n * 2 * M_PI);
			macierzSwiata0[0].y = (float)sin((float)i / n * 2 * M_PI);
			macierzSwiata0[1].x = (float)-sin((float)i / n * 2 * M_PI);
			macierzSwiata0[1].y = (float)cos((float)i / n * 2 * M_PI);
			/*macierzSwiata0[0] = glm::fvec4(cosinus0, sinus0, 0, 0);
			macierzSwiata0[1] = glm::fvec4(-sinus0, cosinus0, 0, 0);*/
			macierzSwiata1[3] = glm::fvec4(i, i, i, 1);
			program.setUniform("macierz", macierzPerspektywy*kamera.przesun(kameraPrzesuniecie,kameraKierunek)*macierzSwiata1*macierzSwiata0);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		//glBindVertexArray(vertexArrayObject1);
		//glDrawArrays(GL_TRIANGLES, 0,36);//rysowanie trojkatow na potstawie tablicy wierzcholkow
		//
		////glEnable(GL_STENCIL_TEST);//wlaczenie stencil test

		////	glStencilFunc(GL_ALWAYS, 1, 0xFF);
		////	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		////	glStencilMask(0xFF);
		////	glDepthMask(GL_FALSE);//wylaczenie wpisywania do buforu glebokosci
		////	glClear(GL_STENCIL_BUFFER_BIT);
		////
		//	glDrawArrays(GL_TRIANGLES, 36, 6); //rysowanie podlogi
		////	
		////	glStencilFunc(GL_EQUAL, 1, 0xFF);
		////	glStencilMask(0x00);
		////	glDepthMask(GL_TRUE);//wlaczenie wpisywania do buforu glebolosci

		//
		//	//rysoxwagnie odbicia szescianu
		//	transformacja2[2].z = -1;//odbicie wzgledem plszczyzny XY
		//	transformacja2[3].z = -1; //obniżenie szesciamu o 1
		//	glBindVertexArray(vertexArrayObject2);//zaladowanie ustawien z VAO1
		//	//glUniformMatrix4fv(uniTransformacja, 1, GL_TRUE, transformacja);
		//	program.setUniform("transformacja", transformacja2);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);

		//////glDisable(GL_STENCIL_TEST);// wyloczenie stencil testu
		
	}



	SDL_GL_DeleteContext(kontekst);//zamykanie kontekstu
	SDL_Quit(); 
	return 0;
}
	


