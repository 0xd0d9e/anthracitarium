//encoding utf-8
#ifndef __VertexVector__
#define __VertexVector__

#include <vector>

#include "point3f.hpp"

namespace Render
{

//! \brief ������ ������
class VertexVector : public std::vector<Point3>
{
public:
    //! ������������� ������� (�� ����)
    void sort();
    //! ��������� ����������
    void unique();
    //! ��������� ������� �� ��������
    void bind();
    //! ����� ������� � ��������
    void unbind();

};

}//namespace Render

#endif//__VertexVector__
