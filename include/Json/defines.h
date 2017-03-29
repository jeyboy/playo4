#ifndef DEFINES
#define DEFINES

#include <qstring.h>
#include <qstringbuilder.h>

#define LSTR(str) QStringLiteral(str)
#define QSTR_TO_CHAR(str) str.toUtf8().constData()

#endif // DEFINES
