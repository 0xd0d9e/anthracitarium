//encoding koi8-r
#ifndef __MemoryObject__
#define __MemoryObject__

#include "indexvector.hpp"
#include "vertexvector.hpp"

namespace Render
{

class MemoryObject
{
public:
    bool create( const VertexVector & vertexVector, const IndexVector & indexVector );
    void paint();

private:
    VertexVector vertexVector_;
    IndexVector indexVector_;

};

}//namespace Render

#endif//__MemoryObject__
