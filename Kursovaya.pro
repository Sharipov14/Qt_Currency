QT       += core gui sql charts
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Database/sqlrec.cpp \
    dialogs/dialogaddbalance.cpp \
    dialogs/dialogeditpassword.cpp \
    dialogs/dialogeditprofil.cpp \
    editors/mydelegate.cpp \
    editors/userseditor.cpp \
    main.cpp \
    mainwindow.cpp \
    menu/mainmenu.cpp \
    menu/wgtedittable.cpp \
    menu/wgtexchangecurrency.cpp \
    menu/wgtgraphic.cpp \
    menu/wgtmyoperations.cpp \
    menu/wgtprofil.cpp \
    reg/loginform.cpp \
    reg/registrationform.cpp \
    reg/restoreaccount.cpp

HEADERS += \
    Database/SQL.h \
    Database/sqlrec.h \
    dialogs/dialogaddbalance.h \
    dialogs/dialogeditpassword.h \
    dialogs/dialogeditprofil.h \
    editors/mydelegate.h \
    editors/userseditor.h \
    mainwindow.h \
    menu/mainmenu.h \
    menu/wgtedittable.h \
    menu/wgtexchangecurrency.h \
    menu/wgtgraphic.h \
    menu/wgtmyoperations.h \
    menu/wgtprofil.h \
    reg/loginform.h \
    reg/registrationform.h \
    reg/restoreaccount.h \
    tables/balance.h \
    tables/contract.h \
    tables/currency.h \
    tables/exchangerates.h \
    tables/myoperation.h \
    tables/operation.h \
    tables/session.h \
    tables/users.h

FORMS += \
    dialogs/dialogaddbalance.ui \
    dialogs/dialogeditpassword.ui \
    dialogs/dialogeditprofil.ui \
    editors/userseditor.ui \
    mainwindow.ui \
    menu/mainmenu.ui \
    menu/wgtedittable.ui \
    menu/wgtexchangecurrency.ui \
    menu/wgtgraphic.ui \
    menu/wgtmyoperations.ui \
    menu/wgtprofil.ui \
    reg/loginform.ui \
    reg/registrationform.ui \
    reg/restoreaccount.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resurce.qrc

DISTFILES += \
    ../../../../Pictures/icons/icons/Adobe Animate.ico
