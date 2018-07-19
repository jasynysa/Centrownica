#pragma once
#include "glm/glm.hpp"
///transformacje 
namespace tran
{

	///obrot wokol Z
	glm::mat4 obrotZ(float kat)
	{
		float sinus = sin(kat);
		float cosinus = cos(kat);

		glm::mat4 macierzObrotuZ(1);
		macierzObrotuZ[0].x = cosinus;
		macierzObrotuZ[0].y = sinus;
		macierzObrotuZ[1].x = -sinus;
		macierzObrotuZ[1].y = cosinus;
		return macierzObrotuZ;
	}


	///obrot wokol X
	glm::mat4 obrotX(float kat)
	{
		float sinus = sin(kat);
		float cosinus = cos(kat);

		glm::mat4 macierzObrotuX(1);
		macierzObrotuX[1].y = cosinus;
		macierzObrotuX[1].z = sinus;
		macierzObrotuX[2].y = -sinus;
		macierzObrotuX[2].z = cosinus;
		return macierzObrotuX;
	}


	///obrot wokol Y
	glm::mat4 obrotY(float kat)
	{
		float sinus = sin(kat);
		float cosinus = cos(kat);

		glm::mat4 macierzObrotuY(1);
		macierzObrotuY[0].x = cosinus;
		macierzObrotuY[0].z = sinus;
		macierzObrotuY[2].x = sinus;
		macierzObrotuY[2].z = cosinus;
		return macierzObrotuY;
	}


	///obrot wokol dowolnego wektora
	glm::mat4 obrotR(glm::vec3 wektorObrotu, float kat)
	{
		float sinus = sin(kat);
		float cosinus = cos(kat);
		float B = 1 - cosinus;
		wektorObrotu = glm::normalize(wektorObrotu);

		glm::mat4 macierzObrotuR(1);

		macierzObrotuR[0].x = wektorObrotu.x*wektorObrotu.x*B + cosinus;
		macierzObrotuR[0].y = wektorObrotu.x*wektorObrotu.y*B + wektorObrotu.z*sinus;
		macierzObrotuR[0].z = wektorObrotu.x*wektorObrotu.z*B - wektorObrotu.y*sinus;

		macierzObrotuR[1].x = wektorObrotu.y*wektorObrotu.x*B - wektorObrotu.z*sinus;
		macierzObrotuR[1].y = wektorObrotu.y*wektorObrotu.y*B + cosinus;
		macierzObrotuR[1].z = wektorObrotu.y*wektorObrotu.z*B + wektorObrotu.x*sinus;

		macierzObrotuR[2].x = wektorObrotu.z*wektorObrotu.x*B + wektorObrotu.y*sinus;
		macierzObrotuR[2].y = wektorObrotu.z*wektorObrotu.y*B - wektorObrotu.x*sinus;
		macierzObrotuR[2].z = wektorObrotu.z*wektorObrotu.z*B + cosinus;

		return macierzObrotuR;
	}


	///obbicie wzgledem wektora normalnego plaszczyzny
	glm::mat4 odbicieN(glm::vec3 wektorNormalny)
	{
		wektorNormalny = glm::normalize(wektorNormalny);

		glm::mat4 macierzOdbicia(1);

		macierzOdbicia[0].x = 1 - 2 * wektorNormalny.x*wektorNormalny.x;
		macierzOdbicia[0].y = -2 * wektorNormalny.x*wektorNormalny.y;
		macierzOdbicia[0].z = -2 * wektorNormalny.x*wektorNormalny.z;

		macierzOdbicia[1].x = -2 * wektorNormalny.y*wektorNormalny.x;
		macierzOdbicia[1].y = 1 - 2 * wektorNormalny.y*wektorNormalny.y;
		macierzOdbicia[1].z = -2 * wektorNormalny.y*wektorNormalny.z;

		macierzOdbicia[2].x = -2 * wektorNormalny.z*wektorNormalny.x;
		macierzOdbicia[2].y = -2 * wektorNormalny.z*wektorNormalny.y;
		macierzOdbicia[2].z = 1 - 2 * wektorNormalny.z*wektorNormalny.z;

		return macierzOdbicia;
	}


	///widok
	glm::mat4 widok(glm::vec3 pozKamery, glm::vec3 pozObiektu, glm::vec3 gora)//obliczaniekierunku kamery na podstawie pozycji obiektu na ktory skierowana jest kamera
	{

		//baza przestrzeni widoku
		glm::fvec3 kameraKierunek = glm::fvec3(glm::normalize(pozObiektu - pozKamery));
		glm::fvec3 kameraGora = glm::normalize(gora - glm::dot(gora, kameraKierunek)*kameraKierunek);
		glm::fvec3 kameraBok = glm::normalize(glm::cross(kameraGora, kameraKierunek));
		//wypelnianie macierzy widoku
		glm::mat4 macierzWidoku(1);
		macierzWidoku[0] = glm::fvec4(kameraBok, 0);
		macierzWidoku[1] = glm::fvec4(kameraGora, 0);
		macierzWidoku[2] = glm::fvec4(kameraKierunek, 0);
		//obliczanie odwrotnosci macierzy
		macierzWidoku = glm::transpose(macierzWidoku);//odwrotnosc macierzy jest trasformacja z przstrzeni swiata do przestrzeni kamery
													  //tanslacja
		macierzWidoku[3] = macierzWidoku * glm::fvec4(pozKamery, 1);

		return macierzWidoku;
	}


	///perspektywa
	glm::mat4 perspektywa(float poleWidzenia, float pierwszyPlan, float drugiPlan)
	{
		float odlegloscRzutni = 1 / atan(poleWidzenia / 2);//rzutni 
		glm::mat4 macierzPerspektywy;
		//wypelnianie macierzy
		macierzPerspektywy[0] = glm::fvec4(odlegloscRzutni, 0, 0, 0);
		macierzPerspektywy[1] = glm::fvec4(0, odlegloscRzutni, 0, 0);
		macierzPerspektywy[2] = glm::fvec4(0, 0, (-pierwszyPlan - drugiPlan) / (pierwszyPlan - drugiPlan), 1);
		macierzPerspektywy[3] = glm::fvec4(0, 0, (2 * pierwszyPlan*drugiPlan) / (pierwszyPlan - drugiPlan), 0);

		return macierzPerspektywy;
	}

}
