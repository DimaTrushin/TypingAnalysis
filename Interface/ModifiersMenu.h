#ifndef NSAPPLICATION_NSINTERFACE_CMODIFIERSMENU_H
#define NSAPPLICATION_NSINTERFACE_CMODIFIERSMENU_H

#include <QObject>

#include "Kernel/TextMode.h"

#include "Library/Observer4/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Library/StlExtension/Supressor.h"
#include "Local/Localizer.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSModifiersMenuDetail {

class CModifiersMenuImpl : public QObject {
  Q_OBJECT
  using CSupressor = NSLibrary::CSupressor;
  using ETextMode = NSKernel::ETextMode;

  using EModifiersMode = NSKernel::EModifierMode;
  using CTextMode = NSKernel::CTextMode;
  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeInput = NSLibrary::CHotInput<CTextMode>;

  using CModifiersMode = NSKernel::CModifiersMode;
  using CModifiersModeObserver = NSLibrary::CObserver<CModifiersMode>;
  using CModifiersObservable = NSLibrary::CObservableData<CModifiersMode>;

  using CLocalizer = NSLocal::CTextModeViewLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

public:
  struct CInitData {
    QMenu* Menu;
    QMenu* ShiftMenu;
    QMenu* CtrlMenu;
    QMenu* AltMenu;
  };
  explicit CModifiersMenuImpl(const CInitData& InitData);
  ~CModifiersMenuImpl();

  CTextModeObserver* modifersModeInput();
  CLocalizerObserver* localizerInput();
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
  void adjustMenu();
  void adjustMenu(QMenu* menu, std::unique_ptr<QActionGroup>* Group);

  void connectShiftMenu();
  void connectCtrlMenu();
  void connectAltMenu();

  void onTextMode(const CTextMode& TextMode);
  void handleModifiersMode(const CModifiersMode& Mode);
  void handleShiftMode(EModifiersMode Mode);
  void handleCtrlMode(EModifiersMode Mode);
  void handleAltMode(EModifiersMode Mode);

  void setLocale(const CLocalizer& Localizer);
  void setShiftLocale(const CLocalizer& Localizer);
  void setCtrlLocale(const CLocalizer& Localizer);
  void setAltLocale(const CLocalizer& Localizer);
  void localizerMenuItems(const CLocalizer& Localizer, QMenu* Menu);

  EModifiersMode getShiftMode() const;
  EModifiersMode getCtrlMode() const;
  EModifiersMode getAltMode() const;
  static EModifiersMode getMode(QMenu* Menu);

  QMenu* Menu_;
  QMenu* ShiftMenu_;
  QMenu* CtrlMenu_;
  QMenu* AltMenu_;

  std::unique_ptr<QActionGroup> ShiftActions_;
  std::unique_ptr<QActionGroup> CtrlActions_;
  std::unique_ptr<QActionGroup> AltActions_;

  CSupressor FromModel_;
  CSupressor MySignal_;

  CTextModeInput ModifiersInput_;
  CModifiersObservable ModifiersOutput_;
  CLocalizerInput LocalizerInput_;
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
