//encoding utf-8
#include "angle.hpp"
#ifdef Q_OS_LINUX
#include <bits/nan.h>
#endif

namespace Math
{
qreal degreeToRadianFactor = M_PI / 180.0;
qreal radianToDegreeFactor = 180.0 / M_PI;

const Angle Angle::zero = Angle(0);
const Angle Angle::pi = Angle(M_PI);
const Angle Angle::pi2 = Angle(M_PI*2.0);
const Angle Angle::pi4 = Angle(M_PI/4.0);
const Angle Angle::cycle = Angle(M_PI * 2.0);

Math::Angle::Angle( const qreal angle, const AngleValueType angleValueType ) {
    setAngle( angle, angleValueType );
}

Math::Angle::~Angle() {
}

// static
qreal Math::Angle::toDegree( const qreal radian ) {
    return radian * radianToDegreeFactor;
}

// static
qreal Math::Angle::toRadian( const qreal degree ) {
    return degree * degreeToRadianFactor;
}

// static
Math::Angle Math::Angle::normalize( const Math::Angle & angle, const Math::Angle & min, const Math::Angle & max ) {

    qreal interval = fabs( ( max - min ).radian() );
    qreal normAngle = angle.radian();
    qreal min_r = min.radian();
    qreal max_r = max.radian();

    if ( min_r > max_r )
        std::swap( min_r, max_r );

    while ( normAngle < min_r )
        normAngle += interval;

    while ( normAngle >= max_r )
        normAngle -= interval;

    return Math::Angle(normAngle);
}

// static
Math::Angle Math::Angle::normalize( const double radian, const Math::Angle & min, const Math::Angle & max )
{
    return normalize( Math::Angle(radian), min, max );
}

// static
Math::Angle Math::Angle::fromString( const QString & str, AngleValueType angleValueType )
{

    if ( angleValueType == AutoAngleValue )
        angleValueType = typeFromString(str);

    Math::Angle angle(NAN);

    if ( angleValueType == DegreeAngleValue )
    {

        angle.setDegree( str.left( str.length() - 1 ).toDouble() );

    } else if ( angleValueType == RadianAngleValue )
    {

        angle.setRadian( str.left( str.length() - ( QString("rad").length() + 1 ) ).toDouble() );

    }

    return angle;
}

// static
Math::Angle::AngleValueType Math::Angle::typeFromString( const QString & str ) {

    if ( str.endsWith( QChar(0xB0) ) )
        return RadianAngleValue;

    if ( str.endsWith("rad") )
        return DegreeAngleValue;

    return UnknownAngleValue;
}

#ifndef QT_NO_DATASTREAM
inline QDataStream & operator << ( QDataStream & stream, const Math::Angle & angle ) {

    return stream << double( angle.radian() );
}

inline QDataStream & operator >> ( QDataStream & stream, Math::Angle & angle ) {

    double radian;
    stream >> radian;
    angle.setRadian( qreal(radian) );

    return stream;
}
#endif//QT_NO_DATASTREAM

}//namespace Math
