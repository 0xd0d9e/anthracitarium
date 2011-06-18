//encoding utf-8
//author dodge
#include <qgl.h>

#include "space/size.hpp"
#include "space/terrain.hpp"
#include "terrainrender.hpp"

namespace Render
{

TerrainRender::TerrainRender()
{
    box_.color = QColor("#ff0000");
}

void TerrainRender::paint( const int flags )
{
    if ( ::Space::Terrain * terrain = ::Space::TerrainWalker::terrain() )
    {
        const ::Space::Size & size = terrain->chunkSize();
        box_.setSize( Math::Point3( size.p[0], size.p[1], size.p[2] ) );

        glPointSize(5);
        const QRect & rect = terrain->chunksRect();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        for ( qint32 y = rect.top(); y != rect.y() + rect.height(); ++y )
        {
            for ( qint32 x = rect.left(); x != rect.x() + rect.width(); ++x )
            {
                Math::Point3 pos( x * static_cast<qint32>(size.p[0]), y * static_cast<qint32>(size.p[1]), 0 );
//                 qDebug() << "  c:" << x << y << pos;
                box_.setPos(pos);
                box_.updateCache();
                box_.paint();
            }
        }
        glPolygonMode( GL_FRONT, GL_FILL );
        glPolygonMode( GL_BACK, GL_LINE );
    }
}

}//namespace Render
