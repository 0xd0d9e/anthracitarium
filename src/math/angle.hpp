//author 0xd0d9e
//encoding utf-8
#ifndef __QyMath_Angle__
#define __QyMath_Angle__

#include <math.h>

#include <QtCore/QDebug>
#include <QtGlobal>


/*! \file Angle declaration
    \author Agapov Yuriy
*/
#ifndef QT_NO_DATASTREAM
class QDataStream;
#endif

namespace Math
{

class Angle;

inline bool operator == ( const Angle &, const Angle & );
inline bool operator == ( const Angle &, double );
inline bool operator != ( const Angle &, const Angle & );
inline bool operator != ( const Angle &, double );
inline bool operator > ( const Angle &, const Angle & );
inline bool operator < ( const Angle &, const Angle & );
inline bool operator >= ( const Angle &, const Angle & );
inline bool operator <= ( const Angle &, const Angle & );

//! \brief Тип для хранения и обработки угловых велечин (хранится в радианах)
class Angle
{
public:
    //! Типы угловых величин
    enum AngleValueType
    {
        UnknownAngleValue,  //!< Определить не удалось (только для typeFromString)
        AutoAngleValue,     //!< Автоматическое определение (обычно означает радианы)
        RadianAngleValue,   //!< Значение в радианах
        Radian = RadianAngleValue, //!< Значение в радианах (псевдоним для RadianAngleValue)
        DegreeAngleValue,   //!< Значение в градцсах
        Degree = DegreeAngleValue //!< Значение в градцсах (псевдоним для DegreeAngleValue)
    };
    //! Конструктор
    Angle( const double angle = 0, const AngleValueType angleValueType = AutoAngleValue );

    //! Деструктор
    ~Angle();

    //! Возвращает true если угол равен 0
    inline bool isNull() const;

    //! Возвращает true если угол не валиден (значение угла равно nan)
    inline bool isValid() const;

    //! Получить угол в радианах
    inline double radian() const;

    //! Получить угол в градусах
    inline double degree() const;

    //! Получить угол в заданных единицах измерения
    inline double angle( const AngleValueType angleValueType ) const;

    //! Получить зеркальное отражение угла (например: 270 <-> 90, 45 <-> 315, 160 <-> 200 )
    inline Angle mirror() const;

    //! Получить значение округленное с учетом заданного дискрета \a value (например: Angle(170).adjust( 45, Angle::DegreeAngleValue ) // return 180 )
    inline Angle adjust( double value, const AngleValueType sectionValueType = AutoAngleValue ) const;

    //! Получить строковое представление значения угла в заданных единицах измерения
    inline QString toString( const AngleValueType angleValueType = AutoAngleValue );

    //! Получить строку для отладки
    inline QString debugString() const;

    //! Вывести отладочную информацию в stdout
    inline void debug() const;

    //! Получить синус угла
    inline double sin() const;

    //! Получить косинус угла
    inline double cos() const;

    //! Расчет синуса и косинуса угла за один вызов
    inline void sincos( double * sinout, double * cosout ) const;

    //! Задать значение в радианах
    inline void setRadian( const double radian );

    //! Задать значение в градцсах
    inline void setDegree( const double degree );

    //! Задать значение в заданных единицах измерения
    inline void setAngle( const double angle, const AngleValueType angleValueType = AutoAngleValue );

    //! \name Операторы
    inline Angle & operator *= ( const Angle & angle );
    inline Angle & operator += ( const Angle & angle );
    inline Angle & operator -= ( const Angle & point );
    inline Angle & operator /= ( const Angle & angle );
    inline Angle & operator = ( const double radian );
    //! @}

    //! Преобразовать радианы в градусы
    static double toDegree( const double radian );

    //! Преобразовать градусы в радианы
    static double toRadian( const double degree );

    //! Прочитать значение из строки
    static Angle fromString( const QString & str, AngleValueType angleValueType = AutoAngleValue );

