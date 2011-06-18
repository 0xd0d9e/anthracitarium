//encoding koi8-r
#ifndef __Conveyer__
#define __Conveyer__

#include "vertexvector.hpp"

namespace Render
{

class IndexVector;

/*! \brief ������� ������
��������� ������������ ������ �������� ������
*/
class Conveyer
{
public:
    Conveyer();

    //! ��������� ������
    const VertexVector * vertexStorage() const;

    //! ������ ��������� ������
    void setVertexStorage( VertexVector * vertexStorage );
    //! ���������� � ������������ (���� ��������� �� ������, ������ false)
    bool begin( const GLenum mode );
    //! ��������� ������������ (������ ������ �������� ������, � ������� ����)
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
