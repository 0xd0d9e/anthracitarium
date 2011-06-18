//encoding utf-8
//author dodge
#ifndef __Block__
#define __Block__

#include <qglobal.h>

namespace Space
{

class Block
{
public:
    Block();
    ~Block();

    quint16 type;
    quint8  sides;

};

}//namespace Space

#endif//__Block__
