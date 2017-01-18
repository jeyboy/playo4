#ifndef TEST_DATA_H
#define TEST_DATA_H

#define INT_KEY 'i'
#define STR_KEY 's'


#define TJSON_OBJ_DEFAULT_KEY QStringLiteral("colorName")
#define TJSON_DEFAULT_VAL QStringLiteral("red")
#define TJSON_DEFAULT_VAL2 QStringLiteral("green")
#define TJSON_DEFAULT_VAL3 QStringLiteral("yellow")

#define TJSON_OBJ_KEY(key) (QStringList() << QString(STR_KEY % key))
#define TJSON_OBJ(key, val) \
    QString(\
        "{"\
        "   \"" % TJSON_OBJ_DEFAULT_KEY % "\":\"" % TJSON_DEFAULT_VAL % "\","\
        "   \"" % key % "\":\"" % val % "\""\
        "}"\
    )

#define TJSON_OBJ2(key, val) \
    QString(\
        "{"\
        "   \"" % TJSON_OBJ_DEFAULT_KEY % "\":\"" % TJSON_DEFAULT_VAL % "\","\
        "   \"" % key % "\":" % val % ""\
        "}"\
    )

#define TJSON_SUB_OBJ_KEY(root_key, key) (QStringList() << QString(STR_KEY % root_key) << QString(STR_KEY % key))
#define TJSON_SUB_OBJ(root_key, key, val) \
    QString(\
        "{"\
        "   \"" % root_key % "\":{"\
        "       \"" % TJSON_OBJ_DEFAULT_KEY % "\":\"" % TJSON_DEFAULT_VAL % "\","\
        "       \"" % key % "\":\"" % val % "\""\
        "   }"\
        "}"\
    )

#define TJSON_ARR_KEY (QStringList() << QString(INT_KEY % QString::number(0)))
#define TJSON_ARR(val) \
    QString(\
        "["\
        "   \"" % val % "\","\
        "   \"" % TJSON_DEFAULT_VAL % "\","\
        "   \"" % TJSON_DEFAULT_VAL2 % "\""\
        "]"\
    )

#define TJSON_ARR2(val) \
    QString(\
        "["\
        "   " % val % ","\
        "   \"" % TJSON_DEFAULT_VAL % "\""\
        "]"\
    )

#define TJSON_SUB_ARR_KEY_ARGS 0, 1
#define TJSON_SUB_ARR_KEY (QStringList() << QString(INT_KEY % QString::number(0)) << QString(INT_KEY % QString::number(1)))
#define TJSON_SUB_ARR(val) \
    QString(\
        "["\
        "   ["\
        "       \"" % TJSON_DEFAULT_VAL % "\","\
        "       \"" % val % "\""\
        "   ]"\
        "]"\
    )

#define TJSON_OBJ_SUB_ARR(root_key, val) \
    QString(\
        "{"\
        "   \"" % root_key % "\":["\
        "       \"" % TJSON_DEFAULT_VAL % "\","\
        "       \"" % val % "\""\
        "   ]"\
        "}"\
    )

#define TJSON_ARR_SUB_OBJ(key, val) \
    QString(\
        "["\
        "   {"\
        "       \"" % TJSON_OBJ_DEFAULT_KEY % "\":\"" % TJSON_DEFAULT_VAL % "\","\
        "       \"" % key % "\":\"" % val % "\""\
        "   },"\
        "   {"\
        "       \"" % TJSON_OBJ_DEFAULT_KEY % "\":\"" % TJSON_DEFAULT_VAL2 % "\","\
        "       \"" % key % "\":\"" % TJSON_DEFAULT_VAL3 % "\""\
        "   }"\
        "]"\
    )

#endif // TEST_DATA_H
