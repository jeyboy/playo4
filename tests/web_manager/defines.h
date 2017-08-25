#ifndef DEFINES
#define DEFINES

#include <qstring.h>
#include <qstringbuilder.h>

#define USTR(str) QStringLiteral(str)
#define LSTR(str) QLatin1Literal(str)
#define QSTR_TO_CHAR(str) str.toUtf8().constData()

#endif // DEFINES