    //! Получить единиуы измерения из строки, если единицы измерения угла не указаны, возвращает UnknownAngleValue
    static AngleValueType typeFromString( const QString & str );

//     //! Нормировать угол
    static Angle normalize( const Angle & angle, const Angle & min = zero,
        const Angle & max = cycle );

//     //! Нормировать угол
    static Angle normalize( const double radian, const Angle & min = zero,
        const Angle & max = cycle );

    friend bool operator == ( const Angle &, const Angle & );
    friend bool operator == ( const Angle &, double );
    friend bool operator != ( const Angle &, const Angle & );
    friend bool operator != ( const Angle &, double );
    friend bool operator > ( const Angle &, const Angle & );
    friend bool operator < ( const Angle &, const Angle & );
    friend bool operator >= ( const Angle &, const Angle & );
    friend bool operator <= ( const Angle &, const Angle & );

    static const Angle zero;  //! Нулевой угол
    static const Angle pi;    //! Половина круга
    static const Angle pi2;   //! Четверть круга
    static const Angle pi4;   //! Восьмая часть круга
    static const Angle cycle; //! Полный круг

private:
    double radian_;

};//class Angle

/*! \name Операторы
    \relates Angle
*/
inline bool operator == ( const Angle &, const Angle & );
inline bool operator == ( const Angle &, double );
inline bool operator != ( const Angle &, const Angle & );
inline bool operator != ( const Angle &, double );
inline bool operator > ( const Angle &, const Angle & );
inline bool operator < ( const Angle &, const Angle & );
inline bool operator >= ( const Angle &, const Angle & );
inline bool operator <= ( const Angle &, const Angle & );
inline const Angle operator + ( const Angle &, const Angle & );
inline const Angle operator - ( const Angle &, const Angle & );
inline const Angle operator * ( const Angle &, const Angle & );
inline const Angle operator - ( const Angle & );
inline const Angle operator / ( const Angle &, const Angle & );
inline const Angle operator * ( const Angle &, const double );
inline const Angle operator / ( const Angle &, const double );

#ifndef QT_NO_DATASTREAM
QDataStream & operator << ( QDataStream & stream, const Angle & angle );
QDataStream & operator >> ( QDataStream & stream, Angle & angle );
#endif//QT_NO_DATASTREAM

inline QDebug operator << ( QDebug debug, const Angle & angle ) {
    return debug << qPrintable( angle.debugString() );
}
//! @}

//! тест угла с порогом
static inline bool qFuzzyAngleIsNull( const Angle & angle ) {
    return fabs( angle.radian() ) <= 0.000000000001;
}

inline bool Angle::isNull() const {
    return qFuzzyAngleIsNull(*this);
}

inline bool Angle::isValid() const {
    return !isnan(radian_);
}

inline double Angle::radian() const {
    return radian_;
}

inline double Angle::degree() const {
    return toDegree(radian_);
}

inline double Angle::angle( const Angle::AngleValueType angleValueType ) const {
    return ( angleValueType == DegreeAngleValue ) ? toDegree(radian_) : radian_;
}

inline Angle Angle::mirror() const {
    return normalize( M_PI * 2.0 - radian_ );
}

inline Angle Angle::adjust( double value, const Angle::AngleValueType sectionValueType ) const {
    if ( sectionValueType == DegreeAngleValue )
        value = toRadian(value);
    return Angle( qRound( radian_ / value ) * value );
}

inline QString Angle::toString( const AngleValueType angleValueType ) {
    return ( angleValueType == DegreeAngleValue )
        ? QString("%1%2").arg( toDegree(radian_) ).arg( QChar(0xB0) )
        : QString("%1 %2").arg(radian_).arg("rad");
}

inline QString Angle::debugString() const {

    return QString("Angle(%1%2,%3)").arg( degree() ).arg( QChar(0xB0) ).arg( radian() );
}

inline void Angle::debug() const {
    qDebug( "%s", qPrintable( debugString() ) );
}

inline double Angle::sin() const {
    return ::sin(radian_);
}

inline double Angle::cos() const {
    return ::cos(radian_);
}

inline void Angle::sincos( double * sinout, double * cosout ) const {

    if ( !sinout || !cosout )
        return;

#ifdef __sincos_code
    double s, c;
    ::__sincos( double(radian_), &s, &c );
    *sinout = s;
    *cosout = c;
#else
    *sinout = ::sin(radian_);
    *cosout = ::cos(radian_);
#endif
}

inline void Angle::setRadian( const double radian ) {
    radian_ = radian;
}

inline void Angle::setDegree( const double degree ) {
    radian_ = toRadian(degree);
}

inline void Angle::setAngle( const double angle, const Angle::AngleValueType angleValueType ) {
    radian_ = ( angleValueType == DegreeAngleValue ) ? toRadian(angle) : angle;
}

inline Angle & Angle::operator *= ( const Angle & angle ) {
    radian_ *= angle.radian_;
    return *this;
}

inline Angle & Angle::operator += ( const Angle & angle ) {
    radian_ += angle.radian_;
    return *this;
}

inline Angle & Angle::operator -= ( const Angle & angle ) {
    radian_ -= angle.radian_;
    return *this;
}

inline Angle & Angle::operator /= ( const Angle & angle ) {
    radian_ /= angle.radian_;
    return *this;
}

inline Angle & Angle::operator = ( const double radian ) {
    radian_ = radian;
    return *this;
}

inline bool operator == ( const Angle & a1, const Angle & a2 ) {
    return qFuzzyAngleIsNull( Angle::normalize(a1) - Angle::normalize(a2) );
}

inline bool operator == ( const Angle & angle, double radian ) {
    return qFuzzyAngleIsNull( Angle::normalize(angle) - Angle::normalize(radian) );
}

inline bool operator != ( const Angle & a1, const Angle & a2 ) {
    return !qFuzzyAngleIsNull( Angle::normalize(a1) - Angle::normalize(a2) );
}

inline bool operator != ( const Angle & angle, const double radian ) {
    return !qFuzzyAngleIsNull( Angle::normalize(angle) - Angle::normalize(radian) );
}

inline bool operator > ( const Angle & a1, const Angle & a2 ) {
    return  Angle::normalize(a1).radian() > Angle::normalize(a2).radian();
}

inline bool operator < ( const Angle & a1, const Angle & a2 ) {
    return  Angle::normalize(a1).radian() <  Angle::normalize(a2).radian();
}

inline bool operator >= ( const Angle & a1, const Angle & a2 ) {
    return a1 == a2 || a1 > a2;
}

inline bool operator <= ( const Angle & a1, const Angle & a2 ) {
    return ( a1 == a2 ) || ( a1 < a2 );
}

inline const Angle operator + ( const Angle & a1, const Angle & a2 ) {
    return Angle( a1.radian() + a2.radian() );
}

inline const Angle operator - ( const Angle & a1, const Angle & a2 ) {
    return Angle( a1.radian() - a2.radian() );
}

inline const Angle operator * ( const Angle & a1, const Angle & a2 ) {
    return Angle( a1.radian() * a2.radian() );
}

inline const Angle operator - ( const Angle & angle ) {
    return Angle( -angle.radian() );
}

inline const Angle operator / ( const Angle & a1, const Angle & a2 ) {
    return Angle( a1.radian() / a2.radian() );
}

inline const Angle operator / ( const Angle & angle, const double radian ) {
    return Angle( angle.radian() / radian );
}

inline const Angle operator * ( const Angle & angle, const double radian ) {
    return Angle( angle.radian() * radian );
}

}//namespace Math

Q_DECLARE_TYPEINFO( Math::Angle, Q_MOVABLE_TYPE );

#endif//__QyMath_Angle__
