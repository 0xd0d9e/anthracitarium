//encoding utf-8
//author dodge
#ifndef __PlaneNode__
#define __PlaneNode__

namespace Space
{

template < typename Type >
class PlaneNode
{
public:
    inline PlaneNode() { reset(); }
    inline void reset() { current = 0; left = 0; right = 0; front = 0; back = 0; }
    inline void moveLeft() { right = current; current = left; }
    inline void moveRight() { left = current; current = right; }
    inline void moveFront() { back = current; current = front; }
    inline void moveBack() { front = current; current = back; }

    Type * current;
    Type * left;
    Type * right;
    Type * front;
    Type * back;
};

}//namespace Space

#endif//__PlaneNode__
