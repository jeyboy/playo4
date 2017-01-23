#include "js.h"

#include <variant_convertor.h>

//call + "(\"" + arg + "\")
QString Js::callBuilder(const QString & func_name, const QVariantList & args) {
    QString res = func_name % '(';
    QString args_str;

    for(QList<QVariant>::ConstIterator arg = args.constBegin(); arg != args.constEnd(); arg++) {
        args_str = args_str % (args_str.isEmpty() ? LSTR("") : LSTR(", ")) % VariantConvertor::toStr(*arg);
    }

    return res % args_str % ')';
}

Js::Js(const QString & script) {
    ctx = duk_create_heap_default();
    duk_eval_string(ctx, (script).toUtf8().constData());
}

Js::~Js() {
    duk_destroy_heap(ctx);
}

QString Js::proceedAsStr(const QString & call) {
    duk_eval_string(ctx, (call % ';').toUtf8().constData());
    QString res = QString(duk_get_string(ctx, -1));
    duk_pop(ctx);
    return res;
}
int Js::proceedAsInt(const QString & call) {
    duk_eval_string(ctx, (call % ';').toUtf8().constData());
    int res = (int)duk_get_int(ctx, -1);
    duk_pop(ctx);
    return res;
}
uint Js::proceedAsUint(const QString & call) {
    duk_eval_string(ctx, (call % ';').toUtf8().constData());
    uint res = (uint)duk_get_uint(ctx, -1);
    duk_pop(ctx);
    return res;
}
bool Js::proceedAsBool(const QString & call) {
    duk_eval_string(ctx, (call % ';').toUtf8().constData());
    bool res = duk_get_boolean(ctx, -1);
    duk_pop(ctx);
    return res;
}
double Js::proceedAsDouble(const QString & call) {
    duk_eval_string(ctx, (call % ';').toUtf8().constData());
    double res = (double)duk_get_number(ctx, -1);
    duk_pop(ctx);
    return res;
}

//template<typename T> T Js::proceed(const QString & call) {
//    //TODO: srite me

////    /* The target function here prints:
////     *
////     *    this: 123
////     *    2 3
////     *
////     * and returns 5.
////     */

////    duk_push_string(ctx, "function(x,y) { print('this:', this); "
////                         "print(x,y); return x+y; }");
////    duk_eval(ctx);  /* -> [ ... func ] */
////    duk_push_int(ctx, 123);
////    duk_push_int(ctx, 2);
////    duk_push_int(ctx, 3);
////    duk_call_method(ctx, 2);  /* [ ... func 123 2 3 ] -> [ 5 ] */
////    printf("2+3=%ld\n", (long) duk_get_int(ctx, -1));  /* prints 5 */
////    duk_pop(ctx);

//    duk_eval_string(ctx, (call % ';').toUtf8().constData());

//    T res;

//    if(std::is_same<T, QString>::value)
//        res = QString(duk_get_string(ctx, -1));
//    else if(std::is_same<T, int>::value)
//        res = (int)duk_get_int(ctx, -1);
//    else if(std::is_same<T, uint>::value)
//        res = (int)duk_get_uint(ctx, -1);
//    else if(std::is_same<T, bool>::value)
//        res = duk_get_boolean(ctx, -1);
//    else if(std::is_same<T, double>::value || std::is_same<T, float>::value)
//        res = (T)duk_get_number(ctx, -1);

////    duk_get_pointer

////    duk_get_prop_string(ctx, -3, "propertyName");
////    printf("obj.propertyName = %s\n", duk_to_string(ctx, -1));
////    duk_pop(ctx);

//    duk_pop(ctx);
//    return res;
//}
