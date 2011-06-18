//encoding utf-8
//author dodge
#ifndef __Size__
#define __Size__

#include <qglobal.h>

#include "index.hpp"

namespace Space
{

class Size : public Index<quint32>
{
public:
    inline explicit Size( const quint32 w = 0, const quint32 l = 0, const quint32 h = 0 )
        : Base( w, l, h ) {}

    inline quint32 square() const { return p[0] * p[1] * p[2]; }

};

}//namespace Space

#endif//__Size__
