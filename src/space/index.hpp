//encoding utf-8
//author dodge
#ifndef __Index__
#define __Index__

#include <QDebug>

namespace Space
{

template < typename Type >
class Index
{
public:
    typedef Index<Type> Base;
    typedef Type BaseType;
    enum { DataCount = 3 };
    enum { DataSize = sizeof(Type) * DataCount };

    inline explicit Index( const Type x = 0, const Type y = 0, const Type z = 0 )
        { p[0] = x; p[1] = y; p[2] = z; }


    inline Base left() const { return Base( p[0] - 1, p[1], p[2] ); }
    inline Base right() const { return Base( p[0] + 1, p[1], p[2] ); }
    inline Base front() const { return Base( p[0], p[1] + 1, p[2] ); }
    inline Base back() const { return Base( p[0], p[1] -  1, p[2] ); }
    inline Base top() const { return Base( p[0], p[1], p[2] - 1 ); }
    inline Base bottom() const { return Base( p[0], p[1], p[2] + 1 ); }

    Type p[3];
};

#ifndef QT_NO_DEBUG
template < typename Type >
inline QDebug operator << ( QDebug dbg, const Index<Type> & i )
{
    dbg.nospace() << "Space::Index(" << i.p[0] << "," << i.p[1] << "," << i.p[2] << ")";
    return dbg.space();
}
#endif//QT_NO_DEBUG

}//namespace Space

#endif//__Index__
