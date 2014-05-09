SOURCES += \
    main.cpp \
    mainframe.cpp \
    smtp.cpp \
    includes/smtpClient/src/emailaddress.cpp \
    includes/smtpClient/src/mimeattachment.cpp \
    includes/smtpClient/src/mimecontentformatter.cpp \
    includes/smtpClient/src/mimefile.cpp \
    includes/smtpClient/src/mimehtml.cpp \
    includes/smtpClient/src/mimeinlinefile.cpp \
    includes/smtpClient/src/mimemessage.cpp \
    includes/smtpClient/src/mimemultipart.cpp \
    includes/smtpClient/src/mimepart.cpp \
    includes/smtpClient/src/mimetext.cpp \
    includes/smtpClient/src/quotedprintable.cpp \
    includes/smtpClient/src/smtpclient.cpp \
    sendnewemail.cpp

HEADERS += \
    global.h \
    mainframe.h \
    includes/smtpClient/src/emailaddress.h \
    includes/smtpClient/src/mimeattachment.h \
    includes/smtpClient/src/mimecontentformatter.h \
    includes/smtpClient/src/mimefile.h \
    includes/smtpClient/src/mimehtml.h \
    includes/smtpClient/src/mimeinlinefile.h \
    includes/smtpClient/src/mimemessage.h \
    includes/smtpClient/src/mimemultipart.h \
    includes/smtpClient/src/mimepart.h \
    includes/smtpClient/src/mimetext.h \
    includes/smtpClient/src/quotedprintable.h \
    includes/smtpClient/src/smtpclient.h \
    includes/smtpClient/src/SmtpMime \
    sendnewemail.h


QT += widgets core network

