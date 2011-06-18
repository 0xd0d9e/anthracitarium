//encoding koi8-r
#include "point3f.hpp"
#include "tools/tools.hpp"

namespace Render
{

Point3::Point3( const GLfloat x, const GLfloat y, const GLfloat z )
    : hash(0)
{
    pos[0] = x; pos[1] = y; pos[2] = z;
    updateHash();
}

void Point3::updateHash()
{
    hash = Tools::checkSum32( reinterpret_cast<char*>(&pos), DataSize );
}

}//namespace Render
