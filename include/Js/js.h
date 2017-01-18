#ifndef JS_H
#define JS_H

#include "js_global.h"

//http://duktape.org/api.html

#include <qstring.h>
#include "pizduck/duktape.h"

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


class JSSHARED_EXPORT Js {
public:
    Js();

    static QString proceedJsCall(const QString & script, const QString & call, const QString & arg) {
        duk_context * ctx = duk_create_heap_default();
        duk_eval_string(ctx, (script + "\n" + call + "(\"" + arg + "\");").toLatin1().constData());
        QString res(duk_get_string(ctx, -1));
        duk_destroy_heap(ctx);
        return res;
    }
};

#endif // JS_H
