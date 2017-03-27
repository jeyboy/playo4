include(../../../pri/curl_lib.pri)

#version 7.52.1

QT -= core gui

TARGET = CurlLib$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += CURLLIB_LIBRARY BUILDING_LIBCURL USE_OPENSSL #ENABLE_IPV6 #CURL_STATICLIB

defined(STATIC_BUILD) {
    CONFIG += staticlib
}

RC_FILE = libcurl.rc

#        "config-amigaos.h" \
#        "config-dos.h" \
#        "config-mac.h" \
#        "config-os400.h" \
#        "config-riscos.h" \
#        "config-symbian.h" \
#        "config-tpf.h" \
#        "config-vxworks.h" \
#        "config-win32.h" \
#        "config-win32ce.h" \

win32 {
    HEADERS += config-win32.h

    LIBS += -lws2_32 -lWldap32
}

#zlib support
DEFINES += HAVE_ZLIB_H HAVE_ZLIB HAVE_LIBZ
LIBS += -lzlib$${LIB_VERSION}
###########

INCLUDE_HEADERS = \
        "curl/curl.h" \
        "curl/curlbuild.h" \
        "curl/curlrules.h" \
        "curl/curlver.h" \
        "curl/easy.h" \
        "curl/mprintf.h" \
        "curl/multi.h" \
        "curl/stdcheaders.h" \
        "curl/typecheck-gcc.h"

HEADERS += \
        $${INCLUDE_HEADERS} \
        "amigaos.h" \
        "arpa_telnet.h" \
        "asyn.h" \
        "conncache.h" \
        "connect.h" \
        "content_encoding.h" \
        "cookie.h" \
        "curlx.h" \
        "curl_addrinfo.h" \
        "curl_base64.h" \
        "curl_des.h" \
        "curl_endian.h" \
        "curl_fnmatch.h" \
        "curl_gethostname.h" \
        "curl_gssapi.h" \
        "curl_hmac.h" \
        "curl_ldap.h" \
        "curl_md4.h" \
        "curl_md5.h" \
        "curl_memory.h" \
        "curl_memrchr.h" \
        "curl_multibyte.h" \
        "curl_ntlm_core.h" \
        "curl_ntlm_wb.h" \
        "curl_printf.h" \
        "curl_rtmp.h" \
        "curl_sasl.h" \
        "curl_sec.h" \
        "curl_setup.h" \
        "curl_setup_once.h" \
        "curl_sspi.h" \
        "curl_threads.h" \
        "dict.h" \
        "dotdot.h" \
        "easyif.h" \
        "escape.h" \
        "file.h" \
        "fileinfo.h" \
        "formdata.h" \
        "ftp.h" \
        "ftplistparser.h" \
        "getinfo.h" \
        "gopher.h" \
        "hash.h" \
        "hostcheck.h" \
        "hostip.h" \
        "http.h" \
        "http2.h" \
        "http_chunks.h" \
        "http_digest.h" \
        "http_negotiate.h" \
        "http_ntlm.h" \
        "http_proxy.h" \
        "if2ip.h" \
        "imap.h" \
        "inet_ntop.h" \
        "inet_pton.h" \
        "llist.h" \
        "memdebug.h" \
        "multihandle.h" \
        "multiif.h" \
        "netrc.h" \
        "non-ascii.h" \
        "nonblock.h" \
        "parsedate.h" \
        "pingpong.h" \
        "pipeline.h" \
        "pop3.h" \
        "progress.h" \
        "rand.h" \
        "rtsp.h" \
        "select.h" \
        "sendf.h" \
        "setup-os400.h" \
        "setup-vms.h" \
        "share.h" \
        "sigpipe.h" \
        "slist.h" \
        "smb.h" \
        "smtp.h" \
        "sockaddr.h" \
        "socks.h" \
        "speedcheck.h" \
        "splay.h" \
        "ssh.h" \
        "strcase.h" \
        "strdup.h" \
        "strerror.h" \
        "strtok.h" \
        "strtoofft.h" \
        "system_win32.h" \
        "telnet.h" \
        "tftp.h" \
        "timeval.h" \
        "transfer.h" \
        "url.h" \
        "urldata.h" \
        "vauth/digest.h" \
        "vauth/ntlm.h" \
        "vauth/vauth.h" \
        "vtls/axtls.h" \
        "vtls/cyassl.h" \
        "vtls/darwinssl.h" \
        "vtls/gskit.h" \
        "vtls/gtls.h" \
        "vtls/mbedtls.h" \
        "vtls/nssg.h" \
        "vtls/openssl.h" \
        "vtls/polarssl.h" \
        "vtls/polarssl_threadlock.h" \
        "vtls/schannel.h" \
        "vtls/vtls.h" \
        "warnless.h" \
        "wildcard.h" \
        "x509asn1.h"

