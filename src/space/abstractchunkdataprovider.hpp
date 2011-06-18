//encoding utf-8
//author dodge
#ifndef __AbstractChunkDataProvider__
#define __AbstractChunkDataProvider__

namespace Space
{

class Chunk;
class ChunkIndex;
class Terrain;

class AbstractChunkDataProvider
{
public:
    virtual void load( Terrain * terrain, Chunk * chunk, const ChunkIndex & index ) const = 0;

};

}//namespace Space

#endif//__AbstractChunkDataProvider__
