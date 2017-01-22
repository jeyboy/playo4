include(../../pri/tag_lib.pri)

QT -= core gui

TARGET = TagLib$${LIB_SUFFIX}
TEMPLATE = lib
#CONFIG += staticlib

DEFINES += TAGLIB_LIBRARY

INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/ape)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/asf)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/flac)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/it)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/mod)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/mp4)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/mpc)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/mpeg)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/mpeg/id3v1)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/mpeg/id3v2)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/mpeg/id3v2/frames)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/ogg)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/ogg/flac)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/ogg/opus)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/ogg/speex)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/ogg/vorbis)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/riff)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/riff/aiff)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/riff/wav)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/s3m)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/toolkit)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/trueaudio)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/wavpack)
INCLUDEPATH += $$quote($${_PRO_FILE_PWD_}/xm)

#HEADERS += config.h
HEADERS += taglib_config.h
HEADERS += audioproperties.h
HEADERS += fileref.h
HEADERS += tag.h
HEADERS += tagutils.h
HEADERS += taglib_export.h
HEADERS += tagunion.h
HEADERS += ape/apefile.h
HEADERS += ape/apefooter.h
HEADERS += ape/apeitem.h
HEADERS += ape/apeproperties.h
HEADERS += ape/apetag.h
HEADERS += asf/asfattribute.h
HEADERS += asf/asffile.h
HEADERS += asf/asfproperties.h
HEADERS += asf/asfpicture.h
HEADERS += asf/asftag.h
HEADERS += flac/flacfile.h
HEADERS += flac/flacproperties.h
HEADERS += flac/flacmetadatablock.h
HEADERS += flac/flacpicture.h
HEADERS += flac/flacunknownmetadatablock.h
HEADERS += it/itfile.h
HEADERS += it/itproperties.h
HEADERS += mp4/mp4atom.h
HEADERS += mp4/mp4coverart.h
HEADERS += mp4/mp4file.h
HEADERS += mp4/mp4item.h
HEADERS += mp4/mp4properties.h
HEADERS += mp4/mp4tag.h
HEADERS += mpc/mpcfile.h
HEADERS += mpc/mpcproperties.h
HEADERS += mpeg/mpegfile.h
HEADERS += mpeg/mpegheader.h
HEADERS += mpeg/mpegproperties.h
HEADERS += mpeg/xingheader.h
HEADERS += mpeg/id3v1/id3v1genres.h
HEADERS += mpeg/id3v1/id3v1tag.h
HEADERS += mpeg/id3v2/id3v2extendedheader.h
HEADERS += mpeg/id3v2/id3v2footer.h
HEADERS += mpeg/id3v2/id3v2frame.h
HEADERS += mpeg/id3v2/id3v2framefactory.h
HEADERS += mpeg/id3v2/id3v2header.h
HEADERS += mpeg/id3v2/id3v2synchdata.h
HEADERS += mpeg/id3v2/id3v2tag.h
HEADERS += mpeg/id3v2/frames/attachedpictureframe.h
HEADERS += mpeg/id3v2/frames/chapterframe.h
HEADERS += mpeg/id3v2/frames/commentsframe.h
HEADERS += mpeg/id3v2/frames/eventtimingcodesframe.h
HEADERS += mpeg/id3v2/frames/generalencapsulatedobjectframe.h
HEADERS += mpeg/id3v2/frames/popularimeterframe.h
HEADERS += mpeg/id3v2/frames/privateframe.h
HEADERS += mpeg/id3v2/frames/relativevolumeframe.h
HEADERS += mpeg/id3v2/frames/tableofcontentsframe.h
HEADERS += mpeg/id3v2/frames/textidentificationframe.h
HEADERS += mpeg/id3v2/frames/ownershipframe.h
HEADERS += mpeg/id3v2/frames/podcastframe.h
HEADERS += mpeg/id3v2/frames/uniquefileidentifierframe.h
HEADERS += mpeg/id3v2/frames/unknownframe.h
HEADERS += mpeg/id3v2/frames/synchronizedlyricsframe.h
HEADERS += mpeg/id3v2/frames/unsynchronizedlyricsframe.h
HEADERS += mpeg/id3v2/frames/urllinkframe.h
HEADERS += mod/modfile.h
HEADERS += mod/modfileprivate.h
HEADERS += mod/modfilebase.h
HEADERS += mod/modproperties.h
HEADERS += mod/modtag.h
HEADERS += ogg/oggfile.h
HEADERS += ogg/oggpage.h
HEADERS += ogg/oggpageheader.h
HEADERS += ogg/xiphcomment.h
HEADERS += ogg/flac/oggflacfile.h
HEADERS += ogg/speex/speexfile.h
HEADERS += ogg/speex/speexproperties.h
HEADERS += ogg/vorbis/vorbisfile.h
HEADERS += ogg/vorbis/vorbisproperties.h
HEADERS += ogg/opus/opusfile.h
HEADERS += ogg/opus/opusproperties.h
HEADERS += riff/rifffile.h
HEADERS += riff/aiff/aifffile.h
HEADERS += riff/aiff/aiffproperties.h
HEADERS += riff/wav/infotag.h
HEADERS += riff/wav/wavfile.h
HEADERS += riff/wav/wavproperties.h
HEADERS += s3m/s3mfile.h
HEADERS += s3m/s3mproperties.h
HEADERS += toolkit/taglib.h
HEADERS += toolkit/tbytevector.h
HEADERS += toolkit/tbytevectorlist.h
HEADERS += toolkit/tdebug.h
HEADERS += toolkit/tdebuglistener.h
HEADERS += toolkit/tfile.h
HEADERS += toolkit/tfilestream.h
HEADERS += toolkit/tiostream.h
HEADERS += toolkit/tlist.h
HEADERS += toolkit/tmap.h
HEADERS += toolkit/trefcounter.h
HEADERS += toolkit/tpropertymap.h
HEADERS += toolkit/tstring.h
HEADERS += toolkit/tstringlist.h
HEADERS += toolkit/tzlib.h
HEADERS += toolkit/unicode.h
HEADERS += trueaudio/trueaudiofile.h
HEADERS += trueaudio/trueaudioproperties.h
HEADERS += wavpack/wavpackfile.h
HEADERS += wavpack/wavpackproperties.h
HEADERS += xm/xmfile.h
HEADERS += xm/xmproperties.h

