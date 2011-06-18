//encoding utf-8
#include <QtOpenGL>

#include "dbg/dbg.hpp"

#include "scene.hpp"
#include "view.hpp"

namespace Render
{

View::View( QWidget * parent )
    : QGraphicsView(parent),
    interval_(0),
    timerId_(0),
    hasOpenGL_(false)
{
    setMouseTracking(true);
    setOpenGL(true);
}

void View::setOpenGL( const bool enabled )
{
    if ( enabled == hasOpenGL_ )
        return;

    hasOpenGL_ = enabled;
    if (hasOpenGL_)
    {
        viewport_ = new QGLWidget( QGLFormat(QGL::SampleBuffers), this );
        setViewport(viewport_);

        viewport_->makeCurrent();
        glClearColor( 0, 0, 0, 1.0 );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //     glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glPolygonMode( GL_FRONT, GL_FILL );
        glPolygonMode( GL_BACK, GL_LINE );
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset( 1.0, 2.0 );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }
    else
    {
        defaultVP_ = new QWidget(this);
        setViewport(defaultVP_);
    }
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setCacheMode(QGraphicsView::CacheNone);
    setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    setForegroundBrush(Qt::NoBrush);
    setBackgroundBrush(Qt::NoBrush);
}

void View::resizeEvent( QResizeEvent * event )
{
    if ( QGraphicsScene * scene_ = scene() )
        scene_->setSceneRect( 0, 0, viewport()->width(), viewport()->height() );
    QGraphicsView::resizeEvent(event);
}

void View::timerEvent( QTimerEvent * timerEvent )
{

    if ( timerId_ == timerEvent->timerId() )
    {
        killTimer(timerId_);
        viewport()->updateGL();
        update();
        repaint();
        scene()->update();
        timerId_ = startTimer(interval_);
    }
    else
    {
        QGraphicsView::timerEvent(timerEvent);
    }

}

void View::mouseMoveEvent( QMouseEvent * event )
{
    if ( Scene * s = dynamic_cast<Scene*>( scene() ) )
    {
        s->cursor = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}

}//namespace Render
