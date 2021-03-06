
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
#include "Obrecz.h"


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

	
	///tworzenie ciagu wierzcholkow i tablicy kolejnosci ich rysowania za pomoca klasy
	Kolo kolo(5);
	Obrecz obrecz(30, 0.2);


	///wczytywanie tekstur za posrednictwem klasy
	Tekstura kot(".\\res\\obraz.png");
	Tekstura sierpIMlot(".\\res\\sierp.png");
		

	///tablica powiazan powina zostac stworzona przed wiazaniem GL_ARRAY_BufFEr(chyba) i wogole przed tworzeneim buforow
	GLuint vaoObrecz,vaoKolo;
	glGenVertexArrays(1, &vaoKolo);	
	glGenVertexArrays(1, &vaoObrecz);
		
	
	///element buffor object
	glBindVertexArray(vaoKolo);
	GLuint eboKolo;
	glGenBuffers(1, &eboKolo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboKolo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, kolo.rozmiarTablicyElementow, kolo.tablicaElementow, GL_STATIC_DRAW);
	
	glBindVertexArray(vaoObrecz);
	GLuint eboObrecz;
	glGenBuffers(1, &eboObrecz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboObrecz);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obrecz.rozmiarTablicyElementow, obrecz.tablicaElementow, GL_STATIC_DRAW);


	///bufor wierzcholkow VBO0/////////////////////////////////////////////////////////////////////////////////////////////
	glBindVertexArray(vaoKolo);
	GLuint vboKolo;
	glGenBuffers(1, &vboKolo);
	glBindBuffer(GL_ARRAY_BUFFER, vboKolo);
	glBufferData(GL_ARRAY_BUFFER, kolo.rozmiarTablicyWierzcholkow, kolo.tablicaWierzcholkow, GL_STATIC_DRAW); 

	glBindVertexArray(vaoObrecz);
	GLuint vboObrecz;
	glGenBuffers(1, &vboObrecz);
	glBindBuffer(GL_ARRAY_BUFFER, vboObrecz);
	glBufferData(GL_ARRAY_BUFFER, obrecz.rozmiarTablicyWierzcholkow, obrecz.tablicaWierzcholkow,GL_DYNAMIC_DRAW);


	///tworzenie programu z dwoma shaderami
	ShaderProgram program(".\\res\\VertexShaderSource.VS", ".\\res\\FragmentShaderSource.FS");	


	///informowanie w jaki sposob odczytywac dane z VBO
	//uzuskiwanie ID/wskaźnika czy czegoś podobnego atrybutow zdefiniowanych w vertexShader
	GLint IdAtrybutuPozycja = glGetAttribLocation(program.programID, "pozycja");
	GLint IdAtrybutuKolor = glGetAttribLocation(program.programID, "kolor");
	GLint IdAtrybutuWspolrzedneTek = glGetAttribLocation(program.programID, "wspolrzedneTek");
	
	//zapisywanie do vaoKolo
	glBindVertexArray(vaoKolo);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, vboKolo);
	//
	glVertexAttribPointer(IdAtrybutuPozycja, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(IdAtrybutuPozycja);
	//
	glVertexAttribPointer(IdAtrybutuKolor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(IdAtrybutuKolor);
	//
	glVertexAttribPointer(IdAtrybutuWspolrzedneTek, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(IdAtrybutuWspolrzedneTek);

	//zapisywanie do vaoObrecz
	glBindVertexArray(vaoObrecz);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, vboObrecz);
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
	float poprzedni=0;
	float time=0;
	int ktoraSzprycha = 0;
	glm::mat4 macierzPerspektywy = tran::perspektywa(M_PI, 0.1, 1000);//macierz perspektywy
	Kamera kamera(glm::fvec3(0, 0, 0), glm::fvec3(0, 1, 0));

	glEnable(GL_DEPTH_TEST);//włączenie testu głębikosci Który powoduje rysowanie tylko najpłytszego piksela
	glClearColor(1, 0, 0, 1);//czyszczenie bufora farmeBufor'a powoduje wypelnienie go tym kolorem
	glLineWidth(10);//grubosc lini
	program.uzyj();
	glUniform1i(glGetUniformLocation(program.programID, "tekstura0"), 0);
	glUniform1i(glGetUniformLocation(program.programID, "tekstura1"), 1);

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///glowna petla programu
	while (czyOtwarte)
	{


		float naciagSzprychy = 0;
		auto t_now = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		float dCzas = time - poprzedni;
		poprzedni = time;
		

		int pozycjaMyszy[2];
		int rozmiarOkna[2];
		SDL_GetMouseState(&pozycjaMyszy[0], &pozycjaMyszy[1]);
		SDL_GetWindowSize(okno, &rozmiarOkna[0], &rozmiarOkna[1]);
		float sinus0 = sin((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 2 * M_PI);
		float cosinus0 = cos((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 2 * M_PI);
		float sinus1= sin((float)pozycjaMyszy[1] / (float)rozmiarOkna[1] * 0.9 * M_PI+0.1);
		float cosinus1 = cos((float)pozycjaMyszy[1] / (float)rozmiarOkna[1] * 0.9 * M_PI+0.1);
		


		

		static glm::fvec3 wektorPredkosci(0);

		while (SDL_PollEvent(&wydarzenie))
		{
			switch (wydarzenie.type)
			{
			case SDL_KEYDOWN:			
				switch (wydarzenie.key.keysym.sym)
				{
				case SDLK_w:
					wektorPredkosci.z = 1;
					break;
				case SDLK_s:
					wektorPredkosci.z = -1;
					break;
				case SDLK_d:
					wektorPredkosci.x = 1;
					break;
				case SDLK_a:
					wektorPredkosci.x = -1;
					break;
				case SDLK_LCTRL:
					wektorPredkosci.y = -1;
					break;
				case SDLK_LSHIFT:
					wektorPredkosci.y = 1;
					break;
				case SDLK_q:
					ktoraSzprycha = ++ktoraSzprycha%obrecz.iloscSegmentow;
					break;
				case SDLK_e:
					naciagSzprychy -= 0.05;
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
		
		
		glm::fvec4 kameraKierunek(0);
		//obracanie kamery wzdledem X
		kameraKierunek.z = sinus1;
		kameraKierunek.y = cosinus1;
		kameraKierunek.w = 1;
		//obracanie kamery wzgledem Y
		kameraKierunek = tran::obrotY((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 2 * M_PI)*kameraKierunek;


		glm::mat4 widokIPerspektywa = macierzPerspektywy * kamera.przesun(kameraPrzesuniecie, kameraKierunek);//sktaca to ilosc operacji wykonywanych w kazdym cyklu petli
		
		glBindVertexArray(vaoObrecz);
		glBufferData(GL_ARRAY_BUFFER, obrecz.rozmiarTablicyWierzcholkow, obrecz.tablicaWierzcholkow, GL_DYNAMIC_DRAW);//poniewarz zmiania sie siadka obreczy
		program.setUniform("macierz", widokIPerspektywa);
		//czyszczenie bufora 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//rysowanie obreczy
		glDrawElements(GL_TRIANGLES, obrecz.iloscElementow, GL_UNSIGNED_INT, 0);

		//rysowanie szprych
		
		
		
		glDrawElements(GL_LINES, obrecz.iloscElementow+obrecz.iloscElementowSzprych, GL_UNSIGNED_INT, (void*)(obrecz.iloscElementow*sizeof(int)));
		obrecz.fizyka(0.1);
		obrecz.regulujSzpryche(ktoraSzprycha,naciagSzprychy);
		
		SDL_GL_SwapWindow(okno);
	}



	SDL_GL_DeleteContext(kontekst);//zamykanie kontekstu
	SDL_Quit(); 
	return 0;
}
	


