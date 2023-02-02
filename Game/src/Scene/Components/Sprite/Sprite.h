#pragma once

#include <stdafx.h>

struct SpriteSheetData {

	GLuint textureID;
	unsigned int tex_width = 0;
	unsigned int tex_height = 0;
	unsigned int rows;
	unsigned int cols;

	SpriteSheetData() {}

	SpriteSheetData(GLuint id, unsigned int w, unsigned int h, unsigned int r, unsigned int c) :
		textureID(id), tex_width(w), tex_height(h), rows(r), cols(c)
	{}

};

struct Sprite {

	GLuint textureID;
	unsigned int frame; // index of image on sprite sheet
	float width;
	float height;
	float points[8]; // copied from SimpleSprite.h
	float uvcoords[8];

	Sprite();
	Sprite(const char* filename, unsigned int frame = 0);
	Sprite(const char* filename, unsigned int rows, unsigned int cols, unsigned int frame = 0);

	void CalculateUVsAndPoints(unsigned int tex_width, unsigned int tex_height, unsigned int nrows, unsigned int ncols);
	
	// Texture width, height, rows & cols not stored in Sprite to save space in Component Array
	static std::unordered_map<const char*, SpriteSheetData> master_list;
};