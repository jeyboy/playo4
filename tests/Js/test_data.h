#ifndef TEST_DATA_H
#define TEST_DATA_H

#define ANONIM_FUNC QStringLiteral(\
    "function(x,y) { "\
    "    return x+y;"\
    "}"\
)

#define NAMED_FUNC_NAME QStringLiteral("art")
#define NAMED_FUNC QString(\
    "function " % NAMED_FUNC_NAME %"(x,y) { "\
    "    return x+y;"\
    "}"\
)

#define NAMED_FUNC_NAME2 QStringLiteral("cool")
#define NAMED_FUNC2 QString(\
    "function " % NAMED_FUNC_NAME2 %"(x) { "\
    "    return x+1;"\
    "}"\
)

#define COMBO_NAMED_FUNCS NAMED_FUNC % '\n' % NAMED_FUNC2

#endif // TEST_DATA_H
