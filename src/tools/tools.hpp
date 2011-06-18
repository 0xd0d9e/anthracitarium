//encoding koi8-r
#ifndef __Tools__
#define __Tools__

namespace Tools
{

//! Подсчет контрольной суммы по алгоритму CRC32 (табличный вариант)
unsigned int checkSum32( const char * data, unsigned int len );

}//namespace Tools

#endif//__Tools__
