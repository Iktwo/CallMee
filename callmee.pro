TARGET = callmee

CONFIG += qdeclarative-boostable

QT += dbus

PKGCONFIG += gq-gconf

SOURCES += src/main.cpp \
    src/autoanswer.cpp

HEADERS += \
    src/autoanswer.h

target.path = /opt/callmee/bin

settingsdesktop.path = /usr/lib/duicontrolpanel/
settingsdesktop.files = resources/callmee.desktop

settingsxml.path = /usr/share/duicontrolpanel/uidescriptions/
settingsxml.files = resources/callmee.xml

mydaemon.files = resources/callmee.conf
mydaemon.path = /etc/init/apps

script.files = src/callmee.sh
script.path = /opt/callmee/bin

INSTALLS += settingsdesktop settingsxml mydaemon script target

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
