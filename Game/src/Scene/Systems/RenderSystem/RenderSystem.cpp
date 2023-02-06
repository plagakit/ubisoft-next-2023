#include <stdafx.h>

#include "RenderSystem.h"
#include "Scene/Scene.h"

void RenderSystem::Render(Entity id) 
{	
    Transform& tf = scene->GetComponent<Transform>(id);
    Sprite& sp = scene->GetComponent<Sprite>(id);

	// Code copied from SimpleSprite.cpp
#if APP_USE_VIRTUAL_RES
    float scalex = (tf.scale.x / APP_VIRTUAL_WIDTH) * 2.0f;
    float scaley = (tf.scale.y / APP_VIRTUAL_HEIGHT) * 2.0f;
#else
    float scalex = tf.scale.x;
    float scaley = tf.scale.y;
#endif
    float x = tf.position.x;
    float y = tf.position.y;
#if APP_USE_VIRTUAL_RES
    APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
#endif

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scalex, scaley, 1.0f);
    glRotatef(tf.rotation * 180 / PI, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sp.textureID);

    glBegin(GL_QUADS);
    for (unsigned int i = 0; i < 8; i += 2)
    {
        glTexCoord2f(sp.uvcoords[i], sp.uvcoords[i + 1]);
        glVertex2f(sp.points[i], sp.points[i + 1]);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

	/*float sx = tf.position.x - sp.width / 2.0f;
	float sy = tf.position.y - sp.height / 2.0f;
	int r = sp.r, g = sp.g, b = sp.b;

	App::DrawLine(sx, sy, sx + sp.width, sy, r, g, b);
	App::DrawLine(sx, sy, sx, sy + sp.height, r, g, b);
	App::DrawLine(sx, sy + sp.height, sx + sp.width, sy + sp.height, r, g, b);
	App::DrawLine(sx + sp.width, sy, sx + sp.width, sy + sp.height, r, g, b);*/
}