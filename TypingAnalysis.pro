QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 rtti_off warn_on

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32-msvc*{
  # Make warning level to be W4
  QMAKE_CXXFLAGS_WARN_ON ~= s/-W./-W4
}

SOURCES += \
    Application.cpp \
    ApplicationGUI.cpp \
    ApplicationGlobals.cpp \
    ApplicationImpl.cpp \
    ApplicationKernel.cpp \
    ExceptionHandler.cpp \
    Keyboard/KeyboardHandler.cpp \
    Keyboard/ListenerExceptionHandler.cpp \
    Keyboard/RawKeyEvent.cpp \
    Keyboard/Windows/RawInputReader.cpp \
    Qt/MainWindow.cpp \
    Qt/QtLoopExceptionHandler.cpp \
    Time.cpp \
    Timer.cpp \
    main.cpp

HEADERS += \
  Application.h \
  ApplicationGUI.h \
  ApplicationGlobals.h \
  ApplicationImpl.h \
  ApplicationKernel.h \
  ExceptionHandler.h \
  Keyboard/AnyKeyboardKiller.h \
  Keyboard/KeyboardHandler.h \
  Keyboard/KeyboardListener.h \
  Keyboard/ListenerExceptionHandler.h \
  Keyboard/RawKeyEvent.h \
  Keyboard/Windows/RawInputReader.h \
  KeyboardHandlerAccess.h \
  Library/AnyObject/AnyMovable.h \
  Library/Singleton/AnyGlobalAccess.h \
  Library/StlExtension/ThreadDetachable.h \
  Qt/MainWindow.h \
  Qt/QtLoopExceptionHandler.h \
  QtLoopException.h \
  Time.h \
  Timer.h \
  TimerAccess.h

FORMS += \
  Qt/MainWindow.ui


win32 {
    HEADERS += \
    Keyboard/Windows/KeyboardListenerWin.h \
    Keyboard/Windows/MessageWindow.h \
    Keyboard/Windows/RawInputHook.h

    SOURCES += \
    Keyboard/Windows/KeyboardListenerWin.cpp
}

macx {
    #HEADERS +=
    #SOURCES +=
}

linux {
    #HEADERS +=
    #SOURCES +=
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
