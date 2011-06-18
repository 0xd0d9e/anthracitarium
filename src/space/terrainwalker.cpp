//encoding utf-8
//author dodge
#include "terrainwalker.hpp"

namespace Space
{

TerrainWalker::TerrainWalker()
    : terrain_(0)
{
}

Terrain * TerrainWalker::terrain() const
{
    return terrain_;
}

void TerrainWalker::setTerrain( Terrain * terrain )
{
    terrain_ = terrain;
}

}//namespace Space
