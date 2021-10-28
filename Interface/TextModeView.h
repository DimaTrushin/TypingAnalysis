#ifndef NSAPPLICATION_NSINTERFACE_CTEXTMODEVIEW_H
#define NSAPPLICATION_NSINTERFACE_CTEXTMODEVIEW_H

#include <QObject>

#include <memory>

#include "Kernel/TextMode.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/Supressor.h"

QT_BEGIN_NAMESPACE
class QButtonGroup;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSTextModeViewDetail {

class CTextModeViewImpl : public QObject {
  Q_OBJECT

  using ETextMode = NSKernel::ETextMode;
  using EModifierMode = NSKernel::EModifierMode;

  using CTextMode = NSKernel::CTextMode;
  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeInput = NSLibrary::CHotInput<CTextMode>;
  using CTextModeObservable = NSLibrary::CObservableData<CTextMode>;

  using CSupressor = NSLibrary::CSupressor;

public:
  CTextModeViewImpl(QButtonGroup*, QButtonGroup*, QButtonGroup*, QButtonGroup*);

  CTextModeObserver* textModeInput();
  void subscribeToTextMode(CTextModeObserver*);

public slots:
  void TextButtonToggled(int id, bool checked);
  void ShiftButtonToggled(int id, bool checked);
  void CtrlButtonToggled(int id, bool checked);
  void AltButtonToggled(int id, bool checked);
  void handleTextModeSwitchByGui();

  void toggleTextButton(int id);
  void toggleShiftButton(int id);
  void toggleCtrlButton(int id);
  void toggleAltButton(int id);

  void toggleAllButtons(CTextMode);
  //  void ShiftButtonClicked(int);
  //  void CtrlButtonClicked(int);
  //  void AltButtonClicked(int);

private:
  static ETextMode getTextMode(int);
  static EModifierMode getModifierMod(int);
  static int getTextInt(ETextMode);
  static int getModifierInt(EModifierMode);

  void onTextModeInput();
  CTextMode getCurrentTextMode() const;

  QButtonGroup* TextButtonGroup_;
  QButtonGroup* ShiftButtonGroup_;
  QButtonGroup* CtrlButtonGroup_;
  QButtonGroup* AltButtonGroup_;

  CSupressor FromModel_;
  CSupressor MySignal_;

  CTextModeInput TextModeInput_;
  CTextModeObservable TextModeOutput_;
};
} // namespace NSTextModeViewDetail

class CTextModeView {
  using CTextModeViewImpl = NSTextModeViewDetail::CTextModeViewImpl;

public:
  CTextModeView(QButtonGroup*, QButtonGroup*, QButtonGroup*, QButtonGroup*);
  CTextModeViewImpl* operator->() const;

private:
  std::unique_ptr<CTextModeViewImpl> Impl_;
};

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTMODEVIEW_H
