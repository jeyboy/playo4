#include "js.h"
#include "pizduck/duktape.h"

#include <variant_convertor.h>

#include <qlist.h>
#include <qvariant.h>

//call + "(\"" + arg + "\")
QString Js::callBuilder(const QString & func_name, const QList<QVariant> & args) {
    QString res = func_name % '(';
    QString args_str;

    for(QList<QVariant>::ConstIterator arg = args.constBegin(); arg != args.constEnd(); arg++) {
        args_str = args_str % (args_str.isEmpty() ? LSTR("") : LSTR(", ")) % VariantConvertor::toStr((*arg));
    }

    return res % args_str % ')';
}

QString Js::proceed(const QString & script, const QString & call) {
    duk_context * ctx = duk_create_heap_default();
    duk_eval_string(ctx, (script % LSTR("\n") % call % LSTR(");")).toUtf8().constData());
    QString res(duk_get_string(ctx, -1));
    duk_destroy_heap(ctx);
    return res;
}

Js::Js(const QString & script) {
    ctx = duk_create_heap_default();
    duk_eval_string(ctx, (script).toUtf8().constData());
}

Js::~Js() {
    duk_destroy_heap(ctx);
}

QString Js::proceed(const QString & call) {
    //TODO: srite me
}
