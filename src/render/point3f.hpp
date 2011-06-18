//encoding koi8-r
#ifndef __Point3__
#define __Point3__

#include <qgl.h>

namespace Render
{

//! \brief Координаты в пространстве
class Point3
{
public:
    //! Размер данных
    enum { DataSize = sizeof(GLfloat) * 3 };
    //! Размер служебной информации
    enum { HashSize = sizeof(GLuint) };

    explicit Point3( const GLfloat x = 0, const GLfloat y = 0, const GLfloat z = 0 );

    //! Обновить хэш
    void updateHash();

    //! Оператор сравнения
    inline bool operator == ( const Point3 & p ) const { return hash == p.hash; }

    GLfloat pos[3];
    GLuint hash;
};

inline bool operator < ( const Point3 & p1, const Point3 & p2 )
{
    return p1.hash < p2.hash;
}

}//namespace Render

#endif//__Point3__
