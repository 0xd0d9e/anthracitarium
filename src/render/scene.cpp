//author 0xd0d9e
//encoding utf-8
#include <QtOpenGL>

#include "dbg/dbg.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "scene.hpp"

namespace Render
{

Scene::Scene( QObject * parent )
    : QGraphicsScene(parent),
    lighting(true),
    camera_(0),
    fov_(60),
    near_(0.1),
    far_(1000)
{
    setForegroundBrush(Qt::NoBrush);
    setBackgroundBrush(Qt::NoBrush);
}

void Scene::paint()
{
    glEnable(GL_DEPTH_TEST);
    foreach ( Object * object, objects )
    {
        object->paint();
    }
    glDisable(GL_DEPTH_TEST);
}

void Scene::paintSel()
{
    glEnable(GL_DEPTH_TEST);
    int i = 0;
    foreach ( Object * object, objects )
    {
        glPushName(i);
        object->paint(Object::SelectMode);
        glPopName();
        ++i;
    }
    glDisable(GL_DEPTH_TEST);
}

void Scene::select()
{
    const GLuint bufferSize = 128;
    GLuint buffer[bufferSize];

    glSelectBuffer( bufferSize, buffer );

    const int w = width(),
              h = height();

    GLint viewport[4];

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport( 0, 0, w, h );
    glGetIntegerv( GL_VIEWPORT, viewport );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glRenderMode(GL_SELECT);
    glInitNames();

    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix( cursor.x(), h - cursor.y() - 1, 5, 5, viewport );
    gluPerspective( fov_, w / float(h), near_, far_ );

    glPushMatrix();

    if (camera_)
        camera_->place();
    paintSel();

    glPopMatrix();
    glPopMatrix();

    quint32 hits = glRenderMode(GL_RENDER),
            count,
            * ptr = buffer;

//     qDebug() << "hits" << hits << ", x" << cursor.x() << ", y" << cursor.y();

    objectsByCursor.clear();
    for ( quint32 i = 0; i < hits; ++i )
    {
        count = *ptr;ptr++;
        if (!count)
            continue;
        ptr++;ptr++;
        objectsByCursor.append( objects[*ptr] );
        ptr++;
    }
}

void Scene::drawBackground( QPainter * painter, const QRectF & )
{

    Q_UNUSED(painter);

    select();

    const int w = width(),
              h = height();

//     painter->beginNativePainting();
    glClearColor( 0, 0, 0, 1.0 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport( 0, 0, w, h );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( fov_, w / float(h), near_, far_ );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    if (camera_)
        camera_->place();

    if (lighting)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        GLfloat globalAmbient[] = { 1, 1, 1, 1 };
        GLfloat ambient[] = { 1, 1, 1, 1 };
        GLfloat diffuse[] = { 1, 1, 1, 1 };
        GLfloat lightPos[] = { 0, 0, 100, 1 };

        glLightModelfv( GL_LIGHT_MODEL_AMBIENT, globalAmbient );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
        glLightfv( GL_LIGHT0, GL_SPECULAR, diffuse );
        glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
        glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
    }

    paint();

    if (lighting)
    {
        glDisable(GL_LIGHTING);
    }

    glPopMatrix();
//     painter->endNativePainting();

}

}//namespace Render
