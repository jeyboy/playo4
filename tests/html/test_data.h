#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <qfile.h>
#include <qstringbuilder.h>
#include <qdebug.h>

#define DATA_PATH(name) SRCDIR % QStringLiteral("test_data/") % name

class TestData {
  public:
    static void convert(const QString & path, const char * codec = "UTF-8") {
        QFile f(path);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QFile fout(path + ".conv");
            if (fout.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream outs(&fout);
                outs.setCodec(codec);
                outs << f.readAll();
                outs.flush();
                fout.close();
            }

            f.close();
        }
    }

    static QByteArray load(const QString & path) {
        QByteArray res;
        QFile f(path);
        if (f.open(QIODevice::ReadOnly)) {
            res = f.readAll();
            f.close();
        }
        else qDebug() << "Error file opening" << path;

        return res;
    }
    static void save(const QString & name, const QByteArray & content) {
        QFile f(DATA_PATH(name));
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            f.write(content);
            f.close();
        }
    }

    static QByteArray dataLoad(const QByteArray & name) { return load(DATA_PATH(name)); }

    static QByteArray dataHtmlRustorka() {
        static QByteArray data_fourshared = load(DATA_PATH(QStringLiteral("rustorka.txt")));
        return data_fourshared;
    }
    static QByteArray dataHtmlFourshared() {
        static QByteArray data_fourshared = load(DATA_PATH(QStringLiteral("fourshared.txt")));
        return data_fourshared;
    }
    static QByteArray dataHtmlGoogle() {
        static QByteArray data_google = load(DATA_PATH(QStringLiteral("google.txt")));
        return data_google;
    }
    static QByteArray dataHtmlYoutube() {
        static QByteArray data_youtube = load(DATA_PATH(QStringLiteral("youtube.txt")));
        return data_youtube;
    }
    static QByteArray dataHtmlKivy() {
        static QByteArray data_kivy = load(DATA_PATH(QStringLiteral("kivy.txt")));
        return data_kivy;
    }
    static QByteArray dataHtmlStackOverflow() {
        static QByteArray data_stackoverflow = load(DATA_PATH(QStringLiteral("stack.txt")));
        return data_stackoverflow;
    }

    static QByteArray dataXmlParser() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_xml.txt")));
        return data_parser;
    }

    static QByteArray dataHtmlParserJs() {
        static QByteArray data_parser_js = load(DATA_PATH(QStringLiteral("test_js_parsing.txt")));
        return data_parser_js;
    }
    static QByteArray dataHtmlParserJs2() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_js.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserMonotags() {
        static QByteArray data_parser_monotags = load(DATA_PATH(QStringLiteral("test_monotags.txt")));
        return data_parser_monotags;
    }
    static QByteArray dataHtmlParserCoding1251() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_1251_head.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserCoding1252() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_1252_head.txt")));
        return data_parser;
    }

    static QByteArray dataHtmlParserCodingUtf8() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_utf8_head.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserAttrs() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_attr.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserAttrsWithoutQuotes() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_attr_without_quotas.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserBaseTemplate() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_base_template.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserShortTemplate() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_base_short_template.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserClasses() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_classes.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserConditionalComments() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_conditional_comments.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserHiddenComments() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_hidden_comments.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserCdataJs() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_cdata_js.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserCdataHtml() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_cdata_html.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserCheckboxes() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_post_form_checkbox.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserRadios() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_post_form_radio.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserSelects() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_post_form_select.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserTexts() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_post_form_text.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserIFrame() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_iframe.txt")));
        return data_parser;
    }
    static QByteArray dataHtmlParserTable() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_table.txt")));
        return data_parser;
    }

    static QByteArray dataHtmlParserPredicableTagClosure() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_html_predicable_tag_closure.txt")));
        return data_parser;
    }

    static QByteArray dataHtml5ParserVideo() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_video_html5.txt")));
        return data_parser;
    }

    static QByteArray dataHtmlParserErrorWrongCloseTag() {
        static QByteArray data_parser = load(DATA_PATH(QStringLiteral("test_wrong_tags_closing.txt")));
        return data_parser;
    }



    static const char * dataSelectorParsingHuge() {
        return "> *:active:3[name='Loop' top] div p.loop #id.tool .yopt[gog loh]~['piza to'=123] p[text*'sdfsdf \\'ssda'] <.sos";
    }
    static const char * dataSelectorParsingRootPs() { return "> p"; }
    static const char * dataSelectorParsingAnyLevelPs() { return "* > p"; }
    static const char * dataSelectorParsingWithAttrs() { return "p[name='Loop' top]"; }
    static const char * dataSelectorParsingWithQuitedAttrs() { return "p['name bli'='Loop' 'lo jka'='cool']"; }
    static const char * dataSelectorParsingWithDoubleAttrs() { return "p[name='Loop'][cool='Lo']"; }
    static const char * dataSelectorParsingWithAttrsNoQuotes() { return "p[name=Loop pop=1]"; }
    static const char * dataSelectorParsingWithAttrsNoTag() { return "[name=Loop]"; }
    static const char * dataSelectorParsingWithAllLimits() { return ".cla#ss:47:disabled:text[name=Loop]"; }
    static const char * dataSelectorParsingWithAdditionalBlanks() { return ".cla[name=Loop  cool] ~ a"; }
    static const char * dataSelectorParsingWithStrictSplitters() { return ".cla[name=Loop cool]~a"; }
    static const char * dataSelectorParsingWithEmptyBrackets() { return ".cla[]"; }

    static const char * dataSelectorParsingCombo1() { return "p.class a"; }
    static const char * dataSelectorParsingCombo2() { return ".cla#ss:47:disabled[name=Loop]"; }
    static const char * dataSelectorParsingCombo3() { return "[name=Loop] > :3"; }
    static const char * dataSelectorParsingCombo4() { return "a ol > li < a ~ div + p - ul"; }
};

#endif // TEST_DATA_H
