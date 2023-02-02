#include <stdafx.h>
#include <App/TextureLoader.h>
#include "../glut/include/GL/freeglut_ext.h"

#include "Sprite.h"

std::unordered_map<const char*, SpriteSheetData> Sprite::master_list;


Sprite::Sprite() {}

Sprite::Sprite(const char* filename, unsigned int frame_)
{
    assert("Sprite not in master list" && master_list.find(filename) != master_list.end());
    
    SpriteSheetData& data = master_list[filename];
    
    textureID = data.textureID;
    frame = frame_;
    width = data.tex_width * (1.0f / data.cols);
    height = data.tex_height * (1.0f / data.rows);
    
    CalculateUVsAndPoints(data.tex_width, data.tex_height, data.rows, data.cols);
}

Sprite::Sprite(const char* filename, unsigned int nrows, unsigned int ncols, unsigned int frame_)
{
    // If the texture is already in the master list, dont load it again
    if (master_list.find(filename) != master_list.end())
    {
        SpriteSheetData &data = master_list[filename];
        
        textureID = data.textureID;
        frame = frame_;
        width = data.tex_width * (1.0f / ncols);
        height = data.tex_height * (1.0f / nrows);
        
        CalculateUVsAndPoints(data.tex_width, data.tex_height, nrows, ncols);
        return;
    }
    
    // Load the texture
    unsigned int tex_width, tex_height;
    unsigned char* imageData = loadBMPRaw(filename, tex_width, tex_height, true);

    assert(imageData && "Error loading image");

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, tex_width, tex_height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    free(imageData);

    master_list[filename] = SpriteSheetData(texture, tex_width, tex_height, nrows, ncols);
    textureID = texture;

    CalculateUVsAndPoints(tex_width, tex_height, nrows, ncols);
}

void Sprite::CalculateUVsAndPoints(unsigned int tex_width, unsigned int tex_height, unsigned int nrows, unsigned int ncols)
{
    // Calculate UVs (copied from SimpleSprite.cpp and modified)
    float u = 1.0f / ncols;
    float v = 1.0f / nrows;
    int row = frame / ncols;
    int column = frame % ncols;

    width = tex_width * u;
    height = tex_height * v;
    uvcoords[0] = u * column;
    uvcoords[1] = v * (float)(row + 1);

    uvcoords[2] = u * (float)(column + 1);
    uvcoords[3] = v * (float)(row + 1);

    uvcoords[4] = u * (float)(column + 1);
    uvcoords[5] = v * row;

    uvcoords[6] = u * column;
    uvcoords[7] = v * row;

    // Calculate points (copied from SimpleSprite.cpp and modified)
    points[0] = -(width / 2.0f);
    points[1] = -(height / 2.0f);
    points[2] = width / 2.0f;
    points[3] = -(height / 2.0f);
    points[4] = width / 2.0f;
    points[5] = height / 2.0f;
    points[6] = -(width / 2.0f);
    points[7] = height / 2.0f;
}