SOURCES += audioproperties.cpp
SOURCES += fileref.cpp
SOURCES += tag.cpp
SOURCES += tagutils.cpp
SOURCES += tagunion.cpp
SOURCES += ape/apefile.cpp
SOURCES += ape/apefooter.cpp
SOURCES += ape/apeitem.cpp
SOURCES += ape/apeproperties.cpp
SOURCES += ape/apetag.cpp
SOURCES += asf/asfattribute.cpp
SOURCES += asf/asffile.cpp
SOURCES += asf/asfproperties.cpp
SOURCES += asf/asfpicture.cpp
SOURCES += asf/asftag.cpp
SOURCES += flac/flacfile.cpp
SOURCES += flac/flacmetadatablock.cpp
SOURCES += flac/flacpicture.cpp
SOURCES += flac/flacproperties.cpp
SOURCES += flac/flacunknownmetadatablock.cpp
SOURCES += it/itfile.cpp
SOURCES += it/itproperties.cpp
SOURCES += mp4/mp4atom.cpp
SOURCES += mp4/mp4coverart.cpp
SOURCES += mp4/mp4file.cpp
SOURCES += mp4/mp4item.cpp
SOURCES += mp4/mp4properties.cpp
SOURCES += mp4/mp4tag.cpp
SOURCES += mpc/mpcfile.cpp
SOURCES += mpc/mpcproperties.cpp
SOURCES += mpeg/mpegfile.cpp
SOURCES += mpeg/mpegheader.cpp
SOURCES += mpeg/mpegproperties.cpp
SOURCES += mpeg/xingheader.cpp
SOURCES += mpeg/id3v1/id3v1genres.cpp
SOURCES += mpeg/id3v1/id3v1tag.cpp
SOURCES += mpeg/id3v2/id3v2extendedheader.cpp
SOURCES += mpeg/id3v2/id3v2footer.cpp
SOURCES += mpeg/id3v2/id3v2frame.cpp
SOURCES += mpeg/id3v2/id3v2framefactory.cpp
SOURCES += mpeg/id3v2/id3v2header.cpp
SOURCES += mpeg/id3v2/id3v2synchdata.cpp
SOURCES += mpeg/id3v2/id3v2tag.cpp
SOURCES += mpeg/id3v2/frames/attachedpictureframe.cpp
SOURCES += mpeg/id3v2/frames/chapterframe.cpp
SOURCES += mpeg/id3v2/frames/commentsframe.cpp
SOURCES += mpeg/id3v2/frames/eventtimingcodesframe.cpp
SOURCES += mpeg/id3v2/frames/generalencapsulatedobjectframe.cpp
SOURCES += mpeg/id3v2/frames/popularimeterframe.cpp
SOURCES += mpeg/id3v2/frames/privateframe.cpp
SOURCES += mpeg/id3v2/frames/relativevolumeframe.cpp
SOURCES += mpeg/id3v2/frames/tableofcontentsframe.cpp
SOURCES += mpeg/id3v2/frames/textidentificationframe.cpp
SOURCES += mpeg/id3v2/frames/ownershipframe.cpp
SOURCES += mpeg/id3v2/frames/podcastframe.cpp
SOURCES += mpeg/id3v2/frames/uniquefileidentifierframe.cpp
SOURCES += mpeg/id3v2/frames/unknownframe.cpp
SOURCES += mpeg/id3v2/frames/synchronizedlyricsframe.cpp
SOURCES += mpeg/id3v2/frames/unsynchronizedlyricsframe.cpp
SOURCES += mpeg/id3v2/frames/urllinkframe.cpp
SOURCES += mod/modfile.cpp
SOURCES += mod/modfilebase.cpp
SOURCES += mod/modproperties.cpp
SOURCES += mod/modtag.cpp
SOURCES += ogg/oggfile.cpp
SOURCES += ogg/oggpage.cpp
SOURCES += ogg/oggpageheader.cpp
SOURCES += ogg/xiphcomment.cpp
SOURCES += ogg/flac/oggflacfile.cpp
SOURCES += ogg/speex/speexfile.cpp
SOURCES += ogg/speex/speexproperties.cpp
SOURCES += ogg/vorbis/vorbisfile.cpp
SOURCES += ogg/vorbis/vorbisproperties.cpp
SOURCES += ogg/opus/opusfile.cpp
SOURCES += ogg/opus/opusproperties.cpp
SOURCES += riff/rifffile.cpp
SOURCES += riff/aiff/aifffile.cpp
SOURCES += riff/aiff/aiffproperties.cpp
SOURCES += riff/wav/infotag.cpp
SOURCES += riff/wav/wavfile.cpp
SOURCES += riff/wav/wavproperties.cpp
SOURCES += s3m/s3mfile.cpp
SOURCES += s3m/s3mproperties.cpp
SOURCES += toolkit/tbytevector.cpp
SOURCES += toolkit/tbytevectorlist.cpp
SOURCES += toolkit/tdebug.cpp
SOURCES += toolkit/tdebuglistener.cpp
SOURCES += toolkit/tfile.cpp
SOURCES += toolkit/tfilestream.cpp
SOURCES += toolkit/tiostream.cpp
SOURCES += toolkit/trefcounter.cpp
SOURCES += toolkit/tpropertymap.cpp
SOURCES += toolkit/tstring.cpp
SOURCES += toolkit/tstringlist.cpp
SOURCES += toolkit/tzlib.cpp
SOURCES += toolkit/unicode.cpp
SOURCES += trueaudio/trueaudiofile.cpp
SOURCES += trueaudio/trueaudioproperties.cpp
SOURCES += wavpack/wavpackfile.cpp
SOURCES += wavpack/wavpackproperties.cpp
SOURCES += xm/xmfile.cpp
SOURCES += xm/xmproperties.cpp

DEFINES += MAKE_TAGLIB_LIB

######## setup block
include(../../pri/headers_preparer.pri)
####### end setup block

win32 {
    QMAKE_TARGET_PRODUCT = Tag Lib
    QMAKE_TARGET_DESCRIPTION = Tag library

#    CONFIG += dll
}

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
