#version 150 core

    in vec3 pozycja;
	in vec3 kolor;
	in vec2 wspolrzedneTek;

	uniform float czas;
	uniform mat4 macierz;
	

	out vec3 Kolor;
	out vec2 WspolrzedneTek;

    void main()
    {
		Kolor=kolor;
		WspolrzedneTek= -wspolrzedneTek;

		
			gl_Position =    macierz * vec4(pozycja,1);
    }        