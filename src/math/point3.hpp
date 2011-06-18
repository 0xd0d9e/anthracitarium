//author 0xd0d9e
//encoding utf-8
#ifndef __QyMathPoint__
#define __QyMathPoint__

#ifndef QT_NO_DEBUG_STREAM
#include <QtCore/QDebug>
#endif
#include <QtCore/QPointF>
#include <QtCore/QRectF>

//! \file Point3 declaration

#ifndef QT_NO_DATASTREAM
class QDataStream;
#endif

namespace Math
{

class Point3;

inline bool operator == ( const Point3 & p1, const Point3 & p2 );
inline bool operator != ( const Point3 & p1, const Point3 & p2 );

//! \brief point x, y, z
class Point3 : public QPointF
{
public:
    //! Constructor
    explicit Point3( const QPointF & pos, const qreal z = 0 );
    explicit Point3( const qreal x = 0, const qreal y = 0, const qreal z = 0 );

    //! return z coordinate
    inline qreal z() const;
    inline Point3 swapAxis() const;

    //! set z coordinate
    inline void setZ( qreal z );

    //! set all coordinates
    inline void set( const qreal x = 0, const qreal y = 0, const qreal z = 0 );

    //! \name operators
    inline Point3 & operator *= ( const qreal factor );
    inline Point3 & operator += ( const Point3 & point );
    inline Point3 & operator -= ( const Point3 & point );
    inline Point3 & operator /= ( const qreal divisor );
    //! @}

    friend inline bool operator == ( const Point3 &, const Point3 & );
    friend inline bool operator != ( const Point3 &, const Point3 & );

    static Point3 randomPoint( const QRectF & rect, const qreal top = 0, const qreal bottom = 0 );

private:
    qreal z_;

}; // class Point3

/*! \name operators
    \relates Point3
*/
inline bool operator == ( const Point3 & p1, const Point3 & p2 );
inline bool operator != ( const Point3 & p1, const Point3 & p2 );
inline const Point3 operator * ( const Point3 & point, const qreal factor );
inline const Point3 operator * ( const qreal factor, const Point3 & point );
inline const Point3 operator + ( const Point3 & p1, const Point3 & p2 );
inline const Point3 operator - ( const Point3 & p1, const Point3 & p2 );
inline const Point3 operator - ( const Point3 & point );
inline const Point3 operator / ( const Point3 & point, const qreal divisor );

#ifndef QT_NO_DATASTREAM
QDataStream & operator << ( QDataStream & stream, const Point3 & point );
QDataStream & operator >> ( QDataStream & stream, Point3 & point );
#endif

#ifndef QT_NO_DEBUG_STREAM
QDebug operator << ( QDebug debug, const Point3 & point );
#endif
//! @}

inline qreal Point3::z() const
{
    return z_;
}

inline Point3 Point3::swapAxis() const {
    return Point3( y(), x(), z() );
}

inline void Point3::setZ( const qreal z )
{
    z_ = z;
}

inline void Point3::set( const qreal x, const qreal y, const qreal z )
{
    setX(x);
    setY(y);
    setZ(z);
}

inline Point3 & Point3::operator *= ( const qreal factor )
{
    QPointF::operator *= (factor);
    z_ *= factor;
    return *this;
}

inline Point3 & Point3::operator += ( const Point3 & point )
{
    QPointF::operator += (point);
    z_ += point.z_;
    return *this;
}

inline Point3 & Point3::operator -= ( const Point3 & point )
{
    QPointF::operator -= (point);
    z_ -= point.z_;
    return *this;
}

inline Point3 & Point3::operator /= ( const qreal divisor )
{
    QPointF::operator /= (divisor);
    z_ /= divisor;
    return *this;
}

// relates
inline bool operator == ( const Point3 & p1, const Point3 & p2 )
{
    return qFuzzyCompare( p1.x() - p2.x(), 0 )
        && qFuzzyCompare( p1.y() - p2.y(), 0 )
        && qFuzzyCompare( p1.z_ - p2.z_, 0 );
}

inline bool operator != ( const Point3 & p1, const Point3 & p2 )
{
    return !qFuzzyCompare( p1.x() - p2.x(), 0 )
        || !qFuzzyCompare( p1.y() - p2.y(), 0 )
        || !qFuzzyCompare( p1.z_ - p2.z_, 0 );
}

inline const Point3 operator * ( const Point3 & point, const qreal factor )
{
    return Point3( point.x() * factor, point.y() * factor, point.z() * factor );
}

inline const Point3 operator * ( const qreal factor, const Point3 & point )
{
    return Point3( point.x() * factor, point.y() * factor, point.z() * factor );
}

inline const Point3 operator + ( const Point3 & p1, const Point3 & p2 )
{
    return Point3( p1.x() + p2.x(), p1.y() + p2.y(), p1.z() + p2.z() );
}

inline const Point3 operator - ( const Point3 & p1, const Point3 & p2 )
{
    return Point3( p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z() );
}

inline const Point3 operator - ( const Point3 & point )
{
    return Point3( -point.x(), -point.y(), -point.z() );
}

inline const Point3 operator / ( const Point3 & point, const qreal divisor )
{
    return Point3( point.x() / divisor, point.y() / divisor, point.z() / divisor );
}

} // namespace Math

Q_DECLARE_TYPEINFO( Math::Point3, Q_MOVABLE_TYPE );

#endif//__Point__
