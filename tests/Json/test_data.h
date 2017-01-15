#ifndef TEST_DATA_H
#define TEST_DATA_H

#define INT_KEY 'i'
#define STR_KEY 's'


#define TJSON_OBJ_KEY(key) (QStringList() << QString(STR_KEY % key))
#define TJSON_OBJ(key, val) \
    QString(\
        "{"\
        "   \"colorName\":\"red\","\
        "   \"" % key % "\":\"" % val % "\""\
        "}"\
    )

#define TJSON_SUB_OBJ_KEY(root_key, key) (QStringList() << QString(STR_KEY % root_key) << QString(STR_KEY % key))
#define TJSON_SUB_OBJ(root_key, key, val) \
    QString(\
        "{"\
        "   \"" % root_key % "\":{"\
        "       \"colorName\":\"red\","\
        "       \"" % key % "\":\"" % val % "\""\
        "   }"\
        "}"\
    )

#define TJSON_ARR_KEY (QStringList() << QString(INT_KEY % QString::number(0)))
#define TJSON_ARR(val) \
    QString(\
        "["\
        "   \"" % val % "\","\
        "   \"red\""\
        "]"\
    )

#define TJSON_SUB_ARR_KEY_ARGS 0, 1
#define TJSON_SUB_ARR_KEY (QStringList() << QString(INT_KEY % QString::number(0)) << QString(INT_KEY % QString::number(1)))
#define TJSON_SUB_ARR(val) \
    QString(\
        "["\
        "   ["\
        "       \"red\","\
        "       \"" % val % "\""\
        "   ]"\
        "]"\
    )

#define TJSON_OBJ_SUB_ARR(root_key, val) \
    QString(\
        "{"\
        "   \"" % root_key % "\":["\
        "       \"red\","\
        "       \"" % val % "\""\
        "   ]"\
        "}"\
    )

#define TJSON_ARR_SUB_OBJ(key, val) \
    QString(\
        "["\
        "   {"\
        "       \"colorName\":\"red\","\
        "       \"" % key % "\":\"" % val % "\""\
        "   }"\
        "]"\
    )

#endif // TEST_DATA_H
