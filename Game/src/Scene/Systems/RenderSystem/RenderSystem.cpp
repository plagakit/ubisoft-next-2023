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

    for (Entity id : scene.GetEntities<Transform, Sprite>())
        RenderSprite(scene, id);

    for (Entity id : scene.GetEntities<Transform, Wireframe>())
        RenderWireframe(scene, id);

#ifdef _DEBUG
    RenderPhysicsBounds(scene);
    App::Print(0, 250, test.c_str());
#endif
    
}

void RenderSystem::RenderSprite(Scene& scene, Entity id)
{	
    const Transform& tf = scene.GetComponent<Transform>(id);
    const Sprite& sp = scene.GetComponent<Sprite>(id);
    const Camera& cam = scene.GetCamera();

	// Code copied & modified from SimpleSprite.cpp
#if APP_USE_VIRTUAL_RES
    float scalex = (tf.scale.x / APP_VIRTUAL_WIDTH);
    float scaley = (tf.scale.y / APP_VIRTUAL_HEIGHT);
#else
    float scalex = tf.scale.x;
    float scaley = tf.scale.y;
#endif
    float x = tf.position.x;
    float y = tf.position.y;
    float cx = APP_VIRTUAL_WIDTH - cam.position.x;
    float cy = APP_VIRTUAL_HEIGHT - cam.position.y;
#if APP_USE_VIRTUAL_RES
    APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
    APP_VIRTUAL_TO_NATIVE_COORDS(cx, cy);
#endif
    glPushMatrix();

    // Zoom in cam
    glScalef(cam.zoom, cam.zoom, 0.0f);

    // Makes sure cam rotation isnt skewed 
    glScalef(scalex, scaley, 1.0f);
    glRotatef(cam.rotation * 180 / PI, 0.0f, 0.0f, 1.0f);
    glScalef(1.0f/scalex, 1.0f/scaley, 1.0f);

    // Translate cam
    glTranslatef(cx, cy, 0.0f);

    // Code copied from SimpleSprite
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

void RenderSystem::RenderWireframe(Scene& scene, Entity id)
{
    Transform& tf = scene.GetComponent<Transform>(id);
    Wireframe& wf = scene.GetComponent<Wireframe>(id);

    DrawWireframe(scene.GetCamera(), tf, wf.points, wf.r, wf.g, wf.b);

}

void RenderSystem::RenderPhysicsBounds(Scene& scene)
{
    for (Entity id : scene.GetEntities<CircleBounds>())
    {
        Transform& tf = scene.GetComponent<Transform>(id);
        CircleBounds& cb = scene.GetComponent<CircleBounds>(id);

        int numLines = 16;
        float angleStep = 2.0f * PI / numLines;
        std::vector<Vector2> points;
        
        // Fill points with the points on a circle
        for (int i = 0; i < numLines + 1; i++)
        {
            int j = i % numLines;

            float x = cosf(angleStep * j) * cb.radius + cb.offset.x;
            float y = sinf(angleStep * j) * cb.radius + cb.offset.y;

            // reverse transform's rotation & scaling for bounds
            Vector2 v = Vector2(x, y).Rotated(-tf.rotation) / tf.scale;
            points.push_back(v);
        }

        DrawWireframe(scene.GetCamera(), tf, points, 0, 0, 1.0f);
    }

    for (Entity id : scene.GetEntities<BoxBounds>())
    {
        Transform& tf = scene.GetComponent<Transform>(id);
        BoxBounds& b = scene.GetComponent<BoxBounds>(id);

        float w = b.width / 2;
        float h = b.height / 2;
        std::vector<Vector2> points = 
        {
            Vector2(-w, -h), // top left
            Vector2(w, -h),  // top right
            Vector2(w, h),   // bottom right
            Vector2(-w, h)   // bottom left
        };
        
        for (auto& v : points)
        {
            v = v.Rotated(-tf.rotation) / tf.scale; // reverse transform's rotation & scaling for bounds
            v += b.offset;
        }

        DrawWireframe(scene.GetCamera(), tf, points, 0, 0, 1.0f);
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