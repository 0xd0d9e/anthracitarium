#ifndef __CameraController__
#define __CameraController__

#include <QWheelEvent>

#include "dbg/dbg.hpp"
#include "render/camera.hpp"
#include "tools/eventcontroller.hpp"

namespace Render
{

class CameraController :
    public ::Tools::EventController,
    public ::Tools::MouseProcessor
{
    Q_OBJECT
    typedef ::Tools::EventProcessor<CameraController,QWheelEvent> WheelEventProcessor;
public:
    explicit CameraController( Camera * camera )
        : zoomFactor(0.5), camera_(camera)
    {
        MouseProcessor::install(this);
        addProcessor( QEvent::Wheel, new WheelEventProcessor( this, &CameraController::wheelEvent ) );
    }

    void mouseMoveEvent( QMouseEvent * event )
    {
        MouseProcessor::mouseMoveEvent(event);
        if ( pressedButtons() == Qt::MidButton )
        {
            Math::Vector3 vector( -moveOffset().x(), moveOffset().y(), 0 );
            Math::Angle angle( camera_->dir().z(), Math::Angle::Degree );
            vector.rotate(angle);

            Math::Vector3 center( camera_->center() + vector / 10.0 );
            camera_->setCenter(center);
            emit centerChanged();
        }
        if ( pressedButtons() == Qt::RightButton )
        {
            Math::Vector3 dir( camera_->dir() - Math::Point3( moveOffset().y(), 0, moveOffset().x() ) );
            camera_->setDir(dir);

            Math::Angle angle( camera_->dir().z(), Math::Angle::Degree );

            emit directionChanged();
        }
    }

    void wheelEvent( QWheelEvent * event )
    {
        int delta = event->delta() / fabs( event->delta() );
        camera_->setPos( Math::Vector3( camera_->pos() + Math::Vector3( 0, 0, zoomFactor ) * delta ) );
        emit zoomChenged();
    }

    qreal zoomFactor;

signals:
    void centerChanged();
    void directionChanged();
    void zoomChenged();

private:
    Render::Camera * camera_;

};

}//namespace Render

#endif//__CameraController__
