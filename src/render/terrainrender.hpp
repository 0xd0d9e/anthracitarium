//encoding utf-8
//author dodge
#ifndef __TerrainRender__
#define __TerrainRender__

#include "object.hpp"
#include "space/terrainwalker.hpp"

namespace Render
{

class TerrainRender :
    public ::Render::Object,
    public ::Space::TerrainWalker
{
public:
    TerrainRender();

    Math::Point3 pos() const { return pos_; }
    void paint( const int flags = 0 );

private:
    void setPos( const Math::Point3 & pos ) { pos_ = pos; }

    Math::Point3 pos_;
    Render::Box box_;

};

}//namespace Render

#endif//__TerrainRender__
