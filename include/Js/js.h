#ifndef JS_H
#define JS_H

#include "js_global.h"

//http://duktape.org/api.html

#include "pizduck/duktape.h"
#include <qvariant.h>

class JSSHARED_EXPORT Js {
    duk_context * ctx;
public:
    //call + "(\"" + arg + "\")
    static QString callBuilder(const QString & func_name, const QVariantList & args);

    Js(const QString & script);
    ~Js();

    QString proceedAsStr(const QString & call);
    int proceedAsInt(const QString & call);
    uint proceedAsUint(const QString & call);
    bool proceedAsBool(const QString & call);
    double proceedAsDouble(const QString & call);
};

#endif // JS_H
