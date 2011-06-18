//encoding utf-8
//author dodge
#ifndef __SpaceNode__
#define __SpaceNode__

#include "planenode.hpp"

namespace Space
{

template < typename Type >
class SpaceNode : public PlaneNode<Type>
{
public:
    inline SpaceNode() { reset(); }
    inline void reset() { PlaneNode<Type>::reset(); top = 0; bottom = 0; }
    inline void moveTop() { bottom = PlaneNode<Type>::current; PlaneNode<Type>::current = top; }
    inline void moveBottom() { top = PlaneNode<Type>::current; PlaneNode<Type>::current = bottom; }

    Type * top;
    Type * bottom;
};


}//namespace Space

#endif//__SpaceNode__
