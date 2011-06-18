//encoding koi8-r
#ifndef __Conveyer__
#define __Conveyer__

#include "vertexvector.hpp"

namespace Render
{

class IndexVector;

/*! \brief Конвейр вершин
Позволяет сформировать массив индексов вершин
*/
class Conveyer
{
public:
    Conveyer();

    //! Хранилище вершин
    const VertexVector * vertexStorage() const;

    //! Задать хранилище вершин
    void setVertexStorage( VertexVector * vertexStorage );
    //! Приступить к формированию (если хранилище не задано, вернет false)
    bool begin( const GLenum mode );
    //! Завершить формирование (вернет вектор индексов вершин, и очистит стэк)
    IndexVector end();
    inline void addVertex( const Point3 & point )
    {
        stack_.push_back(point);
    }

private:
    VertexVector * vertexStorage_;
    VertexVector stack_;
    GLenum mode_;

};

}//namespace Render

#endif//__Conveyer__
