SOURCES += \
    src/main.cpp \
    src/mainframe.cpp \
    src/smtp.cpp \
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
    includes/SQL/sqllitehelper.cpp \
    includes/popClient/popclient.cpp \
    includes/Meeting/addmeeting.cpp \
    includes/Meeting/detailmeeting.cpp \
    includes/Meeting/meeting.cpp \
    includes/Meeting/meetingwindow.cpp \
    includes/Meeting/room.cpp \
    includes/Meeting/user.cpp \
    src/sendnewemail.cpp \
    src/settings.cpp \
    src/initconfig.cpp \
    src/previewedemail.cpp \
    src/detailledemail.cpp \
    src/custommessagelist.cpp \
    src/widgetpreviewed.cpp

HEADERS += \
    src/global.h \
    src/mainframe.h \
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
    includes/SQL/sqllitehelper.h \
    includes/popClient/popclient.h \
    includes/Meeting/addmeeting.h \
    includes/Meeting/detailmeeting.h \
    includes/Meeting/meeting.h \
    includes/Meeting/meetingwindow.h \
    includes/Meeting/room.h \
    includes/Meeting/user.h \
    src/sendnewemail.h \
    src/settings.h \
    src/initconfig.h \
    src/previewedemail.h \
    src/detailledemail.h \
    src/custommessagelist.h \
    src/widgetpreviewed.h \
    includes/smtpClient/src/SmtpMime

QT += widgets core network sql


RESOURCES += \
    ressources.qrc

OTHER_FILES += \
    data/settings/settings.ini
