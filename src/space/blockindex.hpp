//encoding utf-8
//author dodge
#ifndef __BlockIndex__
#define __BlockIndex__

#include <math.h>

#include <qglobal.h>

#include "chunkindex.hpp"
#include "hashindex.hpp"
#include "size.hpp"

namespace Space
{

class BlockIndex : public HashIndex<qint32>
{
public:
    inline BlockIndex( const Base & i ) : HashBase(i) {}
    inline BlockIndex( const HashBase & i ) : HashBase(i) {}
    inline explicit BlockIndex( const qint32 x = 0, const qint32 y = 0, const qint32 z = 0 )
        : HashBase( x, y, z ) {}

    inline ChunkIndex toChunkIndex( const Size & size ) const
        { return ChunkIndex( floor( p[0] / qreal(size.p[0]) ), floor( p[1] / qreal(size.p[1]) ), floor( p[2] / qreal(size.p[2]) ) ); }
    inline quint32 plainIndex( const Size & size ) const
        { return ( p[1] * size.p[0] + p[0] ) + p[2] * ( size.p[0] * size.p[1] ); }

};

template < typename Type >
inline BlockIndex operator - ( const BlockIndex & i1, const HashIndex<Type> & i2 )
{
    return BlockIndex( i1.p[0] - i2.p[0], i1.p[1] - i2.p[1], i1.p[2] - i2.p[2] );
}

}//namespace Space

#endif//__BlockIndex__
