//encoding koi8-r
#ifndef __IndexVector__
#define __IndexVector__

#include <vector>

#include <qgl.h>

namespace Render
{

//! \brief Массив индексов
class IndexVector : public std::vector<GLuint>
{
public:
    //! Конструктор
    explicit IndexVector( const GLenum mode = GL_POINTS );

    //! Возвражает текущий режим отрисовки
    GLenum mode() const;

    //! Задать режим отрисовки
    void setMode( const GLenum mode );

    //! Отрисовка вершин по индексам
    virtual void paint();

private:
    GLenum mode_;

};

}//namespace Render

#endif//__IndexVector__
