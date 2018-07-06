#include "ShaderProgram.h"




ShaderProgram::ShaderProgram(const char* sciezkaVS, const char* sciezkaFS)
{
	///tworzenei programu
	programID = glCreateProgram();

	///odczytywanie kodu zrodlowego z plikow
	std::string zrodloVS, zrodloFS;// stringi ze zrodlem
	std::fstream plikVS, plikFS;//pbiekty umozliwiajace otwarcie pliku
	//sprawdzanie bledow
	plikVS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	plikVS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//otwarcie pliku ze zrodlem
		plikVS.open(sciezkaVS);
		plikFS.open(sciezkaFS);
		//przniesienie zawartosci pliku do jakiedos posredniego bufora 
		std::stringstream streamVS, streamFS;
		streamVS << plikVS.rdbuf();
		streamFS << plikFS.rdbuf();
		//przeniesienie zawartosci bufora do stringow
		zrodloVS = streamVS.str();
		zrodloFS = streamFS.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "BLAD::SHADER::NIEMOZNA_ZALDOWAC_KODU_ZRODLOWEGO_Z_PLIKU" << std::endl;
	}

	///tworzenie i cala reszta zwiazana z shaderami
	//zamniana kodu zrodlowego ze stringa na tablice charow, troche to zagmatwane
	const char* char_zrodloVS = zrodloVS.c_str();
	const char* char_zrodloFS = zrodloFS.c_str();
	//twozenie vertex shader i fragent shader
	GLuint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//zaladowanie kodu zodlowego do shaderow
	glShaderSource(vertexShader, 1, &char_zrodloVS, NULL);
	glShaderSource(fragmentShader, 1, &char_zrodloFS, NULL);
	//kompilowanie
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	//test kompilacji
	char informacja [512];//!tablica do ktorej zostanie zapisany komunikat o bledzie dla kompilacji i linkowania VS i FS 
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == 1)
		std::cout << std::endl << "INFO::SHADER::KOPMILACJA_VERTEX_SHADER::OK";
	else
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, informacja);
		std::cout << std::endl << "BLAD::SHADER::KOMPILACJA_VERTEX_SHADER:: " << informacja;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == 1)
		std::cout << std::endl << "INFO::SHADER::KOPMILACJA_FRAGMENT_SHADER::OK";
	else
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, informacja);
		std::cout << std::endl << "BLAD::SHADER::KOMPILACJA_FRAGMENT_SHADER:: " << informacja;
	}

	//wiazanie shaderow z programem
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	//linkowanie
	glLinkProgram(programID);
	//test linkowania
	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	if(status==1)
		std::cout << std::endl << "INFO::SHADER::LINKOWANIE::OK";
	else
	{
		glGetProgramInfoLog(programID, 512, NULL, informacja);
		std::cout<<std::endl<< "BLAD::SHADER::LINKOWANIE:: " << informacja;
	}

}

void ShaderProgram::uzyj()
{
	glUseProgram(programID);
}

void ShaderProgram::setUniform(const char * nazwa, glm::mat4 macierzTransformacji)
{
	GLint uniMacierz = glGetUniformLocation(programID, nazwa);
	glUniformMatrix4fv(uniMacierz, 1, GL_FALSE, glm::value_ptr(macierzTransformacji));
}

ShaderProgram::~ShaderProgram()
{
}
