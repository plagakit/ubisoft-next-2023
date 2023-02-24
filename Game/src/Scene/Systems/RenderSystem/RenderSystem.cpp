#include <stdafx.h>

#include "RenderSystem.h"

#include "Scene/Scene.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Components/Sprite/Sprite.h"
#include "Scene/Components/Wireframe/Wireframe.h"

#ifdef _DEBUG
#include "Scene/Components/BoxBounds/BoxBounds.h"
#include "Scene/Components/CircleBounds/CircleBounds.h"
#endif

const Vector2 CENTER = Vector2(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);

void RenderSystem::Render(Scene& scene)
{
    Camera& cam = scene.GetCamera();
    EntityManager& entityMgr = scene.GetEntityManager();
    
    for (Entity id : entityMgr.GetEntities<Transform, Sprite>())
        RenderSprite(cam, entityMgr, id);

    for (Entity id : entityMgr.GetEntities<Transform, Wireframe>())
        RenderWireframe(cam, entityMgr, id);

#ifdef _DEBUG
    RenderPhysicsBounds(cam, entityMgr);
#endif
    
}

void RenderSystem::RenderSprite(Camera& cam, EntityManager &entityMgr, Entity id)
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

void RenderSystem::RenderWireframe(Camera& cam, EntityManager& entityMgr, Entity id)
{
    Transform& tf = entityMgr.GetComponent<Transform>(id);
    Wireframe& wf = entityMgr.GetComponent<Wireframe>(id);

    DrawWireframe(cam, tf, wf.points, wf.r, wf.g, wf.b);

}

void RenderSystem::RenderPhysicsBounds(Camera& cam, EntityManager& entityMgr)
{
    for (Entity id : entityMgr.GetEntities<CircleBounds>())
    {
        Transform& tf = entityMgr.GetComponent<Transform>(id);
        CircleBounds& cb = entityMgr.GetComponent<CircleBounds>(id);

        int numLines = 16;
        float angleStep = 2.0f * PI / numLines;
        std::vector<Vector2> points;
        
        // Fill points with the points on a circle
        for (int i = 0; i < numLines + 1; i++)
        {
            int j = i % numLines;

            float x = cosf(angleStep * j) * cb.radius + cb.offset.x;
            float y = sinf(angleStep * j) * cb.radius + cb.offset.y;

            points.push_back(Vector2(x, y));
        }

        DrawWireframe(cam, tf, points, 0, 0, 1.0f);
    }

    for (Entity id : entityMgr.GetEntities<BoxBounds>())
    {
        Transform& tf = entityMgr.GetComponent<Transform>(id);
        BoxBounds& b = entityMgr.GetComponent<BoxBounds>(id);

        std::vector<Vector2> points;
        float w = b.width / 2;
        float h = b.height / 2;
        points.push_back(Vector2(-w, -h) + b.offset); // top left
        points.push_back(Vector2(w, -h) + b.offset); // top right
        points.push_back(Vector2(-w, h) + b.offset); // bottom left
        points.push_back(Vector2(w, h) + b.offset); // bottom right

        DrawWireframe(cam, tf, points, 0, 0, 1.0f);
    }
}


void RenderSystem::DrawWireframe(Camera& cam, Transform& tf, std::vector<Vector2>& points, float r, float g, float b)
{
    auto numPoints = points.size();
    for (int i = 0; i < numPoints + 1; i++)
    {
        // i % numpoints means i wraps around numpoints
        const Vector2& t1 = points[i % numPoints];
        const Vector2& t2 = points[(i + 1) % numPoints];

        // For vector: Scale -> rotate -> translate
        // Then camera: translate -> rotate -> zoom
        // Could have been simplified with a matrix class. If this was 3D, I would try to make one
        Vector2 v1 = (t1 * tf.scale).Rotated(tf.rotation) + tf.position;
        Vector2 v2 = (t2 * tf.scale).Rotated(tf.rotation) + tf.position;

        // Translating by CENTER ensures that cam's pos is the middle of the screen
        v1 = (v1 - cam.position).Rotated(cam.rotation) * cam.zoom + CENTER;
        v2 = (v2 - cam.position).Rotated(cam.rotation) * cam.zoom + CENTER;

        App::DrawLine(v1.x, v1.y, v2.x, v2.y, r, g, b);
    }
}