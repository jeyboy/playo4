#ifndef JS_H
#define JS_H

#include "js_global.h"

//http://duktape.org/api.html

//        namespace Js {
//            class Document {
////                duk_context * ctx;
//            public:
//                static QString proceedJsCall(const QString & script, const QString & call, const QString & arg) {
//                    duk_context * ctx = duk_create_heap_default();
//                    duk_eval_string(ctx, (script + "\n" + call + "(\"" + arg + "\");").toLatin1().constData());
//                    QString res(duk_get_string(ctx, -1));
//                    duk_destroy_heap(ctx);
//                    return res;
//                }

////                Document(const QString & content) {
////                    ctx = duk_create_heap_default();
////                    duk_eval_string(ctx, content.toLatin1().const_pointer());
////                    printf("result is: %s\n", duk_get_string(ctx, -1));
////                    duk_pop(ctx);
////                }

////                ~Document() {
////                    duk_destroy_heap(ctx);
////                }
//            };
//        }
//    }
//}

class duk_context;
class QVariant;
class QList;

class JSSHARED_EXPORT Js {
    duk_context * ctx;
public:
    //call + "(\"" + arg + "\")
    static QString callBuilder(const QString & func_name, const QList<QVariant> & args);

    static QString proceed(const QString & script, const QString & call);

    Js(const QString & script);
    ~Js();

    QString proceed(const QString & call);
};

#endif // JS_H
