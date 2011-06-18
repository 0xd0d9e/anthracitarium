//encoding utf-8
//author dodge
#ifndef __TerrainWalker__
#define __TerrainWalker__

namespace Space
{

class Terrain;

class TerrainWalker
{
public:
    TerrainWalker();

    Terrain * terrain() const;

    void setTerrain( Terrain * terrain );

private:
    Terrain * terrain_;

};

}//namespace Space

#endif//__TerrainWalker__
