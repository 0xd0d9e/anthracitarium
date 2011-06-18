//encoding utf-8
#ifndef __RndarCamera__
#define __RndarCamera__

#include <QtCore/QDebug>
#include <QtCore/QObject>

#include "math/vector3.hpp"

namespace Render {

class Camera : public QObject {
    Q_OBJECT
//     Q_PROPERTY( Math::Vector3 pos READ pos WRITE setPos )
//     Q_PROPERTY( Math::Vector3 center READ center WRITE setCenter )
//     Q_PROPERTY( Math::Vector3 dir READ dir WRITE setDir )
public:
    Camera( const Math::Vector3 & pos,
        const Math::Vector3 & center = Math::Vector3(),
        const Math::Vector3 & dir = Math::Vector3( 0, 0, 1 ), QObject * parent = 0 );
    explicit Camera( QObject * parent = 0 );

    const Math::Vector3 pos() const;
    const Math::Vector3 center() const;
    const Math::Vector3 dir() const;

    void setPos( const Math::Vector3 & pos );
    void setCenter( const Math::Vector3 & center );
    void setDir( const Math::Vector3 & dir );
    void place();

private:
    Math::Vector3 pos_;
    Math::Vector3 center_;
    Math::Vector3 dir_;

}; // class Camera

inline const Math::Vector3 Render::Camera::pos() const {
    return pos_;
}

inline const Math::Vector3 Render::Camera::center() const {
    return center_;
}

inline const Math::Vector3 Render::Camera::dir() const {
    return dir_;
}

inline void Render::Camera::setPos( const Math::Vector3 & pos ) {
    pos_ = pos;
}

inline void Render::Camera::setCenter( const Math::Vector3 & center ) {
    center_ = center;
}

inline void Render::Camera::setDir( const Math::Vector3 & dir ) {
    dir_ = dir;
}

inline QDebug operator << ( QDebug debug, const Render::Camera & camera ) {
    debug.nospace() << "Render::Camera(pos:" << camera.pos() << ",center:" << camera.center() << ",dir:" << camera.dir() << ")";
    return debug;
}

}; // namespace Render

#endif//__RndarCamera__
