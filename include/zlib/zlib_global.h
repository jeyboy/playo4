#ifndef ZLIB_GLOBAL_H
#define ZLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZLIB_LIBRARY)
#  define ZLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ZLIB_GLOBAL_H
