 #version 150 core

	uniform sampler2D tekstura0;
	uniform sampler2D tekstura1;

	in vec3 Kolor;
	in vec2 WspolrzedneTek; 

	out vec4 outColor;

	void main()
	{

		outColor = 0.5*texture(tekstura0,WspolrzedneTek) + 0.5*texture(tekstura1,WspolrzedneTek*4) ;
	}