//encoding koi8-r
#include "indexvector.hpp"

namespace Render
{

IndexVector::IndexVector( const GLenum mode )
    : mode_(mode)
{
}

GLenum IndexVector::mode() const
{
    return mode_;
}

void IndexVector::setMode( const GLenum mode )
{
    mode_ = mode;
}

void IndexVector::paint()
{
    glDrawElements( mode_, size(), GL_UNSIGNED_INT, &front() );
}

}//namespace Render
