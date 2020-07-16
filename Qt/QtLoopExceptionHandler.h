#ifndef NSAPPLICATION_NSQT_CQTLOOPEXCEPTIONHANDLER_H
#define NSAPPLICATION_NSQT_CQTLOOPEXCEPTIONHANDLER_H

#include <QObject>
#include <stdexcept>


namespace NSApplication {
namespace NSQt {

class CQtException : public std::runtime_error {
  using CBase = std::runtime_error;
  using CBase::CBase;
};


class CQtLoopExceptionHandler : public QObject {
  Q_OBJECT
public:
  CQtLoopExceptionHandler();
signals:
  void quit();
public slots:
  void handleException(const CQtException&);
};

} // NSQt
} // NSApplication

#endif // NSAPPLICATION_NSQT_CQTLOOPEXCEPTIONHANDLER_H
