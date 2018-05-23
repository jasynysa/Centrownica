// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL.h"
#include "glew.h"
#include "iostream"
#include "chrono"
#include "SOIL\SOIL.h"
#include "FreeImage\FreeImage.h"
#include "stb_image.h"
#include "glm\glm.hpp"
#include "glm\gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);//inicjalizacja modolow sdl'a

	//tworzenie okna
	SDL_Window* okno = SDL_CreateWindow("Moje okno", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);//ustawienia dla kontekstu OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GLContext kontekst= SDL_GL_CreateContext(okno);//tworzenie kontekstu (cokolwiek to znaczy) OpenGL 

	//powiazanie funkcji OpenGL z moim programem
	glewExperimental = GL_TRUE;
	glewInit();


	//wierzcholki trojkata///////////////////////////////////////////////////////////////////////////////////////////////
	//float trojkat[] = {				//danen maja byc skladowane w zwyklej tablicy
	//	0.5,	0.5,		1,	0,	0,		1,	1,		//X, Y, R, G, B, S, T
	//	-0.5,	0.5,		0,	1,	0,		0,	1,
	//	0.5,	-0.5,		0,	0,	1,		1,	0,

	//	0.5,	-0.5,		0,	0,	1,		0,	0,		
	//	-0.5,	0.5,		0,	1,	0,		0,	1,
	//	-0.5,	-0.5,		1,	0,	0,		0,	0,

	//	0,		1,			1,	0,	0,		0,	0,
	//	0.5,	0.5,		1,	0,	0,		0,	0,
	//	-0.5,	0.5,		0,	1,	0,		0,	0, };
	GLfloat wierzcholki[] = {
		//X		Y		Z		R	G		B	U	V	
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f , 1.0f, 0.0f, 1.0f,

		//pogloga
		- 1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	//
	//elementy do narysowania 
	GLuint elementy[] = {
		0,	1,	2,
		1,	2,	5


	};

	//tekstura
	float piksele[] = {
		0,	0,	0,		1,	1,	1,
		1,	1,	1,		0,	0,	0
	};

	//ładowanie obrazu jako tekstury
	int szerokosc, wysokosc, borys;
	unsigned char* obraz = SOIL_load_image("C:\\Users\\jasyn\\OneDrive\\Documents\\Projekty Visual Studio\\OpenGLNauka2\\Debug\\res\\obraz.png", &szerokosc, &wysokosc, &borys, SOIL_LOAD_RGB);
	if (obraz == 0)
		std::cerr << "Nie mozna zaladowac tekstury  " <<SOIL_last_result();
	else
		std::cout << obraz << "  rozmiar obrazu: " << wysokosc<<" X "<<szerokosc;

	//tablica powiazan powina zostac stworzona przed wiazaniem GL_ARRAY_BufFEr(chyba) i wogole przed tworzeneim buforow
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	//element buffor object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementy), elementy, GL_STATIC_DRAW);
	

	//bufor wierzcholkow VBO0/////////////////////////////////////////////////////////////////////////////////////////////
	GLuint buforWierzcholkow;
	glGenBuffers(1, &buforWierzcholkow);//tworzenie jednego bufora wierzcholkow
	glBindBuffer(GL_ARRAY_BUFFER, buforWierzcholkow);// zwiazanie czy cos zmiennej albo raczej wzkaznika "buforWierzcholkow" z typem bufora OpenGL "GL_ARRAY_BUFFER"
	glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki), wierzcholki, GL_STATIC_DRAW); // zaladowanie danych do bufora


	//tekstury
	GLuint tekstura;//generowanie
	glGenTextures(1, &tekstura);
	glBindTexture(GL_TEXTURE_2D, tekstura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//ustawienia tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//niebardzo wiem co znaczy to S i T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, szerokosc, wysokosc, 0, GL_RGB, GL_UNSIGNED_BYTE, obraz);//wczytywanie tekstury
	
	
	//Vertex shader////////////////////////////////////////////////////////////////////////////////////////////////////////
	//kod zrodlowy
	const char* vertexZrodlo = R"glsl(
    #version 150 core

    in vec3 pozycja;
	in vec3 kolor;
	in vec2 wspolrzedneTek;

	uniform float czas;
	uniform mat4 transformacja;
	uniform mat4 widok;
	uniform mat4 perspektywa;

	out vec3 Kolor;
	out vec2 WspolrzedneTek;

    void main()
    {
		Kolor=kolor;
		WspolrzedneTek= -wspolrzedneTek;

		
			gl_Position =   perspektywa * widok * transformacja * vec4(pozycja,		1);
    }        
)glsl";

	GLuint vertexShader =glCreateShader(GL_VERTEX_SHADER); //tworzenie shadera
	glShaderSource(vertexShader, 1, &vertexZrodlo, NULL);//zaladowanie kodu zrodlowego 3 argument jest dlamnie niezrozumialy
	glCompileShader(vertexShader);//kompilacja kodu zrodlowego
	//test kompilacji
	{
		GLint status;
		char buffor[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
		glGetShaderInfoLog(vertexShader, 512, NULL, buffor);
		if (status != GL_TRUE)
			std::cout << "blad kompilacji vertex shadera : " << std::endl << buffor;
		else
			std::cout << "kompilacaj vertex shadera wporzadku : " << std::endl << buffor;
	}


	//Fragment shader///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//kod
	const char* fragmentShaderZrodlo = R"glsl(
    #version 150 core

	uniform vec3 kolorTrojkata;
	uniform sampler2D tek;


	in vec3 Kolor;
	in vec2 WspolrzedneTek; 

	out vec4 outColor;

	void main()
	{


		outColor = texture(tek, WspolrzedneTek) * Kolor;
	}
	)glsl";
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //	tworzenie shasera
	glShaderSource(fragmentShader, 1, &fragmentShaderZrodlo, NULL);//zaladowanie kodu zrodlowego 3 argument jest dlamnie niezrozumialy
	glCompileShader(fragmentShader);//kompilacja kodu zrodlowego
	//test
	{
		GLint status;
		char buffor[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffor);
		if (status != GL_TRUE)
			std::cout << "blad kompilacji fragment shadera : " << std::endl << buffor;
		else
			std::cout << "kompilacja fragment shadera wporzadku : " << std::endl << buffor;
	}


	//laczenie shaderow////////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint shaderProgram = glCreateProgram();//tworzenie jakiegos programu
	glAttachShader(shaderProgram, vertexShader);//wiazanei vertexShadera
	glAttachShader(shaderProgram, fragmentShader);//wiazanei fargmentShadera
	//linkowanie shaderow
	glLinkProgram(shaderProgram);
	//uruchamianie
	glUseProgram(shaderProgram);


	//wiazanie atrbutu "pozycja" z vertexShadera z tablica wierzcholkow
	GLint pozyjaAtrybut = glGetAttribLocation(shaderProgram, "pozycja");//uzyskiwanie wskaznika do atrybutu
	glVertexAttribPointer(pozyjaAtrybut, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);//okreslenie rodzaju i ukladu danych w GL_ARRAY_BUFFER i zwiazanie go z atrybutem  "pozycja"
	glEnableVertexAttribArray(pozyjaAtrybut);//aktywowanie areybutu


	//pobieranie adresu uniformy "kolorTrojkata" z fragmentShadera
	GLint uniKolor = glGetUniformLocation(shaderProgram, "kolorTrojkata");
	//wiazanie atrybutu "kolor" z tablica danych
	GLint pozycjaAtrybutuKolor = glGetAttribLocation(shaderProgram, "kolor");
	glVertexAttribPointer(pozycjaAtrybutuKolor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(pozycjaAtrybutuKolor);


	//ustawienia atrybutu "wzpolrzedneTekstury"
	GLint wspolrzedneTekAtrybut = glGetAttribLocation(shaderProgram, "wspolrzedneTek");
	glVertexAttribPointer(wspolrzedneTekAtrybut, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(wspolrzedneTekAtrybut);


	//uniform czas uzyskiwanie adresu
	GLint uniCzas = glGetUniformLocation(shaderProgram, "czas");

	GLint uniTransformacja = glGetUniformLocation(shaderProgram, "transformacja");

	GLint uniWidok = glGetUniformLocation(shaderProgram, "widok");

	GLint uniPerspektywa = glGetUniformLocation(shaderProgram, "perspektywa");

	/////////////////////////////////////////////////////////////////////////////////////////////////
	auto t_start = std::chrono::high_resolution_clock::now();
	bool czyOtwarte = true; //zmienna na potrzeby glownej petli programu
	SDL_Event wydarzenie; //zmienna w ktorej sa zapisywane wydarzenia
	glClearColor(1, 1, 0, 0);
	float poprzedni=0;
	float time=0;

	glEnable(GL_DEPTH_TEST);//włączenie testu głębikosci Który powoduje rysowanie tylko najpłytszego trojkata
	
	
	
	
	while (czyOtwarte)
	{
	
		auto t_now = std::chrono::high_resolution_clock::now();
		 time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		std::cout << "rozpoczecie petli: " << time - poprzedni << "\t";

		glUniform1f(uniCzas, time);

		////////////////////////////////////////////to jest model matrix
		float transformacja[16];
		for (int i = 0; i < 16; i++)
		{
			transformacja[i] = 0;
		}
		for (int i = 0; i < 4; i++)//tworzenie macierzy jednostkowej
		{
			transformacja[4*i+i] = 1;
		}


		int pozycjaMyszy[2];
		int rozmiarOkna[2];
		SDL_GetMouseState(&pozycjaMyszy[0], &pozycjaMyszy[1]);
		SDL_GetWindowSize(okno,&rozmiarOkna[0], &rozmiarOkna[1]);
		//macierz obrotu
		transformacja[0] =cos( (float)pozycjaMyszy[0]/(float)rozmiarOkna[0]*6);
		transformacja[1] = sin((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 6);
		transformacja[4*1+0] =-sin((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 6);
		transformacja[4 * 1 +1] = cos((float)pozycjaMyszy[0] / (float)rozmiarOkna[0] * 6);

		glm::mat4 transformacja2 = glm::mat4(1);
		//transformacja2 = glm::rotate(transformacja2, glm::radians((float)pozycjaMyszy[0] / (float)rozmiarOkna[0]*360), glm::vec3(0, 0, 1));

		glUniformMatrix4fv(uniTransformacja, 1, GL_TRUE, (transformacja));
		/////////////////////////////////////////////////////////to jest view matrix
		glm::mat4 widok;
		 widok = glm::lookAt(
			glm::vec3(0, ((float)pozycjaMyszy[1]-300)/100, 2),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 1)
		);
		glUniformMatrix4fv(uniWidok, 1, GL_FALSE, glm::value_ptr(widok));
		////////////////////////////////////////////////////////////////////to jest projection matrix

		glm::mat4 perspektywa = glm::perspective(glm::radians(45.f), 600.f / 600.f, 1.f, 30.f);
		glUniformMatrix4fv(uniPerspektywa, 1, GL_FALSE, glm::value_ptr( perspektywa));


		while (SDL_PollEvent(&wydarzenie))
		{
			if (wydarzenie.type == SDL_QUIT)
				czyOtwarte = false;
			std::cout << "lapie wydarzenie";
		}
		t_now = std::chrono::high_resolution_clock::now();
		 time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		std::cout << "po zlapaniu wydarzenia: " << time - poprzedni << "\t";


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		t_now = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		std::cout << "po czyszczeniu : " << time - poprzedni << "\t";


		
		glDrawArrays(GL_TRIANGLES, 0,36);//rysowanie trojkatow na potstawie tablicy wierzcholkow
		
		glEnable(GL_STENCIL_TEST);//wlaczenie stencil test

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilMask(0xFF);
			glDepthMask(GL_FALSE);//wylaczenie wpisywania do buforu glebokosci
			glClear(GL_STENCIL_BUFFER_BIT);
		
			glDrawArrays(GL_TRIANGLES, 36, 6); //rysowanie podlogi
			
			glStencilFunc(GL_EQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDepthMask(GL_TRUE);//wlaczenie wpisywania do buforu glebolosci

		
			//rysoxwagnie odbicia szescianu
			transformacja[4 * 2 + 2] = -1;//odbicie wzgledem plszczyzny XY
			transformacja[4 * 2 + 3] = -1; //obniżenie szesciamu o 1

			glUniformMatrix4fv(uniTransformacja, 1, GL_TRUE, transformacja);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisable(GL_STENCIL_TEST);// wyloczenie stencil testu

		t_now = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		std::cout << "po czyszczeniu : " << time - poprzedni << "\t";

		SDL_GL_SwapWindow(okno);
		
		t_now = std::chrono::high_resolution_clock::now();
		 time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		std::cout << "po narysowaniu: " << time - poprzedni << "\t"<<std::endl;

		glUniform3f(uniKolor, (sin(time*5) + 1) / 2, (sin(time*4)+1)/2, 0);
		std::cout << time - poprzedni << std::endl;
		poprzedni = time;
		
	}



	SDL_GL_DeleteContext(kontekst);//zamykanie kontekstu
	SDL_Quit(); 
	return 0;
}
	


