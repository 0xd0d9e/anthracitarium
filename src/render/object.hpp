//author 0xd0d9e
//encoding utf-8
#ifndef __Rndar_Object__
#define __Rndar_Object__

#include <math.h>

#include <QColor>
#include <QtGlobal>

#include "math/point3.hpp"

class QGLWidget;

namespace Render
{

class Scene;

class Object
{
public:
    enum PaintFlags
    {
        SelectMode = 1
    };
    Object();

    uint id() const;
    virtual Math::Point3 pos() const = 0;

    virtual void setPos( const Math::Point3 & pos ) = 0;
    virtual void paint( const int flags = 0 ) = 0;
    virtual void select();

    Scene * scene;

private:
    Q_DISABLE_COPY(Object)

    quint32 id_;

};

class Box : public Object
{
public:
    enum Sides
    {
        TopSide     = 1,
        BottomSide  = 1 << 1,
        LeftSide    = 1 << 2,
        RightSide   = 1 << 3,
        FrontSide   = 1 << 4,
        BackSide    = 1 << 5,
        FullBox = TopSide|BottomSide|LeftSide|RightSide|FrontSide|BackSide
    };
    explicit Box( const Math::Point3 & size = Math::Point3(1,1,1) );

    Math::Point3 pos() const;
    Math::Point3 size() const;

    void setPos( const Math::Point3 & pos );
    void setSize( const Math::Point3 & size );

    void paint( const int flags = 0 );
    void updateCache();

    QColor color;
    int sides;

private:
    Math::Point3 pos_;
    Math::Point3 size_;
    quint32 cache;

};

class Axis : public Object
{
public:
    explicit Axis( const qreal size = 1 );

    Math::Point3 pos() const;
    qreal size() const;

    void setPos( const Math::Point3 & pos );
    void setSize( const qreal size );

    void paint( const int flags = 0 );

    QColor colorX;
    QColor colorY;
    QColor colorZ;

private:
    Math::Point3 pos_;
    qreal size_;
};

class Space : public Object
{
public:
    enum
    {
        chunkSize = 16,
        chunkHeight = 128
    };
    class Index3
    {
    public:
        explicit Index3( const qint32 x = 0, const qint32 y = 0, const qint32 z = 0 )
            : x_(x), y_(y), z_(z), i_( ( x * chunkSize + y ) + z * chunkSize * chunkSize ) {}

        qint32 x() const { return x_; }
        qint32 y() const { return y_; }
        qint32 z() const { return z_; }
        qint32 toInt() const { return i_; }
        Index3 sub() const { return Index3( floor( x_ / chunkSize ), floor( y_ / chunkSize ), floor( z_ / chunkHeight ) ); }
        Index3 left() const { return Index3( x_-1, y_, z_ ); }
        Index3 right() const { return Index3( x_+1, y_, z_ ); }
        Index3 top() const { return Index3( x_, y_, z_+1 ); }
        Index3 bottom() const { return Index3( x_, y_, z_-1 ); }
        Index3 front() const { return Index3( x_, y_+1, z_ ); }
        Index3 back() const { return Index3( x_, y_-1, z_ ); }

        inline bool operator < ( const Index3 & i3 ) const
        {
            return i_ < i3.i_;
        }

    private:
        qint32 x_,
               y_,
               z_,
               i_;

    };
    class Material
    {
    public:
        QColor color;
    };
    class Block
    {
    public:
        explicit Block( const Index3 & p ) : pos(p) {}

        quint32 materialId;
        Index3 pos;
    };
    class Chunk : public QVector<Block*>
    {
    public:
        Chunk() : QVector<Block*>( chunkSize * chunkSize * chunkHeight ) {}
    };

    Math::Point3 pos() const;

    Block * block( const Index3 & pos );
    void setPos( const Math::Point3 & pos );
    void paint( const int flags = 0 );

    QMap<int,Material> materials;
    QMap<Index3,Chunk> chunks;

private:
    Math::Point3 pos_;

};

}//namespace Render

inline Render::Space::Index3 operator - ( const Render::Space::Index3 & i3_1, const Render::Space::Index3 & i3_2 )
{
    return Render::Space::Index3( i3_1.x() - i3_2.x(), i3_1.y() - i3_2.y(), i3_1.z() - i3_2.z() );
}

inline Render::Space::Index3 operator + ( const Render::Space::Index3 & i3_1, const Render::Space::Index3 & i3_2 )
{
    return Render::Space::Index3( i3_1.x() + i3_2.x(), i3_1.y() + i3_2.y(), i3_1.z() + i3_2.z() );
}

inline QDebug operator << ( QDebug dbg, const Render::Space::Index3 & i3 )
{
    dbg.nospace() << "Index3(" << i3.x() << "," << i3.y() << "," << i3.z() << ")";
    return dbg;
}

#endif//__Rndar_Object__
