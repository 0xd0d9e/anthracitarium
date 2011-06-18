//encoding utf-8
//author dodge
#ifndef __HashIndex__
#define __HashIndex__

#include <qglobal.h>
#include <qbytearray.h>

#include "index.hpp"
#include "size.hpp"

namespace Space
{

template < typename Type >
class HashIndex : public Index<Type>
{
public:
    typedef Index<Type> Base;
    typedef HashIndex<Type> HashBase;
    inline HashIndex( const Base & i ) : Base(i) { rehash(); }
    inline explicit HashIndex( const Type x = 0, const Type y = 0, const Type z = 0 )
        : Base( x, y, z ) { rehash(); }
    inline void rehash() { hash = qChecksum( reinterpret_cast<const char*>(Base::p), Base::DataSize ); }
    inline void set( const Type x, const Type y, const Type z )
        { Base::p[0] = x; Base::p[1] = y; Base::p[2] = z; rehash(); }

    inline bool operator == ( const HashIndex<Type> & index ) const { return hash == index.hash; }

    quint16 hash;
};

template < typename Type >
inline bool operator < ( const HashIndex<Type> & i1, const HashIndex<Type> & i2 )
{
    return i1.hash < i2.hash;
}

template < typename Type >
inline HashIndex<Type> operator * ( const HashIndex<Type> & i1, const Size & i2 )
{
    return HashIndex<Type>( i1.p[0] * i2.p[0], i1.p[1] * i2.p[1], i1.p[2] * i2.p[2] );
}

}//namespace Space

#endif//__HashIndex__
