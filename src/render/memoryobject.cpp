//encoding koi8-r
#include <stdio.h>

#include "memoryobject.hpp"

namespace Render
{

bool MemoryObject::create( const VertexVector & vertexVector, const IndexVector & indexVector )
{
    vertexVector_ = vertexVector;
    indexVector_ = indexVector;

    printf( "* vertex count   %d\n", vertexVector_.size() );
    printf( "* index count    %d\n", indexVector_.size() );
    printf( "* side count     %d\n", indexVector_.size() / 4 );
    return true;
}

void MemoryObject::paint()
{
    glPolygonMode( GL_FRONT, GL_LINE );
    vertexVector_.bind();
    indexVector_.paint();
    vertexVector_.unbind();
}

}//namespace Render
