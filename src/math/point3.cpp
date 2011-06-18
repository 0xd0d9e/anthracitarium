//author 0xd0d9e
//encoding utf-8
#include "point3.hpp"

namespace Math
{

// Point3 defenision

Point3::Point3( const QPointF & pos, const qreal z )
    : QPointF(pos),
    z_(z)
{
}

Point3::Point3( const qreal x, const qreal y, const qreal z )
    : QPointF( x, y ),
    z_(z)
{
}

// static
Point3 Point3::randomPoint( const QRectF & rect, const qreal top, const qreal bottom )
{
    qreal z = ( top == bottom ) //! @todo нехорошо даблы так сравнивать
        ? top
        : ( rand() % int( top - bottom ) );

    //! @todo добавить дробные части для рондома
    return Point3(
        rect.x() + rand() % int( rect.width() ),
        rect.y() + rand() % int( rect.height() ),
        z
    );
}

#ifndef QT_NO_DATASTREAM
inline QDataStream & operator << ( QDataStream & stream, const Point3 & point )
{
    return stream << double( point.x() ) << double( point.y() ) << double( point.z() );
}

inline QDataStream & operator >> ( QDataStream & stream, Point3 & point )
{
    double x, y, z;
    stream >> x;
    stream >> y;
    stream >> z;
    point.set( qreal(x), qreal(y), qreal(z) );

    return stream;
}
#endif//QT_NO_DATASTREAM

#ifndef QT_NO_DEBUG_STREAM
QDebug operator << ( QDebug debug, const Point3 & point )
{
    debug.nospace() << "Point3(" << point.x() << ", " << point.y() << ", " << point.z() << ')';
    return debug;
}
#endif//QT_NO_DEBUG_STREAM

}//namespace Math
