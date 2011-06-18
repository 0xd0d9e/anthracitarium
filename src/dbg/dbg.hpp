//author 0xd0d9e
//encoding utf-8
#ifndef __Dbg__
#define __Dbg__

#include <QDebug>
#include <QVariant>

#ifdef QT_DEBUG
// #warning Debug is enabled
#define DbgPrintable(v) qPrintable( QVariant(v).toString() )
#define DbgPos() qDebug( "* %s at %d from %s", __PRETTY_FUNCTION__, __LINE__, __FILE__ );
#define DbgObjPos() qDebug() << "*" << this << __func__ << "at" << __LINE__ << "from" __FILE__;
#define DbgMsg(msg) qDebug( "* %s at %d from %s say:\n  %s", __PRETTY_FUNCTION__, __LINE__, __FILE__, DbgPrintable(msg) );
#define DbgValue(v) qDebug( "  %s=%s", #v, DbgPrintable(v) )
#else//QT_DEBUG
// #warning Debug is disabled
#define DbgPrintable(v)
#define DbgPos()
#define DbgObjPos()
#define DbgMsg(msg)
#define DbgValue(v)
#endif//QT_DEBUG

#endif//__Dbg__
