//encoding utf-8
//author dodge
#ifndef __Chunk__
#define __Chunk__

#include <vector>

#include <qglobal.h>

#include "block.hpp"
#include "size.hpp"

namespace Space
{

class ChunkUserData {};

class Chunk : public std::vector<Block>
{
public:
    inline explicit Chunk( Size s ) { resize( s.square() ); }

    inline Block * block( const quint32 index )
        { return ( index < size() ) ? &this->operator [] (index) : 0; }

    template < class ChunkUserDataType >
    ChunkUserDataType * userData( const int type ) const
        { return static_cast<ChunkUserDataType*>( userData_.value( type, 0 ) ); }

    void setUserData( const int type, ChunkUserData * userData ) { userData_[type] = userData; }

private:
    QMap<int,ChunkUserData*> userData_;

};

}//namespace Space

#endif//__Chunk__
