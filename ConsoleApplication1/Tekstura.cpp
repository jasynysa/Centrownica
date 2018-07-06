#include "Tekstura.h"
#include <iostream>


Tekstura::Tekstura(const char* sciezkaTek)
{

	///³adowanie obrazu jako tekstury
	int szerokosc, wysokosc, borys;
	unsigned char* obraz = SOIL_load_image(sciezkaTek, &szerokosc, &wysokosc, &borys, SOIL_LOAD_RGB);
	//sprawdzanie bledow
	if (obraz == 0)
		std::cerr << std::endl << "BLAD::TEKSTURA::WCZYTYWANIE_OBRAZU::"<<sciezkaTek<<"::" << SOIL_last_result();
	else
		std::cout << std::endl << "INFO::TEKSTURA::WCZYTYWANIE_OBRAZU::OK";


	///tekstura
	GLuint tekstura;
	glGenTextures(1, &tekstura);
	glActiveTexture(GL_TEXTURE0+idTekstury);
	glBindTexture(GL_TEXTURE_2D, tekstura);
	
	//ustawienia tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//niebardzo wiem co znaczy to S i T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//wczytywanie tekstury do pamieci GPU(chyba)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, szerokosc, wysokosc, 0, GL_RGB, GL_UNSIGNED_BYTE, obraz);
	//tworzenie mipmapy, czyli zbioru tekstur o roznej rozdzielczosci
	glGenerateMipmap(GL_TEXTURE_2D);
	//inkrementacja zmiennej statycznej idTekstury
	idTekstury++;
}


Tekstura::~Tekstura()
{
}
//inicjalizacja zmiennej statycznej
int Tekstura::idTekstury = 0;