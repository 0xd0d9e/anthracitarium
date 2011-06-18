//encoding utf-8
//author dodge
#ifndef __ChunkIndex__
#define __ChunkIndex__

#include <qglobal.h>

#include "hashindex.hpp"

namespace Space
{

class ChunkIndex : public HashIndex<qint32>
{
public:
    inline ChunkIndex( const Base & i ) : HashBase(i) {}
    inline ChunkIndex( const HashBase & i ) : HashBase(i) {}
    inline explicit ChunkIndex( const qint32 x = 0, const qint32 y = 0, const qint32 z = 0 )
        : HashBase( x, y, z ) {}
};

}//namespace Space

#endif//__ChunkIndex__
