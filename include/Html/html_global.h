#ifndef HTML_GLOBAL_H
#define HTML_GLOBAL_H

#include <QtCore/qglobal.h>
#include "html_keys.h"

#if defined(HTML_LIBRARY)
#  define HTMLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HTMLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HTML_GLOBAL_H