SOURCES += "amigaos.c" \
        "asyn-ares.c" \
        "asyn-thread.c" \
        "base64.c" \
        "conncache.c" \
        "connect.c" \
        "content_encoding.c" \
        "cookie.c" \
        "curl_addrinfo.c" \
        "curl_des.c" \
        "curl_endian.c" \
        "curl_fnmatch.c" \
        "curl_gethostname.c" \
        "curl_gssapi.c" \
        "curl_memrchr.c" \
        "curl_multibyte.c" \
        "curl_ntlm_core.c" \
        "curl_ntlm_wb.c" \
        "curl_rtmp.c" \
        "curl_sasl.c" \
        "curl_sspi.c" \
        "curl_threads.c" \
        "dict.c" \
        "dotdot.c" \
        "easy.c" \
        "escape.c" \
        "file.c" \
        "fileinfo.c" \
        "formdata.c" \
        "ftp.c" \
        "ftplistparser.c" \
        "getenv.c" \
        "getinfo.c" \
        "gopher.c" \
        "hash.c" \
        "hmac.c" \
        "hostasyn.c" \
        "hostcheck.c" \
        "hostip.c" \
        "hostip4.c" \
        "hostip6.c" \
        "hostsyn.c" \
        "http.c" \
        "http2.c" \
        "http_chunks.c" \
        "http_digest.c" \
        "http_negotiate.c" \
        "http_ntlm.c" \
        "http_proxy.c" \
        "idn_win32.c" \
        "if2ip.c" \
        "imap.c" \
        "inet_ntop.c" \
        "inet_pton.c" \
        "krb5.c" \
        "ldap.c" \
        "llist.c" \
        "md4.c" \
        "md5.c" \
        "memdebug.c" \
        "mprintf.c" \
        "multi.c" \
        "netrc.c" \
        "non-ascii.c" \
        "nonblock.c" \
        "nwlib.c" \
        "nwos.c" \
        "openldap.c" \
        "parsedate.c" \
        "pingpong.c" \
        "pipeline.c" \
        "pop3.c" \
        "progress.c" \
        "rand.c" \
        "rtsp.c" \
        "security.c" \
        "select.c" \
        "sendf.c" \
        "share.c" \
        "slist.c" \
        "smb.c" \
        "smtp.c" \
        "socks.c" \
        "socks_gssapi.c" \
        "socks_sspi.c" \
        "speedcheck.c" \
        "splay.c" \
        "ssh.c" \
        "strcase.c" \
        "strdup.c" \
        "strerror.c" \
        "strtok.c" \
        "strtoofft.c" \
        "system_win32.c" \
        "telnet.c" \
        "tftp.c" \
        "timeval.c" \
        "transfer.c" \
        "url.c" \
        "vauth/cleartext.c" \
        "vauth/cram.c" \
        "vauth/digest.c" \
        "vauth/digest_sspi.c" \
        "vauth/krb5_gssapi.c" \
        "vauth/krb5_sspi.c" \
        "vauth/ntlm.c" \
        "vauth/ntlm_sspi.c" \
        "vauth/oauth2.c" \
        "vauth/spnego_gssapi.c" \
        "vauth/spnego_sspi.c" \
        "vauth/vauth.c" \
        "version.c" \
        "vtls/axtls.c" \
        "vtls/cyassl.c" \
        "vtls/darwinssl.c" \
        "vtls/gskit.c" \
        "vtls/gtls.c" \
        "vtls/mbedtls.c" \
        "vtls/nss.c" \
        "vtls/openssl.c" \
        "vtls/polarssl.c" \
        "vtls/polarssl_threadlock.c" \
        "vtls/schannel.c" \
        "vtls/vtls.c" \
        "warnless.c" \
        "wildcard.c" \
        "x509asn1.c"



include($${PROJECT_ROOT_PATH}/pri/headers_preparer.pri)

win32 {
    QMAKE_TARGET_PRODUCT = LibCurl
    QMAKE_TARGET_DESCRIPTION = Socket requests lib
}
