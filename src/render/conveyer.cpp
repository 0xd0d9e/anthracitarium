//encoding koi8-r
#include <algorithm>

#include <qglobal.h>
#include <qdebug.h>

#include "conveyer.hpp"
#include "indexvector.hpp"
#include "point3f.hpp"

namespace Render
{


Conveyer::Conveyer()
    : vertexStorage_(0)
{
}

const VertexVector * Conveyer::vertexStorage() const
{
    return vertexStorage_;
}

void Conveyer::setVertexStorage( VertexVector * vertexStorage )
{
    vertexStorage_ = vertexStorage;
}

bool Conveyer::begin( const GLenum mode )
{
    if (!vertexStorage_)
        return false;
    mode_ = mode;
    return true;
}

inline GLint indexOf( VertexVector::const_iterator b, VertexVector::const_iterator e, const Point3 & point )
{
    int i = 0;
    for ( VertexVector::const_iterator current = b; current != e; ++current, ++i )
    {
        if ( point == (*current) )
        {
            return i;
        }
    }
    return -1;
}

IndexVector Conveyer::end()
{
    Q_ASSERT(vertexStorage_);

    IndexVector indexVector(mode_);

    Q_ASSERT(vertexStorage_);

//         QTime time;
//         time.start();

//     qDebug() << "stack_.size" << stack_.size();
//     indexVector.reserve( stack_.size() );
    VertexVector::iterator begin = vertexStorage_->begin(),
                           end = vertexStorage_->end(),
                           current;
//     qDebug() << vertexStorage_->size();
    foreach ( Point3 point, stack_ )
    {
//             qDebug() << ++i << point.pos[0] << point.pos[1] << point.pos[2];

        current = std::lower_bound( begin, end, point );
        if ( current >= end )
        {
            qDebug() << "index" << vertexStorage_->size() << "," << point.pos[0] << point.pos[1] << point.pos[2];
            qFatal("Point not found");
//             indexVector.push_back( vertexStorage_->size() );
//             vertexStorage_->push_back(point);
//             begin = vertexStorage_->begin();
//             end = vertexStorage_->end();
        }
        else
        {
            GLuint i( current - begin );
//             qDebug() << "index" << i << "," << point.pos[0] << point.pos[1] << point.pos[2] << point.hash;
//             indexVector.push_back( GLuint( current - begin ) );
            indexVector.push_back(i);
        }

        /*GLint i = indexOf( begin, end, point );
//         if ( i < 0 )
//         {
//             i = vertexStorage_->size();
//             vertexStorage_->push_back(point);
//         }
        qDebug() << "index" << i << "," << point.pos[0] << point.pos[1] << point.pos[2] << point.hash;
        if ( i < 0 )
        {
            qFatal("dsadjsamdashnasdjhjsda");
        }
        indexVector.push_back(i);*/
    }
//         qDebug() << "Gen index time" << time.elapsed() << "ms"; time.start();
    stack_.clear();
//     qDebug() << "indexVector.size" << indexVector.size();
    return indexVector;
}

}//namespace Render
