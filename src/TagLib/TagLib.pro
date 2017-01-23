include(../../pri/tag_lib.pri)

QT -= core gui

TARGET = TagLib$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += TAGLIB_LIBRARY MAKE_TAGLIB_LIB

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

INCLUDEPATH += \
    $$quote($${_PRO_FILE_PWD_}/ape) \
    $$quote($${_PRO_FILE_PWD_}/asf) \
    $$quote($${_PRO_FILE_PWD_}/flac) \
    $$quote($${_PRO_FILE_PWD_}/it) \
    $$quote($${_PRO_FILE_PWD_}/mod) \
    $$quote($${_PRO_FILE_PWD_}/mp4) \
    $$quote($${_PRO_FILE_PWD_}/mpc) \
    $$quote($${_PRO_FILE_PWD_}/mpeg) \
    $$quote($${_PRO_FILE_PWD_}/mpeg/id3v1) \
    $$quote($${_PRO_FILE_PWD_}/mpeg/id3v2) \
    $$quote($${_PRO_FILE_PWD_}/mpeg/id3v2/frames) \
    $$quote($${_PRO_FILE_PWD_}/ogg) \
    $$quote($${_PRO_FILE_PWD_}/ogg/flac) \
    $$quote($${_PRO_FILE_PWD_}/ogg/opus) \
    $$quote($${_PRO_FILE_PWD_}/ogg/speex) \
    $$quote($${_PRO_FILE_PWD_}/ogg/vorbis) \
    $$quote($${_PRO_FILE_PWD_}/riff) \
    $$quote($${_PRO_FILE_PWD_}/riff/aiff) \
    $$quote($${_PRO_FILE_PWD_}/riff/wav) \
    $$quote($${_PRO_FILE_PWD_}/s3m) \
    $$quote($${_PRO_FILE_PWD_}/toolkit) \
    $$quote($${_PRO_FILE_PWD_}/trueaudio) \
    $$quote($${_PRO_FILE_PWD_}/wavpack) \
    $$quote($${_PRO_FILE_PWD_}/xm)



HEADERS += \
    #config.h \
    taglib_config.h \
    audioproperties.h \
    fileref.h \
    tag.h \
    tagutils.h \
    taglib_export.h \
    tagunion.h \
    ape/apefile.h \
    ape/apefooter.h \
    ape/apeitem.h \
    ape/apeproperties.h \
    ape/apetag.h \
    asf/asfattribute.h \
    asf/asffile.h \
    asf/asfproperties.h \
    asf/asfpicture.h \
    asf/asftag.h \
    flac/flacfile.h \
    flac/flacproperties.h \
    flac/flacmetadatablock.h \
    flac/flacpicture.h \
    flac/flacunknownmetadatablock.h \
    it/itfile.h \
    it/itproperties.h \
    mp4/mp4atom.h \
    mp4/mp4coverart.h \
    mp4/mp4file.h \
    mp4/mp4item.h \
    mp4/mp4properties.h \
    mp4/mp4tag.h \
    mpc/mpcfile.h \
    mpc/mpcproperties.h \
    mpeg/mpegfile.h \
    mpeg/mpegheader.h \
    mpeg/mpegproperties.h \
    mpeg/xingheader.h \
    mpeg/id3v1/id3v1genres.h \
    mpeg/id3v1/id3v1tag.h \
    mpeg/id3v2/id3v2extendedheader.h \
    mpeg/id3v2/id3v2footer.h \
    mpeg/id3v2/id3v2frame.h \
    mpeg/id3v2/id3v2framefactory.h \
    mpeg/id3v2/id3v2header.h \
    mpeg/id3v2/id3v2synchdata.h \
    mpeg/id3v2/id3v2tag.h \
    mpeg/id3v2/frames/attachedpictureframe.h \
    mpeg/id3v2/frames/chapterframe.h \
    mpeg/id3v2/frames/commentsframe.h \
    mpeg/id3v2/frames/eventtimingcodesframe.h \
    mpeg/id3v2/frames/generalencapsulatedobjectframe.h \
    mpeg/id3v2/frames/popularimeterframe.h \
    mpeg/id3v2/frames/privateframe.h \
    mpeg/id3v2/frames/relativevolumeframe.h \
    mpeg/id3v2/frames/tableofcontentsframe.h \
    mpeg/id3v2/frames/textidentificationframe.h \
    mpeg/id3v2/frames/ownershipframe.h \
    mpeg/id3v2/frames/podcastframe.h \
    mpeg/id3v2/frames/uniquefileidentifierframe.h \
    mpeg/id3v2/frames/unknownframe.h \
    mpeg/id3v2/frames/synchronizedlyricsframe.h \
    mpeg/id3v2/frames/unsynchronizedlyricsframe.h \
    mpeg/id3v2/frames/urllinkframe.h \
    mod/modfile.h \
    mod/modfileprivate.h \
    mod/modfilebase.h \
    mod/modproperties.h \
    mod/modtag.h \
    ogg/oggfile.h \
    ogg/oggpage.h \
    ogg/oggpageheader.h \
    ogg/xiphcomment.h \
    ogg/flac/oggflacfile.h \
    ogg/speex/speexfile.h \
    ogg/speex/speexproperties.h \
    ogg/vorbis/vorbisfile.h \
    ogg/vorbis/vorbisproperties.h \
    ogg/opus/opusfile.h \
    ogg/opus/opusproperties.h \
    riff/rifffile.h \
    riff/aiff/aifffile.h \
    riff/aiff/aiffproperties.h \
    riff/wav/infotag.h \
    riff/wav/wavfile.h \
    riff/wav/wavproperties.h \
    s3m/s3mfile.h \
    s3m/s3mproperties.h \
    toolkit/taglib.h \
    toolkit/tbytevector.h \
    toolkit/tbytevectorlist.h \
    toolkit/tdebug.h \
    toolkit/tdebuglistener.h \
    toolkit/tfile.h \
    toolkit/tfilestream.h \
    toolkit/tiostream.h \
    toolkit/tlist.h \
    toolkit/tmap.h \
    toolkit/trefcounter.h \
    toolkit/tpropertymap.h \
    toolkit/tstring.h \
    toolkit/tstringlist.h \
    toolkit/tzlib.h \
    toolkit/unicode.h \
    trueaudio/trueaudiofile.h \
    trueaudio/trueaudioproperties.h \
    wavpack/wavpackfile.h \
    wavpack/wavpackproperties.h \
    xm/xmfile.h \
    xm/xmproperties.h

