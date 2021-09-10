#include "Kernel/TextModule/TextModule.h"
#include "Library/Observer/Observer.h"

#include <memory>

namespace NSApplication {

namespace NSQt {
class CMainWindow;
}

namespace NSInterface {
class CTextModuleGUI;

namespace NSTextModuleOutDetail {
class CTextModuleOutImpl : public QObject {

  using CTextModuleImpl =
      NSApplication::NSKernel::NSTextModuleDetail::CTextModuleImpl;
  using CTextMode = NSApplication::NSKernel::NSTextModuleDetail::CTextMode;

  using CTextModeGetType = CTextModuleImpl::CTextModeGetType;
  using CTextModeObserver = CTextModuleImpl::CTextModeObserver;
  using CTextModeObservable = NSLibrary::CObservable<CTextMode>;

  using CQStringGetType = CTextModuleImpl::CQStringGetType;
  using CTextObserver = CTextModuleImpl::CQStringObserver;
  using CTextInput = NSLibrary::CObserverHot<QString>;

  using CMainWindow = NSApplication::NSQt::CMainWindow;

public:
  CTextModuleOutImpl(CMainWindow*);
  ~CTextModuleOutImpl();

  void subscribeToTextMode(CTextModeObserver*);

  CTextObserver* textInput();

private:
  void connectUI();
  void synchronizeTextMode();
  void updateTextMode();

  void setUpUI(CQStringGetType);
  void outputText(const QString&);
  void outputEmptyCase();

  QString getOutputText(const QString&);

  std::unique_ptr<CTextModuleGUI> ui_;

  CTextInput TextInput_;
  CTextModeObservable TextModeOutput_;

  CTextMode TextMode_;
};

} // namespace NSTextModuleOutDetail

namespace NSTextModuleOut {
class CTextModuleOut {
  using CMainWindow = NSApplication::NSQt::CMainWindow;
  using CTextModuleOutImpl = NSTextModuleOutDetail::CTextModuleOutImpl;

public:
  CTextModuleOut(CMainWindow*);
  CTextModuleOutImpl* operator->();

private:
  std::unique_ptr<CTextModuleOutImpl> Impl_;
};
} // namespace NSTextModuleOut

} // namespace NSInterface
} // namespace NSApplication
