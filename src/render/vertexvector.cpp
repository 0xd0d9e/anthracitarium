//encoding koi8-r
#include <algorithm>

#include <qgl.h>

#include "vertexvector.hpp"

namespace Render
{

void VertexVector::sort()
{
//     QTime time;
//     time.start();

//     qDebug() << "vec size" << size(); time.start();

    // сортируем
    std::sort( begin(), end() );
//     qDebug() << "Sort time" << time.elapsed() << "ms"; time.start();
}

void VertexVector::unique()
{
//     QTime time;
//     time.start();

//     qDebug() << "vec size" << size(); time.start();

    // сортируем
    std::sort( begin(), end() );
//     qDebug() << "Sort time" << time.elapsed() << "ms"; time.start();

    // переносим неуникальные элементы в конец
    std::vector<Point3>::iterator last = std::unique( begin(), end() );

//     qDebug() << "unique: " << ( last == end() );

    // купируем
//         erase( last, end() );
    resize( last - begin() );
//     qDebug() << "Unique gen time" << time.elapsed() << "ms"; time.start();

//     qDebug() << "Unique vec size" << size();
}

void VertexVector::bind()
{
    glEnableClientState(GL_VERTEX_ARRAY);
//     glVertexPointer( 3, GL_FLOAT, Point3::dataSize + Point3::hashSize, &front() );
    glVertexPointer( 3, GL_FLOAT, sizeof(value_type), &front() );
}

void VertexVector::unbind()
{
//     glVertexPointer( 3, GL_FLOAT, 0, 0 );
    glDisableClientState(GL_VERTEX_ARRAY);
}

}//namespace Render
