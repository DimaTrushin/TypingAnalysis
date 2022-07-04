#ifndef NSAPPLICATION_NSINTERFACE_CMODIFIERSMENU_H
#define NSAPPLICATION_NSINTERFACE_CMODIFIERSMENU_H

#include <QObject>

#include "Kernel/TextMode.h"

#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Library/StlExtension/Supressor.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSModifiersMenuDetail {

class CModifiersMenuImpl : public QObject {
  Q_OBJECT
  using CSupressor = NSLibrary::CSupressor;

  using EModifiersMode = NSKernel::EModifierMode;
  using CTextMode = NSKernel::CTextMode;
  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeInput = NSLibrary::CHotInput<CTextMode>;

  using CModifiersMode = NSKernel::CModifiersMode;
  using CModifiersModeObserver = NSLibrary::CObserver<CModifiersMode>;
  using CModifiersObservable = NSLibrary::CObservableData<CModifiersMode>;

public:
  struct CInitData {
    QMenu* Menu;
    QMenu* ShiftMenu;
    QMenu* CtrlMenu;
    QMenu* AltMenu;
  };
  explicit CModifiersMenuImpl(const CInitData& InitData);

  CTextModeObserver* modifersModeInput();
  void subscribeToModifiersMode(CModifiersModeObserver* obs);

public Q_SLOTS:
  void shiftNonToggled(bool checked);
  void shiftAllToggled(bool checked);
  void shiftEssentialToggled(bool checked);

  void ctrlNonToggled(bool checked);
  void ctrlAllToggled(bool checked);
  void ctrlEssentialToggled(bool checked);

  void altNonToggled(bool checked);
  void altAllToggled(bool checked);
  void altEssentialToggled(bool checked);

private:
  void connectShiftMenu();
  void connectCtrlMenu();
  void connectAltMenu();

  void handleModifiersMode(const CModifiersMode& Mode);
  void handleShiftMode(EModifiersMode Mode);
  void handleCtrlMode(EModifiersMode Mode);
  void handleAltMode(EModifiersMode Mode);

  EModifiersMode getShiftMode() const;
  EModifiersMode getCtrlMode() const;
  EModifiersMode getAltMode() const;
  EModifiersMode getMode(QMenu* Menu) const;

  QMenu* Menu_;
  QMenu* ShiftMenu_;
  QMenu* CtrlMenu_;
  QMenu* AltMenu_;

  CSupressor FromModel_;
  CSupressor MySignal_;

  CTextModeInput ModifiersInput_;
  CModifiersObservable ModifiersOutput_;
};

} // namespace NSModifiersMenuDetail

class CModifiersMenu : public NSLibrary::CViewWrapper<
                           NSModifiersMenuDetail::CModifiersMenuImpl> {
  using CBase =
      NSLibrary::CViewWrapper<NSModifiersMenuDetail::CModifiersMenuImpl>;
  using CModifiersMenuImpl = NSModifiersMenuDetail::CModifiersMenuImpl;

public:
  using CBase::CBase;
  using CInitData = CModifiersMenuImpl::CInitData;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CMODIFIERSMENU_H
