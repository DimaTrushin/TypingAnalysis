QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 rtti_off warn_on

DEFINES += KEYBOARD_HANDLER_DEBUG

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
  win32-msvc*{
    QMAKE_CXXFLAGS_WARN_ON ~= s/-W./-W4
    QMAKE_CXXFLAGS += /MP /permissive-

    LIBS += -luser32
  }

  win32-g++*{
  }

  win32-clang*{
  }
}

linux {
  linux-g++*{
  }

  linux-clang*{
  }
}

macx {
  macx-g++*{
  }

 macx-clang*{
 }
}

HEADERS += \
  AppStatusAccess.h \
  Interface/KeyboardShutter.h \
  Interface/SessionFlusher.h \
  Kernel/KeyEvent.h \
  Kernel/Seance.h \
  Kernel/SeanceMaker.h \
  Kernel/SeanceManager.h \
  Kernel/SeanceManagerImpl.h \
  Kernel/Session.h \
  Keyboard/AnyKeyboardKiller.h \
  Keyboard/KeyID.h \
  Keyboard/KeyPosition.h \
  Keyboard/KeyboardHandler.h \
  Keyboard/KeyboardListener.h \
  Keyboard/ListenerExceptionHandler.h \
  Keyboard/RawKeyEvent.h \
  Library/AnyObject/AnyMovable.h \
  Library/Observer/Impl/Observable.h \
  Library/Observer/Impl/ObservableImpl.h \
  Library/Observer/Impl/Observer.h \
  Library/Observer/Impl/Source.h \
  Library/Observer/Impl/TypeHelper.h \
  Library/Observer/Observer.h \
  Library/Singleton/AnyGlobalAccess.h \
  Library/StlExtension/ThreadDetachable.h \
  Library/AnyObject/AnyMovable.h \
  Library/Singleton/AnyGlobalAccess.h \
  Library/StlExtension/ThreadDetachable.h \
  Qt/AppState.h \
  Qt/AppStatus.h \
  Qt/MainWindow.h \
  Qt/QtLoopExceptionHandler.h \
  Application.h \
  ApplicationGUI.h \
  ApplicationGlobals.h \
  ApplicationImpl.h \
  ApplicationKernel.h \
  ExceptionHandler.h \
  KeyboardHandlerAccess.h \
  QtLoopException.h \
  TimeApp.h \
  Timer.h \
  TimerAccess.h

SOURCES += \
  AppStatusAccess.cpp \
  Interface/KeyboardShutter.cpp \
  Interface/SessionFlusher.cpp \
  Kernel/KeyEvent.cpp \
  Kernel/Seance.cpp \
  Kernel/SeanceMaker.cpp \
  Kernel/SeanceManager.cpp \
  Kernel/SeanceManagerImpl.cpp \
  Kernel/Session.cpp \
  Keyboard/KeyID.cpp \
  Keyboard/KeyboardHandler.cpp \
  Keyboard/KeyboardListener.cpp \
  Keyboard/ListenerExceptionHandler.cpp \
  Keyboard/RawKeyEvent.cpp \
  Qt/AppState.cpp \
  Qt/AppStatus.cpp \
  Qt/MainWindow.cpp \
  Qt/QtLoopExceptionHandler.cpp \
  Application.cpp \
  ApplicationGUI.cpp \
  ApplicationGlobals.cpp \
  ApplicationImpl.cpp \
  ApplicationKernel.cpp \
  ExceptionHandler.cpp \
  TimeApp.cpp \
  Timer.cpp \
  main.cpp

FORMS += \
  Qt/MainWindow.ui


win32 {
    HEADERS += \
    Keyboard/Windows/KeyboardListenerWin.h \
    Keyboard/Windows/MessageWindow.h \
    Keyboard/Windows/KeyIDWin.h \
    Keyboard/Windows/KeyMapper.h \
    Keyboard/Windows/KeyPositionWin.h \
    Keyboard/Windows/KeyShifters.h \
    Keyboard/Windows/KeyTextMaker.h \
    Keyboard/Windows/RawInputHook.h \
    Keyboard/Windows/RawInputReader.h \
    Keyboard/Windows/VkCode.h \
    Keyboard/Windows/WinKeyboardApi.h

    SOURCES += \
    Keyboard/Windows/KeyboardListenerWin.cpp \
    Keyboard/Windows/KeyIDWin.cpp \
    Keyboard/Windows/KeyMapper.cpp \
    Keyboard/Windows/KeyPositionWin.cpp \
    Keyboard/Windows/KeyShifters.cpp \
    Keyboard/Windows/KeyTextMaker.cpp \
    Keyboard/Windows/RawInputReader.cpp \
    Keyboard/Windows/VkCode.cpp \
    Keyboard/Windows/WinKeyboardApi.cpp
}

macx {
    HEADERS += \
    Keyboard/Macos/KeyboardListenerMac.h

    SOURCES += \
    Keyboard/Macos/KeyboardListenerMac.cpp
}

linux {
    HEADERS += \
    Keyboard/Linux/KeyboardListenerLin.h

    SOURCES += \
    Keyboard/Linux/KeyboardListenerLin.cpp
}

contains(DEFINES, KEYBOARD_HANDLER_DEBUG) {
    HEADERS += \
    AppDebug/KeyboardHandlerDebugGUI.h \
    AppDebug/KeyboardHandlerDebugOut.h
    SOURCES += \
    AppDebug/KeyboardHandlerDebugGUI.cpp \
    AppDebug/KeyboardHandlerDebugOut.cpp
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
