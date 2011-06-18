//encoding utf-8
#include <QtOpenGL>

#include "dbg/dbg.hpp"
#include "camera.hpp"

using namespace Render;

Camera::Camera( const Math::Vector3 & pos, const Math::Vector3 & center,
    const Math::Vector3 & dir, QObject * parent )
    : QObject(parent),
    pos_(pos),
    center_(center),
    dir_(dir)
{
}

Camera::Camera( QObject * parent )
    : QObject(parent)
{
}

void Camera::place() {
//     gluLookAt(
//         pos_.x(), pos_.y(), pos_.z(),
//         center_.x(), center_.y(), center_.z(),
//         dir_.x(), dir_.y(), dir_.z()
//     );
//     QyDbgPos();
//     QyDbgValue(pos_.x());QyDbgValue(pos_.y());QyDbgValue(pos_.z());
//     QyDbgValue(dir_.x());QyDbgValue(dir_.y());QyDbgValue(dir_.z());
//     QyDbgValue(center_.x());QyDbgValue(center_.y());QyDbgValue(center_.z());
    glTranslated( pos_.x(), pos_.y(), pos_.z() );
    glRotated( dir_.x(), 1.0, 0.0, 0.0 );
    glRotated( dir_.y(), 0.0, 1.0, 0.0 );
    glRotated( dir_.z(), 0.0, 0.0, 1.0 );
    glTranslated( center_.x(), center_.y(), center_.z() );
}
