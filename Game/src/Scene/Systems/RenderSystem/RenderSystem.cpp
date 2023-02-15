#include <stdafx.h>

#include "RenderSystem.h"

#include <Scene/Components/Transform/Transform.h>
#include <Scene/Components/Sprite/Sprite.h>
#include <Scene/Components/Wireframe/Wireframe.h>

void RenderSystem::Update(EntityManager& entityMgr)
{
    for (auto id : entityMgr.GetEntities<Transform, Sprite>())
        Render(entityMgr, id);

    for (auto id : entityMgr.GetEntities<Transform, Wireframe>())
        RenderWireframe(entityMgr, id);
}

void RenderSystem::Render(EntityManager &entityMgr, Entity id) 
{	
    const Transform& tf = entityMgr.GetComponent<Transform>(id);
    const Sprite& sp = entityMgr.GetComponent<Sprite>(id);

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

}

void RenderSystem::RenderWireframe(EntityManager& entityMgr, Entity id)
{
    const Transform& tf = entityMgr.GetComponent<Transform>(id);
    const Wireframe& wf = entityMgr.GetComponent<Wireframe>(id);

    int len = wf.points.size();
    for (int i = 0; i < len + 1; i++)
    {
        Vector2 v1 = tf.position + wf.points[i % len];
        Vector2 v2 = tf.position + wf.points[(i + 1) % len];
        App::DrawLine(v1.x, v1.y, v2.x, v2.y, wf.r, wf.g, wf.b);
    }

}