QT += widgets

HEADERS     = toolkits.h \
              pages.h
SOURCES     = toolkits.cpp \
              main.cpp \
              pages.cpp
RESOURCES   += toolkits.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/dialogs/toolkits
INSTALLS += target

wince50standard-x86-msvc2005: LIBS += libcmt.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib commctrl.lib coredll.lib winsock.lib ws2.lib
