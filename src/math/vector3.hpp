//author 0xd0d9e
//encoding utf-8
#ifndef __QyMath_Vector3__
#define __QyMath_Vector3__

#include "angle.hpp"
#include "point3.hpp"

//! \file Vector3 declaration

namespace Math
{

//! \brief for vector math
class Vector3 : public Point3
{
public:
    //! Constructor
    explicit Vector3( const qreal x = 0, const qreal y = 0, const qreal z = 0 );

    //! Copy constructor
    explicit Vector3( const Point3 & point ) : Point3(point) {}

    //! return vector length
    inline qreal length() const;

    //! move vector
    inline Vector3 & move( const qreal distance, const Angle & angle );

    //! rotate vector around coordinate center
    inline Vector3 & rotate( const Angle & angle );

};//class Vector

/*! \name utilites
    \relates Point3 Vector3
*/
//! return legs for triangle framed of vectors \a p1 and \a p2
inline Vector3 legs( const Point3 & p1, const Point3 & p2 );

//! return distance between \a p1 and \a p2
inline qreal distance( const Point3 & p1, const Point3 & p2 );

//! return direction from \a p1 to \a p2 on into Z plane
inline Angle direction( const Point3 & p1, const Point3 & p2 );
//! @}


inline qreal Vector3::length() const
{
    return sqrt( x() * x() + y() * y() );
}

inline Vector3 & Vector3::move( const qreal distance, const Angle & angle )
{

    qreal dc_sin,
          dc_cos;

    angle.sincos( &dc_sin, &dc_cos );

    rx() += dc_sin * distance;
    ry() += dc_cos * distance;

    return *this;
}

inline Vector3 & Vector3::rotate( const Angle & angle )
{
    if ( !angle.isNull() )
    {
        Angle trueAngle = -angle;
        qreal sin,
              cos;

        trueAngle.sincos( &sin, &cos );

        qreal nx = x() * cos - y() * sin;
        qreal ny = x() * sin + y() * cos;
        setX(nx);
        setY(ny);
    }

    return *this;
}

inline Vector3 legs( const Point3 & p1, const Point3 & p2 )
{

    return Vector3( p2 - p1 );
}

inline qreal distance( const Point3 & p1, const Point3 & p2 )
{

    Point3 legs = p2 - p1;
    return sqrt( legs.x() * legs.x() + legs.y() * legs.y() + legs.z() * legs.z() );
}

inline Angle direction( const Point3 & p1, const Point3 & p2 )
{

        qreal hypotenuse = distance( p1, p2 );

        if ( qFuzzyCompare( hypotenuse, 0 ) )
            return Angle();

        Angle angle( asin( ( p2.x() - p1.x() ) / hypotenuse ) );

        return ( ( p2.y() - p1.y() ) < 0 )
            ? Angle::normalize( M_PI - angle.radian() )
            : angle;
}

} //Math

Q_DECLARE_TYPEINFO( Math::Vector3, Q_MOVABLE_TYPE );

#endif//__Math_Vector3__
//author 0xd0d9e
