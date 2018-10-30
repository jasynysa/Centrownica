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
#include "Transformacja.h"
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
	
	///tworzenie tablicy kolejnosci rysowania wierzcholkow 
	GLuint elementy[] = {
		0,	1,	2,
		1,	2,	5


	};


	///tworzenie ciagu wierzcholkow i tablicy kolejnosci ich rysowania za pomoca klasy
	Kolo kolo(10);
	Obrecz obrecz(30, 0.2);


	///wczytywanie tekstur za posrednictwem klasy
	Tekstura kot(".\\res\\obraz.png");
	Tekstura sierpIMlot(".\\res\\sierp.png");
		

	///tablica powiazan powina zostac stworzona przed wiazaniem GL_ARRAY_BufFEr(chyba) i wogole przed tworzeneim buforow
	GLuint vertexArrayObject1;
	glGenVertexArrays(1, &vertexArrayObject1);
	GLuint vertexArrayObject2;
	glGenVertexArrays(1, &vertexArrayObject2);
	GLuint vaoKolo;
	glGenVertexArrays(1, &vaoKolo);
	GLuint vaoObrecz;
	glGenVertexArrays(1, &vaoObrecz);
	
	
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
	
	glBindVertexArray(vaoObrecz);
	GLuint eboObrecz;
	glGenBuffers(1, &eboObrecz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboObrecz);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obrecz.rozmiarTablicyElementow, obrecz.tablicaElementow, GL_STATIC_DRAW);

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

	glBindVertexArray(vaoObrecz);
	GLuint vboObrecz;
	glGenBuffers(1, &vboObrecz);
	glBindBuffer(GL_ARRAY_BUFFER, vboObrecz);
	glBufferData(GL_ARRAY_BUFFER, obrecz.rozmiarTablicyWierzcholkow, obrecz.tablicaWierzcholkow,GL_DYNAMIC_DRAW);


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

	//zapisywanie do vaoObrecz
	glBindVertexArray(vaoObrecz);
	//
	glBindBuffer(GL_ARRAY_BUFFER, vboObrecz);
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
	Kamera kamera(glm::fvec3(0, 0, 0), glm::fvec3(0, 1, 0));

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
		//obracanie kamery wzgledem Y
		kameraKierunek = tran::obrotY((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 2 * M_PI)*kameraKierunek;

		glBindVertexArray(vertexArrayObject1);
		glm::mat4 widokIPerspektywa = macierzPerspektywy * kamera.przesun(kameraPrzesuniecie, kameraKierunek);//sktaca to ilosc operacji wykonywanych w kazdym cyklu petli
		int n = 10;
		for (int i = 1 ; i < n; i++)
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
			program.setUniform("macierz",widokIPerspektywa *macierzSwiata1*macierzSwiata0);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		glBindVertexArray(vaoObrecz);
		//glBufferData(GL_ARRAY_BUFFER, obrecz.rozmiarTablicyWierzcholkow, obrecz.tablicaWierzcholkow, GL_DYNAMIC_DRAW);
		program.setUniform("macierz", widokIPerspektywa);
		glDrawElements(GL_TRIANGLES, obrecz.iloscElementow, GL_UNSIGNED_INT, 0);

		//dif((int)time%2==0)
		obrecz.regulujSzpryche((int)time%3*2, 1+sin(time)*0.2);
		SDL_GL_SwapWindow(okno);//zmiana bufora ktory jest wyswietlany na ekranie
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
	


