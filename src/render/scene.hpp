//author 0xd0d9e
//encoding utf-8
#ifndef __RndarScene__
#define __RndarScene__

#include <QtGui/QGraphicsScene>

namespace Render
{

class Camera;
class Object;

class Scene : public QGraphicsScene
{
public:
    explicit Scene( QObject * parent = 0 );


    inline Camera * camera() const { return camera_; }
    inline double getFov() const { return fov_; }
    inline double getNear() const { return near_; }
    inline double getFar() const { return far_; }

    inline void setCamera( Camera * camera ) { camera_ = camera; }
    inline void setFov( const double f ) { fov_ = f; }
    inline void setNear( const double n ) { near_ = n; }
    inline void setFar( const double f ) { far_ = f; }

    QList<Object*> objects;
    QList<Object*> objectsByCursor;
    QPointF cursor;
    bool lighting;

protected:
    virtual void paint();
    virtual void paintSel();
    virtual void select();

private:
    void drawBackground( QPainter * painter, const QRectF & );

    Camera * camera_;
    double fov_;
    double near_;
    double far_;

};

};//namespace Render

#endif//__RndarScene__
