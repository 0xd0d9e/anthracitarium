//author 0xd0d9e
//encoding utf-8
#include <QtOpenGL>

#include "object.hpp"
#include "scene.hpp"

namespace Render
{

static quint32 objectIds = 0;

//--------------------------------------------------------------------------------------------------

Object::Object()
    : scene(0), id_(++objectIds)
{
}

uint Object::id() const
{
    return id_;
}


void Object::select()
{
    paint(SelectMode);
}

//--------------------------------------------------------------------------------------------------

Box::Box( const Math::Point3 & size )
    : size_(size), cache(0)
{
    color = Qt::white;
    sides = FullBox;
}

Math::Point3 Box::pos() const
{
    return pos_;
}

Math::Point3 Box::size() const
{
    return size_;
}

void Box::setPos( const Math::Point3 & pos )
{
    pos_ = pos;
}

void Box::setSize( const Math::Point3 & size )
{
    size_ = size;
}

void Box::paint( const int flags )
{
    if (!cache)
        updateCache();
    glCallList(cache);
}

void Box::updateCache()
{
    if (!cache)
        cache = glGenLists(1);
    glNewList( cache, GL_COMPILE );
    glColor3f( color.redF(), color.greenF(), color.blueF() );
    Math::Point3 halfSize = size_ / 2.0;
//     qDebug() << "Box" << pos_ << halfSize;
    glBegin(GL_QUADS);
    // bottom
    if ( sides & BottomSide )
    {
        glNormal3d( 0, 0,-1 );
        glTexCoord2d( 0, 0 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() - halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 0, 1 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() + halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 1, 1 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() + halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 1, 0 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() - halfSize.y(), pos_.z() - halfSize.z() );
    }
    // top
    if ( sides & TopSide )
    {
        glNormal3d( 0, 0, 1 );
        glTexCoord2d( 0, 0 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() - halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 1, 0 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() - halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 1, 1 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() + halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 0, 1 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() + halfSize.y(), pos_.z() + halfSize.z() );
    }
    // front
    if ( sides & FrontSide )
    {
        glNormal3d( 1,-1, 0 );
        glTexCoord2d( 0, 0 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() - halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 1, 0 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() - halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 1, 1 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() - halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 0, 1 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() - halfSize.y(), pos_.z() + halfSize.z() );
    }
    // back
    if ( sides & BackSide )
    {
        glNormal3d( 1, 1, 0 );
        glTexCoord2d( 0, 0 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() + halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 0, 1 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() + halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 1, 1 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() + halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 1, 0 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() + halfSize.y(), pos_.z() - halfSize.z() );
    }
    // left
    if ( sides & LeftSide )
    {
        glNormal3d(-1, 0, 0 );
        glTexCoord2d( 0, 0 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() - halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 0, 1 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() - halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 1, 1 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() + halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 1, 0 ); glVertex3d( pos_.x() - halfSize.x(), pos_.y() + halfSize.y(), pos_.z() - halfSize.z() );
    }
    // right
    if ( sides & RightSide )
    {
        glNormal3d( 1, 0, 0 );
        glTexCoord2d( 0, 0 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() - halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 1, 0 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() + halfSize.y(), pos_.z() - halfSize.z() );
        glTexCoord2d( 1, 1 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() + halfSize.y(), pos_.z() + halfSize.z() );
        glTexCoord2d( 0, 1 ); glVertex3d( pos_.x() + halfSize.x(), pos_.y() - halfSize.y(), pos_.z() + halfSize.z() );
    }
    glEnd();
    glEndList();
}

//--------------------------------------------------------------------------------------------------

Axis::Axis( const qreal size )
    : size_(size)
{
    colorX = Qt::red;
    colorY = Qt::green;
    colorZ = Qt::blue;
}

Math::Point3 Axis::pos() const
{
    return pos_;
}

qreal Axis::size() const
{
    return size_;
}

void Axis::setPos( const Math::Point3 & pos )
{
    pos_ = pos;
}

void Axis::setSize( const qreal size )
{
    size_ = size;
}

void Axis::paint( const int flags )
{
    glBegin(GL_LINES);
    glColor3f( colorX.redF(), colorX.greenF(), colorX.blueF() );
    glVertex3d( pos_.x(), pos_.y(), pos_.z() );
    glVertex3d( pos_.x() + size_, pos_.y(), pos_.z() );
    glColor3f( colorY.redF(), colorY.greenF(), colorY.blueF() );
    glVertex3d( pos_.x(), pos_.y(), pos_.z() );
    glVertex3d( pos_.x(), pos_.y() + size_, pos_.z() );
    glColor3f( colorZ.redF(), colorZ.greenF(), colorZ.blueF() );
    glVertex3d( pos_.x(), pos_.y(), pos_.z() );
    glVertex3d( pos_.x(), pos_.y(), pos_.z() + size_ );
    glEnd();
}

//--------------------------------------------------------------------------------------------------

Math::Point3 Space::pos() const
{
    return pos_;
}

Space::Block * Space::block( const Index3 & pos )
{
    Index3 chunkIndex = pos.sub();
    return chunks[chunkIndex][ ( pos - chunkIndex ).toInt() ];
}

void Space::setPos( const Math::Point3 & pos )
{
    pos_ = pos;
}

void Space::paint( const int )
{
    QMapIterator<Index3,Chunk> iter(chunks);

    while ( iter.hasNext() )
    {
        iter.next();
    }
}

//--------------------------------------------------------------------------------------------------
}//namespace Render
