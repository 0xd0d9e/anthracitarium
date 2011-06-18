//encoding koi8-r
#ifndef __IndexVector__
#define __IndexVector__

#include <vector>

#include <qgl.h>

namespace Render
{

//! \brief ������ ��������
class IndexVector : public std::vector<GLuint>
{
public:
    //! �����������
    explicit IndexVector( const GLenum mode = GL_POINTS );

    //! ���������� ������� ����� ���������
    GLenum mode() const;

    //! ������ ����� ���������
    void setMode( const GLenum mode );

    //! ��������� ������ �� ��������
    virtual void paint();

private:
    GLenum mode_;

};

}//namespace Render

#endif//__IndexVector__