SOURCES += \
    audioproperties.cpp \
    fileref.cpp \
    tag.cpp \
    tagutils.cpp \
    tagunion.cpp \
    ape/apefile.cpp \
    ape/apefooter.cpp \
    ape/apeitem.cpp \
    ape/apeproperties.cpp \
    ape/apetag.cpp \
    asf/asfattribute.cpp \
    asf/asffile.cpp \
    asf/asfproperties.cpp \
    asf/asfpicture.cpp \
    asf/asftag.cpp \
    flac/flacfile.cpp \
    flac/flacmetadatablock.cpp \
    flac/flacpicture.cpp \
    flac/flacproperties.cpp \
    flac/flacunknownmetadatablock.cpp \
    it/itfile.cpp \
    it/itproperties.cpp \
    mp4/mp4atom.cpp \
    mp4/mp4coverart.cpp \
    mp4/mp4file.cpp \
    mp4/mp4item.cpp \
    mp4/mp4properties.cpp \
    mp4/mp4tag.cpp \
    mpc/mpcfile.cpp \
    mpc/mpcproperties.cpp \
    mpeg/mpegfile.cpp \
    mpeg/mpegheader.cpp \
    mpeg/mpegproperties.cpp \
    mpeg/xingheader.cpp \
    mpeg/id3v1/id3v1genres.cpp \
    mpeg/id3v1/id3v1tag.cpp \
    mpeg/id3v2/id3v2extendedheader.cpp \
    mpeg/id3v2/id3v2footer.cpp \
    mpeg/id3v2/id3v2frame.cpp \
    mpeg/id3v2/id3v2framefactory.cpp \
    mpeg/id3v2/id3v2header.cpp \
    mpeg/id3v2/id3v2synchdata.cpp \
    mpeg/id3v2/id3v2tag.cpp \
    mpeg/id3v2/frames/attachedpictureframe.cpp \
    mpeg/id3v2/frames/chapterframe.cpp \
    mpeg/id3v2/frames/commentsframe.cpp \
    mpeg/id3v2/frames/eventtimingcodesframe.cpp \
    mpeg/id3v2/frames/generalencapsulatedobjectframe.cpp \
    mpeg/id3v2/frames/popularimeterframe.cpp \
    mpeg/id3v2/frames/privateframe.cpp \
    mpeg/id3v2/frames/relativevolumeframe.cpp \
    mpeg/id3v2/frames/tableofcontentsframe.cpp \
    mpeg/id3v2/frames/textidentificationframe.cpp \
    mpeg/id3v2/frames/ownershipframe.cpp \
    mpeg/id3v2/frames/podcastframe.cpp \
    mpeg/id3v2/frames/uniquefileidentifierframe.cpp \
    mpeg/id3v2/frames/unknownframe.cpp \
    mpeg/id3v2/frames/synchronizedlyricsframe.cpp \
    mpeg/id3v2/frames/unsynchronizedlyricsframe.cpp \
    mpeg/id3v2/frames/urllinkframe.cpp \
    mod/modfile.cpp \
    mod/modfilebase.cpp \
    mod/modproperties.cpp \
    mod/modtag.cpp \
    ogg/oggfile.cpp \
    ogg/oggpage.cpp \
    ogg/oggpageheader.cpp \
    ogg/xiphcomment.cpp \
    ogg/flac/oggflacfile.cpp \
    ogg/speex/speexfile.cpp \
    ogg/speex/speexproperties.cpp \
    ogg/vorbis/vorbisfile.cpp \
    ogg/vorbis/vorbisproperties.cpp \
    ogg/opus/opusfile.cpp \
    ogg/opus/opusproperties.cpp \
    riff/rifffile.cpp \
    riff/aiff/aifffile.cpp \
    riff/aiff/aiffproperties.cpp \
    riff/wav/infotag.cpp \
    riff/wav/wavfile.cpp \
    riff/wav/wavproperties.cpp \
    s3m/s3mfile.cpp \
    s3m/s3mproperties.cpp \
    toolkit/tbytevector.cpp \
    toolkit/tbytevectorlist.cpp \
    toolkit/tdebug.cpp \
    toolkit/tdebuglistener.cpp \
    toolkit/tfile.cpp \
    toolkit/tfilestream.cpp \
    toolkit/tiostream.cpp \
    toolkit/trefcounter.cpp \
    toolkit/tpropertymap.cpp \
    toolkit/tstring.cpp \
    toolkit/tstringlist.cpp \
    toolkit/tzlib.cpp \
    toolkit/unicode.cpp \
    trueaudio/trueaudiofile.cpp \
    trueaudio/trueaudioproperties.cpp \
    wavpack/wavpackfile.cpp \
    wavpack/wavpackproperties.cpp \
    xm/xmfile.cpp \
    xm/xmproperties.cpp

######## setup block
include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Tag Lib
    QMAKE_TARGET_DESCRIPTION = Tag library
}
