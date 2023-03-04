#include <stdafx.h>

#include "Color.h"

Color::Color() :
	r(255), g(255), b(255)
{}

Color::Color(unsigned char _r, unsigned char _g, unsigned char _b) :
	r(_r), g(_g), b(_b)
{}

Color::Color(Colors col)
{
	switch (col)
	{
	case Colors::BLACK: 
		r = 0; 
		g = 0; 
		b = 0;
		break;

	case Colors::WHITE:
		r = 255;
		g = 255;
		b = 255;
		break;

	case Colors::RED:
		r = 255;
		g = 0;
		b = 0;
		break;

	case Colors::ORANGE:
		r = 255;
		g = 174;
		b = 0;
		break;

	case Colors::YELLOW:
		r = 255;
		g = 255;
		b = 0;
		break;

	case Colors::GREEN:
		r = 20;
		g = 150;
		b = 0;
		break;

	case Colors::BLUE:
		r = 0;
		g = 0;
		b = 255;
		break;

	case Colors::PURPLE:
		r = 174;
		g = 0;
		b = 255;
		break;

	case Colors::LIGHT_GREEN:
		r = 0;
		g = 255;
		b = 0;
		break;

	case Colors::LIGHT_BLUE:
		r = 0;
		g = 255;
		b = 255;
		break;

	case Colors::PINK:
		r = 255;
		g = 130;
		b = 213;
		break;
	}
}