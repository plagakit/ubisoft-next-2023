#pragma once

#include <stdafx.h>

enum struct Colors
{
	BLACK,
	WHITE,
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE,
	LIGHT_GREEN,
	LIGHT_BLUE,
	PINK
};

struct Color {

	unsigned char r;
	unsigned char g;
	unsigned char b;

	Color();
	Color(unsigned char r, unsigned char b, unsigned char g);
	Color(Colors col);

};