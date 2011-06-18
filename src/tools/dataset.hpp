//author 0xd0d9e
//encoding utf-8
#ifndef __Tools_DataSet__
#define __Tools_DataSet__

#include <QtCore/QDataStream>

#define TOOLS_TYPELIST1(t) Tools::Typelist< t, Tools::EndOfTypeList >
#define TOOLS_TYPELIST2(t1,t2) Tools::Typelist< t1, TOOLS_TYPELIST1(t2) >
#define TOOLS_TYPELIST3(t1,t2,t3) Tools::Typelist< t1, TOOLS_TYPELIST2(t2,t3) >
#define TOOLS_TYPELIST4(t1,t2,t3,t4) Tools::Typelist< t1, TOOLS_TYPELIST3(t2,t3,t4) >
#define TOOLS_TYPELIST5(t1,t2,t3,t4,t5) Tools::Typelist< t1, TOOLS_TYPELIST4(t2,t3,t4,t5) >

#define TOOLS_LISTTYPE0( t ) t->Current
#define TOOLS_LISTTYPE1( t ) t->Base
#define TOOLS_LISTTYPE2( t ) TOOLS_LISTTYPE1(t)::Base
#define TOOLS_LISTTYPE3( t ) TOOLS_LISTTYPE2(t)::Base
#define TOOLS_LISTTYPE4( t ) TOOLS_LISTTYPE3(t)::Base

#define TOOLS_FIELD0( t ) TOOLS_LISTTYPE0(t)::value
#define TOOLS_FIELD1( t ) TOOLS_LISTTYPE1(t)::value
#define TOOLS_FIELD2( t ) TOOLS_LISTTYPE2(t)::value
#define TOOLS_FIELD3( t ) TOOLS_LISTTYPE3(t)::value
#define TOOLS_FIELD4( t ) TOOLS_LISTTYPE4(t)::value

namespace Tools
{

struct EndOfTypeList;

template < typename T_ValueType, typename T_NextItem >
struct Typelist
{
    typedef T_ValueType ValueType;
    typedef T_NextItem NextItem;
};

template < class T_Typelist > struct TypelistLength;

template <>
struct TypelistLength <EndOfTypeList>
{
    enum { value = 0 };
};

template < typename T, typename U >
struct TypelistLength < Typelist< T, U > >
{
    enum { value = 1 + TypelistLength<U>::value };
};

template < typename T > struct DataSet;

template <>
struct DataSet<EndOfTypeList>
{
    void saveToStream( QDataStream & ) const {}
    void restoreFromStream( QDataStream & ) {}
};

template < typename T, typename U >
struct DataSet < Typelist< T, U > > : public DataSet<U>
{
    T value;
    typedef DataSet< Typelist< T, U > > Current;
    typedef DataSet<U> Base;
    void saveToStream( QDataStream & stream ) const
    {
        stream << value;
        Base::saveToStream(stream);
    }
    void restoreFromStream( QDataStream & stream )
    {
        stream >> value;
        Base::restoreFromStream(stream);
    }
    QByteArray toQByteArray() const
    {
        QByteArray data;
        QDataStream ds( &data, QIODevice::WriteOnly );
        ds.setVersion(QDataStream::Qt_4_4);
        saveToStream(ds);
        return data;
    }
    void fromQByteArray( QByteArray data )
    {
        QDataStream ds( &data, QIODevice::ReadOnly );
        ds.setVersion(QDataStream::Qt_4_4);
        restoreFromStream(ds);
    }
};

}//namespace Tools

#endif//__Tools_DataSet__
